/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODragAndDrop

\brief    ODragAndDrop enables Objects to handle Drag and drop
          Encapsulates QT DnD events to simple functions

\date     $Date: 2006/07/03 05:01:40,21 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODragAndDrop"

#include  <pogui7.h>
#include  <cDragAndDropActions.h>
#include  <cDragAndDropTypes.h>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODragObject.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sPropertyHandle.hpp>
#include  <sODragAndDrop.hpp>


/******************************************************************************/
/**
\brief  GetNewKey - 


\return string - Character string

\param  ph - 
\param  text1 - 
\param  text2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewKey"

char *ODragAndDrop :: GetNewKey (PropertyHandle *ph, char *text1, char *text2 )
{
  static  char       keyarea[513];
  char              *string;
  *keyarea = 0;
  if ( string = GetString(text1,text2,"",oeh_widget) )
  {
    if ( ph && ph->IsValid() )
    {
      if ( string = ph->StringToKey(string).GetData() )
        memcpy(keyarea,string,ph->GetSortKeyLength());
    }
    else
      strcpy(keyarea,string);
  }
  return( *keyarea ? keyarea : NULL) ;
}

/******************************************************************************/
/**
\brief  IsLocalDrop - 


\return cond - 

\param  pQWidget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocalDrop"

logical ODragAndDrop :: IsLocalDrop (QWidget *pQWidget )
{

  return ( pQDropSource == pQWidget ? YES : NO);

}

/******************************************************************************/
/**
\brief  ODragAndDrop - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODragAndDrop"

     ODragAndDrop :: ODragAndDrop ( )
                     :   oeh_widget(NULL),
  decoded_dbhandle(NULL),
  decoded_dictionaryhandle(NULL),
  decoded_propertyhandle(NULL),
  decoded_text(),
  drop_action(Qt::IgnoreAction),
  drop_islocal(YES),
  drop_index(AUTO),
  drop_point(),
  pQDropSource(NULL),
  drop_type(0),
  qtDropStart(),
  drop_event(NULL)
{



}

/******************************************************************************/
/**
\brief  UpdateDropType - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateDropType"

logical ODragAndDrop :: UpdateDropType ( )
{
  logical                 term = NO;
  drop_type = DDT_undefined;
  if(decoded_text.indexOf(SZ2QS("\n"))>=0)
    drop_type = drop_type | DDT_MultibleItems;
  else
    drop_type = drop_type | DDT_SingleItem;
  if(!decoded_propertyhandle)
    drop_type = drop_type | DDT_External;

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_allow - 


\return allow - 

\param  pphTarget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_allow"

int ODragAndDrop :: dnd_allow (PropertyHandle *pphTarget )
{
  int      allow = DNDA_undefined;
BEGINSEQ
  if(!dnd_test(pphTarget,decoded_propertyhandle))                 ERROR
  /* detect by globalid */
  if ( pphTarget->GetGlobalID(decoded_propertyhandle->ExtractKey()) )
    allow = DNDA_CopyA|DNDA_Link;
  else
    allow = DNDA_CopyB;
  if( !decoded_propertyhandle->IsReadOnly())
    allow = allow | (allow&DNDA_CopyA?DNDA_MoveA:DNDA_MoveB);

RECOVER
  allow = DNDA_undefined;
ENDSEQ
  return(allow);
}

