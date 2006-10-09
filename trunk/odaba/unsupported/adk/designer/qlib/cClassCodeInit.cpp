/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassCodeInit

\brief    Context for init code in CPP functions and OSI expressions2


\date     $Date: 2006/06/01 16:49:18,93 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassCodeInit"

#include  <pdesign.h>
#include  <scClassCodeInit.hpp>


/******************************************************************************/
/**
\brief  Create

\return 

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassCodeInit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassCodeInit();
  return(NO);


}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return 

\param  fname
\param  chk_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cClassCodeInit :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetupInitCode",ALINK(this,cClassCodeInit,SetupInitCode)),
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
    term = cClassCodeBase::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupInitCode

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInitCode"

logical cClassCodeInit :: SetupInitCode ( )
{
  PropertyHandle  *prophdl = GetPropertyHandle();    
  PropertyHandle  *fcti_ph = prophdl->GetParentProperty();
  logical          term    = NO;
BEGINSEQ
  ExecuteAction("StoreEntry",ACT_Function);
  fcti_ph->Save();
  if ( prophdl->NoWrite() )                          ERROR
  
  fcti_ph->ExecuteInstanceAction("SetupInitCode","NO");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cClassCodeInit


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassCodeInit"

     cClassCodeInit :: cClassCodeInit ( )
                     : cClassCodeBase ()

{
}

/******************************************************************************/
/**
\brief  ~cClassCodeInit


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassCodeInit"

     cClassCodeInit :: ~cClassCodeInit ( )
{
}


