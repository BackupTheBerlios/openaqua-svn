/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    dbTransparent

\brief    


\date     $Date: 2006/07/21 14:19:51,85 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "dbTransparent"

#include  <pvgkctxi.h>
#include  <sVGK_Import.hpp>
#include  <spc0_ImportProtokoll.hpp>
#include  <sdbTransparent.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_db_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 dbTransparent :: Create (CTX_DataBase **ctx_db_ptrp )
{

  *ctx_db_ptrp = new dbTransparent();
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

logical dbTransparent :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("ImportImportProtokoll",ALINK(this,dbTransparent,ImportImportProtokoll)),
                           cfte("ImportOpenXMLActions",ALINK(this,dbTransparent,ImportOpenXMLActions)),
                           cfte("ImportStammdaten",ALINK(this,dbTransparent,ImportStammdaten)),
                           cfte("ImportXMLActions",ALINK(this,dbTransparent,ImportXMLActions)),
                           cfte("InitializeImportXMLActions",ALINK(this,dbTransparent,InitializeImportXMLActions)),
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
    term = CTX_DataBase::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ImportImportProtokoll - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportImportProtokoll"

logical dbTransparent :: ImportImportProtokoll ( )
{


  return ( VGK_Import().ImportImportProtokoll(GetDBHandle(),
                                              Parm(1))        );

}

/******************************************************************************/
/**
\brief  ImportOpenXMLActions - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportOpenXMLActions"

logical dbTransparent :: ImportOpenXMLActions ( )
{
  pc0_ImportProtokoll  import(GetDBHandle(),PI_Write);

  return ( import.ImportOpenXMLActions() );

}

/******************************************************************************/
/**
\brief  ImportStammdaten - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportStammdaten"

logical dbTransparent :: ImportStammdaten ( )
{


  return ( VGK_Import().ImportStammdaten(GetDBHandle()) );

}

/******************************************************************************/
/**
\brief  ImportXMLActions - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportXMLActions"

logical dbTransparent :: ImportXMLActions ( )
{
  pc0_ImportProtokoll  import(GetDBHandle(),PI_Write);
  char                *parm1     = Parm(1);
  int32                imp_ident = 0;
  logical              term      = NO;
BEGINSEQ
  if ( !parm1 || !(imp_ident = atol(parm1)) )        CTXERR(21)
  if ( import.ImportXMLActions(imp_ident) )          ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitializeImportXMLActions - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeImportXMLActions"

logical dbTransparent :: InitializeImportXMLActions ( )
{
  pc0_ImportProtokoll  import(GetDBHandle(),PI_Write);
  NString              parm(Parm(1));
  logical              term = NO;

BEGINSEQ
  if ( parm.IsEmpty() )                             CTXERR(99)
  parm.UTFToASCII();
  parm.ReplaceCharacter(1,',');

  if ( import.InitializeImportXMLActions(parm) )    ERROR

  GetDBHandle().SetActionResult(import.GetString("__AUTOIDENT"));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dbTransparent - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbTransparent"

     dbTransparent :: dbTransparent ( )
                     : CTX_DataBase()
{



}

/******************************************************************************/
/**
\brief  ~dbTransparent - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~dbTransparent"

     dbTransparent :: ~dbTransparent ( )
{



}


