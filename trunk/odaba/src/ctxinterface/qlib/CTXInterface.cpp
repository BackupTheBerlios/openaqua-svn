/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    CTXInterface



\date     $Date: 2006/05/31 18:41:36,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTXInterface"

#include  <popa7.h>
#include  <sCTX_DataBase.hpp>
#include  <sCTX_Object.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sstest.hpp>

#include  <iCTXInterface.h>

/******************************************************************************/
/**
\brief  CreateDBCtx - 


\return dbctx

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBCtx"

CTX_DataBase *__cdecl CreateDBCtx (int32 resid )
{

  return ( NULL );

}

/******************************************************************************/
/**
\brief  CreateObjCtx

\return objctx

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateObjCtx"

CTX_Object *__cdecl CreateObjCtx ( )
{

  return ( NULL );

}

/******************************************************************************/
/**
\brief  CreatePropCtx

\return propctx - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePropCtx"

CTX_Property *__cdecl CreatePropCtx (int32 resid )
{

  return ( NULL );

}

/******************************************************************************/
/**
\brief  CreateStrCtx

\return strctx - Structure Context

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStrCtx"

CTX_Structure *__cdecl CreateStrCtx (int32 resid )
{

  return ( NULL );

}

