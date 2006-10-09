/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OSingleLineEdit

\brief    


\date     $Date: 2006/04/26 12:40:36,23 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSingleLineEdit"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOSingleLineEdit.h>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODSTree.hpp>
#include  <sODataWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOEHEvent.hpp>
#include  <sOPopupMenu.hpp>
#include  <sOSingleLineEdit.hpp>


/******************************************************************************/
/**
\brief  Activate

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OSingleLineEdit :: Activate ( )
{
  logical          ini  = stscini();
  logical          term = NO;
  OEHControlValue::ActivateValue(YES,NO);
  
  if ( !ini )
    connect(this,SIGNAL(textChanged(const QString &)),
            this,SLOT  (storeToValue()));      // Store intern
   
// connects fuer coll-events liefen bisher erst hier, jetzt schon oben
    

  return(term);
}

/******************************************************************************/
/**
\brief  ClearData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OSingleLineEdit :: ClearData ( )
{

  clear();
  


}

/******************************************************************************/
/**
\brief  Deactivate

\return term - 

\param  data_only
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OSingleLineEdit :: Deactivate (logical data_only )
{
  logical          ini  = stscini();

  if ( ini && !data_only )
    disconnect(this,SIGNAL(textChanged(const QString &)),
               this,SLOT  (storeToValue()));      // Store intern
  
  OEHControlValue::DeactivateValue(YES,NO,data_only);

  return(NO);
}

/******************************************************************************/
/**
\brief  FillData


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OSingleLineEdit :: FillData ( )
{

  ods()->ValueInit();
  setText(ods()->Value());
  
// bis 02/2005 war Layout mit mehreren Spalten unststuetzt  
//             s.a. initValue 



}

/******************************************************************************/
/**
\brief  GetTextPosition

\return position

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextPosition"

DPoint OSingleLineEdit :: GetTextPosition ( )
{
  DPoint         position(1,1);
  if ( hasFocus() )
    position.X = cursorPosition() + 1;
  return(position);
}

/******************************************************************************/
/**
\brief  Initialize

\return term - 

\param  pwd_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OSingleLineEdit :: Initialize (logical pwd_opt )
{
  logical                 term = NO;
  has_edit = YES;
  setDragEnabled(true);

  if ( pwd_opt ) 
    setEchoMode(QLineEdit::Password);
  return(term);
}

/******************************************************************************/
/**
\brief  OSingleLineEdit - 


-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods
\param  pwd_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSingleLineEdit"

                        OSingleLineEdit :: OSingleLineEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, logical pwd_opt )
                     : QLineEdit(pODataWidget ? pODataWidget->WidgetQ() : NULL ),
OEHControlValue(pODataWidget,oODataWidget,create_ods),
  rxMaskValidator(NULL),
  rxMask(NULL),
  ods_ref(NULL)

{

BEGINSEQ
  OGUICERR
  Initialize(pwd_opt);  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS
\param  pwd_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSingleLineEdit"

                        OSingleLineEdit :: OSingleLineEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical pwd_opt )
                     : QLineEdit(pODataWidget ? pODataWidget->WidgetQ() : NULL ),
OEHControlValue(pODataWidget,oODataWidget,pODS),
  rxMaskValidator(NULL),
  rxMask(NULL),
  ods_ref(NULL)
{

BEGINSEQ
  OGUICERR
  Initialize(pwd_opt);   

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02


\param  pQWidget
\param  oODataWidget - Owning data widget
\param  pODS
\param  pwd_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSingleLineEdit"

                        OSingleLineEdit :: OSingleLineEdit (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS, logical pwd_opt )
                     : QLineEdit(pQWidget),
OEHControlValue(oODataWidget,oODataWidget,pODS),
  rxMaskValidator(NULL),
  rxMask(NULL),
  ods_ref(NULL)
{
BEGINSEQ
  OGUICERR
  Initialize(pwd_opt);   

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  i03


\param  pQWidget
\param  oODataWidget - Owning data widget
\param  create_ods
\param  pwd_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSingleLineEdit"

                        OSingleLineEdit :: OSingleLineEdit (QWidget *pQWidget, ODataWidget *oODataWidget, logical create_ods, logical pwd_opt )
                     : QLineEdit(pQWidget),
OEHControlValue(NULL,oODataWidget,create_ods),
  rxMaskValidator(NULL),
  rxMask(NULL),
  ods_ref(NULL)
{
BEGINSEQ
  OGUICERR
  Initialize(pwd_opt);
RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  ProvideContextMenu - Bereitstellen eines ContextMenüs


\return term - 

\param  watched
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideContextMenu"

logical OSingleLineEdit :: ProvideContextMenu (QObject *watched )
{
  logical          is_read_only = IsReadOnly();
  logical          term         = NO;
BEGINSEQ
  if ( !context_menu )
  {
    if ( !event_handling )                           LEAVESEQ
    if ( !ods()->IsReference() )                     ERROR
      
    if ( !(context_menu = new OPopupMenu(this,this)) )
                                                     OGUIERR(95)
    context_menu->SetupActions(oeh()->FindAction(NULL,"___ContextMenu",NO));
  }
  
  oeh()->SetActionDisabled("SelectEntry",NULL,is_read_only);
  oeh()->SetActionDisabled("RemoveEntry",NULL,is_read_only);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaultReactions

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OSingleLineEdit :: SetDefaultReactions ( )
{
  logical                 term = NO;
  OEHDataWidget::SetDefaultReactions();
  
  SetGUIDefReaction(NULL,"___ContextMenu",NULL);
  
  SetGUIDefReaction("EditEntry"  ,NULL,"___ContextMenu");
  SetGUIDefReaction("SelectEntry",NULL,"___ContextMenu");
  SetGUIDefReaction("RemoveEntry",NULL,"___ContextMenu")->SetSeparated(YES);

  return(term);
}

/******************************************************************************/
/**
\brief  SetFlat

\return term - 

\param  toggle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFlat"

logical OSingleLineEdit :: SetFlat (bool toggle )
{
  logical                 term = NO;
   setFrame(!toggle);
  return(term);
}

/******************************************************************************/
/**
\brief  SetReadOnly


\param  fReadOnly
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReadOnly"

void OSingleLineEdit :: SetReadOnly (logical fReadOnly )
{

  setReadOnly(fReadOnly);


}

/******************************************************************************/
/**
\brief  SetTextPosition


\param  position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextPosition"

void OSingleLineEdit :: SetTextPosition (DPoint &position )
{

  setFocus();
  setCursorPosition(MAX(0,position.X-1));


}

/******************************************************************************/
/**
\brief  SetTextSelection

-------------------------------------------------------------------------------
\brief  i0


\param  start_pos
\param  length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextSelection"

void OSingleLineEdit :: SetTextSelection (int32 start_pos, int32 length )
{

  setFocus();
  setSelection(start_pos,length);

}

/******************************************************************************/
/**
\brief  i01


\param  start_point
\param  end_point
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextSelection"

void OSingleLineEdit :: SetTextSelection (DPoint start_point, DPoint end_point )
{
  setFocus();
  setSelection(MAX(0,start_point.X-1),
               MAX(0,end_point.X-start_point.X));
}

/******************************************************************************/
/**
\brief  UseDefaultHeight - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UseDefaultHeight"

logical OSingleLineEdit :: UseDefaultHeight ( )
{

  return(YES);
}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OSingleLineEdit :: WidgetQ ( )
{

  return(this);
}

/******************************************************************************/
/**
\brief  getEnabled

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEnabled"

logical OSingleLineEdit :: getEnabled ( )
{
  ODSItem         *oi = ods()->Item();
  logical          cond = NO;
  if ( oi )
    cond = oi->get_is_reference() 
           ? oi->ColIsValid(YES,YES)  
           : oi->ProvideItem() >= IST_selected;

  return(cond);
}

/******************************************************************************/
/**
\brief  initValue


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "initValue"

void OSingleLineEdit :: initValue ( )
{
  PropertyHandle   *ods_ph = ods()->Handle();
BEGINSEQ
// 4.3.2005 war SLOT fuer SIGNAL(OnActivated(logical)
// muss in Activate wieder aufgerufen werden, wenn wir die Anzeige bestimmter Columns zulassen ...
/*
  ods_ref = UNDEF;
    
  if ( event_handling && ods_ph->IsCollection() )
  {  
    if ( !olayout )                                    OGUIERR(99)
    if ( !olayout->get_columns() )
      olayout->AddColumn(NULL,NULL,NO,NULL,PT_Key);
  
    ODSPropPath  save_path(*olayout);
    olayout->SetPath(NULL,NULL,save_path.get_collection(),NULL,PT_Self);
    if ( ods_ref = new ODSTree(this,olayout) )
    {
      ods_ref->SetParentODS(ods());
      ods_ref->Activate();
    }
    olayout->SetPath(save_path);
  }
  
  loadValue();
*/
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  setMask - Enables Masking Singlelineedit
        To  ensure  a  specific  format  in  a  single  line you can set regular
        expressions to match against the content.
        don't forget to escape \ :)
        please inform the user about your regular expressions (use tooltips)

\return term - 

\param  szMask
\param  bCaseSensitive
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setMask"

logical OSingleLineEdit :: setMask (char *szMask, char bCaseSensitive )
{
  logical                 term = NO;
  if(!rxMaskValidator) rxMaskValidator = new QRegExpValidator(this);
  if(!rxMask) rxMask = new QRegExp(); 
  this->setValidator(rxMaskValidator);
  rxMask->setPattern(SZ2QS(szMask));
  rxMaskValidator->setRegExp(*rxMask);

  return(term);
}

/******************************************************************************/
/**
\brief  storeToValue


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "storeToValue"

void OSingleLineEdit :: storeToValue ( )
{

  StoreToValue(text());  



}

/******************************************************************************/
/**
\brief  updateSelection


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "updateSelection"

void OSingleLineEdit :: updateSelection ( )
{

// ggf müssen wir hier das PH einstellen (auf den Schlüsel im Edith)

}

/******************************************************************************/
/**
\brief  ~OSingleLineEdit - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSingleLineEdit"

                        OSingleLineEdit :: ~OSingleLineEdit ( )
{
  Deactivate(NO);
  
  delete ods_ref;
  ods_ref = NULL;
}


