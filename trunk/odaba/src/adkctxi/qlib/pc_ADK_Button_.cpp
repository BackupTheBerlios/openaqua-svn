/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    pc_ADK_Button_

\brief    Button functions


\date     $Date: 2006/04/21 17:46:07,21 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_Button_"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_Button_.hpp>


/******************************************************************************/
/**
\brief  SetupButton - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupButton"

logical pc_ADK_Button_ :: SetupButton ( )
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
\brief  pc_ADK_Button_ - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Button_"

                        pc_ADK_Button_ :: pc_ADK_Button_ (PropertyHandle *prophdl )
                     : pc_ADK_StyleElement_(prophdl)
{



}

/******************************************************************************/
/**
\brief  ~pc_ADK_Button_ - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pc_ADK_Button_"

                        pc_ADK_Button_ :: ~pc_ADK_Button_ ( )
{



}


