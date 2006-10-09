/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    sADK_EventAction

\brief    


\date     $Date: 2006/03/30 21:25:26,43 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sADK_EventAction"

#include  <padkctxi.h>
#include  <spc_ADK_KeyEvent.hpp>
#include  <ssADK_EventAction.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sADK_EventAction :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sADK_EventAction();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreated - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical sADK_EventAction :: DBCreated ( )
{
  PropertyHandle         *ph = GetPropertyHandle();
  logical                 term = NO;
  *ph->GPH("default_action.sys_ident") = *ph->GPH("sys_ident");
  return(term);
}

/******************************************************************************/
/**
\brief  DBRead - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sADK_EventAction :: DBRead ( )
{

  return(SetKeyString());

}

/******************************************************************************/
/**
\brief  DBStored

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBStored"

logical sADK_EventAction :: DBStored ( )
{

  return(SetKeyString());

}

/******************************************************************************/
/**
\brief  SetKeyString

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKeyString"

logical sADK_EventAction :: SetKeyString ( )
{
  PropertyHandle     *prophdl = GetPropertyHandle();
  pc_ADK_KeyEvent    ke(prophdl->GPH("key_event"));

  ke.SetKeyString();
  return(NO);
}

/******************************************************************************/
/**
\brief  sADK_EventAction - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sADK_EventAction"

                        sADK_EventAction :: sADK_EventAction ( )
                     : sLanguageDependendBase ()
{



}

/******************************************************************************/
/**
\brief  ~sADK_EventAction - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sADK_EventAction"

                        sADK_EventAction :: ~sADK_EventAction ( )
{



}


