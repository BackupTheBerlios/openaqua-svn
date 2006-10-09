/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPExpressionDecl

\brief    


\date     $Date: 2006/07/28 12:09:42,53 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPExpressionDecl"

#include  <poql.h>
#include  <dlincl.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDLInterpreter.hpp>
#include  <sDictionary.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPVariableSpec.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSchemaResources.hpp>
#include  <sOPExpressionDecl.hpp>


/******************************************************************************/
/**
\brief  Call - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  co - 
\param  parmlist - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPExpressionDecl :: Call (PropertyHandle *co, ParmList *parmlist, int8 set_operation )
{
  logical     intern_opt = IsIntern();
  logical     term       = NO;
BEGINSEQ
  SetupEnvironment();
  if ( !co ) 
    co = CO();
  PushCO(co);
  
  Initialize(AUTO);
  if ( has_errors )                                  ERROR
  
  if ( !intern_opt )
  {
    InitParameters(parmlist);
    InitVariables();
  }
  
  term = CallIntern2(co,set_operation);

  if ( debugger )
    debugger->SetPreviousExpression(this);
  
  if ( !intern_opt )
  {
    DeInitVariables();
    DeInitParameters();
  }
  

RECOVER
  term = YES;
ENDSEQ
  PopCO();
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  co - 
\param  call_parms - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPExpressionDecl :: Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation )
{
  logical     intern_opt = IsIntern();
  logical     term       = NO;
BEGINSEQ
  SetupEnvironment();
  if ( !co ) 
    co = CO();
  PushCO(co);
  
  Initialize(AUTO);
  if ( has_errors )                                  ERROR
  
  if ( !intern_opt )
  {
    InitParameters(call_parms);
    InitVariables();
  }
  
  term = CallIntern2(co,set_operation);

  if ( !intern_opt )
  {
    DeInitVariables();
    DeInitParameters();
  }

RECOVER
  term = YES;
ENDSEQ
  PopCO();
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 



\return term - 

\param  impl_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical OPExpressionDecl :: Create (PropertyHandle *impl_ph )
{

BEGINSEQ
statistics1.Start();
  if ( impl_ph )
  {
    if ( OPDecl::CreateDecl(impl_ph) )               ERROR
  }
  else
    if ( CreateDecl(operand_bnf->GetElement("meth_dcl")) )
                                                     OQLSERR(145)

  re_open = 10;    // init once
RECOVER
  has_errors = YES;
ENDSEQ
statistics1.Stop();
  return(has_errors);
}

/******************************************************************************/
/**
\brief  CreateDecl - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDecl"

logical OPExpressionDecl :: CreateDecl (BNFData *bdata )
{
  DictionaryHandle        dictionary(DictHandle());
  int32                   index = 0;
  BNFData                *parmspc;
  BNFData                *parm_suc;
  logical                 term = NO;
BEGINSEQ
// meth_dcl := [oneway] mtype_ref [ref_symbol(*)] meth_ident parameter_dcls [raises_expr] [context_expr]

  if ( !bdata )
  {
    SetOPName("__inline_expression__");              LEAVESEQ
  }
  
  while ( !bdata->GetElement(index)->IsSymbol("mtype_ref") )
    index++;
    
  if ( Schema()->LoadMethodDcl(ProvideDescription(),bdata,index) )
                                                     ERROR
  SetOPName(fldfmcb->fmcbname);
  if ( fldfmcb )
    value.Open(GetDescription(),NULL);
  if ( !class_ref && !CO()->IsValid() )
    fldfmcb->fmcbstat = YES;

  Parmlist()->Clear();
  if ( parmspc = bdata->GetElement("parameter_dcls") )
  {
    Parameters()->ClearList();
    
    if ( parmspc = parmspc->GetElement("params_dcl") )
    {
      index = 0;
      CreateParameter(parmspc->GetElement(index));
      while ( parm_suc = parmspc->GetElement(++index) )
        CreateParameter(parm_suc->GetElement(1));
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateParameter - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateParameter"

logical OPExpressionDecl :: CreateParameter (BNFData *bdata )
{
  PropertyHandle         ph;
  OPBase                 *op_node;
  logical                 term = NO;
BEGINSEQ
// param_dcl := [param_attribute] simple_type_spec declarator

  if ( !(op_node = CreateMember(bdata->GetElement("simple_type_spec"),
                           bdata->GetElement("declarator")       )) )
                                                     ERROR
  Parameters()->Add(op_node);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateVars - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateVars"

logical OPExpressionDecl :: CreateVars (BNFData *bdata )
{
  BNFData                *member;
  int32                   index = 1;
  logical                 term = NO;
BEGINSEQ
// var_defs := _variables [ member(*) ]
// member   := [_global] type_spec declarators ';'

  if ( !bdata )                                      LEAVESEQ
    
  Variables()->ClearList();
  
  while ( member = bdata->GetElement(index++) )
    CreateVariable(member,NO);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeInitVariables - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeInitVariables"

logical OPExpressionDecl :: DeInitVariables ( )
{
  int32                   indx0 = 0;
  OPBase                 *op_node;
  logical                 term = NO;
  while ( op_node = Variables()->GetAt(indx0++) )
    op_node->Initialize(11); // de-initialize variable specification
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 



\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPExpressionDecl :: Execute ( )
{
  ExecReturnCodes      rc = ERC_success;
  OPBase              *op_node;
  int32                indx0 = 0;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( Value() )
    value = "";  
  SetLastValue(Value());
  
  while ( indx0 >= 0 && (op_node = Parmlist()->GetAt(indx0++)) )
  {
    switch ( rc = ExecuteTrace(op_node) )
    {
      case ERC_success   : break;
      case ERC_error     : if ( (indx0 = GetBlockIndex(CB_ErrorBlock)) == AUTO )
                             indx0 = GetBlockIndex(CB_FinalBlock);
                           break;
      case ERC_leave     : indx0 = GetBlockIndex(CB_FinalBlock);
                           break;
      case ERC_return    : indx0 = AUTO;
                           break;
      case ERC_terminate : if ( (indx0 = GetBlockIndex(CB_ErrorBlock)) != AUTO )
                             rc = ERC_success;
                           else
                             ERROR
                           break;
      default : ;
    }
    if ( fldfmcb )
    {
      if ( !CheckSourceValue(LastValue()) )    
        SetValue(LastValue());
    }
    else
      value.RegisterNode(local_expr ? op_node->Value() : LastValue());
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

int8 OPExpressionDecl :: GetBlockIndex (OQL_CodeBlock blktype )
{
  OPBase    *op_node;
  int32      indx0 = 0;
BEGINSEQ
  while ( op_node = Parmlist()->GetAt(indx0++) )
    if ( op_node->GetBlockType() == blktype )        LEAVESEQ

  ERROR
RECOVER
  indx0 = 0;
ENDSEQ
  return(indx0-1);
}

/******************************************************************************/
/**
\brief  InitResult - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  co - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical OPExpressionDecl :: InitResult (PropertyHandle *co )
{

  return(InitResult());

}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical OPExpressionDecl :: InitResult ( )
{

  return( GetValue()->Open(GetDescription(),NULL) );

}

/******************************************************************************/
/**
\brief  InitVariables - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitVariables"

logical OPExpressionDecl :: InitVariables ( )
{
  int32                   indx0 = 0;
  OPBase                 *op_node;
  logical                 term = NO;
  while ( op_node = Variables()->GetAt(indx0++) )
    op_node->Initialize(10); // init variable specification
  return(term);
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

logical OPExpressionDecl :: Initialize (int32 ini_opt )
{
  BNFData                *code;
  logical                 term = NO;
BEGINSEQ
statistics0.Start();
  SetReopen(ini_opt);
  if ( re_open < 10 || has_errors )                  LEAVESEQ
  re_open = 0;
  
  if ( !(code = operand_bnf->GetElement("proc_code")) )
  {
    if ( !(code = operand_bnf->GetSymbol("operand")) )
                                                     OQLERR(145)
    local_expr = YES;
  }
      
  if ( CreateVars(operand_bnf->GetElement("var_defs"))                   || 
       ProvideBlock(operand_bnf->GetElement("init_code"),CB_IniBlock)    ||
       ProvideBlock(code,CB_ProcessBlock)                                ||
       ProvideBlock(operand_bnf->GetElement("error_code"),CB_ErrorBlock) ||
       ProvideBlock(operand_bnf->GetElement("final_code"),CB_FinalBlock)    )
                                                     OQLERR(145)


RECOVER
  has_errors = YES;
ENDSEQ
statistics0.Stop();
  return(has_errors);
}

/******************************************************************************/
/**
\brief  OPExpressionDecl - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dictptr - 
\param  resobj - 
\param  obhandle - 
\param  scope_str - 
\param  co - 
\param  expr_string - 
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPExpressionDecl"

     OPExpressionDecl :: OPExpressionDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, char *expr_string, OperEnvironment *operenv_w )
                     : OPDecl (NULL),
  local_expr(NO),
  has_errors(NO)
{

BEGINSEQ
  op_type = NT_OPExpressionDecl;
  
  if ( Open(dictptr,resobj,obhandle,scope_str,co,expr_string,operenv_w) )
                                                     ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  operenv - 
\param  co - 
\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPExpressionDecl"

     OPExpressionDecl :: OPExpressionDecl (OperEnvironment *operenv, PropertyHandle *co, BNFData *oper_bnf )
                     : OPDecl (NULL),
  local_expr(NO),
  has_errors(NO)
{

BEGINSEQ
  op_type = NT_OPExpressionDecl;

  if ( Open(operenv,co,oper_bnf) )                   ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i02 - 



\param  dictptr - 
\param  obhandle - 
\param  co - 
\param  impl_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPExpressionDecl"

     OPExpressionDecl :: OPExpressionDecl (Dictionary *dictptr, ACObject *obhandle, PropertyHandle *co, PropertyHandle *impl_ph )
                     : OPDecl (NULL),
  local_expr(NO),
  has_errors(NO)
{

BEGINSEQ
  op_type = NT_OPExpressionDecl;

  if ( Open(dictptr,obhandle,co,impl_ph) )           ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03 - 



\param  dictptr - 
\param  resobj - 
\param  obhandle - 
\param  scope_str - 
\param  co - 
\param  oper_bnf - 
\param  operenv_w - 
\param  expr_dup_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPExpressionDecl"

     OPExpressionDecl :: OPExpressionDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, BNFData *oper_bnf, OperEnvironment *operenv_w, char *expr_dup_w )
                     : OPDecl (NULL),
  local_expr(NO),
  has_errors(NO)
{
  logical           term = NO;
BEGINSEQ
  op_type = NT_OPExpressionDecl;

  if ( Open(dictptr,resobj,obhandle,scope_str,co,oper_bnf,operenv_w,expr_dup_w) )
                                                     ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04 - 



\param  expr_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPExpressionDecl"

     OPExpressionDecl :: OPExpressionDecl (char *expr_name )
                     : OPDecl (NULL),
  local_expr(NO),
  has_errors(NO)
{

  op_type = NT_OPExpressionDecl;
  SetOPName(expr_name);

}

/******************************************************************************/
/**
\brief  Open - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dictptr - 
\param  resobj - 
\param  obhandle - 
\param  scope_str - 
\param  co - 
\param  expr_string - 
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical OPExpressionDecl :: Open (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, char *expr_string, OperEnvironment *operenv_w )
{
  logical           term = NO;
BEGINSEQ
  OQLRESET
  
  if ( !expr_string )                                OQLSERR(99)
  if ( CreateEnvironment(dictptr,resobj,scope_str,NULL,obhandle,co,this) )
                                                     ERROR
  if ( operenv_w )
    CopyEnvironment(operenv_w,YES);
    
  if ( !(operand_bnf = oper_env->SetExpression(strdup(expr_string),NULL)) )
                                                     ERROR
  Set_OPName(oper_env->get_expression());
  
  class_ref = scope_str;
  if ( Create(NULL) )                                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  operenv - 
\param  co - 
\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical OPExpressionDecl :: Open (OperEnvironment *operenv, PropertyHandle *co, BNFData *oper_bnf )
{
  logical           term = NO;
BEGINSEQ
  op_type = NT_OPExpressionDecl;

  OQLRESET
  if ( CreateEnvironment(NULL,NULL,NULL,oper_bnf,NULL,co,this) )
                                                     ERROR
  CopyEnvironment(operenv,YES);
  operand_bnf = oper_bnf;
  class_ref = Scope();
  if ( Create(NULL) )                                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  dictptr - 
\param  obhandle - 
\param  co - 
\param  impl_ph - 
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical OPExpressionDecl :: Open (Dictionary *dictptr, ACObject *obhandle, PropertyHandle *co, PropertyHandle *impl_ph, OperEnvironment *operenv_w )
{
  DBStructDef          *scope    = NULL;
  PropertyHandle       *class_ph = NULL;
  logical               term     = NO;
BEGINSEQ
  op_type = NT_OPExpressionDecl;

  OQLRESET
  if ( !impl_ph )                                    OQLSERR(99)
  
  if ( class_ph = impl_ph->GetParentProperty()->GetParentProperty() )
    scope = dictptr->ProvideStructDef(class_ph->GPH("sys_ident")->GetString());
  
  class_ref = scope;
  if ( CreateEnvironment(dictptr,impl_ph->GetObjectHandle().get_obhandle(),
                         scope,NULL,obhandle,co,this) )
                                                     ERROR
  if ( operenv_w )
    CopyEnvironment(operenv_w,NO);
  
  if ( !(operand_bnf = oper_env->CreateExpression(impl_ph)) )
                                                     ERROR
  if ( Create(impl_ph) )                             ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  dictptr - 
\param  resobj - 
\param  obhandle - 
\param  scope_str - 
\param  co - 
\param  oper_bnf - 
\param  operenv_w - 
\param  expr_dup_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical OPExpressionDecl :: Open (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, BNFData *oper_bnf, OperEnvironment *operenv_w, char *expr_dup_w )
{
  logical           term = NO;
BEGINSEQ
  op_type = NT_OPExpressionDecl;

  OQLRESET
  
  if ( expr_dup_w )
    Set_OPName(expr_dup_w);
    
  if ( CreateEnvironment(dictptr,resobj,scope_str,oper_bnf,obhandle,co,this,expr_dup_w) )
                                                     ERROR
  if ( operenv_w )
    CopyEnvironment(operenv_w,YES);
    
  if ( !(operand_bnf = oper_bnf) )                   OQLSERR(99)
  class_ref = scope_str;
  if ( Create(NULL) )                                ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OPExpressionDecl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPExpressionDecl"

     OPExpressionDecl :: ~OPExpressionDecl ( )
{
  Dictionary            *dictptr;
  if ( opname )
    if ( dictptr = DictHandle() )
      dictptr->RemoveExpression(this,Scope());


}


