/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    Context



\date     $Date: 2006/05/31 18:46:15,50 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Context"

#include  <pops7.h>
#include  <iCtxIncl.h>
#include  <iCTXFunctionalModel.h>
#include  <sCTX_Base.hpp>
#include  <sctxe.hpp>

#include  <iContext.h>

/******************************************************************************/
/**
\brief  SysCreateContext

\return ctx_base

\param  resid
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SysCreateContext"

CTX_Base *__cdecl SysCreateContext (int32 resid )
{
  ctxe      *ctxeptr  = NULL;
  CTX_Base  *ctx_base = NULL;
  static   ctxe cttbl[] = {
#include <iCtxClasses.h>      
      ctxe()
  };

  static   srt   ctxesrt(sizeof(cttbl)/CTXE,CTXE,UNDEF,UNDEF,UNDEF,(char *)cttbl,NO);
  
  CTXRESET

  if ( !ctxesrt.srtkln() )
    ctxesrt.srtsor(CTXE_KPS,CTXE_KLN,CTXE_KTP);

  if ( ctxeptr = (ctxe *)ctxesrt.srtigt(ctxesrt.srtssr((void *)&resid)) )
    ctxeptr->VoidCall(&ctx_base);
  else
    ctx_base = SysFMCreateContext(resid);

  CTXRESET
  return(ctx_base);
}

