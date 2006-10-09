/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cPFunctionReturnTable

\brief    


\date     $Date: 2006/04/24 13:43:27,80 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cPFunctionReturnTable"

#include  <pdesign.h>
#include  <scPFunctionReturnTable.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cPFunctionReturnTable :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cPFunctionReturnTable();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterSaveData

\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSaveData"

int8 cPFunctionReturnTable :: DoAfterSaveData ( )
{

  cSDBResourceNotifyHigh:: DoAfterStoreData();

  Changed();
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterStoreData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterStoreData"

int8 cPFunctionReturnTable :: DoAfterStoreData ( )
{

  cSDBResourceNotifyHigh:: DoAfterStoreData();

  Changed();
  return(NO);
}

/******************************************************************************/
/**
\brief  cPFunctionReturnTable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cPFunctionReturnTable"

                        cPFunctionReturnTable :: cPFunctionReturnTable ( )
                     : cSDBResourceNotifyHigh ()
{



}

/******************************************************************************/
/**
\brief  ~cPFunctionReturnTable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cPFunctionReturnTable"

                        cPFunctionReturnTable :: ~cPFunctionReturnTable ( )
{



}


