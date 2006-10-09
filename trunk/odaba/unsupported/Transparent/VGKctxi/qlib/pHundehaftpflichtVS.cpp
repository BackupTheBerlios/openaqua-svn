/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pHundehaftpflichtVS

\brief    


\date     $Date: 2006/07/06 14:53:00,57 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pHundehaftpflichtVS"

#include  <pvgkctxi.h>
#include  <spHundehaftpflichtVS.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pHundehaftpflichtVS :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pHundehaftpflichtVS();
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

logical pHundehaftpflichtVS :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GetSparte",ALINK(this,pHundehaftpflichtVS,GetSparte)),
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

logical pHundehaftpflichtVS :: GetSparte ( )
{
  PropertyHandle   *ph = GetPropertyHandle();
  ph->SetActionResult("HHV");
  return(NO);
}

/******************************************************************************/
/**
\brief  pHundehaftpflichtVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pHundehaftpflichtVS"

     pHundehaftpflichtVS :: pHundehaftpflichtVS ( )
                     : pVS_base()
{



}

/******************************************************************************/
/**
\brief  ~pHundehaftpflichtVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pHundehaftpflichtVS"

     pHundehaftpflichtVS :: ~pHundehaftpflichtVS ( )
{



}


