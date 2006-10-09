/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ceditFieldControl

\brief    


\date     $Date: 2006/06/13 23:01:28,75 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ceditFieldControl"

#include  <pdesign.h>
#include  <spc1_ADK_FieldControl.hpp>
#include  <sceditFieldControl.hpp>


/******************************************************************************/
/**
\brief  Check - 


\return  - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ceditFieldControl :: Check ( )
{
  logical              term = NO;
  pc1_ADK_FieldControl  pc_fc(GetPropertyHandle());
  term = pc_fc.Check(GetPropertyHandle()->GetLOID(),YES);
    
  P_DISPLAY(102+term);


  return(term);
}

/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 ceditFieldControl :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new ceditFieldControl();
  return(NO);

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

logical ceditFieldControl :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Check",ALINK(this,ceditFieldControl,Check)),
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
    term = cSDBResource_Base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ceditFieldControl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ceditFieldControl"

     ceditFieldControl :: ceditFieldControl ( )
                     : cSDBResource_Base ()
{



}

/******************************************************************************/
/**
\brief  ~ceditFieldControl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ceditFieldControl"

     ceditFieldControl :: ~ceditFieldControl ( )
{



}


