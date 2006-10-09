/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pKFZVS

\brief    


\date     $Date: 2006/07/06 14:53:13,65 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pKFZVS"

#include  <pvgkctxi.h>
#include  <spKFZVS.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pKFZVS :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pKFZVS();
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

logical pKFZVS :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GetSparte",ALINK(this,pKFZVS,GetSparte)),
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

logical pKFZVS :: GetSparte ( )
{
  PropertyHandle   *ph = GetPropertyHandle();
  ph->SetActionResult("KFZ");
  return(NO);
}

/******************************************************************************/
/**
\brief  pKFZVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pKFZVS"

     pKFZVS :: pKFZVS ( )
                     : pVS_base()
{



}

/******************************************************************************/
/**
\brief  ~pKFZVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pKFZVS"

     pKFZVS :: ~pKFZVS ( )
{



}


