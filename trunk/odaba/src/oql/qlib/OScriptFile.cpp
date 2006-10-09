/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OScriptFile

\brief    


\date     $Date: 2006/07/12 13:32:18,45 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OScriptFile"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sBNFParser.hpp>
#include  <sOScriptFile.hpp>


/******************************************************************************/
/**
\brief  OScriptFile - 



\param  script_path - 
\param  parser - 
\param  symbol - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OScriptFile"

     OScriptFile :: OScriptFile (char *script_path, BNFParser *parser, char *symbol )
                     : expression(NULL),
  bnf_data(NULL),
  path(NULL)
{

BEGINSEQ
  OQLEV1(script_path,UNDEF)
  path = strdup(script_path);
  if ( !FileRead(script_path,(void **)&expression) )     OQLERR(451)
    
  if ( !(bnf_data = parser->Analyze(expression,symbol,YES)) )
  {
    OQLError().TraceMessage("Parser error:\n",parser->GetLastError());
    parser->PrintError();
    OQLERR(378)
  }


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OScriptFile - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OScriptFile"

     OScriptFile :: ~OScriptFile ( )
{

  delete expression;
  expression = NULL;

  delete bnf_data;
  bnf_data = NULL;

  if ( path )
    free(path);
  path = NULL;

}


