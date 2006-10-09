/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pDesigner

\brief    


\date     $Date: 2006/08/28 07:57:11,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pDesigner"

#include  <pdesign.h>
#include  <ifil.h>
#include  <sdc_ResourceDB.hpp>
#include  <spc1_ADKC_Bitmap.hpp>
#include  <spDesigner.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - 

\param  ctx_prj_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pDesigner :: Create (CTX_Project **ctx_prj_ptrp )
{

  *ctx_prj_ptrp = new pDesigner();
  return(NO);

}

/******************************************************************************/
/**
\brief  DefineBitmapsFromFolder - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DefineBitmapsFromFolder"

logical pDesigner :: DefineBitmapsFromFolder ( )
{
  char        *str;
  char        *cpath  = NULL;
  char        *sysvar = NULL;
  srt         *table  = NULL;
  logical      term   = NO;
BEGINSEQ
  if ( !(str = GetString("Define Bitmaps from Folders","Folder","")) )
                                                     ERROR
  cpath = strdup(str);                                                     

  if ( !(str = GetString("Define generic bitmap path","System variable","")) )
                                                     ERROR
  sysvar = strdup(str);                                                     

  if ( !(table = CreateFileTable(cpath,"*.bmp")) )   ERROR
  
  pc1_ADKC_Bitmap((DBObjectHandle&)GetDBHandle(),PI_Update).DefineFromList(table,sysvar,"*.bmp");

RECOVER
  term = YES;
ENDSEQ
  if ( cpath )
    free(cpath);
  if ( sysvar )
    free(sysvar);
  delete table;
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterHandleActivated - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleActivated"

int8 pDesigner :: DoAfterHandleActivated ( )
{

  pODE::DoAfterHandleActivated();

  SelectProject("");
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 pDesigner :: DoAfterOpen ( )
{
  char        *option = NULL;
  logical      term = NO;
  term = pODE::DoAfterOpen();

  strcpy(application_name,"Designer");
  
  option = GetOption("InputHelp");
  SetActionToggled("InputHelp",*option == 'Y' || *option == 'y' ? YES : NO);

  SelectProject("");    // has been set in pODE::DoAfterOpen
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

logical pDesigner :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("DefineBitmapsFromFolder",ALINK(this,pDesigner,DefineBitmapsFromFolder)),
                           cfte("InitResourceDB",ALINK(this,pDesigner,InitResourceDB)),
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
\brief  InitResourceDB - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pDesigner :: InitResourceDB ( )
{
  dc_ResourceDB    resdb(GetResourceDB(),PI_Read);
  dc_ResourceDB    datdb(GetDBHandle(),PI_Write);
  logical          term  = NO;
  datdb.InitResourceDB_DE(&resdb);
  return(term);
}

/******************************************************************************/
/**
\brief  pDesigner - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pDesigner"

     pDesigner :: pDesigner ( )
                     : pODE ()
{



}

/******************************************************************************/
/**
\brief  ~pDesigner - Destruktor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pDesigner"

     pDesigner :: ~pDesigner ( )
{



}


