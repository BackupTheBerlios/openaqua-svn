/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pUnfallVS

\brief    


\date     $Date: 2006/07/06 14:53:56,60 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pUnfallVS"

#include  <pvgkctxi.h>
#include  <spUnfallVS.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pUnfallVS :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pUnfallVS();
  return(NO);


}

/******************************************************************************/
/**
\brief  ExecuteFunction - 



\return  - 

\param  fname - Name der Funktion
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical pUnfallVS :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GetSparte",ALINK(this,pUnfallVS,GetSparte)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    cfteptr->LINKINST(this);
    term = cfteptr->ActionCall();
  }
  else
    term = pVS_base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetSparte - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSparte"

logical pUnfallVS :: GetSparte ( )
{
  PropertyHandle   *ph = GetPropertyHandle();
  ph->SetActionResult("UN");
  return(NO);
}

/******************************************************************************/
/**
\brief  pUnfallVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pUnfallVS"

     pUnfallVS :: pUnfallVS ( )
                     : pVS_base()
{



}

/******************************************************************************/
/**
\brief  ~pUnfallVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pUnfallVS"

     pUnfallVS :: ~pUnfallVS ( )
{



}


