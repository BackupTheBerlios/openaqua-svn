/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OPushButton

\brief    Push button
          The  push  button  is  a  button  associated  with an action, which is
          called, when clicking the button.

\date     $Date: 2006/03/13 21:36:09,95 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPushButton"

#include  <pogui7.h>
#include  <mOPushButton.h>
#include  <sODataWidget.hpp>
#include  <sOEH.hpp>
#include  <sOEHAction.hpp>
#include  <sOIconSet.hpp>
#include  <sOPushButton.hpp>


/******************************************************************************/
/**
\brief  Activate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OPushButton :: Activate ( )
{
  QIcon         *pQIcon = NULL;
  logical        term   = NO;
  SetupFont();
  
  if ( pQIcon = olayout->GetIcon() )
    setIcon(*pQIcon);
  return(term);
}

/******************************************************************************/
/**
\brief  Deactivate - 


\return term -

\param  data_only -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OPushButton :: Deactivate (logical data_only )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  OPushButton - Constructor



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  toggle_state -
\param  default_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPushButton"

                        OPushButton :: OPushButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, int8 toggle_state, logical default_opt )
                     : QPushButton(pODataWidget ? pODataWidget->WidgetQ() : NULL),
ODataWidget(pODataWidget,oODataWidget,NO)
{

  OGUIRESET
  ///TODO: check this
  ///  setToggleButton(toggle_state > 1 ? TRUE : FALSE);
  setCheckable(toggle_state>1);
  setDefault(default_opt);
  
  connect(this,SIGNAL(clicked()),this,SLOT(doClicked()));  // qt3: oeh()::doClicked()


}

/******************************************************************************/
/**
\brief  SetStandardAction - Set standard action for push button
        The  function sets the standard action  for a GUI element (data widget).
        The  function  is  used  to  set standard actions for a button, which is
        called,  when the button  is clicked. You  may push a standard action by
        setting  a new standard action for  the button. Disconnecting the action
        from the button will reactivate the previous action.

\return term -

\param  act_namesc - Action name
\param  loid - Identification for an action object
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStandardAction"

logical OPushButton :: SetStandardAction (const char *act_namesc, char *loid )
{
  OEHAction     *action;
  logical        term = NO;
BEGINSEQ
  if ( !(action = SetAction(act_namesc,loid,GEV_Click,this)) )
                                                     ERROR
  addAction(action->get_qaction());
RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return pQWidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OPushButton :: WidgetQ ( )
{

  return ( this );

}

/******************************************************************************/
/**
\brief  doClicked - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doClicked"

logical OPushButton :: doClicked ( )
{

  return ( actions().isEmpty() ? YES : oeh()->ExecuteReaction(actions().first()) );

}