/******************************************************************************/
/**
\brief  dnd_can_decode - 


\return cond - 

\param  pQMimeData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_can_decode"

logical ODragAndDrop :: dnd_can_decode (const QMimeData *pQMimeData )
{
  logical            cond = NO;
  if(pQMimeData->hasFormat("application/vnd.odaba.propertyhandle"))
    cond |= YES;
  if(pQMimeData->hasFormat("text/xml"))
    cond |= YES;
  if(pQMimeData->hasFormat("text/plain"))
    cond |= YES;
  if(pQMimeData->hasFormat("application/x-qabstractitemmodeldatalist"))
    cond |= YES;


  return(cond);
}

/******************************************************************************/
/**
\brief  dnd_copy - 


\return term - 

\param  pphTarget - 
\param  pphSource - 
\param  iPos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_copy"

logical ODragAndDrop :: dnd_copy (PropertyHandle *pphTarget, PropertyHandle *pphSource, int iPos )
{
  char                   *new_name = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !dnd_test(pphTarget,pphSource) )              ERROR
  
  if ( pphTarget->GetSortKeySMCB() &&
       ( pphTarget->GetID(pphSource->ExtractKey()) || 
         pphTarget->GetGlobalID(pphSource->ExtractKey()) ) )
  {
    new_name = GetNewKey(pphTarget,"Copy Instance","Enter new key value");
    if ( !new_name || !*new_name )                   ERROR
  }
  
  if ( !pphTarget->Copy(*pphSource,new_name,iPos,REPL_local) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drag_init - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drag_init"

logical ODragAndDrop :: dnd_drag_init ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop - 
        handles  the  drop  event.  drop_point  can be used to identify the drop
        position.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop"

logical ODragAndDrop :: dnd_drop ( )
{
  logical                 term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop_end - 
        stops  dragging. used to clean up after  a drop or if the drag continued
        off the item

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_end"

logical ODragAndDrop :: dnd_drop_end ( )
{
  logical                 term = YES;
  drop_index = AUTO;
  //delete decoded_propertyhandle;
  if ( decoded_dictionaryhandle )//drop from other application
  { 
    delete decoded_dictionaryhandle;
    delete decoded_propertyhandle;
    delete decoded_dbhandle;
  }
  
  decoded_propertyhandle = NULL;
  decoded_dbhandle=NULL;
  decoded_dictionaryhandle = NULL; 
  
  decoded_text        = QString();

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop_init - 
        initializes the drag, uses decoded data in decoded_text and
        decoded_propertyhandle
        at the viewportpoint
        drag_init_point
        "

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_init"

logical ODragAndDrop :: dnd_drop_init ( )
{
  logical                 term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop_move - 
        updates  the  drag  while  it  moves  over a control. this is useful for
        controls  containing  more  than  a  single dataitem. drag_move_point is
        provided for identification of the items

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_move"

logical ODragAndDrop :: dnd_drop_move ( )
{
  logical                 term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  dnd_drop_propertyhandle - 


\return term - 

\param  pPropertyHandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_drop_propertyhandle"

logical ODragAndDrop :: dnd_drop_propertyhandle (PropertyHandle *pPropertyHandle )
{
  PropertyHandle  *sph  = NULL;
  PropertyHandle  *tph  = NULL;
  logical          term = NO;
  QString          sfrom, sto;

BEGINSEQ
  if ( !(sph = decoded_propertyhandle) ||
       !(tph = pPropertyHandle)            )         ERROR

  sph->StartRTA();
  
  switch(drop_action)
  {
    case Qt::LinkAction: term = dnd_link(tph,sph,drop_index);
                         break;
    case Qt::CopyAction: term = dnd_copy(tph,sph,drop_index);
                         break;
    case Qt::MoveAction: term = dnd_move(tph,sph,drop_index);
                         break;
    default: break;
  }
  
  sph->StopRTA(YES);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dnd_link - 


\return term - 

\param  pphTarget - 
\param  pphSource - 
\param  iPos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_link"

logical ODragAndDrop :: dnd_link (PropertyHandle *pphTarget, PropertyHandle *pphSource, int iPos )
{
  logical                 term = NO;
BEGINSEQ
  if ( !dnd_test(pphTarget,pphSource) )              ERROR
    
  if ( pphTarget->GetGlobalID(pphSource->ExtractKey()) &&      
       pphTarget->GetSortKeySMCB() )
    term = pphTarget->Copy(*pphSource,iPos,REPL_local);
  else
    term = dnd_copy(pphTarget,pphSource,iPos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dnd_move - 


\return term - 

\param  pphTarget - 
\param  pphSource - 
\param  iPos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_move"

logical ODragAndDrop :: dnd_move (PropertyHandle *pphTarget, PropertyHandle *pphSource, int iPos )
{
  char                   *new_name = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !dnd_test(pphTarget,pphSource) )              ERROR
    
  if ( pphTarget->GetSortKeySMCB() &&
       ( pphTarget->GetID(pphSource->ExtractKey()) || 
         pphTarget->GetGlobalID(pphSource->ExtractKey()) ) )
  {
    new_name = GetNewKey(pphSource,"Move Instance","Enter new key value");
    if ( !new_name || !*new_name )                   ERROR
    if ( !pphTarget->Copy(*pphSource,new_name,iPos,REPL_local) )
                                                     ERROR
    if ( strcmp(pphSource->GetType(),"VOID") )
      pphSource->Delete();
  }
  else
  {
    if ( iPos>=0 )
      pphTarget->Get(iPos);
    else
      pphTarget->ToTop();
    if ( !pphTarget->Move(*pphSource,REPL_local) )   ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dnd_test - 


\return term - 

\param  pphTarget - 
\param  pphSource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dnd_test"

logical __cdecl ODragAndDrop :: dnd_test (PropertyHandle *pphTarget, PropertyHandle *pphSource )
{

BEGINSEQ
  return ( pphSource->ExtractKey() && pphTarget ? YES : NO );                                     ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  dragEnterEvent - 
        This  event handler is called  when a drag is  in progress and the mouse
        enters this widget.
        calls dnd_drag_init

\return term - 

\param  pQDragEnterEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dragEnterEvent"

logical ODragAndDrop :: dragEnterEvent (QDragEnterEvent *pQDragEnterEvent )
{
  QMimeData       *mime = NULL;
  logical          term = YES;
BEGINSEQ
  ODragAndDrop::dnd_drop_end();
  qtDropStart = QTime::currentTime ();

  pQDropSource = NULL;
  if ( !pQDragEnterEvent )                           ERROR
  if ( ! (mime = (QMimeData*) pQDragEnterEvent->mimeData() ))      ERROR
  if ( !dnd_can_decode(mime) ) {
    pQDragEnterEvent->ignore();
    LEAVESEQ
  }
  // unfold well known formats for better dnd preview
  if ( mime->hasFormat("application/vnd.odaba.propertyhandle") )
  {
    ODragObject::decode(mime,&decoded_propertyhandle,&decoded_dbhandle,&decoded_dictionaryhandle);
    ODragObject::decode(mime,decoded_text);
  }
  if ( pQDragEnterEvent->provides("text/plain") )
  {
    ODragObject::decode(mime,decoded_text);
  } 
  UpdateDropType();
 
  //060502 opt member drop_init_point = pQDragEnterEvent->pos();
  drop_islocal = (pQDragEnterEvent->source())?YES:NO;
  if ( dnd_drop_init() )
    pQDragEnterEvent->accept();
  else
    pQDragEnterEvent->ignore();

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dragEvent - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dragEvent"

logical ODragAndDrop :: dragEvent ( )
{
  logical          term = YES;
BEGINSEQ
  if ( oeh_widget )
    if ( oeh_widget->GenerateEvent(GEV_BeginDrag) == YES )  
                                                     LEAVESEQ
  if ( !dnd_drag_init() )                            ERROR

  if ( oeh_widget )
    oeh_widget->GenerateEvent(GEV_EndDrag); // das ist die falsche stelle

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dragLeaveEvent - 
        This  event handler is called  when a drag is  in progress and the mouse
        leaves this widget.
        calls dnd_drag_end

\return term - 

\param  pQDragLeaveEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dragLeaveEvent"

logical ODragAndDrop :: dragLeaveEvent (QDragLeaveEvent *pQDragLeaveEvent )
{
  logical          term = YES;
  pQDropSource = ((QDropEvent*)pQDragLeaveEvent)->source ();
  dnd_drop_end();
  return(term);
}

/******************************************************************************/
/**
\brief  dragMoveEvent - 
        This  event handler is called  when a drag is  in progress and the mouse
        enters this widget, and whenever it moves within the widget.
        calls dnd_drag_move

\return term - 

\param  pQDragMoveEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dragMoveEvent"

logical ODragAndDrop :: dragMoveEvent (QDragMoveEvent *pQDragMoveEvent )
{
  logical          term = YES;
BEGINSEQ
  if ( qtDropStart.msecsTo(QTime::currentTime()) < 500) // prevent drops by accident
                                                     ERROR

  if(!pQDragMoveEvent)                               ERROR
  /* if you need this data export it somehow
  if(drop_move_point  == pQDragMoveEvent->pos())     LEAVESEQ
  drop_move_point  = pQDragMoveEvent->pos();
  drop_move_action = pQDragMoveEvent->dropAction();
  */
  if(dnd_drop_move())
    pQDragMoveEvent->accept();

