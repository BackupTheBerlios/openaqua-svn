/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPOperation

\brief    


\date     $Date: 2006/07/17 20:50:08,57 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPOperation"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <sOPBase.hpp>
#include  <sOPBinary.hpp>
#include  <sOPDecl.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOPFunctionDecl.hpp>
#include  <sOPOperation.hpp>
#include  <sOPOperationDecl.hpp>
#include  <sOPParmList.hpp>
#include  <sOPSynBlock.hpp>
#include  <sOPSynBreak.hpp>
#include  <sOPSynCase.hpp>
#include  <sOPSynContinue.hpp>
#include  <sOPSynError.hpp>
#include  <sOPSynIf.hpp>
#include  <sOPSynLeave.hpp>
#include  <sOPSynReturn.hpp>
#include  <sOPSynSwitch.hpp>
#include  <sOPSynWhile.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOPOperation.hpp>


/******************************************************************************/
/**
\brief  CreateExpression - 


\return oper_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExpression"

OPDecl *OPOperation :: CreateExpression ( )
{
  OPDecl           *fdecl;
  DBStructDef      *classref = class_ref;
  ParmList         *plist = NULL;
  logical           term = NO;
BEGINSEQ
  if ( !classref ) 
    classref = Scope();
    
  plist = Parmlist()->CreateParmlist();
  
  if ( classref )
  {
    if ( !(fdecl = classref->GetExprDecl(opname,&value,CO(),plist,NO,YES)) )
      fdecl = classref->GetExprDecl(opname,&value,CO(),plist,YES,YES);
  }
  else
    fdecl = DictHandle()->GetExpression(NULL,opname,plist);
  
  if ( !(operation = fdecl) )                       OQLERR(99)
  operation->InitResult(CO());
RECOVER
  delete plist;
  RemoveOperation();
  operation = NULL;
  term = YES;
ENDSEQ
  return(operation);
}

/******************************************************************************/
/**
\brief  CreateFunction - 


\return oper_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFunction"

OPDecl *OPOperation :: CreateFunction ( )
{
  OPFunctionDecl *fdecl;
  DBStructDef      *classref = class_ref;
  PropertyHandle    ph(CO());
  PropertyHandle   *co;
  ParmList         *plist = NULL;
  logical           term = NO;
BEGINSEQ
  if ( !classref ) 
    if ( !(classref = Scope()) )                     OQLSERR(99)
  
  co = ProvideCO(ph,DictHandle(),classref);
  
  plist = Parmlist()->CreateParmlist();
  if ( !(fdecl = classref->GetFctDecl(opname,&value,CO(),plist,NO,YES)) )
    fdecl = classref->GetFctDecl(opname,&value,CO(),plist,YES,YES);
  
  if ( !fdecl || (fdecl->Init(co,plist)) )           OQLSERR(160)

  operation = fdecl;
RECOVER
  delete plist;
  RemoveOperation();
  operation = NULL;
  term = YES;
ENDSEQ
  return(operation);
}

/******************************************************************************/
/**
\brief  CreateOPDecl - 


\return term - 

\param  op_code - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOPDecl"

logical OPOperation :: CreateOPDecl (ST_OpCodes op_code )
{
  DBFieldDef             *fielddef;
  logical                 term = NO;
BEGINSEQ
  if ( operation )
  {
    if ( !operation->IsVirtual() )                    LEAVESEQ
    RemoveOperation();
  }
    
  switch ( oper_type )
  {
    case FT_Function    : CreateFunction();
                          break;
    case FT_PHFunction  : CreatePHFunction();
                          break;
    case FT_SysFunction : CreateSysFunction();
                          break;
    case FT_Expression  : CreateExpression();
                          break;
    default             : ;
  }
  if ( !operation )                                  ERROR
  
  operation->CopyEnvironment(oper_env,NO);
  
  if ( fielddef = operation->GetDescription() )
  {
    SetDescription(fielddef);
    if ( !fielddef->fmcbstat && !fielddef->get_set_operation() )
      is_set_operand = NO;
  } 
  value.RegisterNode(operation->Value());
  OQLCERR
RECOVER
  RemoveOperation();
  operation = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateOperation - 


\return term - 

\param  op_code - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperation"

logical OPOperation :: CreateOperation (ST_OpCodes op_code )
{
  logical                 term = NO;
  operation = new OPOperationDecl(op_code,this);

  owner = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  CreatePHFunction - 


\return oper_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePHFunction"

OPDecl *OPOperation :: CreatePHFunction ( )
{
  OPFunctionDecl         *fdecl;
  ParmList               *plist = NULL;
  PropertyHandle          ph(CO());
  PropertyHandle         *co;
  logical                 term = NO;
BEGINSEQ
  plist = Parmlist()->CreateParmlist();
  co = ProvideCO(ph,DictHandle(),class_ref ? class_ref : Scope());
  if ( !(fdecl = DBStructDef::GetPHFctDecl(opname,GetValue(),
                                   co,plist)) )    OQLSERR(159)
  if ( fdecl->Init(co,plist) )                       OQLSERR(160)

  operation = fdecl;
  owner = YES;
RECOVER
  delete plist;
  RemoveOperation();
  operation = NULL;
  term = YES;
ENDSEQ
  return(operation);
}

/******************************************************************************/
/**
\brief  CreateSysFunction - 


\return oper_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSysFunction"

OPDecl *OPOperation :: CreateSysFunction ( )
{
  OPFunctionDecl         *fdecl;
  ParmList               *plist = NULL;
  logical                 term = NO;
BEGINSEQ
  plist = Parmlist()->CreateParmlist();
  if ( !(fdecl = DBStructDef::GetSysFctDecl(opname,GetValue(),plist)) )
                                                     OQLSERR(159)
  if ( fdecl->Init(NULL,plist) )                     OQLSERR(160)
  
  operation = fdecl;
  owner = YES;
RECOVER
  delete plist;
  RemoveOperation();
  operation = NULL;
  term = YES;
ENDSEQ
  return(operation);
}

/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPOperation :: Execute ( )
{
  ExecReturnCodes         rc = ERC_success;
  PropertyHandle         *co;
  logical                 term = NO;
BEGINSEQ
  if ( op_type != NT_OPOperation ) // binary or unary operation or access path
  {
    switch ( ExecuteSource() )
    {
      case ERC_terminate : ERROR
      case ERC_null      : rc = ERC_null;           LEAVESEQ
      default            : ;
    }
    co = source->GetValue();
  }
  else
    co = CO();
    
  switch ( ExecuteParameters(0) )
  {
    case ERC_terminate : ERROR
    case ERC_null      : rc = ERC_null;             LEAVESEQ
    default            : ;
  }
    
  if ( !(term = CheckCO()) )
    term = operation->CallDecl(oper_env,co,Parmlist(),is_set_operand);
  
  if ( term )
  {
    ResetValue();                                    ERROR
  }
  
  if ( operation->Value() )
    value.RegisterNode(operation->Value());
  else
  {
    term = YES;
    rc   = ERC_null;
  }

RECOVER
  rc = ERC_terminate;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  GetBlockIndex - 


\return indx0 - 

\param  blktype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBlockIndex"

int8 OPOperation :: GetBlockIndex (OQL_CodeBlock blktype )
{
  OPBase    *op_node;
  int32      indx0 = 0;
BEGINSEQ
  while ( op_node = Parmlist()->GetAt(indx0++) )
    if ( op_node->GetBlockType() == blktype )        LEAVESEQ

  ERROR
RECOVER
  indx0 = AUTO;
ENDSEQ
  return(indx0);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - 

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPOperation :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( oper_type == FT_undefined )       LEAVESEQ
              if ( SetupSource() )                   ERROR
              if ( SetupParameters() )               ERROR   
    case  4 : if ( CreateOPDecl(ST_undefined) )      ERROR
              SetupResult(); 
    default : re_open = 0;
              LEAVESEQ
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPOperation - 


\return term - 

\param  classref - 
\param  optype - 
\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPOperation"

     OPOperation :: OPOperation (DBStructDef *classref, FunctionTypes optype, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (classref,oper_bnf,parent_node,parm_bnf),
  oper_type(optype),
  operation(NULL),
  owner(NO)
{

  op_type = NT_OPOperation;
  
  Initialize(0);

}

/******************************************************************************/
/**
\brief  RemoveOperation - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveOperation"

void OPOperation :: RemoveOperation ( )
{

  if ( owner )
    delete operation;

  owner = NO;
  operation = NULL;

}

/******************************************************************************/
/**
\brief  SetupResult - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupResult"

logical OPOperation :: SetupResult ( )
{
  logical                 term = NO;
  if ( operation && !fldfmcb )
    SetDescription(operation->GetDescription());
  return(term);
}

/******************************************************************************/
/**
\brief  SetupSource - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSource"

logical OPOperation :: SetupSource ( )
{
  logical                 term = NO;
BEGINSEQ
  switch ( op_type )
  {
    // operand
    case NT_OPBinary    : if ( !(source = CreateUniOp(operand_bnf)) )   ERROR
                          break;
    case NT_OPUnary     : if ( !(source = CreateSimpleOp(operand_bnf)) )   ERROR
                          break;
    // pname
    case NT_OPOperation : source = parent;
                          SetOPName(operand_bnf->StringValue());    
                          break;
    default             : OQLSERR(99)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OPOperation - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPOperation"

     OPOperation :: ~OPOperation ( )
{

  RemoveOperation();


}


