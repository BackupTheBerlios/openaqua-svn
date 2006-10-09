/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_DokumentReferenz

\brief    


\date     $Date: 2006/07/19 22:13:02,79 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_DokumentReferenz"

#include  <pVGKbase.h>
#include  <ifil.h>
#include  <spc_DokumentReferenz.hpp>


/******************************************************************************/
/**
\brief  CreateReferenz - 



\return term - Abbruchbedingung
-------------------------------------------------------------------------------
\brief  cpath - 



\param  cpath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReferenz"

logical pc_DokumentReferenz :: CreateReferenz (char *cpath )
{
  char      folder[256];
  char      filname[256];
  char      filext[256];
  logical   term = NO;
BEGINSEQ
  if ( !cpath )                                     ERROR
  
  GetDirectoryPathInfo(cpath,folder,sizeof(folder)-1);
  GetFileNameInfo(cpath,filname,filext,sizeof(filname)-1,sizeof(filext)-1);
  
  term = CreateReferenz(folder,filname,filext);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i00 - 



\param  path - 
\param  filename - 
\param  filext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReferenz"

logical pc_DokumentReferenz :: CreateReferenz (char *path, char *filename, char *filext )
{
  logical     term = NO;
BEGINSEQ
  Add(Key::NewAutoident());                         SDBCERR

  if ( path )
    *GPH("pfad") = path;
  if ( filename )
    *GPH("name") = filename;
  if ( filext )
    *GPH("kennung") = filext;
  
  Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCompletePath - 



\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompletePath"

char *pc_DokumentReferenz :: GetCompletePath (NString &nstring )
{
  PropertyHandle   *pfad    = GPH("pfad");
  PropertyHandle   *kennung = GPH("kennung");
BEGINSEQ
  nstring = "";
  
  if ( !IsPositioned() )                            ERROR
  
  if ( !pfad->IsEmpty() )
  {
    nstring += pfad->GetString();
    nstring += "/";
  }
  
  nstring += GPH("name")->GetString();

  if ( !kennung->IsEmpty() )
  {
    nstring += ".";
    nstring += kennung->GetString();
  }
RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  pc_DokumentReferenz - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_DokumentReferenz"

     pc_DokumentReferenz :: pc_DokumentReferenz (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  extnames - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_DokumentReferenz"

     pc_DokumentReferenz :: pc_DokumentReferenz (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : PropertyHandle(dbhandle,extnames,accopt)
{



}


