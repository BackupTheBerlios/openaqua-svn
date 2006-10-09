/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sImportProtokoll

\brief    


\date     $Date: 2006/06/29 15:33:32,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sImportProtokoll"

#include  <pvgkctxi.h>
#include  <spc0_ImportProtokoll.hpp>
#include  <ssImportProtokoll.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sImportProtokoll :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sImportProtokoll();
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

logical sImportProtokoll :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("ImportXMLActions",ALINK(this,sImportProtokoll,ImportXMLActions)),
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
    term = CTX_Structure::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportXMLActions - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLActions"

logical sImportProtokoll :: ImportXMLActions ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  term = pc0_ImportProtokoll(ph).ImportXMLActions();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sImportProtokoll - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sImportProtokoll"

     sImportProtokoll :: sImportProtokoll ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~sImportProtokoll - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sImportProtokoll"

     sImportProtokoll :: ~sImportProtokoll ( )
{



}


