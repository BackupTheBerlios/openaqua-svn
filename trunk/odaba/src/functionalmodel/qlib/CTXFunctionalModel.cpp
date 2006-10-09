/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    CTXFunctionalModel

\brief    


\date     $Date: 2006/06/12 08:44:39,00 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTXFunctionalModel"

#include  <pfmodel.h>
#include  <iCtxIncl.h>
#include  <sCTX_Base.hpp>
#include  <sctxe.hpp>
#include  <ssODC_PFunction.hpp>
#include  <ssODC_Variable.hpp>

#include  <iCTXFunctionalModel.h>

/******************************************************************************/
/**
\brief  SysFMCreateContext - 


\return ctx_base - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SysFMCreateContext"

CTX_Base *__cdecl SysFMCreateContext (int32 resid )
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

  CTXRESET
  return(ctx_base);
}

