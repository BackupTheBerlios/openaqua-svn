/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pImportProtokoll

\brief    


\date     $Date: 2006/06/29 15:02:54,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pImportProtokoll"

#include  <pvgkctxi.h>
#include  <spc0_ImportProtokoll.hpp>
#include  <spImportProtokoll.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pImportProtokoll :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new pImportProtokoll();
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

logical pImportProtokoll :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("ImportXMLAction",ALINK(this,pImportProtokoll,ImportXMLAction)),
                           cfte("ImportXMLOpenActions",ALINK(this,pImportProtokoll,ImportXMLOpenActions)),
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
    term = CTX_Property::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportXMLAction - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLAction"

logical pImportProtokoll :: ImportXMLAction ( )
{
  logical     term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ImportXMLOpenActions - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLOpenActions"

logical pImportProtokoll :: ImportXMLOpenActions ( )
{
  pc0_ImportProtokoll      pc_imp(GetPropertyHandle());
  logical                  term = NO;
  return(pc_imp.ImportOpenXMLActions());

}

/******************************************************************************/
/**
\brief  pImportProtokoll - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pImportProtokoll"

     pImportProtokoll :: pImportProtokoll ( )
                     : CTX_Property()
{



}

/******************************************************************************/
/**
\brief  ~pImportProtokoll - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pImportProtokoll"

     pImportProtokoll :: ~pImportProtokoll ( )
{



}


