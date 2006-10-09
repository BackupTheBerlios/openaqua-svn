/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    UCTXInterface

\brief    


\date     $Date: 2006/07/05 14:04:39,13 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UCTXInterface"

#include  <podcp8.h>
#include  <sCTX_Base.hpp>
#include  <sctxe.hpp>

#include  <iUCTXInterface.h>

/******************************************************************************/
/**
\brief  CreateContext - 



\return ctx_base - 

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
//#include <iCtxClasses.h>      
      ctxe()
  };

  static   srt   ctxesrt(sizeof(cttbl)/CTXE,CTXE,UNDEF,UNDEF,UNDEF,(char *)cttbl,NO);
  
  OADIRESET

  if ( !ctxesrt.srtkln() )
    ctxesrt.srtsor(CTXE_KPS,CTXE_KLN,CTXE_KTP);

  if ( ctxeptr = (ctxe *)ctxesrt.srtigt(ctxesrt.srtssr((void *)&resid)) )
    ctxeptr->VoidCall(&ctx_base);
  return(ctx_base);
}

