/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pRechtsschutzVS

\brief    


\date     $Date: 2006/07/06 14:53:38,12 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pRechtsschutzVS"

#include  <pvgkctxi.h>
#include  <spRechtsschutzVS.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pRechtsschutzVS :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pRechtsschutzVS();
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

logical pRechtsschutzVS :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GetSparte",ALINK(this,pRechtsschutzVS,GetSparte)),
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

logical pRechtsschutzVS :: GetSparte ( )
{
  PropertyHandle   *ph = GetPropertyHandle();
  ph->SetActionResult("RS");
  return(NO);
}

/******************************************************************************/
/**
\brief  pRechtsschutzVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pRechtsschutzVS"

     pRechtsschutzVS :: pRechtsschutzVS ( )
                     : pVS_base()
{



}

/******************************************************************************/
/**
\brief  ~pRechtsschutzVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pRechtsschutzVS"

     pRechtsschutzVS :: ~pRechtsschutzVS ( )
{



}


