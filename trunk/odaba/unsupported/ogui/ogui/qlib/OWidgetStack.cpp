/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OWidgetStack

\brief    


\date     $Date: 2006/08/01 20:10:37,92 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWidgetStack"

#include  <pogui7.h>
#include  <sDBStructDef.hpp>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sODTabControl.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOWidgetStack.hpp>


/******************************************************************************/
/**
\brief  ActivateODChildren - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  child - Child to be displayed within the control/window
\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateODChildren"

logical OWidgetStack :: ActivateODChildren (ODataWidget *child, PropertyHandle *prophdl )
{
  ODataWidget            *tab_child = NULL;
  ODControl              *od_child  = NULL;
  ODTabControl           *od_tab    = NULL;
  PropertyHandle          ph(prophdl);  // increase use count!!
  logical                 term      = NO;
  children.GoTop();
  while ( tab_child = children.GetNext() )
  {
    if ( od_tab = GetODTabControl() )
      od_child = od_tab->GetSubWindow(tab_child->get_display_level());
  
    if ( od_child )
      od_child->SetPropertyHandle(tab_child == child ? prophdl : NULL,NO);
    else 
      child->SetPropertyHandle(tab_child == child ? prophdl : NULL,NO);
  }
/* vorerst kümmern wir uns nur um das aktivierte child
  if ( od_tab = GetODTabControl() )
    od_child = od_tab->GetSubWindow(child->get_display_level());
  
  if ( od_child )
    od_child->SetPropertyHandle(prophdl,NO);
  else 
    child->SetPropertyHandle(prophdl,NO);
*/

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateODChildren"

