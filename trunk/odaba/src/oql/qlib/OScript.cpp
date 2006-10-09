/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OScript

\brief    


\date     $Date: 2006/07/28 12:09:52,50 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OScript"

#include  <poql.h>
#include  <dlincl.h>
#include  <sBNFData.hpp>
#include  <sDLInterpreter.hpp>
#include  <sDictionary.hpp>
#include  <sParmList.hpp>
#include  <sSchemaResources.hpp>
#include  <sOScript.hpp>


/******************************************************************************/
/**
\brief  Execute - 



\return term - 

\param  entry_point - 
\param  parmlist - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical OScript :: Execute (char *entry_point, ParmList *parmlist )
{
  OPDecl                 *op;
  DLInterpreter          *debugger;
  NString                 nstring;
  PropertyHandle          ph;
  logical                 term = NO;
BEGINSEQ
  InitDebug(NULL);
    
  if ( !entry_point || !*entry_point )
    entry_point = "main";

  if ( !(op = DictHandle()->GetExpression(NULL,entry_point,NULL)) )
                                                     ERROR
  op->Call(NULL,parmlist,NO);

  if ( debugger = op->get_debugger() )
    debugger->ExecuteCommands(op);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadDebugInfo - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadDebugInfo"

logical OScript :: LoadDebugInfo (BNFData *bdata )
{
  logical                 term = NO;
// debug_info   := _debugprocs '=' location 

  InitDebug(bdata->GetElement(2)->GetStringValue(NULL,NULL));
  return(term);
}

/******************************************************************************/
/**
\brief  LoadDefinition - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadDefinition"

logical OScript :: LoadDefinition (BNFData *bdata )
{
  BNFData                *def;
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
// osi_element           := [block_intro(*)] osi_definition ';'
  
  while ( def = bdata->GetElement(indx0++) )
  {
    if ( !def->IsSymbol("block_intro") )
      break;
    else if ( def->IsSymbol("member") )
      CreateVariable(def->GetSymbol("member"),YES);  // create global variable
    else if ( def->IsSymbol("file_reference") )
      LoadFile(def->GetSymbol("file_reference"));
  }
  
  bdata = bdata->GetElement("osi_definition")->GetElement(0);
  if ( resources->LoadScriptDefinition(bdata) )      ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadFile - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadFile"

logical OScript :: LoadFile (BNFData *bdata )
{
  OScriptFile       *sfile = NULL;
  char              *path;
  logical            term = NO;
BEGINSEQ
// file_reference := _include string
  
  path = bdata->GetElement(1)->GetStringConstant();
  if ( !(sfile = LocateFile(path)) )
    if ( !(sfile = ParseFile(path,"osi_element")) )  ERROR

  if ( LoadDefinition(sfile->get_bnf_data()->GetElement(0)) )
                                                     ERROR

RECOVER
  delete sfile;
  sfile = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LoadScript - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LoadScript"

logical OScript :: LoadScript (BNFData *bdata )
{
  BNFData       *edata;
  int32          indx0 = 0;
  logical                 term = NO;
BEGINSEQ
// OSI     := [data_source] [debug_info] osi_element(*)

  if ( edata = bdata->GetElement("debug_info") )
    if ( TestSysVariable("OSI_DEBUG","YES") )
      LoadDebugInfo(edata);

  while ( edata = bdata->GetElement(indx0++) )
    if ( edata = edata->GetSymbol("osi_element") )
      if ( LoadDefinition(edata) )                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OScript - 




\param  script_path - 
\param  ini_file - 
\param  dict_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OScript"

     OScript :: OScript (char *script_path, char *ini_file, char *dict_path )
                     : OSchema (script_path,ini_file,dict_path,"OSI"),
OPDecl (NULL),
  main_function()
{
  char              *svar;
  ODABAClient        client;
BEGINSEQ
  InitDebug(NULL);
    
  if ( CreateEnvironment(dictionary.get_dictionary(),
                         resdb.IsValid() ? resdb.get_dbhandle() : NULL,
                         NULL,NULL,
                         database.IsValid() ? database.get_dbhandle() : NULL,
                         NULL,this) )
                                                     ERROR  
  resources = Schema();
  resources->set_schema_only(YES);
  if ( LoadScript(file_list.GetHead()->get_bnf_data()->GetElement(0)) ) 
                                                     ERROR
  if ( resources->Validate() )                        ERROR
  resources->set_schema_only(NO);
  if ( LoadScript(file_list.GetHead()->get_bnf_data()->GetElement(0)) ) 
                                                     ERROR


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OScript - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OScript"

OScript :: ~OScript ( )
{
  OScriptFile       *sfile = NULL;

  database.Close();
  resdb.Close();
  dictionary.Close();

  delete oper_env;
  oper_env = NULL;
  


}


