/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    GlobalC



\date     $Date: 2006/04/24 11:58:41,29 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "GlobalC"

#include  <padkctxi.h>
#include  <cProgramLanguage.h>

#include  <iGlobalC.h>

/******************************************************************************/
/**
\brief  ClassLanguageExt - 


\return extension

\param  dbhandle - 
\param  clsnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClassLanguageExt"

char *__cdecl ClassLanguageExt (DatabaseHandle &dbhandle, char *clsnames )
{
  char          clsname[ID_SIZE];
  char         *extension = NULL;
BEGINSEQ
  gvtxstb(clsname,clsnames,ID_SIZE);

  PropertyHandle  oci_pi(dbhandle,"ODC_ImpClass",PI_Read);  
                                                     SDBCERR
  if ( !oci_pi(clsname) )                            CTXERR(99)

  if ( !(extension = PLLanguageExt(dbhandle,(ProgramLanguage)oci_pi.GetInt("opt_language"))) )
                                                     ERROR

RECOVER
  extension = NULL;
ENDSEQ
  return(extension);
}

/******************************************************************************/
/**
\brief  PLLanguageExt - 


\return extension

\param  dbhandle - 
\param  plang - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PLLanguageExt"

char *__cdecl PLLanguageExt (DatabaseHandle &dbhandle, ProgramLanguage plang )
{
  static char extarea[4];
  char       *extension = extarea;
  char       *ext;

BEGINSEQ
  if ( plang == PL_undefined )                       CTXERR(60)
    
  CS       pl(dbhandle,"ProgramLanguage",PI_Read);   SDBCERR
  if ( !(ext = pl.GetCodeString(plang)) )            CTXERR(99)

  gvtslwr(gvtxbts(extension,ext+3,3));
RECOVER
  extension = NULL;
ENDSEQ
  return(extension);
}

