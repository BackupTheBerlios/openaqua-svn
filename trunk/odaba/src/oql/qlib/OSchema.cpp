/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OSchema

\brief    


\date     $Date: 2006/04/12 10:13:58,81 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSchema"

#include  <poql.h>
#include  <dlincl.h>
#include  <sBNFData.hpp>
#include  <sBNFParser.hpp>
#include  <sOScriptFile.hpp>
#include  <sSchemaResources.hpp>
#include  <sOSchema.hpp>


/******************************************************************************/
/**
\brief  LoadSchema - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadSchema"

logical OSchema :: LoadSchema ( )
{
  BNFData       *bdata;
  BNFData       *edata;
  int32          indx0 = 0;
  logical        term = NO;
BEGINSEQ
// ODL     := [data_source] sc_element(*)

  resources->set_schema_only(YES);

  bdata = file_list.GetHead()->get_bnf_data()->GetElement(0);

  while ( edata = bdata->GetElement(indx0++) )
    if ( edata = edata->GetSymbol("sc_element") )
      if ( resources->LoadSchemaElement(NULL,edata) )   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateFile - 


\return sfile - 

\param  script_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateFile"

OScriptFile *OSchema :: LocateFile (char *script_path )
{
  OScriptFile       *sfile = NULL;

BEGINSEQ
  file_list.GoTop();
  while ( sfile = file_list.GetNext() )
    if ( !strcmp(script_path,sfile->get_path()) )    LEAVESEQ

  ERROR
RECOVER
  sfile = NULL;
ENDSEQ
  return(sfile);
}

/******************************************************************************/
/**
\brief  OSchema - 



\param  script_path - 
\param  ini_file - 
\param  dict_path - 
\param  applname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSchema"

                        OSchema :: OSchema (char *script_path, char *ini_file, char *dict_path, char *applname )
                     : resources(NULL),
  parser(NULL),
  file_list(),
  dictionary(),
  resdb()
{
  ODABAClient        client;
  OScriptFile       *sfile = NULL;
BEGINSEQ
  if ( ini_file )
  {
    client.Initialize(ini_file,applname,NULL,APT_Console,YES);
    if ( !dict_path || !*dict_path )
      dict_path = GetSysVariable("DICTIONARY");
  }
  dictionary = GetSystemDictionary();
  if ( !dictionary.IsValid() )
    dictionary.Open(client,NULL,PI_Read,NO);  // temporary dictionary for parser
  
  if ( !ParseFile(script_path,applname) )         ERROR

  if ( Open(dict_path) )                             ERROR
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Open - 


\return term

\param  dict_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical OSchema :: Open (char *dict_path )
{
  BNFData        *bnf_data = file_list.GetHead()->get_bnf_data();
  BNFData        *bdata;
  char           *dc_path = NULL;
  char           *db_path = NULL;
  ODABAClient     client;
  logical         term    = NO;
BEGINSEQ
  bdata = bnf_data->GetElement(0)->GetElement(0);
  if ( bdata->IsSymbol("dictionary") )
  {
    bdata = bdata->GetSymbol("dictionary");
    if ( !dict_path )
      dc_path = dict_path = strdup(bdata->GetElement(2)->GetStringConstant());
    if ( bdata = bdata->GetElement("database") )
      db_path = strdup(bdata->GetElement(2)->GetStringConstant());
  }
  
  if ( dict_path )
  {
    if ( dictionary.Open(client,dict_path,PI_Write,YES) )
                                                     ERROR
    resdb = dictionary;
  }
    
  if ( db_path )
    if ( database.Open(dictionary,db_path,PI_Write,YES) )
                                                     ERROR
  
  if ( bdata = bdata->GetSymbol("datasource") )
  {
    DataSourceHandle        dsh;
    if ( dsh.Open(client,bdata->GetElement(2)->GetStringConstant()) )
                                                     ERROR
    dictionary = dsh.dictionary;
    resdb      = dsh.reshandle.IsValid() ? dsh.reshandle : dsh.dictionary;
    database   = dsh.dbhandle;
  }
  if ( !dictionary.IsOpened() )                      SDBERR(452)

  resources = new SchemaResources(dictionary.get_dictionary(),
                                  resdb.get_dbhandle(),NULL);

RECOVER
  term = YES;
ENDSEQ
  if ( dc_path )
    free(dc_path);
  return(term);
}

/******************************************************************************/
/**
\brief  ParseFile - 


\return sfile - 

\param  script_path - 
\param  symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParseFile"

OScriptFile *OSchema :: ParseFile (char *script_path, char *symbol )
{
  OScriptFile       *sfile = NULL;
  logical            term = NO;
BEGINSEQ
  if ( !parser )
    parser = dictionary->GetParser();
    
  sfile = new OScriptFile(script_path,parser,symbol);OQLCERR
                                                     
  file_list.AddTail(sfile);
RECOVER
  delete sfile;
  sfile = NULL;
ENDSEQ
  return(sfile);
}

/******************************************************************************/
/**
\brief  ~OSchema - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSchema"

                        OSchema :: ~OSchema ( )
{
  OScriptFile       *sfile = NULL;

  while ( sfile = file_list.RemoveTail() )
    delete sfile;
      
  database.Close();
  resdb.Close();
  dictionary.Close();

  delete resources;
  resources = NULL;

  parser = NULL;

}


