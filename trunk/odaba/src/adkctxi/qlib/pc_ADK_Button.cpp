/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    pc_ADK_Button

\brief    Button functions


\date     $Date: 2006/05/23 13:08:16,85 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_Button"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_Button.hpp>


/******************************************************************************/
/**
\brief  SetupButton

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupButton"

logical pc_ADK_Button :: SetupButton ( )
{
  PropertyHandle         *pbc   = GetParentProperty();
  char                   *names = NULL;
  logical                 term = NO;
  DBObjectHandle          dbo;
  names = strdup(GPH("sys_ident")->GetString());

  SetupFromParent();
  *GPH("auto_open") = YES;
  dbo = GetObjectHandle();
  PropertyHandle   buttons(dbo,"ADK_EventActionControl",PI_Read);  
  PropertyHandle   ph_default("_default");
  if ( buttons(*GPH("sys_ident")) || buttons.Get(ph_default) )
    GPH("button_control")->Add(buttons.ExtractKey());
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADK_Button


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Button"

     pc_ADK_Button :: pc_ADK_Button (PropertyHandle *prophdl )
                     : pc_ADK_StyleElement(prophdl)
{
}

/******************************************************************************/
/**
\brief  ~pc_ADK_Button


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pc_ADK_Button"

     pc_ADK_Button :: ~pc_ADK_Button ( )
{
}


