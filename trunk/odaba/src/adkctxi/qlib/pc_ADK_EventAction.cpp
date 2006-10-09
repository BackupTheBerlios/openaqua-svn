/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_EventAction



\date     $Date: 2006/05/23 13:10:41,54 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_EventAction"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_Allign.hpp>
#include  <spc_ADK_EventAction.hpp>


/******************************************************************************/
/**
\brief  Setup

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical pc_ADK_EventAction :: Setup ( )
{
  char                   *names = NULL;
  logical                 term = NO;
  names = strdup(GPH("sys_ident")->GetString());
  PropertyHandle *pphAllign = GPH("allign");
  pc_ADK_Allign(pphAllign).Setup(NO,NO);
  *GPH("auto_open") = YES;
  
  PropertyHandle   actions(GetObjectHandle(),"ADK_EventActionControl",PI_Read);  
  PropertyHandle ph_default("_default");
  if ( actions(*GPH("sys_ident")) || actions.Get(ph_default) )
    GPH("action_control")->Add(actions.ExtractKey());
  else
  {
    *GPH("default_action.action_type") = "ACT_Function";
    
    *names = toupper(*names);
    STRExchange(names,"_"," ",UNDEF);
    *GPH("text_definitions.title") = names;
    
  }
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADK_EventAction


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_EventAction"

     pc_ADK_EventAction :: pc_ADK_EventAction (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{
}