logical OWidgetStack :: ActivateODChildren (char *typenames )
{
  ODataWidget            *child;
  char                   *struct_name;
  logical                 dsp_level = UNDEF;
BEGINSEQ
  if ( !(child = GetChild(typenames)) )              ERROR
    
  dsp_level = child->get_display_level();


RECOVER
  dsp_level = UNDEF;
ENDSEQ
  return(dsp_level);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  struct_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateODChildren"

logical OWidgetStack :: ActivateODChildren (DBStructDef *struct_def )
{
  DBStructDef            *strdef = NULL;
  char                    names[ID_SIZE+1];
  int32                   indx0  = 0;;
  logical                 dsp_level = UNDEF;
BEGINSEQ
  while ( strdef = struct_def->GetBaseStructure(indx0++) )
    if ( dsp_level = SetTypeLevel(gvtxbts(names,strdef->smcbname,ID_SIZE)) )          
                                                     LEAVESEQ

  indx0 = 0;
  while ( strdef = struct_def->GetBaseStructure(indx0++) )
    if ( dsp_level = SetTypeLevel(strdef) )          LEAVESEQ

ENDSEQ
  return(dsp_level);
}

/******************************************************************************/
/**
\brief  AddChild - Adds a ODataWidget into the Widgetstack at the given index

        Inserts  the Widget if it is not already  in the stack and makes sure it
        does not display during the operation

\return term - 

\param  child - Child to be displayed within the control/window
\param  tab_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddChild"

logical OWidgetStack :: AddChild (ODataWidget *child, int32 tab_index )
{
  QWidget                *qwidget = NULL;
  logical                 vstate = NO;
  logical                 term = NO;
BEGINSEQ
  if ( !child )                                     ERROR
  qwidget = child->WidgetQ();
  if ( indexOf(qwidget) >=0 )                       LEAVESEQ // already in stack
  qwidget->setParent(NULL);
  // hide if visible
  vstate = qwidget->isVisible();
 // if(vstate)
  qwidget->hide();
  
  insertWidget(tab_index,qwidget);
  child->set_display_level(tab_index+1);
  // unhide if was visible
  
  //if(vstate)
  //  qwidget->show();
  children.AddTail(child);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FrameQ - 



\return pQFrame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OWidgetStack :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetChild - 



\return pODataWidget - Parent data widget
-------------------------------------------------------------------------------
\brief  i00 - 



\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetChild"

ODataWidget *OWidgetStack :: GetChild (char *typenames )
{
  ODataWidget            *child;
  char                   *struct_name;
  logical                 dsp_level = UNDEF;
BEGINSEQ
  if ( !typenames )                                 ERROR

  children.GoTop();
  while ( child = children.GetNext() )
    if ( (struct_name = child->ods()->GetStructure()) && !strcmp(typenames,struct_name) )
      break;


RECOVER
  child = NULL;
ENDSEQ
  return(child);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetChild"

ODataWidget *OWidgetStack :: GetChild (int16 dsp_level )
{
  ODataWidget            *child = NULL;
  children.GoTop();
  while ( child = children.GetNext() )
    if ( child->get_display_level() == dsp_level )
      break;


  return(child);
}

/******************************************************************************/
/**
\brief  GetODTabControl - 



\return pODTabControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetODTabControl"

ODTabControl *OWidgetStack :: GetODTabControl ( )
{
  ODTabControl       *pODTabControl = NULL;
BEGINSEQ
  if ( !parent_odw || !parent_odw->get_od_control() )
                                                     ERROR
  pODTabControl = (ODTabControl *)parent_odw->get_od_control();
RECOVER
  pODTabControl = NULL;
ENDSEQ
  return(pODTabControl);
}

/******************************************************************************/
/**
\brief  OWidgetStack - Konstruktor



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWidgetStack"

     OWidgetStack :: OWidgetStack (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QStackedWidget (pODataWidget ? pODataWidget->WidgetQ() : NULL),
ODataWidget (pODataWidget,oODataWidget,create_ods),
  children()
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWidgetStack"

     OWidgetStack :: OWidgetStack (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS )
                     : QStackedWidget (pODataWidget ? pODataWidget->WidgetQ() : NULL),
ODataWidget (pODataWidget,oODataWidget,pODS),
  children()
{



}

/******************************************************************************/
/**
\brief  SetDisplayLevel - 



\return term - 

\param  tab_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical OWidgetStack :: SetDisplayLevel (int32 tab_index )
{
  QWidget                *qw;
  QWidget                *nqw;
  logical                 term = NO;
BEGINSEQ
  if ( tab_index < 0 || !(nqw = widget(tab_index)) )  ERROR
  setCurrentIndex(tab_index);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetTypeLevel - 



\return dsp_level - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTypeLevel"

int16 OWidgetStack :: SetTypeLevel (PropertyHandle *prophdl )
{
  ODataWidget            *child;
  char                   *struct_name;
  logical                 dsp_level = UNDEF;
BEGINSEQ
  if ( !prophdl )                                    ERROR
  if ( child = GetChild(prophdl->GetCurrentType()) )
    dsp_level = child->get_display_level();
  else
  {
    dsp_level = SetTypeLevel(prophdl->GetCurrentTypeDef());
    child = GetChild(dsp_level);
  }
  if ( !dsp_level )                                  ERROR

  ActivateODChildren(child,prophdl);

RECOVER
  dsp_level = UNDEF;
ENDSEQ
  return(dsp_level);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTypeLevel"

int16 OWidgetStack :: SetTypeLevel (char *typenames )
{
  ODataWidget            *child;
  char                   *struct_name;
  logical                 dsp_level = UNDEF;
BEGINSEQ
  if ( !(child = GetChild(typenames)) )              ERROR
    
  dsp_level = child->get_display_level();


RECOVER
  dsp_level = UNDEF;
ENDSEQ
  return(dsp_level);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  struct_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTypeLevel"

int16 OWidgetStack :: SetTypeLevel (DBStructDef *struct_def )
{
  DBStructDef            *strdef = NULL;
  char                    names[ID_SIZE+1];
  int32                   indx0  = 0;;
  logical                 dsp_level = UNDEF;
BEGINSEQ
  while ( strdef = struct_def->GetBaseStructure(indx0++) )
    if ( dsp_level = SetTypeLevel(gvtxbts(names,strdef->smcbname,ID_SIZE)) )          
                                                     LEAVESEQ

  indx0 = 0;
  while ( strdef = struct_def->GetBaseStructure(indx0++) )
    if ( dsp_level = SetTypeLevel(strdef) )          LEAVESEQ

ENDSEQ
  return(dsp_level);
}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return pQWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OWidgetStack :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  ~OWidgetStack - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OWidgetStack"

     OWidgetStack :: ~OWidgetStack ( )
{

  children.Clear();

}


