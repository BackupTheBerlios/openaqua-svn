/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ExpressionReference

\brief    


\date     $Date: 2006/03/12 19:17:33,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExpressionReference"

#include  <popa7.h>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sOPBase.hpp>
#include  <sOPDecl.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sExpressionReference.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code

\param  retval_ref -
\param  co -
\param  variables -
\param  parameters -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ExpressionReference :: Execute (PropertyHandle &retval_ref, PropertyHandle *co, ParmList *variables, ParmList *parameters )
{
  char                    wstr[1025];
  char                    key[1025];
  logical                 term = NO;
  if ( expr_decl )
    expr_decl->Call(co,(ParmList *)NULL,NO);

  return(term);
}

/******************************************************************************/
/**
\brief  ExpressionReference - 


-------------------------------------------------------------------------------
\brief i0


\param  struct_def - Pointer to generel structure definition
\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExpressionReference"

                        ExpressionReference :: ExpressionReference (DBStructDef *struct_def, char *expression )
                     : string(NULL),
  bnf(NULL),
  expr_decl(NULL),
  type(ADT_undefined),
  structure(struct_def),
  oper_env(NULL)

{

  SetExpression(expression);



}

/******************************************************************************/
/**
\brief i01


\param  exprref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExpressionReference"

                        ExpressionReference :: ExpressionReference (ExpressionReference &exprref )
                     :   string(NULL),
  bnf(exprref.bnf),
  expr_decl(NULL),
  type(exprref.type),
  structure(exprref.structure),
  oper_env(NULL)
{

  if ( exprref.string )
    string = strdup(exprref.string);

// bnf ??

}

/******************************************************************************/
/**
\brief i02


\param  struct_def - Pointer to generel structure definition
\param  expr_bnf -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExpressionReference"

                        ExpressionReference :: ExpressionReference (DBStructDef *struct_def, BNFData *expr_bnf )
                     : string(NULL),
  bnf(expr_bnf),
  expr_decl(NULL),
  type(ADT_undefined),
  structure(struct_def)
{



}

/******************************************************************************/
/**
\brief  GetBNFData - 


\return bnf_data -

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBNFData"

BNFData *ExpressionReference :: GetBNFData (Dictionary *dictptr )
{

BEGINSEQ
  if ( !this )                                       ERROR
  if ( bnf )                                         LEAVESEQ
  if ( !dictptr || !string || !*string )             ERROR

  if ( !(bnf = dictptr->ParseExpression(string,"operand",NULL)) )
                                                     ERROR

RECOVER
  delete bnf;
  bnf = NULL;
ENDSEQ
  return( this ? bnf : NULL);
}

/******************************************************************************/
/**
\brief  GetExpressionDecl - 


\return expr_decl

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpressionDecl"

OPDecl *ExpressionReference :: GetExpressionDecl (Dictionary *dictptr )
{

BEGINSEQ
  if ( !this )                                       ERROR
  if ( expr_decl )                                   LEAVESEQ

  if ( !dictptr || !string )                         ERROR
  if ( !bnf && !GetBNFData(dictptr) )                ERROR
    
  expr_decl = dictptr->ProvExpression(NULL,structure->smcbname,bnf,NULL,NULL,oper_env);
  

RECOVER

ENDSEQ
  return( this ? expr_decl : NULL);
}

/******************************************************************************/
/**
\brief  GetResultDescription - 


\return dbfield_def -

\param  dictptr - Dictionary handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResultDescription"

DBFieldDef *ExpressionReference :: GetResultDescription (Dictionary *dictptr )
{
  int32          offset;
  DBFieldDef    *dbfield_def = NULL;
BEGINSEQ
  if ( !this || !structure || !string )              ERROR
    
  if ( type == ADT_undefined )
    if ( !GetBNFData(dictptr) )                      ERROR
      
  if ( type == ADT_PropertyPath )    
    dbfield_def = structure->SearchField(string,&offset,NULL)->GetDescription();
RECOVER

ENDSEQ
  return(dbfield_def);
}

/******************************************************************************/
/**
\brief  GetString - 


\return expr_string -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *ExpressionReference :: GetString ( )
{

  return ( this ? string : NULL );

}

/******************************************************************************/
/**
\brief  ReleaseExpression - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseExpression"

void ExpressionReference :: ReleaseExpression ( )
{

  delete expr_decl;
  expr_decl = NULL;
  
  if ( string )
  {
    free(string);
    delete bnf;
  }
  string = NULL;
  bnf = NULL;


}

/******************************************************************************/
/**
\brief  SetExpression - 



\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExpression"

void ExpressionReference :: SetExpression (char *expression )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( expression )
  {
    ReleaseExpression();
    string = strdup(expression);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetOperEnvironment - 



\param  operenv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOperEnvironment"

void ExpressionReference :: SetOperEnvironment (OperEnvironment *operenv )
{

BEGINSEQ
  if ( operenv == oper_env )                         LEAVESEQ
    
  delete expr_decl;
  expr_decl = NULL;

  oper_env = operenv;
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetStructDef - 



\param  struct_def - Pointer to generel structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStructDef"

void ExpressionReference :: SetStructDef (DBStructDef *struct_def )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  structure = struct_def;
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~ExpressionReference - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ExpressionReference"

                        ExpressionReference :: ~ExpressionReference ( )
{

  ReleaseExpression();


}


