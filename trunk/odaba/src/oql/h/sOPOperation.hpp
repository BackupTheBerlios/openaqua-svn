/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPOperation

\brief    


\date     $Date: 2006/03/12 19:20:07,93 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPOperation_HPP
#define   OPOperation_HPP

class     OPOperation;

class     ACObject;
class     BNFData;
class     OPBase;
class     OPDecl;
class     OPOperation;
class     ParmList;
class     PropertyHandle;
#include  <cExecReturnCodes.h>
#include  <cFunctionTypes.h>
#include  <cOQL_CodeBlock.h>
#include  <cST_OpCodes.h>
#include  <sOPVariable.hpp>
class  OPOperation :public OPVariable
{
protected  :         FunctionTypes                                oper_type;                                                 //
protected  :         OPDecl                                      *operation;                                                 //
protected  :         logical                                      owner;                                                     //

public     :
                     FunctionTypes                                get_oper_type() { return(oper_type); }
                     OPDecl                                      *get_operation() { return(operation); }
                     logical                                      get_owner() { return(owner); }
public     :                                     OPDecl *CreateExpression ( );
public     :                                     OPDecl *CreateFunction ( );
public     :                                     logical CreateOPDecl (ST_OpCodes op_code );
public     :                                     logical CreateOperation (ST_OpCodes op_code );
public     :                                     OPDecl *CreatePHFunction ( );
public     :                                     OPDecl *CreateSysFunction ( );
public     :                                     ExecReturnCodes Execute ( );
public     :                                     int8 GetBlockIndex (OQL_CodeBlock blktype=CB_undefined );
public     :                                     logical Initialize (int32 ini_opt );
public     :                                                             OPOperation (DBStructDef *classref, FunctionTypes optype, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf );
public     :                                     void RemoveOperation ( );
public     :                                     logical SetupResult ( );
public     :                                     logical SetupSource ( );
public     :                                                             ~OPOperation ( );
};

#endif
