/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSDBStructure_edit

\brief    


\date     $Date: 2006/06/01 17:10:57,26 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cSDBStructure_edit"

#include  <pdesign.h>
#include  <scSDBStructure_edit.hpp>


/******************************************************************************/
/**
\brief  Check - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical cSDBStructure_edit :: Check ( )
{
  PropertyHandle *ph            = GetCurrentPropertyHandle();
  char           *show_warnings = ODEOption(this,"StructureCheckWarningLevel");
  logical         term          = NO;
BEGINSEQ
  ODEOutput(this,"  ",YES);
  ODEOutput(this,ph->GPH("sys_ident")->GetString(),NO);

  if ( ph->NoWrite() )                               ERROR
  
  if ( ph->IsA("ODC_ImpClass") )
    ph = ph->GPH("SDB_Structure");
    
  ODEOutput(this,"...Checking structure\n",NO);
  if ( ph->ExecuteInstanceAction("CheckStructure",show_warnings) )
    ODEOutput(this,"...  terminated with errors\n",NO);
  else
    ODEOutput(this,ph->GetActionResult(),NO);

  FillControl();

RECOVER
  ODEOutput(this,"...not available for update\n",NO);
  term = YES;
ENDSEQ
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

int32 cSDBStructure_edit :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cSDBStructure_edit();
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

logical cSDBStructure_edit :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Check",ALINK(this,cSDBStructure_edit,Check)),
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
    term = cSDBResourceNotifyHigh::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cSDBStructure_edit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cSDBStructure_edit"

     cSDBStructure_edit :: cSDBStructure_edit ( )
                     : cSDBResourceNotifyHigh()
{



}

/******************************************************************************/
/**
\brief  ~cSDBStructure_edit - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cSDBStructure_edit"

     cSDBStructure_edit :: ~cSDBStructure_edit ( )
{



}


