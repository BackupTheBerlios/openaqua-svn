/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SYS_CTXInterface

\brief    


\date     $Date: 2006/03/13 21:30:24,40 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SYS_CTXInterface"

#include  <pops7.h>
#include  <sCTX_DataBase.hpp>
#include  <sCTX_Object.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <iContext.h>
#include  <scfte.hpp>
#include  <spSDB_ResourceRef.hpp>
#include  <spTypeInSDB_Member.hpp>
#include  <ssDSC_Concept.hpp>
#include  <ssDSC_Term.hpp>
#include  <ssDSC_Topic.hpp>
#include  <ssLanguageDependend.hpp>
#include  <ssSDB_Member.hpp>
#include  <ssView.hpp>

#include  <iSYS_CTXInterface.h>

/******************************************************************************/
/**
\brief  SYS_CreateDBCtx - 


\return dbctx

\param  resid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SYS_CreateDBCtx"

CTX_DataBase *__cdecl SYS_CreateDBCtx (int32 resid )
{
  CTX_Base       *ctx_base = NULL;
  CTX_DataBase   *dbctx    = NULL;
  if ( ctx_base = SysCreateContext(resid) )
    dbctx = (CTX_DataBase *)ctx_base;
     
/*  
  return ( new CTX_DataBase() );
*/  

  return(dbctx);
}

/******************************************************************************/
/**
\brief  SYS_CreateObjCtx - 


\return objctx

\param  resid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SYS_CreateObjCtx"

CTX_Object *__cdecl SYS_CreateObjCtx (int32 resid )
{
  CTX_Base       *ctx_base = NULL;
  CTX_Object     *objctx   = NULL;
  if ( ctx_base = SysCreateContext(resid) )
    objctx = (CTX_Object *)ctx_base;
/*  
  return ( new CTX_Object() );
*/  

  return(objctx);
}

/******************************************************************************/
/**
\brief  SYS_CreatePropCtx - 


\return propctx

\param  resid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SYS_CreatePropCtx"

CTX_Property *__cdecl SYS_CreatePropCtx (int32 resid )
{
  CTX_Base      *ctx_base = NULL;
  CTX_Property  *propctx  = NULL;
  char           ctxid[ID_SIZE];
  if ( ctx_base = SysCreateContext(resid) )
    propctx = (CTX_Property *)ctx_base;

  return(propctx);
}

/******************************************************************************/
/**
\brief  SYS_CreateStrCtx - 


\return strctx

\param  resid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SYS_CreateStrCtx"

CTX_Structure *__cdecl SYS_CreateStrCtx (int32 resid )
{
  CTX_Base      *ctx_base = NULL;
  CTX_Structure *strctx   = NULL;
  char           ctxid[ID_SIZE];
  if ( ctx_base = SysCreateContext(resid) )
    strctx = (CTX_Structure *)ctx_base;


  return(strctx);
}

