/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TActionHandler

\brief    


\date     $Date: 2006/08/01 18:37:14,28 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TActionHandler"

#include  <poadi.h>
#include  <ioadii.h>
#ifndef   GSRT_TAction_HPP
#define   GSRT_TAction_HPP
#include  <sTAction.hpp>
#include  <sGSRT.h>
#endif
#include  <sCTX_Control.hpp>
#include  <sDKey.hpp>
#include  <sOCAU_Action.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHActionHandler.hpp>
#include  <sTProjectManager.hpp>
#include  <igvts.h>
#include  <iigui.h>
#include  <sTActionHandler.hpp>


/******************************************************************************/
/**
\brief  CloseControl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseControl"

logical TActionHandler :: CloseControl ( )
{
  TWidgetControl         *tcontrol;
  logical                 term = NO;
BEGINSEQ
  if ( !context )                                    ERROR

  if ( (tcontrol = context->get_control()) && !tcontrol->IsDeleting() )
    delete tcontrol;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteAction - 



\return executed - How was function exetuted

\param  act_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

int8 TActionHandler :: ExecuteAction (char *act_names )
{
  TAction        *action;
  char            act_name[TACTION_KEYLEN];
  short           indx     = 0;
  char            executed = AUTO;
BEGINSEQ
  gvtxstb(act_name,act_names,sizeof(act_name));
  
  if ( !actions ||
       (indx = actions->FindEntry(act_name)) <= 0 )  
  {
    if ( !context ||
         TProjectManager::TPM->get_std_actions()
                      ->FindEntry(act_name) <= 0 )   LEAVESEQ
    
    if ( (executed = context->ExecuteFunction(act_names,NO)) != AUTO )
                                                     LEAVESEQ
    executed = ExecuteDefaultAction(act_names);
  }
  else
  {
    action   = actions->GetEntry(indx);
    executed = action->Execute(context);
  }

ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteDBEventAction - 



\return rc - 

\param  ogui_db_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDBEventAction"

int32 TActionHandler :: ExecuteDBEventAction (ADK_DBEVENT ogui_db_event )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteDataEventAction - 



\return rc - 

\param  ogui_data_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDataEventAction"

int32 TActionHandler :: ExecuteDataEventAction (ADK_DATAEVENT ogui_data_event )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteDefaultAction - 



\return executed - How was function exetuted

\param  act_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteDefaultAction"

char TActionHandler :: ExecuteDefaultAction (char *act_names )
{
  char                 executed = AUTO;
BEGINSEQ
// action list
  static char    *actions[] = { "Exit",                 // 1
                                "ForceClose",           // 2
                                "EditEntry",            // 3
                                "CreateDocument",       // 4
                                "LoadDynamicControl",   // 5
                                };
  switch ( STRToPosition(act_names,sizeof(actions)/sizeof(actions[0]),actions) )
  {
    case 1  : executed = ::Quit();
              break;
    case 2  : executed = CloseControl();
              break;
    case 3  : executed = ::ExecuteAction(act_names,ACT_Window,context);
              break;
    case 4  : // not yet supported
              // break;
    case 5  : executed = LoadDynamicControl();
              break;
    default : ERROR
  }
 

RECOVER
  executed = AUTO;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteGUIEventAction - 



\return rc - 

\param  ogui_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteGUIEventAction"

int32 TActionHandler :: ExecuteGUIEventAction (ADK_GUIEVENT ogui_event )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  LoadDynamicControl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadDynamicControl"

logical TActionHandler :: LoadDynamicControl ( )
{
  TWidgetControl         *tcontrol;
  char                   *control_name;
  logical                 term = NO;
BEGINSEQ
  if ( !context )                                    ERROR
  
  if ( !(tcontrol = context->get_control()) )        ERROR
    
  if ( control_name = GetSysVariable("DYNLOAD_CONTROL") ) 
    if ( !*control_name )
      control_name = NULL;
    
  if ( tcontrol->LoadDynamicControl(GetSysVariable("DYNLOAD_CLASS"),control_name) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProcessKeyEvent - Process key event

        This  functions provides a feature for  handling general key events. The
        function  is  calling  the  KeyEvent()  kontext  function,  which can be
        overloaded  for  handling  general  key events. The function returns the
        result  from  the  KeyEvent()  function  or  AUTO,  when  no  KeyEvent()
        function has been implemented.
        (

\return executed - How was function exetuted

\param  dkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessKeyEvent"

int32 TActionHandler :: ProcessKeyEvent (DKey dkey )
{

  return ( context ? context->KeyEvent(dkey) : AUTO );

}

/******************************************************************************/
/**
\brief  SetAction - 



\return term - 

\param  act_names - 
\param  pOCAU_Action - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAction"

logical TActionHandler :: SetAction (char *act_names, OCAU_Action *pOCAU_Action )
{
  TAction        new_act(act_names,pOCAU_Action);
  TAction       *tact;
  short          indx;
  logical        term = NO;
BEGINSEQ
  if ( !actions )
  {
    
    if ( !(actions = new GSRT(TAction)(10,sizeof(TAction),TACTION_KEYLEN,1,'C',YES)) )
                                                     OADIERR(95)
  }
  else
    if ( (indx = actions->FindEntry(new_act.get_sys_ident())) > 0 )
    {
      OADIEV1(act_names,0)
      tact = actions->GetEntry(indx);
      if ( !pOCAU_Action )                           OADIERR(11)
      if ( *tact->get_action() == *pOCAU_Action )    LEAVESEQ
      else                                           OADIERR(11)
    }
  
  actions->AddEntry(&new_act);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetContext - 




\param  ctx_ctl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContext"

void TActionHandler :: SetContext (CTX_Control *ctx_ctl )
{

  context = ctx_ctl;

}

/******************************************************************************/
/**
\brief  TActionHandler - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TActionHandler"

     TActionHandler :: TActionHandler ( )
                     : OEHActionHandler (),
  actions(NULL)
{



}

/******************************************************************************/
/**
\brief  ~TActionHandler - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TActionHandler"

     TActionHandler :: ~TActionHandler ( )
{

  delete actions;
  actions = NULL;

}


