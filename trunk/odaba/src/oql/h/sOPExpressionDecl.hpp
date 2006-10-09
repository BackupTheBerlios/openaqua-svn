/********************************* Class Declaration ***************************/
/**
\package  OQL - 
\class    OPExpressionDecl

\brief    


\date     $Date: 2006/07/17 20:44:28,87 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPExpressionDecl_HPP
#define   OPExpressionDecl_HPP

class     OPExpressionDecl;

class     ACObject;
class     BNFData;
class     Dictionary;
class     OPBase;
class     OPParmList;
class     OperEnvironment;
class     ParmList;
class     PropertyHandle;
#include  <cExecReturnCodes.h>
#include  <cOQL_CodeBlock.h>
#include  <sOPDecl.hpp>
class  OPExpressionDecl :public OPDecl
{
protected  :         logical                                      local_expr;                                                // 
protected  :         logical                                      has_errors;                                                // 

public     :
                     logical                                      get_local_expr() { return(local_expr); }
                     logical                                      get_has_errors() { return(has_errors); }
public     :                                        logical Call (PropertyHandle *co, ParmList *parmlist, int8 set_operation=NO );
public     :                                        logical Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation=NO );
public     :                                        logical Create (PropertyHandle *impl_ph );
public     :                                        logical CreateDecl (BNFData *bdata );
public     :                                        logical CreateParameter (BNFData *bdata );
public     :                                        logical CreateVars (BNFData *bdata );
public     :                                        logical DeInitVariables ( );
public     :                                        ExecReturnCodes Execute ( );
public     :                                        int8 GetBlockIndex (OQL_CodeBlock blktype=CB_undefined );
public     : virtual                                logical InitResult (PropertyHandle *co );
public     : virtual                                logical InitResult ( );
public     :                                        logical InitVariables ( );
public     : virtual                                logical Initialize (int32 ini_opt );
public     :                                             OPExpressionDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, char *expr_string, OperEnvironment *operenv_w=NULL );
public     :                                             OPExpressionDecl (OperEnvironment *operenv, PropertyHandle *co, BNFData *oper_bnf );
public     :                                             OPExpressionDecl (Dictionary *dictptr, ACObject *obhandle, PropertyHandle *co, PropertyHandle *impl_ph );
public     :                                             OPExpressionDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, BNFData *oper_bnf, OperEnvironment *operenv_w=NULL, char *expr_dup_w=NULL );
public     :                                             OPExpressionDecl (char *expr_name );
public     :                                        logical Open (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, char *expr_string, OperEnvironment *operenv_w=NULL );
public     :                                        logical Open (OperEnvironment *operenv, PropertyHandle *co, BNFData *oper_bnf );
public     :                                        logical Open (Dictionary *dictptr, ACObject *obhandle, PropertyHandle *co, PropertyHandle *impl_ph, OperEnvironment *operenv_w=NULL );
public     :                                        logical Open (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, BNFData *oper_bnf, OperEnvironment *operenv_w=NULL, char *expr_dup_w=NULL );
public     :                                             ~OPExpressionDecl ( );
};

#endif
