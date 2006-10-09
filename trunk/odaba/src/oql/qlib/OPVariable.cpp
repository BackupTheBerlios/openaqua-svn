/********************************* Class Source Code ***************************/
/**
\package  OQL
\class    OPVariable



\date     $Date: 2006/05/26 17:15:48,20 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPVariable"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sDictionary.hpp>
#include  <sExpressionReference.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPVariable.hpp>
#include  <sOperEnvironment.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSchemaResources.hpp>
#include  <snode.hpp>
#include  <sOPVariable.hpp>


/******************************************************************************/
/**
\brief  Execute

\return exec_rc

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPVariable :: Execute ( )
{
  ExecReturnCodes           rc = ERC_success;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( source )
    value.RegisterNode(source->Value());
  
  Get();


RECOVER
  rc = ERC_terminate;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  ExecuteParameter

\return exec_rc

\param  indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteParameter"

ExecReturnCodes OPVariable :: ExecuteParameter (int32 indx0 )
{
  OPBase                 *op_node;
  PropertyHandle         *co = NULL;
  ExecReturnCodes         rc = ERC_undefined;
  SaveCO();
  
  if ( op_node = Parmlist()->GetAt(indx0) )
    if ( (rc = op_node->Execute()) == ERC_null )
      rc = Environment()->GetNullValueERC();

  RestoreCO();
  return(rc);
}

/******************************************************************************/
/**
\brief  ExecuteParameters

\return exec_rc

\param  indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteParameters"

ExecReturnCodes OPVariable :: ExecuteParameters (int32 indx0 )
{
  OPBase                 *op_node;
  PropertyHandle         *co = NULL;
  ExecReturnCodes         rc = ERC_success;
  int32                   parm_cnt = 0;
BEGINSEQ
  SaveCO();
  
  while ( op_node = Parmlist()->GetAt(indx0++) )
  {
    if ( (rc = op_node->Execute()) == ERC_null )
      rc = Environment()->GetNullValueERC();
    switch ( rc )
    {
      case ERC_terminate :                         ERROR
      case ERC_null      :                         
      case ERC_success   :                         break;
      default            : LEAVESEQ
    }
    parm_cnt++;
  }
RECOVER
  rc = ERC_terminate;
ENDSEQ
  RestoreCO();
  return(rc);
}

/******************************************************************************/
/**
\brief  ExecuteSource

\return exec_rc

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteSource"

ExecReturnCodes OPVariable :: ExecuteSource ( )
{

  return ( source ? ExecuteTrace(source) : ERC_terminate );


}

/******************************************************************************/
/**
\brief  ExecuteStatement

\return exec_rc

\param  indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteStatement"

ExecReturnCodes OPVariable :: ExecuteStatement (int32 indx0 )
{
  OPBase                 *op_node;
  ExecReturnCodes         rc = ERC_undefined;
  if ( op_node = Parmlist()->GetAt(indx0) )
//  if ( (rc = op_node->Execute()) == ERC_success )
  {
    if ( rc == ERC_null )
      rc = ERC_success;
      
    if ( (rc = ExecuteTrace(op_node)) == ERC_success )
      SetLastValue(op_node->Value());  
  }
  return(rc);
}

/******************************************************************************/
/**
\brief  ExecuteStatements

\return exec_rc

\param  indx0
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteStatements"

ExecReturnCodes OPVariable :: ExecuteStatements (int32 indx0 )
{
  OPBase                 *op_node;
  ExecReturnCodes         rc = ERC_success;

BEGINSEQ
  while ( op_node = Parmlist()->GetAt(indx0++) )
    switch ( rc = ExecuteTrace(op_node) )
    {
      case ERC_success   : SetLastValue(op_node->Value()); 
                                                     break;
      case ERC_null      : rc = ERC_success;         break;
      case ERC_break     :
      case ERC_leave     :
      case ERC_error     :
      case ERC_return    : LEAVESEQ
      case ERC_terminate : ERROR      
      default            : break;
    }
RECOVER
  rc = ERC_terminate;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  Get

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical OPVariable :: Get ( )
{
  ExecReturnCodes           rc = ERC_success;
  logical                   term = NO;
BEGINSEQ
  value.Execute(NULL);
  
  if ( !value.IsCollection() )
    if ( !value.Get(AUTO) )         
      if ( !value.Get(FIRST_INSTANCE) )            ERROR

  on_top = NO;                                     
  

RECOVER
  on_top = YES;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetVariable

\return vnode

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVariable"

OPVariable *OPVariable :: GetVariable ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  IsSetOperand

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSetOperand"

logical OPVariable :: IsSetOperand ( )
{

  return(is_set_operand);

}

/******************************************************************************/
/**
\brief  Next

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical OPVariable :: Next ( )
{
  logical       term = NO;
BEGINSEQ
  if ( !value.IsCollection() )
  {
    if ( !on_top )
    {  
      value.Cancel();
      on_top = YES;
      ERROR
    }
    if ( on_top = Get() )                            ERROR
  }
  else
    if ( on_top = value.Position(1) )                ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPVariable

\return term

\param  classref
\param  oper_bnf
\param  parent_node
\param  parm_bnf
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPVariable"

     OPVariable :: OPVariable (DBStructDef *classref, BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPBase (oper_bnf,parent_node),
  parm_bnf(parm_bnf),
  default_parm(NO),
  last_type_id(0),
  last_instid(0),
  on_top(NO),
  is_set_operand(AUTO),
  local_scope(NO)
{

  if ( !classref && parent_node )
    classref = parent_node->LocalScope();
  
  if ( classref )
    class_ref = classref;
  


}

/******************************************************************************/
/**
\brief  Previous

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Previous"

logical OPVariable :: Previous ( )
{
  logical       term = NO;
BEGINSEQ
  if ( !value.IsCollection() )
  {
    if ( !on_top )
    {  
      value.Cancel();
      on_top = YES;
      ERROR
    }
    if ( on_top = Get() )                            ERROR
  }
  else
    if ( on_top = value.Position(-1) )               ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetValue


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetValue"

void OPVariable :: ResetValue ( )
{
  // do not close value for Variable
}

/******************************************************************************/
/**
\brief  RestoreCO


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreCO"

void OPVariable :: RestoreCO ( )
{

  if ( parent->LocalScope() )
  {
    PushCO(&save_co);
    save_co.Close();
  }

}

/******************************************************************************/
/**
\brief  SaveCO


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveCO"

void OPVariable :: SaveCO ( )
{

  if ( parent->LocalScope() )
  {
    save_co.Open(CO());
    PopCO();
  }

}

/******************************************************************************/
/**
\brief  SetupFieldDef

\return fielddef - Internal field defintion

\param  bdata
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupFieldDef"

DBFieldDef *OPVariable :: SetupFieldDef (BNFData *bdata )
{
  DBFieldDef         *fielddef = NULL;
  DictionaryHandle    dict(DictHandle());
BEGINSEQ
  fielddef = new DBFieldDef();
  if ( Schema()->LoadParmSpec(fielddef,bdata) )      ERROR
RECOVER
  delete fielddef;
  fielddef = NULL;
ENDSEQ
  return(fielddef);
}

/******************************************************************************/
/**
\brief  SetupParameters

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupParameters"

logical OPVariable :: SetupParameters ( )
{
  BNFData                *bparms;
  BNFData                *parm_ext;
  BNFData                *parm_data;
  OPBase                 *op_node;
  int32                   index = 0;
  DBStructDef            *classref = class_ref;
  logical                 term = NO;
BEGINSEQ
  SaveCO();
  
  if ( parent->ResetScope() )
    class_ref = parent->GetScope();
    
  if ( !parm_bnf )                                   LEAVESEQ

  Parmlist()->ClearList();
  if ( !(bparms = ((BNFExpData *)parm_bnf)->GetParmList()) )  // operand in bin_op
  { 
    if ( !parm_bnf->IsSymbol("operand") )            OQLERR(99)
    if ( !(op_node = SetupParmHandle(parm_bnf)) )    ERROR
    Parmlist()->Add(op_node);
  }
  else
  { 
    if ( !bparms->GetElementCount() )                // empty parmlist
    {
      if ( !value.IsCollection() )
      parm_bnf = NULL;                               LEAVESEQ
    }
    
    index = 0;
    parm_data = bparms->GetElement(index);           // parameter
    while ( parm_data )
    {
      if ( !(op_node = SetupParmHandle(parm_data)) ) ERROR
      Parmlist()->Add(op_node);
      parm_data = NULL;
      if ( parm_ext = bparms->GetElement(++index) )  // param_ext
        parm_data = parm_ext->GetElement(1);         // , parameter
    }
  }

RECOVER
  term = YES;
ENDSEQ
  RestoreCO();
  class_ref = classref;
  return(term);
}

/******************************************************************************/
/**
\brief  SetupParmHandle

\return op_node

\param  bparms
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupParmHandle"

OPBase *OPVariable :: SetupParmHandle (BNFData *bparms )
{
  DBFieldDef             *fielddef  = NULL;
  Dictionary             *dictptr   = DictHandle();
  OPBase                 *parm_node = NULL;
  logical                 term = NO;
BEGINSEQ
  switch ( bparms->GetSymbolCode("*","parm_spec","operand") )
  {
    case 1 : default_parm = YES;                     break;
    case 2 : if ( !(fielddef = SetupFieldDef(bparms->GetSymbol("parm_spec"))) )
                                                     ERROR
             bparms = parm_bnf = fielddef->get_initval_expr()->GetBNFData(dictptr);
    case 3 : parm_node = CreateOperand(bparms);
  }

RECOVER
  parm_node = NULL;
ENDSEQ
  return(parm_node);
}

/******************************************************************************/
/**
\brief  ToTop

\return term

\param  recursive
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToTop"

logical OPVariable :: ToTop (logical recursive )
{

  on_top = YES;
  return ( value.ToTop() );

}

/******************************************************************************/
/**
\brief  ~OPVariable

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPVariable"

     OPVariable :: ~OPVariable ( )
{



}


