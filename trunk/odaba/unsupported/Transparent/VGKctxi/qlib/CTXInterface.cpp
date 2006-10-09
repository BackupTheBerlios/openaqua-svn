/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    CTXInterface

\brief    Contextklasseninterface


\date     $Date: 2006/07/07 12:34:00,10 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTXInterface"

#include  <pvgkctxi.h>
#include  <iCtxIncl.h>
#include  <sCTX_Base.hpp>
#include  <sctxe.hpp>

#include  <iCTXInterface.h>

/******************************************************************************/
/**
\brief  CreateContext - 



\return ctx_ptr - 

\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateContext"

CTX_Base *__cdecl CreateContext (int32 resid )
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

