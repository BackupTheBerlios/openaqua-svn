/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    UCTXDesignerInterface

\brief    


\date     $Date: 2006/03/12 19:36:58,34 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "UCTXDesignerInterface"

#include  <pdesign.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <iCtxIncl.h>
#include  <sctxe.hpp>

#include  <iUCTXDesignerInterface.h>

/******************************************************************************/
/**
\brief  CreateContext - 


\return

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
  OADIRESET
  
  if ( !ctxesrt.srtkln() )
    ctxesrt.srtsor(CTXE_KPS,CTXE_KLN,CTXE_KTP);
  
  if ( ctxeptr = (ctxe *)ctxesrt.srtigt(ctxesrt.srtssr((void *)&resid)) )
    ctxeptr->VoidCall(&ctx_base);
  return(ctx_base);
}

