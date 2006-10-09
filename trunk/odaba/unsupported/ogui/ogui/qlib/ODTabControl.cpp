/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODTabControl

\brief    Tab Control
          Tab  Controls  are  complex  windows, which are displayed on different
          levels.  Each tab  in a  tab controls  has its own window area to draw
          the elements assigned to the tab control. 
          Adding  field controls, which  are not windows,  to a tab control will
          create  static  controls  which  are  displayed  independently  on the
          selected tab. 
          New  tabs  can  be  creates  with  the  CreateSubWindow  function. The
          function  should be calles  after creating all  static elements in the
          tab  control.  The  function  determins  the  free area below the last
          static  control or  tries to  locate the  window according to size and
          position as defined for window.

\date     $Date: 2006/07/18 18:58:22,06 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODTabControl"

#include  <pogui7.h>
#include  <sODControl.hpp>
#include  <sODControlList.hpp>
#include  <sODTabControl.hpp>
#include  <sODWindow.hpp>
#include  <sODataWidget.hpp>
#include  <sOTab.hpp>
#include  <sOWidgetStack.hpp>
#include  <sODTabControl.hpp>


/******************************************************************************/
/**
\brief  ActivateElements - 



\return term - 

\param  act_curent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateElements"

logical ODTabControl :: ActivateElements (logical act_curent )
{
  OTab      *tab = (OTab *)controlWidget;
  ODControl *odc = NULL;
  logical    term = NO;
  if ( !tab->get_dynamic() )                         
    term = ODControl::ActivateElements(act_curent);
  else if ( odc = GetActiveControl() )
    term = odc->ActivateElements(act_curent);

  return(term);
}

/******************************************************************************/
/**
\brief  CreateLayout - 




\param  grid_size - 
\param  dmargin - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateLayout"

void ODTabControl :: CreateLayout (DSize &grid_size, DMargin &dmargin )
{



}

/******************************************************************************/
/**
\brief  CreateSubWindow - Create new tab-window

        New  tabs can be creates with the CreateSubWindow function. The function
        should  be calles after creating all static elements in the tab control.
        The  function determins the  free area below  the last static control or
        tries  to locate  the window  according to  size and position as defined
        for window.

\return pODWindow - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubWindow"

ODWindow *ODTabControl :: CreateSubWindow (char *names )
{
  OTab            *tc = (OTab *)controlWidget;
  ODWindow        *pODWindow = NULL;
  pODWindow = ODControl::CreateSubWindow(names);


  return(pODWindow);
}

/******************************************************************************/
/**
\brief  CreateTab - Set tab-Text



\return term - 

\param  pODControl - 
\param  label_text - Label text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTab"

logical ODTabControl :: CreateTab (ODControl *pODControl, char *label_text )
{
  OTab        *tc = (OTab *)controlWidget;

  pODControl->ODataWidget::SetDisplayLevel(
    tc->AddElement(pODControl->WidgetFrame(),SZ2QS(label_text),
                   pODControl->get_display_level())            );

  return(NO);
}

/******************************************************************************/
/**
\brief  GetActiveControl - 



\return pODControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveControl"

ODControl *ODTabControl :: GetActiveControl ( )
{

  return( GetSubWindow(display_level) );

}

/******************************************************************************/
/**
\brief  GetSubWindow - 



\return pODControl - 

\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSubWindow"

ODControl *ODTabControl :: GetSubWindow (int16 dsp_level )
{
  ODControl        *pODControl = NULL;
BEGINSEQ
  if ( !controls )                                   ERROR
    
  controls->GoTop();
  while ( pODControl = controls->GetNext() )
    if ( pODControl->get_display_level() == dsp_level )
      break;
RECOVER
  pODControl = NULL;
ENDSEQ
 return(pODControl);
}

/******************************************************************************/
/**
\brief  GetTabControl - 



\return pODTabControl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTabControl"

ODTabControl *ODTabControl :: GetTabControl ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  ODTabControl - Constructor




\param  pODControl - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODTabControl"

     ODTabControl :: ODTabControl (ODControl *pODControl, char *names )
                     : ODControl (pODControl,pODControl,YES,names)
{

  enableEventHandling(NO);

}

/******************************************************************************/
/**
\brief  PanelWidgetParent - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PanelWidgetParent"

ODataWidget *ODTabControl :: PanelWidgetParent ( )
{
  OTab        *tc = (OTab *)controlWidget;

  return(tc ? tc->Panels() : NULL);
}

/******************************************************************************/
/**
\brief  SetTabText - 




\param  label_text - Label text
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTabText"

void ODTabControl :: SetTabText (char *label_text, int16 dsp_level )
{
  OTab                   *tc = (OTab *)controlWidget;

  tc->SetTabText(label_text,dsp_level);

}

/******************************************************************************/
/**
\brief  UpdateLayout - 




\param  position - 
\param  inner_dist - 
\param  outer_dist - 
\param  dsize - 
\param  frame_size - 
\param  dalign - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateLayout"

void ODTabControl :: UpdateLayout (DPoint &position, int16 inner_dist, int16 outer_dist, DSize &dsize, DSize &frame_size, DAlign &dalign, int16 dsp_level )
{
  OTab            *tc = (OTab *)controlWidget;

  grid_control = 4; // tab layout
  
  ODControl::UpdateLayout(position,inner_dist,outer_dist,dsize,frame_size,
                          dalign,dsp_level);

  if ( tc )
    tc->UpdateLayout();



}

/******************************************************************************/
/**
\brief  ~ODTabControl - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODTabControl"

     ODTabControl :: ~ODTabControl ( )
{



}


