/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cContextClass

\brief    


\date     $Date: 2006/06/01 17:00:08,70 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cContextClass"

#include  <pdesign.h>
#include  <scContextClass.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cContextClass :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cContextClass();
  return(NO);

}

/******************************************************************************/
/**
\brief  EditEntry - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EditEntry"

logical cContextClass :: EditEntry ( )
{
  logical                 term = NO;
  PropertyHandle *        ph;
BEGINSEQ
  ph = GetCurrentPropertyHandle()->GetPropertyHandle("smceclas");
  if ( ! ph->Get(FIRST_INSTANCE) )                   LEAVESEQ
  ExecuteWindow(ph, "ODC_ImpClass", "Edit", NO);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cContextClass :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("EditEntry",ALINK(this,cContextClass,EditEntry)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = CTX_Control::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}


