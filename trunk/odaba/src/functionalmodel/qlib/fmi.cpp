/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    fmi

\brief    


\date     $Date: 2006/07/24 13:23:16,78 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "fmi"

#include  <pfmodel.h>

#include  <ifmi.h>

/******************************************************************************/
/**
\brief  ProgramLanguageExtension - 



\return extension - 

\param  nstring - 
\param  dbhandle - 
\param  plang - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProgramLanguageExtension"

char *__cdecl ProgramLanguageExtension (NString &nstring, DatabaseHandle &dbhandle, ProgramLanguage plang )
{
  char        string[4];
  char       *ext       = NULL;
BEGINSEQ
  nstring = "";
  
  if ( plang == PL_undefined )                       SDBERR(60)
    
  PropertyHandle   pl(dbhandle.GetDictionary(),"ProgramLanguage",PI_Read);
                                                     SDBCERR
  pl.SetOrder("code");
  if ( !pl.Get((char *)&plang) )                     SDBERR(99)
  ext = pl.ExtractKey();

  nstring = gvtslwr(gvtxbts(string,ext+3,3));
RECOVER

ENDSEQ
  return(ext ? (char *)nstring : (char *)NULL);
}

