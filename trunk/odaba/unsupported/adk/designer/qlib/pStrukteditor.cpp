/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pStrukteditor

\brief    


\date     $Date: 2006/06/01 17:30:19,85 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pStrukteditor"

#include  <pdesign.h>
#include  <spStrukteditor.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return  - 

\param  ctx_prj_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pStrukteditor :: Create (CTX_Project **ctx_prj_ptrp )
{

  *ctx_prj_ptrp = new pStrukteditor();
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

logical pStrukteditor :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GenerateSQLDefinitions",ALINK(this,pStrukteditor,GenerateSQLDefinitions)),
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
    term = pODE::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateSQLDefinitions - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateSQLDefinitions"

logical pStrukteditor :: GenerateSQLDefinitions ( )
{
  logical  term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  pStrukteditor - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pStrukteditor"

     pStrukteditor :: pStrukteditor ( )
                     : pODE()
{



}

/******************************************************************************/
/**
\brief  ~pStrukteditor - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pStrukteditor"

     pStrukteditor :: ~pStrukteditor ( )
{



}


