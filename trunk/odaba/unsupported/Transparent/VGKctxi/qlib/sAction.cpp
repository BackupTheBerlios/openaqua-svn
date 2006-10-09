/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sAction

\brief    


\date     $Date: 2006/07/07 12:27:44,01 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sAction"

#include  <pvgkctxi.h>
#include  <ssAction.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sAction :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sAction();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBInitialize - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBInitialize"

logical sAction :: DBInitialize ( )
{

  InitKey("extern_id","Action");

  return(NO);
}

/******************************************************************************/
/**
\brief  DBOpened - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpened"

logical sAction :: DBOpened ( )
{
  PropertyHandle    *ph        = GetPropertyHandle();

  ph->GPH("versicherungsnehmer")->SetType("Person");

  return(NO);
}

/******************************************************************************/
/**
\brief  sAction - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sAction"

     sAction :: sAction ( )
                     : sBase_SharedData()
{



}

/******************************************************************************/
/**
\brief  ~sAction - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sAction"

     sAction :: ~sAction ( )
{



}