RECOVER
  pQDragMoveEvent->ignore();
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dragObject - 


\return pQDrag - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dragObject"

QDrag *ODragAndDrop :: dragObject ( )
{
  ODragObject                *pODragObject = NULL;

//  pODragObject = new ODragObject(qwidget,"dragObject");
  return(pODragObject);
}

/******************************************************************************/
/**
\brief  dropEvent - 
        This event handler is called when the drag is dropped on this widget.
        calls dnd_drop,dnd_drag_end

\return term - 

\param  pQDropEvent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dropEvent"

logical ODragAndDrop :: dropEvent (QDropEvent *pQDropEvent )
{
  logical          term = YES;
BEGINSEQ
//  if ( qtDropStart.msecsTo(QTime::currentTime()) < 500) // prevent drops by accident
//                                                     ERROR
  
  if ( !pQDropEvent )                                LEAVESEQ
  drop_action  = pQDropEvent->dropAction();
  drop_point   = pQDropEvent->pos();
  pQDropSource = pQDropEvent->source ();
  drop_event   = pQDropEvent;
  drop_index   = AUTO;  //external information
  if ( oeh_widget )
    if ( oeh_widget->GenerateEvent(GEV_BeginDrop) == YES ) 
                                                     LEAVESEQ
  if ( dnd_drop() )                                  ERROR
  pQDropEvent->accept();
  if ( oeh_widget )
    oeh_widget->GenerateEvent(GEV_EndDrop);
  drop_event   = NULL;
RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  xxdnd_drop_pos_after - relative to rect
        returns true if the drop pos is on the lower half of the rect.

\return cond - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  point - 
\param  rcQRect - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxdnd_drop_pos_after"

logical ODragAndDrop :: xxdnd_drop_pos_after (DPoint point, const QRect &rcQRect )
{
  logical                 cond = NO;
/*  
  cond =    point.Y >  rcQRect.top()+rcQRect.height()/2
         && point.Y <= rcQRect.top()+rcQRect.height();
*/
  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  rcQRect - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxdnd_drop_pos_after"

logical ODragAndDrop :: xxdnd_drop_pos_after (const QRect &rcQRect )
{

/*
  return dnd_drop_pos_after ( DPoint(drop_point.x(),drop_point.y())
                            , rcQRect 
                            );
*/
return(NO);

}


