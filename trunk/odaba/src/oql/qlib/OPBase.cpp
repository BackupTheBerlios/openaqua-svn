/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPBase

\brief    Base for operation nodes
          When  creating  an  operation  node  the  expression  is  sntactically
          analyzed.  As long as a calling  object whith a valid field definition
          is  passed, the system  resolves further references.  When this is not
          possible, references are resolved later.

\date     $Date: 2006/08/28 12:38:02,57 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPBase"

#include  <poql.h>
#include  <dlincl.h>
#include  <iopbase.h>
#include  <oqlglob.h>
#include  <cDebugModi.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sDBreakPoint.hpp>
#include  <sDLInterpreter.hpp>
#include  <sDictionary.hpp>
#include  <sOqlExtentList.hpp>
#include  <sFieldSource.hpp>
#include  <sNodeStack.hpp>
#include  <sOPAccessPath.hpp>
#include  <sOPBase.hpp>
#include  <sOPBaseCollection.hpp>
#include  <sOPBinary.hpp>
#include  <sOPConstant.hpp>
#include  <sOPDecl.hpp>
#include  <sOPExtent.hpp>
#include  <sOPFunctionDecl.hpp>
#include  <sOPGlobalVariable.hpp>
#include  <sOPLocalVariable.hpp>
#include  <sOPOperation.hpp>
#include  <sOPParameter.hpp>
#include  <sOPParmList.hpp>
#include  <sOPProperty.hpp>
#include  <sOPSynBlock.hpp>
#include  <sOPSynBreak.hpp>
#include  <sOPSynCase.hpp>
#include  <sOPSynContinue.hpp>
#include  <sOPSynError.hpp>
#include  <sOPSynExceptHandling.hpp>
#include  <sOPSynException.hpp>
#include  <sOPSynFor.hpp>
#include  <sOPSynIf.hpp>
#include  <sOPSynLeave.hpp>
#include  <sOPSynNVHandling.hpp>
#include  <sOPSynReturn.hpp>
#include  <sOPSynSwitch.hpp>
#include  <sOPSynWhile.hpp>
#include  <sOPSystemVariable.hpp>
#include  <sOPUnary.hpp>
#include  <sOPVariable.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sSchemaResources.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sOPBase.hpp>


/******************************************************************************/
/**
\brief  AddParameter - 



\return term - 

\param  parent_node - 
\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddParameter"

logical OPBase :: AddParameter (OPBase *parent_node, DBFieldDef *fielddef )
{
  OPBase                 *op_node = NULL;
  FieldSource            *srce_def;
  BNFData                *expr_bnf;
  logical                 term = NO;
BEGINSEQ
  if ( !(srce_def = fielddef->GetSource(0)) ||
       !(expr_bnf = srce_def->GetBNFData(DictHandle())) )
                                                     OQLERR(99)
  if ( !(op_node = CreateOperandNode(parent_node,expr_bnf)) )
                                                     ERROR
  op_node->GetValue()->Close();
  op_node->SetDescription(fielddef);
  parmlist->Add(op_node);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AllocDescription - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocDescription"

void OPBase :: AllocDescription ( )
{

  if ( !fldfaloc )
    fldfmcb = NULL;
    
  if ( !fldfmcb )
  {
    fldfmcb = new DBFieldDef();
    fldfaloc = YES;
  }


}

/******************************************************************************/
/**
\brief  i01 - 



\param  fldtypes - 
\param  fldityp - 
\param  fldsize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocDescription"

void OPBase :: AllocDescription (char *fldtypes, int16 fldityp, uint32 fldsize )
{
  DBFieldDef     *dbflddef    = NULL;
  int32           intpos      = 0;
  int32           extpos      = 0;
  int32           netpos      = 0;
  int8            max_aligned = 1;
  SetDescription(NULL);

  dbflddef = new DBFieldDef(fldtypes,fldtypes,0,RL_direct,fldsize,0,1,NULL,UNDEF,NO,NULL,NULL,NULL);
  dbflddef->fmcbityp = fldityp;
  dbflddef->SetupAttribute(intpos,extpos,netpos,1,max_aligned);  
  
  fldfmcb  = dbflddef;
  fldfaloc = YES;


}

/******************************************************************************/
/**
\brief  CO - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CO"

PropertyHandle *OPBase :: CO ( )
{

  return(oper_env ? oper_env->CO() : NULL);

}

/******************************************************************************/
/**
\brief  Call - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  co - 
\param  call_parms - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPBase :: Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  co - 
\param  parm_list - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPBase :: Call (PropertyHandle *co, ParmList *parm_list, int8 set_operation )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  CheckCO - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckCO"

logical OPBase :: CheckCO ( )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(oper_env->GetReopen(&last_co));
  last_co.CopyHandle(CO());
  if ( Initialize(0) )                               ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckSourceValue - 



\return term - 

\param  source_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckSourceValue"

logical OPBase :: CheckSourceValue (node *source_node )
{
  DBFieldDef        *fielddef     = GetDescription();
  DBFieldDef        *source_field = NULL;
  logical            term         = NO;
BEGINSEQ
  if ( fielddef->IsNoField() )                       LEAVESEQ
  if ( !source_node )                                OQLSERR(99)
  
  source_field = source_node->GetFieldDef();  
  if ( !(source_node  = source_node->GetNode()) )    ERROR
  
  if ( fielddef->get_by_reference() )
  {
    if ( !source_node->Inherits(fielddef->fmcbtype) )OQLSERR(153)
    if ( !fielddef->CanReference(source_field) )
    { 
      if ( fielddef->fmcbdim != 1 )                  OQLSERR(154)
      if ( !source_node->IsSelected() )
      {
        source_node->AutoLocate(NO);
        if ( !source_node->IsSelected() )            ERROR
      }
    }
  }
  else 
    if ( CheckValue(source_node) )                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckType - 



\return term - 

\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckType"

logical OPBase :: CheckType (DBFieldDef *fielddef )
{
  DBFieldDef             *proto_field;
  DBStructDef            *strdef;
  node                   *nodeptr = Value();
  logical                 basic_type = NO;
  logical                 term = NO;
BEGINSEQ
  inherits = AUTO;
  conversion = AUTO;
  
  if ( !proto_type || !fldfmcb )                     LEAVESEQ
  proto_field = GetDescription();
    
  if ( !fielddef )
  {
    if ( !nodeptr )                                  LEAVESEQ
    if ( !(fielddef = nodeptr->GetFieldDef()) )
                                                     LEAVESEQ
  }

  if ( strdef = fielddef->GetDBStruct(DictHandle()) )
    if ( strdef->IsBasedOn(proto_field->fmcbtype) ||
         !memcmp(proto_field->fmcbtype,strdef->smcbname,ID_SIZE) )
      inherits = YES;
  if ( fielddef->fmcbbase() )
    basic_type = YES;
    
  if ( proto_field->get_by_reference() )
  {
    if ( !inherits )                                 OQLSERR(149)
  }
  else 
    conversion = basic_type || !inherits;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckValue - 



\return term - 

\param  source_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValue"

logical OPBase :: CheckValue (node *source_node )
{
  DBFieldDef        *fielddef     = GetDescription();
  logical            term         = NO;
BEGINSEQ
  if ( !fielddef->get_by_reference() )
  { 
    if ( fielddef->fmcbdim != 1 && source_node->IsCollection() )  // collection
    {
      if ( !source_node->Inherits(fielddef->fmcbtype) ) 
                                                     OQLSERR(154)
      LEAVESEQ
    }
    else if ( !source_node->IsSelected() )
    {
      source_node->AutoLocate(NO);
      if ( !source_node->IsSelected() )              ERROR
    }
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyEnvironment - 




\param  operenv - 
\param  intern_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyEnvironment"

void OPBase :: CopyEnvironment (OperEnvironment *operenv, logical intern_opt )
{

  if ( oper_env && env_owner )
    oper_env->Copy(operenv,intern_opt);

}

/******************************************************************************/
/**
\brief  CreateBStatement - 



\return op_node - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBStatement"

OPBase *OPBase :: CreateBStatement (BNFData *bdata )
{
  OPBase                 *op_node = NULL;
  BNFData                *bstmt;
  logical                 term = NO;
BEGINSEQ
// bstatement   := block | statement
  
  bstmt = bdata->GetElement(0);
  switch ( bstmt->GetSymbolCode("statement","block") )
  {
    case 1 : op_node = CreateStatement(bstmt);
             break;
    case 2 : if ( !(op_node = new OPSynBlock(bstmt,this,CB_undefined)) )
             break;
    default : ;
  }
  OQLCERR
RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateBinOp - 



\return expr_node - 

\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBinOp"

OPBase *OPBase :: CreateBinOp (BNFData *oper_bnf )
{
  OPBase         *op_node = NULL;
BEGINSEQ
// operand     := un_operation bin_operand   
// bin_operand := bin_op operand  

  oper_bnf = oper_bnf->GetSymbol("operand");
  op_node = new OPBinary(oper_bnf,this);
  
  OQLCERR
  
  op_node = ((OPBinary *)op_node)->OrderOperands();

RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateBlock - 



\return op_node - 

\param  bdata - 
\param  blktype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBlock"

OPBase *OPBase :: CreateBlock (BNFData *bdata, OQL_CodeBlock blktype )
{
  OPBase                 *op_node = NULL;
BEGINSEQ
// ???_code   := [_???] statement(*)  
// block      := '{' statements(*) '}'
// case_stmt  := _case simple_op ':' statement(*)
// other_stmt := _default ':' statement(*)
  
  op_node = new OPSynBlock(bdata,this,blktype);      OQLCERR
RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateCase - 



\return op_node - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCase"

OPBase *OPBase :: CreateCase (BNFData *bdata )
{
  OPBase                 *op_node = NULL;

BEGINSEQ
// case_stmt   := [debug_opt] _case simple_op ':' statement(*)

  op_node = new OPSynCase(bdata,this);               OQLCERR

RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateDOperand - 



\return op_node - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDOperand"

OPBase *OPBase :: CreateDOperand (BNFData *bdata )
{
  BNFData                *boper;
  logical                 debug_opt = NO;
  OPBase                 *op_node = NULL;
BEGINSEQ
// dopernad      := [debug_opt] operand
  
  if ( bdata->GetElement(0)->IsSymbol("debug_opt") )
  {
    debug_opt = YES;
    boper = bdata->GetElement(1);
  }
  else
    boper = bdata->GetElement(0);
    
  if ( !(op_node = CreateOperand(boper)) )            ERROR
  
  if ( debug_opt )
    op_node->SetBreakPoint(bdata->GetElement(0));

RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateEnvironment - 



\return term - 

\param  dictionary - 
\param  resobj - 
\param  scope_str - 
\param  bdata - 
\param  obhandle - 
\param  co - 
\param  op_decl - 
\param  expr_dup_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEnvironment"

logical OPBase :: CreateEnvironment (Dictionary *dictionary, ACObject *resobj, DBStructDef *scope_str, BNFData *bdata, ACObject *obhandle, PropertyHandle *co, OPDecl *op_decl, char *expr_dup_w )
{
  logical                 term = NO;
// when passing bdata and expression, the both become resource of
// the environment. Expression string and bdata must belong together!!

  oper_env = new OperEnvironment(dictionary,resobj,scope_str,
                                 bdata,obhandle,co,op_decl,expr_dup_w);
  env_owner = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  CreateGlobalVariable - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGlobalVariable"

logical OPBase :: CreateGlobalVariable ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( DictHandle()->GetGlobalVariable(GetDescription()->fmcbname) )
                                                     LEAVESEQ
  Execute();      // init value
  
  PropertyHandle     ph(Value());
  DictHandle()->CreateGlobalVariable(ph,NULL);

  Value()->fldfalos(YES);      // wir geben der global variable die Description
  fldfaloc = NO;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateNode - 



\return op_node - 

\param  source_type - 
\param  optype - 
\param  parent_node - 
\param  clsname - 
\param  oper_bnf - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

OPBase *__cdecl OPBase :: CreateNode (ADT_Types source_type, FunctionTypes optype, OPBase *parent_node, char *clsname, BNFData *oper_bnf, BNFData *parm_bnf )
{
  OPBase         *op_node  = NULL;
  switch ( source_type )
  {
    case ADT_Operation     :
    case ADT_InstOperation :
    case ADT_SetOperation  :
    case ADT_MetaOperation :
    case ADT_undefined     : op_node = CreateOperationNode(optype,parent_node,
                                                           clsname,oper_bnf,parm_bnf);
                             break;
    default                : op_node = CreateOperandNode(source_type,parent_node,
                                                      clsname,oper_bnf,parm_bnf);
                             break;
  }


  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateOperand - 



\return op_node - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperand"

OPBase *OPBase :: CreateOperand (BNFData *bdata )
{
  OPBase                 *op_node = NULL;
  logical                 term = NO;
BEGINSEQ
// operand      := un_operation [ bin_operand ]  
// un_operation := ...
 
  if ( bdata->IsA("un_operation") )
    op_node = CreateUniOp(bdata); 
  else
  {
    bdata = bdata->GetSymbol("operand");
    switch ( bdata->GetElementCount() )
    {
      case 1 : op_node = CreateUniOp(bdata);
               break;
      case 2 : op_node = CreateBinOp(bdata);
               break;
      default: OQLSERR(99)
    }
  }
  OQLCERR
RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateOperandNode - 



\return op_node - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  parent_node - 
\param  srce_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperandNode"

OPBase *__cdecl OPBase :: CreateOperandNode (OPBase *parent_node, BNFData *srce_def )
{
  ADT_Types       source_type = ADT_undefined;
  char            clsname[ID_SIZE+1];
  BNFData        *oper_bnf = NULL;
  BNFData        *parm_bnf = NULL;
  OPBase         *op_node  = NULL;
BEGINSEQ
  oper_bnf = srce_def;
  *clsname = 0;
  
  if ( srce_def->IsSymbol("path_element") )
  {
    if ( !(op_node = CreatePathElementNode(parent_node,
                               srce_def->GetSymbol("path_element"),clsname)) )
                                                     ERROR
  }
  else if ( !srce_def->IsSymbol("simple_op") && !srce_def->IsSymbol("access_path") )
  {
    if ( srce_def->IsSymbol("operand") )
      op_node = parent_node->CreateOperand(srce_def);
    else
      source_type = ADT_Expression;
  }
  else 
  {
    oper_bnf = srce_def;
    if ( srce_def->IsSymbol("simple_op") )
      oper_bnf = srce_def = srce_def->GetSymbol("simple_op")->GetElement(0);
    switch ( srce_def->GetSymbolCode("OQLStatement","access_path","block",
                                     "sngl_operand","std_constant","sys_variable") )
    {
      case 1 : 
      case 2 : if ( !(op_node = CreateOperationNode(FT_Property,parent_node,
                                                    clsname,oper_bnf,NULL)) )
                                                     ERROR
                                                     break;
      case 3 : source_type = ADT_Expression;         break;
      case 4 : if ( !(op_node = CreateOperandNode(parent_node,
                                      srce_def->GetElement("operand"))) )
                                                     ERROR
               op_node->SetMaxPriority();
                                                     break;
      case 5 : source_type = ADT_Constant;           break;
      case 6 : source_type = ADT_SystemVariable;     break;
    }
  }
  if ( !op_node )   
    op_node = CreateNode(source_type,FT_undefined,parent_node,clsname,oper_bnf,parm_bnf);
  
  if ( !op_node )                                    ERROR

RECOVER
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  source_type - 
\param  parent_node - 
\param  clsname - 
\param  oper_bnf - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperandNode"

OPBase *__cdecl OPBase :: CreateOperandNode (ADT_Types source_type, OPBase *parent_node, char *clsname, BNFData *oper_bnf, BNFData *parm_bnf )
{
  OPBase         *op_node  = NULL;
BEGINSEQ
  switch ( source_type )
  {
    case ADT_Constant       : op_node = new OPConstant(oper_bnf,parent_node);
                              break;
    case ADT_SystemVariable : op_node = new OPSystemVariable(oper_bnf,parent_node);
                              break;
    case ADT_BaseCollection : op_node = new OPBaseCollection(oper_bnf,parent_node,
                                                    parm_bnf);
                              break;
    case ADT_AccessPath     : op_node = new OPAccessPath(NULL,oper_bnf,parent_node,parm_bnf,0,NO);
                              break;
    case ADT_Operation      : op_node = CreateOperationNode(FT_undefined,parent_node,
                                                    clsname,oper_bnf,parm_bnf);
                              break;
    default                 : OQLERR(99)
  }

      

RECOVER
  op_node  = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateOperationNode - 



\return op_node - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  op_type - 
\param  parent_node - 
\param  clsname - 
\param  oper_bnf - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperationNode"

OPBase *__cdecl OPBase :: CreateOperationNode (FunctionTypes op_type, OPBase *parent_node, char *clsname, BNFData *oper_bnf, BNFData *parm_bnf )
{
  Dictionary         *dictionary = parent_node->DictHandle();
  PropertyHandle     *co         = parent_node->CO();
  DBStructDef        *classref   = GetParentType(parent_node,clsname);
  DBStructDef        *class_ref  = NULL;
  char               *op_name    = NULL;
  OPBase             *op_node    = NULL;
BEGINSEQ
  if ( *clsname )
  {
    if ( !classref )                                ERROR
    class_ref = classref;
  }

  if ( op_type == FT_undefined && (op_name = oper_bnf->StringValue()) )
  {
    if ( parent_node )
    {
      if ( parent_node->Variables()->Get(op_name) ) 
        op_type = FT_Variable;
      else if ( parent_node->Parameters()->Get(op_name) )
        op_type = FT_Parameter;
    }
    
    if ( op_type == FT_undefined ) 
      op_type = GetOperationType(parent_node->Environment(),classref,op_name);
  
    if ( op_type == FT_undefined )
      op_type = IsPHFunction(parent_node->DictHandle(),classref,co,op_name);
  }
  
  if ( op_type == FT_error || op_type == FT_undefined ) // verhindert spätere Auflösung von Membern in weak/untyped references 
    parent_node->ShowError(109,OBJ_ID,MOD_ID,oper_bnf);  
  op_node = CreateOperationNode(op_type,parent_node,class_ref,oper_bnf,parm_bnf);
RECOVER
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  op_type - 
\param  parent_node - 
\param  class_ref - 
\param  oper_bnf - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateOperationNode"

OPBase *__cdecl OPBase :: CreateOperationNode (FunctionTypes op_type, OPBase *parent_node, DBStructDef *class_ref, BNFData *oper_bnf, BNFData *parm_bnf )
{
  OPBase        *op_node = NULL;
BEGINSEQ
  switch ( op_type )
  {
    case FT_Variable         : op_node = new OPLocalVariable(oper_bnf,parent_node,parm_bnf);
                               break;
    case FT_Parameter        : op_node = new OPParameter(oper_bnf,parent_node,parm_bnf);
                               break;
    case FT_Global           : op_node = new OPGlobalVariable(oper_bnf,parent_node,parm_bnf);
                               break;
    case FT_Extent           : 
    case FT_Enumeration      : 
    case FT_Property         : op_node = new OPProperty(class_ref,oper_bnf,parent_node,parm_bnf);
                               break;
    case FT_Function         : 
    case FT_Expression       : 
    case FT_PHFunction       : 
    case FT_SysFunction      : op_node = new OPOperation(class_ref,op_type,oper_bnf,parent_node,parm_bnf);
                               break;
    
    case FT_Action           : // term = InitAction(dictionary);                               // break;
                               parent_node->ShowError(109,OBJ_ID,MOD_ID,oper_bnf);
    case FT_undefined        : LEAVESEQ
    default                  : ;
  }
  OQLCERR
RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreatePathElementNode - 



\return op_node - 

\param  parent_node - 
\param  srce_def - 
\param  clsname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathElementNode"

OPBase *__cdecl OPBase :: CreatePathElementNode (OPBase *parent_node, BNFData *srce_def, char *clsname )
{
  ADT_Types       source_type = ADT_undefined;
  FunctionTypes   optype      = FT_undefined;
  BNFData        *oper_bnf = NULL;
  BNFData        *parm_bnf = NULL;
  OPBase         *op_node  = NULL;
  int8            path_opt;
  int32           autopos;
BEGINSEQ
  oper_bnf = srce_def;
  
  source_type = ADT_AccessPath;
  if ( srce_def->IsSymbol("path_element") )
  {
    oper_bnf = srce_def->GetElement("path_operand");
    if ( !srce_def->IsSymbol("path_operand") )
      parm_bnf = srce_def->GetElement("operand_list");
    switch ( oper_bnf->GetSymbolCode("coll_operand","expr_code","path_name") )
    {
      case 1 : oper_bnf = oper_bnf->GetElement("access_path");
               op_node = CreateOperationNode(FT_Property,parent_node,clsname,oper_bnf,parm_bnf);
                                                   break;
      case 2 : op_node = CreateOperationNode(FT_Expression,parent_node,clsname,oper_bnf,parm_bnf); 
                                                   break;
      case 3 : // path_name
        if ( ((BNFExpData *)srce_def)->GetPathElement(parent_node->DictHandle(),srce_def, 
                             GetParentType(parent_node,clsname),parent_node->oper_env,optype,path_opt,autopos,NULL) )
        {
          op_node = CreateOperationNode(optype,parent_node,clsname,srce_def,NULL);
                                                   break;
        }
        if ( !oper_bnf->IsSymbol("pname") )
          parm_bnf = oper_bnf->GetElement("index_name"); 
        oper_bnf = oper_bnf->GetElement("pname");
        source_type = ADT_Operation;
        switch ( oper_bnf->GetSymbolCode("oql_oper","scoped_name","any_type","db_name") )
        {
          case 1 : // OQL operation
            source_type = ADT_SetOperation;
            switch ( oper_bnf->GetSymbolCode("_minus","_union","_intersect","_group_by") )
            {
              case 2 : optype = FT_OQLMinus;       break;
              case 3 : optype = FT_OQLUnion;       break;
              case 4 : optype = FT_OQLIntersect;   break;
              case 5 : optype = FT_OQLGroupBy;     break;
              default:
                source_type = ADT_InstOperation;
                switch ( oper_bnf->GetSymbolCode("_select","_use","_from","_tofile","_todb","_join") )
                {
                  case 1 : optype = FT_OQLSelect;      break;
                  case 2 : optype = FT_OQLUse;         break;
                  case 3 : optype = FT_OQLFrom;        break;
                  case 4 : optype = FT_OQLToFile;      break;
                  case 5 : optype = FT_OQLToDB;        break;
                  case 6 : optype = FT_OQLJoin;        break;
                  default:
                    source_type = ADT_MetaOperation;
                    switch ( oper_bnf->GetSymbolCode("_where","_having","_order_by") )
                    {
                      case 1 : 
                      case 2 : optype = FT_OQLWhere;       break;
                      case 3 : optype = FT_OQLOrderBy;     break;
                    }
                }
            }
            break;
          case 2 : // scoped name
            oper_bnf = oper_bnf->GetSymbol("scoped_name");
            if ( !oper_bnf->IsSymbol("identifier") )
            {
              gvtxbts(clsname,oper_bnf->GetElement("identifier")->StringValue(),ID_SIZE);
              oper_bnf = oper_bnf->GetElement(oper_bnf->GetElementCount()-1)->GetElement(1);
              break;
            }
            if ( srce_def->IsValue("_BASE_COLLECTION") )
              source_type = ADT_BaseCollection;
          case 3 : // VOID or ANY (all instances)
          case 4 : // data base name starting with '#', e.g. for overlay extent
            break;
         }
    }
  }

  if ( !op_node )   
    op_node = CreateNode(source_type,optype,parent_node,clsname,oper_bnf,parm_bnf);
  if ( !op_node )                                    ERROR

RECOVER
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateSimpleOp - 



\return op_node - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSimpleOp"

OPBase *OPBase :: CreateSimpleOp (BNFData *bdata )
{
  OPBase                 *op_node = NULL;
BEGINSEQ
  if ( !(op_node = CreateOperandNode(this,bdata)) )  ERROR

RECOVER
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateStatement - 



\return op_node - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatement"

OPBase *OPBase :: CreateStatement (BNFData *bdata )
{
  OPBase                 *op_node = NULL;
  BNFData                *bstmt;
  logical                 debug_opt = NO;
  logical                 term = NO;
BEGINSEQ
// statement      := [debug_opt] istatement
// istatement     := basic_stmt | if_block | case_block | while_block | for_block | syntax_op | ';'
// basic_stmt     := stmt_operlist ';' 
// stmt_operlist  := doperand [stoplist_ext(*)] 
// syntax_op      := return_op | error_op | leave_op | continue_op | break_op | exception_op
  OQLRESET
  
  if ( bdata->GetElement(0)->IsSymbol("debug_opt") )
  {
    debug_opt = YES;
    bstmt = bdata->GetElement(1)->GetElement(0);
  }
  else
    bstmt = bdata->GetElement(0)->GetElement(0);
    
  switch ( bstmt->GetSymbolCode("basic_stmt","if_block","case_block",
                                "while_block","for_block","syntax_op") )
  {
    case 1 : op_node = CreateStatementOpList(bstmt->GetElement(0));
             break;
    case 2 : op_node = new OPSynIf(bstmt,this);
             break;
    case 3 : op_node = new OPSynSwitch(bstmt,this);
             break;
    case 4 : op_node = new OPSynWhile(bstmt,this);
             break;
    case 5 : op_node = new OPSynFor(bstmt,this);
             break;
    case 6 : bstmt = bstmt->GetElement(0);
             switch ( bstmt->GetSymbolCode("return_op","error_op",
                                "leave_op","continue_op","break_op","exception_op", 
                                "nv_op", "eh_op") )
             {
               case 1 : op_node = new OPSynReturn(this,bstmt->GetElement(1));
                        break;
               case 2 : op_node = new OPSynError(this,bstmt->GetElement(1));
                        break;
               case 3 : op_node = new OPSynLeave(this);
                        break;
               case 4 : op_node = new OPSynContinue(this);
                        break;
               case 5 : op_node = new OPSynBreak(this);
                        break;
               case 6 : op_node = new OPSynException(this,bstmt->GetElement(1));
                        break;
               case 7 : op_node = new OPSynNVHandling(this,bstmt->GetElement(1));
                        break;
               case 8 : op_node = new OPSynExceptHandling(this,bstmt->GetElement(1));
                        break;
             }
             break;
    default: op_node = NULL;             // ';'
  }
  OQLCERR
  
  if ( op_node && debug_opt )
    op_node->SetBreakPoint(bdata->GetElement(0));

RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateStatementOpList - 



\return op_node - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatementOpList"

OPBase *OPBase :: CreateStatementOpList (BNFData *bdata )
{
  OPBase                 *op_node;
  logical                 term = NO;
// stmt_operlist     := doperand [stoplist_ext(*)] 
// stoplist_ext      := ',' doperand
// foperand          := [debug_opt] doperand
  
  op_node = bdata->IsSymbol("doperand")
            ? CreateDOperand(bdata->GetElement(0))
            : new OPSynBlock(bdata,this);

  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateUniOp - 



\return expr_node - 

\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateUniOp"

OPBase *OPBase :: CreateUniOp (BNFData *oper_bnf )
{
  OPBase             *op_node = NULL;
BEGINSEQ
// un_operation  := [un_oper] simple_op 
  
  oper_bnf = oper_bnf->GetSymbol("un_operation");
  if ( oper_bnf->GetElement(0)->IsSymbol("un_oper") )
    op_node = new OPUnary(oper_bnf,this);
  else
    op_node = CreateSimpleOp(oper_bnf->GetSymbol("simple_op"));
  
  OQLCERR

RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  Declaration - 



\return op_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Declaration"

OPDecl *OPBase :: Declaration ( )
{

  return ( this && oper_env ? oper_env->get_declaration() : NULL);

}

/******************************************************************************/
/**
\brief  DictHandle - 



\return dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DictHandle"

Dictionary *OPBase :: DictHandle ( )
{

  return ( this && oper_env ? oper_env->DictHandle() : NULL);

}

/******************************************************************************/
/**
\brief  Environment - 



\return operenv - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Environment"

OperEnvironment *OPBase :: Environment ( )
{

  return( this ? oper_env : NULL );

}

/******************************************************************************/
/**
\brief  Execute - Execute operation



\return exec_rc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPBase :: Execute ( )
{

  return(ERC_success);

}

/******************************************************************************/
/**
\brief  ExecuteTrace - 



\return exec_rc - 

\param  op_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteTrace"

ExecReturnCodes OPBase :: ExecuteTrace (OPBase *op_node )
{
  char                  *svar;
  NString                nstring("application");
  ODABAClient            client;
  OPDecl                *opdecl;
  ExecReturnCodes        rc = ERC_success;
SOSTRY 
{
  if ( debug == AUTO )
    InitDebug(NULL);
      
  if ( debugger )
    rc = debugger->Debug(op_node);
  else
    op_node->TraceCalls(rc = op_node->Execute());
  if ( rc == ERC_null )
    rc = Environment()->GetNullValueERC();
}
SOSCATCH
{
  rc = ERC_terminate;
  nstring = "system";
}
  if ( rc == ERC_terminate )
    rc = Environment()->GetExceptionERC();
  if ( rc == ERC_terminate )          // abnormal termination
  {
    nstring += " exception";
    if ( opdecl = GetExpressionDecl() )
    {
      nstring += " in";
      nstring += ' ';
      if ( *opdecl->get_type_name() > ' ' )
      {
        nstring.Append(opdecl->get_type_name(),ID_SIZE);
        nstring += "::";
      }
      nstring += opdecl->get_opname();
      if ( *opdecl->get_impl_name() > ' ' )
      {
        nstring += '(';
        nstring.Append(opdecl->get_impl_name(),8);
        nstring += ')';
      }
    }
    nstring += "\n  at line:";
    nstring += ' ';
    nstring += op_node->GetCurrentLine();
    
    if ( debugger ) 
    {
      nstring += "\n";
      debugger->Output(nstring);
      if ( debugger->get_mode() != DM_terminate )
        debugger->SetMode(DM_step_in);
      rc = debugger->Debug(op_node);
      if ( rc == ERC_terminate )
        debugger->SetMode(DM_terminate);
    }
    else 
      OQLError().OutputMessage("OQL","Info",nstring);
  }

  return(rc);
}

/******************************************************************************/
/**
\brief  Get - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical OPBase :: Get ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  GetAutoRun - 



\return name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAutoRun"

char *OPBase :: GetAutoRun ( )
{

  return ( this && debug_break 
           ? debug_break->get_auto_proc() 
           : NULL);

}

/******************************************************************************/
/**
\brief  GetBlockType - 



\return blktype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBlockType"

OQL_CodeBlock OPBase :: GetBlockType ( )
{

  return(CB_undefined);

}

/******************************************************************************/
/**
\brief  GetCurrentLine - 



\return string - String area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentLine"

char *OPBase :: GetCurrentLine ( )
{

  if ( this && operand_bnf ) return (operand_bnf->GetCurrentLine());
  else return  "";

}

/******************************************************************************/
/**
\brief  GetDescription - 



\return fielddef - Internal field defintion

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDescription"

DBFieldDef *OPBase :: GetDescription ( )
{

  return((DBFieldDef *)fldfmcb);

}

/******************************************************************************/
/**
\brief  GetExpression - 



\return string - String area

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpression"

char *OPBase :: GetExpression ( )
{

  return ( oper_env ? oper_env->GetExpression() : NULL );

}

/******************************************************************************/
/**
\brief  GetExpressionDecl - 



\return expr_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpressionDecl"

OPDecl *OPBase :: GetExpressionDecl ( )
{

  return ( oper_env ? oper_env->GetExpressionDecl() : NULL );

}

/******************************************************************************/
/**
\brief  GetExtentList - 



\return ext_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentList"

OqlExtentList *OPBase :: GetExtentList ( )
{

  return( oper_env->GetExtentList() );

}

/******************************************************************************/
/**
\brief  GetFieldDef - 



\return fielddef - Internal field defintion

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldDef"

DBFieldDef *OPBase :: GetFieldDef ( )
{

  return(GetDescription());

}

/******************************************************************************/
/**
\brief  GetOPNode - 



\return op_node - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOPNode"

OPBase *OPBase :: GetOPNode ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetOperationType - 



\return optype - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  operenv - 
\param  classref - 
\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOperationType"

FunctionTypes __cdecl OPBase :: GetOperationType (OperEnvironment *operenv, DBStructDef *classref, char *opname )
{
  DBObjectHandle      obh(operenv->ResOBHandle());
  PropertyHandle      class_ph;  
  FunctionTypes       op_type = FT_undefined;
  logical             term    = NO;
BEGINSEQ
  if ( classref )
  {
    op_type = GetOperationType(operenv,opname,classref);         
      
    if ( op_type == FT_error )                       ERROR
    if ( op_type != FT_undefined )                   LEAVESEQ
  }
  // static
    
  if ( (op_type = IsGlobalVariable(operenv->DictHandle(),opname)) == FT_Global )
                                                     LEAVESEQ
  if ( (op_type = IsGlobalExpression(operenv->DictHandle(),opname)) == FT_Expression )
                                                     LEAVESEQ
  if ( (op_type = IsSysFunction(opname)) == FT_SysFunction )  // System-Function
                                                     LEAVESEQ
  if ( (op_type = IsEnumeration(operenv->DictHandle(),opname)) == FT_Enumeration)
                                                     LEAVESEQ
  if ( (op_type = IsExtent(operenv->DictHandle(),opname)) == FT_Extent)
                                                     LEAVESEQ

RECOVER
  op_type = FT_error;
ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  operenv - 
\param  opname - 
\param  classref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOperationType"

FunctionTypes __cdecl OPBase :: GetOperationType (OperEnvironment *operenv, char *opname, DBStructDef *classref )
{
  FunctionTypes       op_type = FT_undefined;
  DBStructDef        *strdef  = classref;
  int                 indx0   = 0;
BEGINSEQ
  if ( !classref )                                   ERROR
  if ( !classref->smcbityp )
    if ( !operenv->DictHandle()->GetStructDef(classref->smcbname) )
                                                     ERROR
  if ( classref->IsUndefinedMember(opname) )         LEAVESEQ
  
  if ( (op_type = IsProperty(classref,opname)) == FT_Property )
                                                     LEAVESEQ
  if ( (op_type = IsFunction(operenv->DictHandle(),operenv->ResOBHandle(),opname,classref)) == FT_Function )
                                                     LEAVESEQ
  if ( (op_type = IsExpression(operenv,opname,classref)) == FT_Expression )
                                                     LEAVESEQ
  if ( (op_type = IsAction(opname,classref)) == FT_Action )
                                                     LEAVESEQ
    
  for ( indx0 = 1; indx0 <= classref->get_base_info().get_count() && op_type == FT_undefined; indx0++ )
  {
    classref = DBStructDef::GetDBStruct(classref->GetEntry(indx0)->fmcbsmcb);
    op_type = GetOperationType(operenv,opname,classref);         
  }

  if ( op_type == FT_undefined || op_type == FT_error )
    strdef->AddUndefinedMember(opname);

RECOVER
  op_type = FT_error;
ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  GetParentType - 



\return dbstrdef - 

\param  parent_node - 
\param  clsname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParentType"

DBStructDef *__cdecl OPBase :: GetParentType (OPBase *parent_node, char *clsname )
{
  Dictionary         *dictionary = parent_node->DictHandle();
  PropertyHandle     *co         = parent_node->CO();
  DBStructDef        *classref   = NULL;

BEGINSEQ
  if ( *clsname )
    if ( !(classref = dictionary->ProvideStructDef(clsname)) )  // scoped name
                                                     ERROR
//  if ( co && !classref )
//    classref = co->GetCurrentTypeDef();             // temporary scope for element
  if ( !classref )
    if ( !(classref = parent_node->LocalScope()) )    // not passed as temporary scope; 
      classref = parent_node->Scope();                                


RECOVER
  classref = NULL;
ENDSEQ
  return(classref);
}

/******************************************************************************/
/**
\brief  GetParmDescription - 



\return fielddef - Internal field defintion

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmDescription"

DBFieldDef *OPBase :: GetParmDescription (int32 indx0 )
{
  OPBase      *op_node;
  return ( this && (op_node = parmlist->GetAt(indx0))
           ? op_node->GetDescription()
           : NULL                        );

}

/******************************************************************************/
/**
\brief  GetParmValue - 



\return ph - 

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmValue"

PropertyHandle *OPBase :: GetParmValue (int32 indx0 )
{
  OPBase      *op_node;
  return ( this && (op_node = parmlist->GetAt(indx0))
           ? op_node->GetValue()
           : NULL                        );

}

/******************************************************************************/
/**
\brief  GetParmlist - 



\return parmlist - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmlist"

ParmList *OPBase :: GetParmlist ( )
{
  ParmList               *parmlist = NULL;

  return(parmlist);
}

/******************************************************************************/
/**
\brief  GetPreviousOPDecl - 



\return expr_decl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPreviousOPDecl"

OPDecl *OPBase :: GetPreviousOPDecl ( )
{

  return ( oper_env ? oper_env->GetPreviousOPDecl() : NULL );

}

/******************************************************************************/
/**
\brief  GetPriority - 



\return priority - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPriority"

int16 OPBase :: GetPriority ( )
{


  return(999);
}

/******************************************************************************/
/**
\brief  GetPropertyHandle - 



\return ph - 

\param  prop_path - Property path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle OPBase :: GetPropertyHandle (char *prop_path )
{
  char                   *pos;
  char                   *pos2 = NULL;
  char                   *pos3 = NULL;
  char                    name[ID_SIZE+1];
  char                   *path = NULL;
  OPBase                 *op_node;
  logical                 is_member = NO;
  PropertyHandle          prophdl;
  PropertyHandle         *ph = NULL;
BEGINSEQ
  memset(name,0,sizeof(name));
  
  if ( prop_path )
  {
    if ( pos = strchr(prop_path,'.') )
    {
      *pos = 0;
      if ( pos2 = strchr(prop_path,'(') )
        *pos2 = 0;
      if ( pos3 = strchr(prop_path,'[') )
        *pos3 = 0;
      strncpy(name,prop_path,ID_SIZE); 
      if ( pos3 )
        *pos3= '[';
      if ( pos2 )
        *pos2= '(';
      *pos = '.';
      path = pos+1;
    }
    else
      strncpy(name,prop_path,ID_SIZE);
    
    if ( op_node = Parameters()->Get(name) )
      ph = op_node->GetValue();
    else if ( op_node = Variables()->Get(name) )
      ph = op_node->GetValue();
    else if ( IsProperty(CO()->GetStructDef(),name) )
      is_member = YES;
    else
      ph = DictHandle()->GetGlobalVariable(name);
      
    if ( ph )
    {
      if ( pos2 || pos3 )                            ERROR
      if ( path )
        prophdl.Open(ph,path);
      else
        prophdl.CopyHandle(ph);
    }
    else if ( is_member )
      prophdl.Open(CO(),prop_path);
  }
  else
    prophdl.CopyHandle(CO());

RECOVER
  prophdl.Close();
ENDSEQ
  return(&prophdl);
}

/******************************************************************************/
/**
\brief  GetReopen - 



\return init_val - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReopen"

int16 OPBase :: GetReopen ( )
{

  return ( oper_env ? oper_env->GetReopen(NULL) : 0 );

}

/******************************************************************************/
/**
\brief  GetScope - 



\return struct_def - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetScope"

DBStructDef *OPBase :: GetScope ( )
{

  return ( oper_env ? oper_env->get_scope() : NULL );

}

/******************************************************************************/
/**
\brief  GetValue - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValue"

PropertyHandle *OPBase :: GetValue ( )
{

  return(&value);

}

/******************************************************************************/
/**
\brief  GetVariable - 



\return vnode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVariable"

OPVariable *OPBase :: GetVariable ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  InitDebug - 




\param  proc_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDebug"

void __cdecl OPBase :: InitDebug (char *proc_path )
{
  char                  *svar;
  ODABAClient            client;
  ExecReturnCodes        rc = ERC_success;
  if ( debug == AUTO )
    if ( !debugger )
      if ( svar = GetSysVariable("OSI_DEBUG") )
      {
        if ( debug = *svar == 'Y' || *svar == 'y' )
          debugger = new DLInterpreter(client);
      }
      else
        debug = NO;
        
  if ( debugger )
  {
    debug = YES;
    if ( proc_path )
      debugger->LoadProcedure(proc_path);
  }


}

/******************************************************************************/
/**
\brief  InitDescription - 




\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDescription"

void OPBase :: InitDescription (DBFieldDef *fielddef )
{

  AllocDescription();
  
  if ( fielddef )
    GetDescription()->CopyDescription(*fielddef);


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

logical OPBase :: InitResult (PropertyHandle *co )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical OPBase :: InitResult ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  InitSource - 



\return op_node - 

\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSource"

OPBase *OPBase :: InitSource (BNFData *oper_bnf )
{

  return( source = CreateOperandNode(this,oper_bnf) );
                                                     


}

/******************************************************************************/
/**
\brief  InitValue - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitValue"

logical OPBase :: InitValue ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( Value() )                                     LEAVESEQ
  
  GetValue()->Open(GetDescription(),NULL); 

ENDSEQ
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

logical OPBase :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
  re_open = 0;
  return(term);
}

/******************************************************************************/
/**
\brief  IsAction - 



\return fttype - 

\param  opname - 
\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAction"

FunctionTypes __cdecl OPBase :: IsAction (char *opname, smcb *smcbptr )
{
  FunctionTypes       op_type = FT_undefined;
BEGINSEQ
  if ( strlen(opname) > ID_SIZE )                   LEAVESEQ
    
  LEAVESEQ // kommst später
  op_type = FT_Action;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsDebug - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDebug"

logical OPBase :: IsDebug ( )
{


  return(debug_break != NULL);
}

/******************************************************************************/
/**
\brief  IsEnumeration - 



\return fttype - 

\param  dictionary - 
\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumeration"

FunctionTypes __cdecl OPBase :: IsEnumeration (Dictionary *dictionary, char *opname )
{
  DBExtend           *dbext;
  FunctionTypes       op_type = FT_undefined;
BEGINSEQ
  if ( strlen(opname) > ID_SIZE )                    LEAVESEQ
    
  if ( !dictionary->GetExtentType(opname) )          LEAVESEQ
    
  if ( !(dbext = dictionary->ProvideExtendDef(opname)) || 
         dbext->fmcbsmcb->smcbatyp != AT_CODE )      LEAVESEQ
    
  op_type = FT_Enumeration;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsExpression - 



\return fttype - 

\param  operenv - 
\param  opname - 
\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExpression"

FunctionTypes __cdecl OPBase :: IsExpression (OperEnvironment *operenv, char *opname, smcb *smcbptr )
{
  FunctionTypes       op_type = FT_undefined;
BEGINSEQ
  if ( strlen(opname) > ID_SIZE )                    LEAVESEQ
    
  if ( !operenv->DictHandle()->ProvExpression(operenv->ResOBHandle(),
                                              smcbptr->smcbname,opname,NULL,
                                              (ParmList *)NULL,NULL,operenv) )
                                                     LEAVESEQ
  op_type = FT_Expression;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsExtent - 



\return fttype - 

\param  dictionary - 
\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExtent"

FunctionTypes __cdecl OPBase :: IsExtent (Dictionary *dictionary, char *opname )
{
  FunctionTypes       op_type = FT_undefined;
BEGINSEQ
  if ( strlen(opname) > ID_SIZE )                    LEAVESEQ
    
  if ( !dictionary->GetExtentType(opname) )          LEAVESEQ
    op_type = FT_Extent;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsFunction - 



\return fttype - 

\param  dictionary - 
\param  resobj - 
\param  opname - 
\param  smcbptr - Pointer to general structure definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFunction"

FunctionTypes __cdecl OPBase :: IsFunction (Dictionary *dictionary, ACObject *resobj, char *opname, smcb *smcbptr )
{
  FunctionTypes       op_type = FT_undefined;
BEGINSEQ
  if ( strlen(opname) > ID_SIZE )                    LEAVESEQ
    
  if ( !dictionary->ProvFunction(resobj,
                                 smcbptr->smcbname,opname,NULL) )
                                                     LEAVESEQ
  op_type = FT_Function;
ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsGlobalExpression - 



\return fttype - 

\param  dictionary - 
\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGlobalExpression"

FunctionTypes __cdecl OPBase :: IsGlobalExpression (Dictionary *dictionary, char *opname )
{
  FunctionTypes       op_type = FT_undefined;
BEGINSEQ
  if ( strlen(opname) > ID_SIZE )                    LEAVESEQ
    
  if ( !dictionary->GetExpression(NULL,opname,NULL) )
                                                     LEAVESEQ
  op_type = FT_Expression;

ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsGlobalVariable - 



\return fttype - 

\param  dictionary - 
\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGlobalVariable"

FunctionTypes __cdecl OPBase :: IsGlobalVariable (Dictionary *dictionary, char *opname )
{
  FunctionTypes       op_type = FT_undefined;
  if ( dictionary->GetGlobalVariable(opname) )
    op_type = FT_Global;
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsInline - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInline"

logical OPBase :: IsInline ( )
{

  return( !opname || !strcmp(opname,"__inline_expression__") );

}

/******************************************************************************/
/**
\brief  IsIntern - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIntern"

logical OPBase :: IsIntern ( )
{

  return ( oper_env->get_intern_env() );

}

/******************************************************************************/
/**
\brief  IsOrdered - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOrdered"

logical OPBase :: IsOrdered ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  IsPHFunction - 



\return fttype - 

\param  dictionary - 
\param  classref - 
\param  co - 
\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPHFunction"

FunctionTypes __cdecl OPBase :: IsPHFunction (Dictionary *dictionary, DBStructDef *classref, PropertyHandle *co, char *opname )
{
  FunctionTypes           fttype = FT_undefined;
  PropertyHandle          ph(co);
  PropertyHandle          retval;
  OPFunctionDecl         *fct_decl;
BEGINSEQ
  co = ProvideCO(ph,dictionary,classref);
    
  if ( !(fct_decl = DBStructDef::GetPHFctDecl(opname,&retval,co,NULL)) )
                                                     LEAVESEQ
  delete fct_decl;
  fttype = FT_PHFunction;
ENDSEQ
  return(fttype);
}

/******************************************************************************/
/**
\brief  IsProperty - 



\return fttype - 

\param  smcbptr - Pointer to general structure definition
\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsProperty"

FunctionTypes __cdecl OPBase :: IsProperty (smcb *smcbptr, char *opname )
{
  FunctionTypes           op_type = FT_undefined;
  int32                   offset = 0;
BEGINSEQ
  if ( !smcbptr->SearchField(opname,&offset) &&
       !DBStructDef::GetMetaAttribute(opname)     )    LEAVESEQ
       
  op_type = FT_Property;
ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsSetOperand - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSetOperand"

logical OPBase :: IsSetOperand ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  IsStandardOperation - 



\return fftype - 

\param  co - 
\param  op_code - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsStandardOperation"

FunctionTypes OPBase :: IsStandardOperation (PropertyHandle *co, ST_OpCodes op_code )
{
  ParmList        *parmlist = NULL; // kommt wieder raus
  FunctionTypes    op_type    = FT_undefined;  
  node            *co_node = co ? co->GetNode() : NULL;
  DBFieldDef      *co_flddef;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !co_node || !(co_flddef = co_node->GetFieldDef()) ) 
                                                     LEAVESEQ
  switch (op_code)
  {
      case ST_plus          :
      case ST_minus         :   switch ( co_flddef->fmcbityp )
                                {
                                  case T_CHAR      :
                                  case T_STRING    :
                                  case T_CCHAR     :
                                  case T_LO        :
                                  case T_TIME      : SetDescription(co_flddef);
                                                     break;
                                  case T_UINT      :
                                  case T_INT       :
                                  case T_REAL      : SetDescription(DBFieldDef::GetStaticFieldDef(T_REAL));
                                                     break;
                                  case T_GUID      : SetDescription(DBFieldDef::GetStaticFieldDef(T_GUID));
                                                     break;
                                  case T_DATE      : if ( parmlist && (*parmlist)[0]->GetDescription()->fmcbityp == T_DATE )
                                                       SetDescription(DBFieldDef::GetStaticFieldDef(T_INT));
                                                     else
                                                       SetDescription(DBFieldDef::GetStaticFieldDef(T_DATE));
                                                     break;
                                  default          : if ( !co_node->IsCollection() || !(*parmlist)[0]->IsCollection() )  
                                                     OQLSERR(240)
                                }
                                break;
     case ST_power          :
     case ST_multi          :
     case ST_divi           :   switch ( co_flddef->fmcbityp )
                                {
                                  case T_UINT      :
                                  case T_INT       :
                                  case T_REAL      : SetDescription(DBFieldDef::GetStaticFieldDef(T_REAL));
                                                     break;
                                  case T_LO        : SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                                                     break;
                                  default          :           ERROR
                                }
                                break;

     case ST_remainder      :   SetDescription(co_flddef);
                                break;

     case ST_greaterEqual   :
     case ST_greater        :
     case ST_lower          :
     case ST_lowerEqual     :
     case ST_equal          :
     case ST_unequal        :
     case ST_and            :
     case ST_xor            :
     case ST_or             :
     case ST_not            :   SetDescription(DBFieldDef::GetStaticFieldDef(T_LO));
                                break;

     case ST_assign_ref     :
     case ST_assign         :   SetDescription(co_flddef);
                                break;

     default                :                                   ERROR
  }

  op_type = FT_Operation;

RECOVER
  op_type = FT_error;
ENDSEQ
  return(op_type);
}

/******************************************************************************/
/**
\brief  IsSysFunction - 



\return fttype - 

\param  opname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSysFunction"

FunctionTypes __cdecl OPBase :: IsSysFunction (char *opname )
{
  FunctionTypes           fttype = FT_undefined;
  OPFunctionDecl         *fct_decl;
BEGINSEQ
  if ( !(fct_decl = DBStructDef::GetSysFctDecl(opname,NULL,NULL)) )
                                                     LEAVESEQ
  delete fct_decl;
  fttype = FT_SysFunction;

ENDSEQ
  return(fttype);
}

/******************************************************************************/
/**
\brief  LastValue - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LastValue"

node *OPBase :: LastValue ( )
{

  return( oper_env ? oper_env->get_last_executed().get_nodeptr() : NULL);

}

/******************************************************************************/
/**
\brief  ListCallStack - 



\return term - 

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListCallStack"

logical OPBase :: ListCallStack (int32 count )
{
  logical                 term = NO;
  if ( this ) 
    GetExpressionDecl()->ListCallStack(count);
  return(term);
}

/******************************************************************************/
/**
\brief  LocalScope - 



\return structdef - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocalScope"

DBStructDef *OPBase :: LocalScope ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  MarkResetScope - 




\param  rscope - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MarkResetScope"

void OPBase :: MarkResetScope (logical rscope )
{



}

/******************************************************************************/
/**
\brief  Next - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Next"

logical OPBase :: Next ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  OPBase - 




\param  oper_bnf - 
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPBase"

     OPBase :: OPBase (BNFData *oper_bnf, OPBase *parent_node )
                     : fld (),
  class_ref(parent_node ? parent_node->Scope()
                        : NULL),
  op_type(NT_OPBase),
  oper_env(parent_node ? 
           parent_node->get_oper_env() : NULL),
  operand_bnf(oper_bnf),
  opname(NULL),
  row(0),
  column(0),
  parent(parent_node),
  result_position(0),
  source(NULL),
  value(),
  parmlist(NULL),
  re_open(-1),
  env_owner(NO),
  proto_type(NO),
  conversion(NO),
  inherits(NO),
  debug_break(NULL)
{

  op_type = NT_OPBase;
  
  if ( oper_bnf )
  {
//    opname = strdup(oper_bnf->StringValue());
    oper_bnf->GetTextPosition(NULL,row,column,NO);
  }

opnode_count++;
}

/******************************************************************************/
/**
\brief  OPName - 



\return op_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPName"

char *OPBase :: OPName ( )
{

   if (this && opname) return opname;
   else return "";
  
}

/******************************************************************************/
/**
\brief  ObjectHandle - 



\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectHandle"

ACObject *OPBase :: ObjectHandle ( )
{

  return ( oper_env ? oper_env->ObjectHandle() : NULL);

}

/******************************************************************************/
/**
\brief  Output - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  fstring - 
\param  parm1 - 
\param  parm2 - 
\param  parm3 - 
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical OPBase :: Output (char *fstring, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{
  char        string[4096];
  logical     term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  sprintf(string,fstring,parm1,parm2,parm3,parm4,parm5);
  SystemOutput(string,NO,YES);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  fstring - 
\param  intval - 
\param  parm1 - 
\param  parm2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical OPBase :: Output (char *fstring, int32 intval, char *parm1, char *parm2 )
{
  char        string[4096];
  logical     term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  sprintf(string,fstring,intval,parm1,parm2);
  SystemOutput(string,NO,YES);

  return(term);
}

/******************************************************************************/
/**
\brief  Parameters - 



\return parameters - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parameters"

OPParmList *OPBase :: Parameters ( )
{

  return(oper_env->Parameters());

}

/******************************************************************************/
/**
\brief  ParentHasChanged - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParentHasChanged"

logical OPBase :: ParentHasChanged ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Parmlist - 



\return parmlist - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parmlist"

OPParmList *OPBase :: Parmlist ( )
{

  if ( !parmlist )
    parmlist = new OPParmList(YES);
  return(parmlist);

}

/******************************************************************************/
/**
\brief  PopCO - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PopCO"

void OPBase :: PopCO ( )
{

  oper_env->PopCO();

}

/******************************************************************************/
/**
\brief  Position - 



\return term - 

\param  count_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical OPBase :: Position (int32 &count_ref )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Previous - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Previous"

logical OPBase :: Previous ( )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  ProvideBStatement - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideBStatement"

logical OPBase :: ProvideBStatement (BNFData *bdata )
{
  PropertyHandle          ph;
  OPBase                 *op_node;
  logical                 term = NO;
BEGINSEQ
  if ( op_node = CreateBStatement(bdata) )
    Parmlist()->Add(op_node);
  else
    OQLCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideBlock - 



\return term - 

\param  bdata - 
\param  blktype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideBlock"

logical OPBase :: ProvideBlock (BNFData *bdata, OQL_CodeBlock blktype )
{
  PropertyHandle          ph;
  OPBase                 *op_node;
  logical                 term = NO;
BEGINSEQ
// ???_code := [_???] statement(*)  
// block    := '{' statements(*) '}'
// operand  := ...
  
  if ( !bdata )                                      LEAVESEQ
  
  if ( !(op_node = bdata->IsSymbol("operand")
                   ? CreateOperandNode(this,bdata)
                   : CreateBlock(bdata,blktype)) )   ERROR

  Parmlist()->Add(op_node);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideCO - 



\return co - 

\param  prophdl - 
\param  dictionary - 
\param  classref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideCO"

PropertyHandle *__cdecl OPBase :: ProvideCO (PropertyHandle &prophdl, Dictionary *dictionary, DBStructDef *classref )
{
  PropertyHandle       *co = &prophdl;
  if ( !prophdl.IsValid() && dictionary && classref )
  {
    DictionaryHandle  dicthdl(dictionary);
    prophdl.Open(dicthdl,classref->smcbname);
  }

  return(co);
}

/******************************************************************************/
/**
\brief  ProvideDescription - 



\return fielddef - Internal field defintion

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDescription"

DBFieldDef *OPBase :: ProvideDescription ( )
{

  if ( !fldfmcb )
    AllocDescription();
  return(GetDescription());

}

/******************************************************************************/
/**
\brief  ProvideSimpleOp - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideSimpleOp"

logical OPBase :: ProvideSimpleOp (BNFData *bdata )
{
  OPBase                 *op_node;
  logical                 term = NO;
BEGINSEQ
  if ( !(op_node = CreateSimpleOp(bdata)) )          ERROR
  Parmlist()->Add(op_node);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideStatement - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStatement"

logical OPBase :: ProvideStatement (BNFData *bdata )
{
  OPBase                 *op_node;
  logical                 term = NO;
BEGINSEQ
  if ( op_node = CreateStatement(bdata) )
    Parmlist()->Add(op_node);
  else
    OQLCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideStatementOpList - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStatementOpList"

logical OPBase :: ProvideStatementOpList (BNFData *bdata )
{
  OPBase                 *op_node;
  logical                 term = NO;
BEGINSEQ
  if ( !(op_node = CreateStatementOpList(bdata)) )    ERROR
  Parmlist()->Add(op_node);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideStatementOperands - 



\return term - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStatementOperands"

logical OPBase :: ProvideStatementOperands (BNFData *bdata )
{
  OPBase                 *op_node;
  BNFData                *bstmt;
  BNFData                *oper_bnf;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
// stmt_operlist := foperand [stoplist_ext(*)] 
// stoplist_ext  := ',' doperand

  oper_bnf = bdata->GetElement(0);
  while ( oper_bnf ) 
  {
     if ( !(op_node = CreateDOperand(oper_bnf)) )
                                                     ERROR
     Parmlist()->Add(op_node);
     oper_bnf = NULL;
     if ( bstmt = bdata->GetElement(++indx0) )
       oper_bnf = bstmt->GetElement(1);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideStatements - 



\return term - 

\param  bdata - 
\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideStatements"

logical OPBase :: ProvideStatements (BNFData *bdata, int32 indx0 )
{
  BNFData                *bstmt;
  logical                 term = NO;
// ???_code      := [_???] statement(*)  
// block         := '{' statements(*) '}'
// case_stmt     := _case simple_op ':' statement(*)
// other_stmt    := _default ':' statement(*)

  while ( bstmt = bdata->GetElement(indx0++) ) 
    if ( bstmt->IsSymbol("statement") )   // skip possible keyword or '{'
      if ( ProvideStatement(bstmt) )
        term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  PushCO - 




\param  co - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PushCO"

void OPBase :: PushCO (PropertyHandle *co )
{

  oper_env->PushCO(co);

}

/******************************************************************************/
/**
\brief  RegisterLastValue - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterLastValue"

void OPBase :: RegisterLastValue ( )
{

  value.RegisterNode(LastValue());


}

/******************************************************************************/
/**
\brief  ResOBHandle - 



\return obhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResOBHandle"

ACObject *OPBase :: ResOBHandle ( )
{

  return ( oper_env ? oper_env->ResOBHandle() : NULL);

}

/******************************************************************************/
/**
\brief  ResetScope - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetScope"

logical OPBase :: ResetScope ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ResetValue - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetValue"

void OPBase :: ResetValue ( )
{

  value.Close();

}

/******************************************************************************/
/**
\brief  Schema - 



\return schema_resource - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Schema"

SchemaResources *OPBase :: Schema ( )
{

  return( this && oper_env ? oper_env->get_resources() : NULL );

}

/******************************************************************************/
/**
\brief  Scope - 



\return strdef - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Scope"

DBStructDef *OPBase :: Scope ( )
{

  return(oper_env ? oper_env->get_scope() : NULL);

}

/******************************************************************************/
/**
\brief  SetBreakPoint - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  bp_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBreakPoint"

logical OPBase :: SetBreakPoint (logical bp_opt )
{
  char                   *name = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  if ( bp_opt )
    name = "";
  SetBreakPoint(name);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBreakPoint"

logical OPBase :: SetBreakPoint (BNFData *bdata )
{
  char                   *autorun = "";
  logical                 term = NO;
BEGINSEQ
// debug_opt    := '#' [ auto_run ]
// autorun      := ':' identifier

  if ( !bdata )                                      ERROR
  if ( bdata->GetElement(1) )
    autorun = bdata->GetElement(1)->GetElement(1)->GetStringValue(NULL,NULL);

  if ( !autorun )
    autorun = "";

  SetBreakPoint(autorun);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBreakPoint"

logical OPBase :: SetBreakPoint (char *name )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  
  if ( !name )
  {
    delete debug_break;
    debug_break = NULL;
  }
  else
  {
    if ( !debug_break )
      debug_break = new DBreakPoint();
    debug_break->SetAutoRun(name);
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCO - 



\return term - 

\param  co - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCO"

logical OPBase :: SetCO (PropertyHandle *co )
{
  logical                 term = NO;
  SetReopen(oper_env->SetCO(co));
  last_co.CopyHandle(co);

  return(term);
}

/******************************************************************************/
/**
\brief  SetDescription - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDescription"

logical OPBase :: SetDescription (DBFieldDef *fielddef )
{
  logical                 term = NO;
  if ( fldfaloc && fldfmcb )
    delete (DBFieldDef *)fldfmcb;

  fldfmcb = fielddef;
  fldfaloc = NO;

  fielddef->GetDBStruct(DictHandle());
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDescription"

logical OPBase :: SetDescription ( )
{
  DBFieldDef       *fielddef;
// skizze
  if ( !(fielddef = source->Value()
                    ? source->GetValue()->GetDescription()
                    : source->GetDescription()          ) )
    fielddef = parent->GetDescription();

  if ( fielddef )
    SetDescription(fielddef);
  return(NO);
}

/******************************************************************************/
/**
\brief  SetLastValue - 




\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastValue"

void OPBase :: SetLastValue (node *nodeptr )
{

  if ( oper_env )
    oper_env->set_last_executed(nodeptr);


}

/******************************************************************************/
/**
\brief  SetMaxPriority - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMaxPriority"

void OPBase :: SetMaxPriority ( )
{



}

/******************************************************************************/
/**
\brief  SetOPName - 




\param  op_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOPName"

void OPBase :: SetOPName (char *op_name )
{
  char              string[ID_SIZE+1];

BEGINSEQ
  if ( !op_name || !*op_name )                       LEAVESEQ

  Set_OPName(strdup(gvtxbts(string,op_name,ID_SIZE))); 

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetParent - 




\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParent"

void OPBase :: SetParent (OPBase *parent_node )
{

  parent = parent_node;

}

/******************************************************************************/
/**
\brief  SetParmCount - 




\param  parm_count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParmCount"

void OPBase :: SetParmCount (int32 parm_count )
{

  oper_env->SetParmCount(parm_count);

}

/******************************************************************************/
/**
\brief  SetReference - 



\return term - 

\param  source_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReference"

logical OPBase :: SetReference (node *source_node )
{
  DBFieldDef        *fielddef = GetDescription();
  DBFieldDef        *source_field = source_node->GetFieldDef();
  node              *value_node = Value();
  logical            term = NO;
BEGINSEQ
  if ( !fielddef->get_by_reference() )               OQLSERR(158)
  
  if ( !fielddef->fmcbtype == T_VOID &&
       !source_node->Inherits(fielddef->fmcbtype) )  OQLSERR(153)
    
  if ( !value_node )
  {
    GetValue()->Open(fielddef,Instance());
    value_node = Value();
  }
  value_node->SetTransientProperty(source_node->GetNode());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetReopen - 




\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReopen"

void OPBase :: SetReopen (int32 ini_opt )
{

  if ( re_open >= 0 && re_open < ini_opt )
    re_open = ini_opt;

}

/******************************************************************************/
/**
\brief  SetScope - 




\param  strdef - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetScope"

void OPBase :: SetScope (DBStructDef *strdef )
{

  if ( oper_env )
  {
    if ( !strdef && parent && !Scope() )
      strdef = parent->Scope();
    oper_env->SetScope(strdef);
  }

}

/******************************************************************************/
/**
\brief  SetSource - 




\param  op_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSource"

void OPBase :: SetSource (OPBase *op_node )
{

  source = op_node;

}

/******************************************************************************/
/**
\brief  SetUpperCO - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUpperCO"

logical OPBase :: SetUpperCO ( )
{

  return( oper_env->SetUpperCO() );

}

/******************************************************************************/
/**
\brief  SetValue - 



\return term - 

\param  source_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical OPBase :: SetValue (node *source_node )
{
  DBFieldDef        *fielddef     = GetDescription();
  DBFieldDef        *source_field = NULL;
  node              *value_node   = Value();
  logical            term         = NO;
BEGINSEQ
  if ( fielddef->IsNoField() )                       LEAVESEQ
  
  if ( !source_node )                                OQLSERR(99)
    
  source_field = source_node->GetFieldDef();  
  if ( !(source_node  = source_node->GetNode()) )    ERROR
  
  if ( fielddef->fmcbdim != 1 && source_node->IsCollection() )  // collection
  {
    GetValue()->set_nodeptr(source_node->CreateCopy());
    LEAVESEQ
  }

  if ( !value_node )
  {
    GetValue()->Open(fielddef,Instance());
    value_node = Value();
  }
  
  if ( value_node = value_node->GetNode() )
    value_node->SetValue(source_node,YES);



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetValueOrReference - 



\return term - 

\param  source_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValueOrReference"

logical OPBase :: SetValueOrReference (node *source_node )
{
  DBFieldDef        *fielddef = GetDescription();
  return( fielddef->get_by_reference() 
          ? SetReference(source_node)
          : SetValue(source_node) );
  


}

/******************************************************************************/
/**
\brief  Set_OPName - 




\param  op_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Set_OPName"

void OPBase :: Set_OPName (char *op_name )
{
  char              string[ID_SIZE+1];

BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  if ( opname )
    if ( !oper_env || opname != oper_env->get_expression() )
      free(opname);
  
  opname = NULL;  
    
  if ( !op_name || !*op_name )                       LEAVESEQ
  opname = op_name; 
    

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetupEnvironment - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupEnvironment"

void OPBase :: SetupEnvironment ( )
{

  if ( oper_env )
  {
    if ( env_owner )
      oper_env->SetupEnvironment();
    oper_env->SetNVHType(NVH_undefined);
  }

}

/******************************************************************************/
/**
\brief  ShowError - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  oper_bnf - 
\param  name1 - 
\param  name2 - 
\param  name3 - 
\param  name4 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowError"

void OPBase :: ShowError (BNFData *oper_bnf, char *name1, char *name2, char *name3, char *name4 )
{
  OPDecl      *op_decl;
  DBFieldDef  *fielddef;
  int          err_code = OQLERROR;
  int          r = row;
  int          c = column;
  char         classname[ID_SIZE+1];
  char         name[ID_SIZE+1];
  char         location[256];
  char         valstr[81];
  char         string1[ID_SIZE+1];
  char         string2[ID_SIZE+1];
  char         string3[ID_SIZE+1];
  char         string4[ID_SIZE+1];
  NString      nstring;
BEGINSEQ
  strcpy(classname,"Unknown");
  strcpy(name,"Unknown");
  
  *string1 = *string2 = *string3 = *string4 = 0;
  if ( fielddef = CO()->GetDescription() )
  {
    gvtxbts(string1,fielddef->fmcbname,ID_SIZE);
    gvtxbts(string2,fielddef->fmcbtype,ID_SIZE);
  }
  if ( (fielddef = GetDescription()) )
  {
    gvtxbts(string3,fielddef->fmcbname,ID_SIZE);
    gvtxbts(string4,fielddef->fmcbtype,ID_SIZE);
  }
  
  if ( op_decl = Declaration() )
  {
    if ( op_decl->OPName() && op_decl->OPName() )
      gvtxbts(name,op_decl->OPName(),ID_SIZE);
    
    if ( op_decl->Scope() )
      gvtxbts(classname,op_decl->Scope()->smcbname,ID_SIZE);
  }

  if ( !oper_bnf )
    oper_bnf = operand_bnf;
  if ( !oper_bnf && parent )
    oper_bnf = parent->get_operand_bnf();
    
  oper_bnf->GetTextPosition(NULL,r,c,NO);
  sprintf(location,"Error in %s::%s at row(%i), column(%i): \n",classname,name,r,c);  
  nstring = location;
  if ( oper_bnf )
  {
    nstring += ' ';
    nstring += ' ';
    nstring += oper_bnf->GetCurrentLine();
    nstring += '\n';
    nstring += "   operand or operation '";
    nstring += oper_bnf->GetValue(valstr,sizeof(valstr)-1);
    nstring += '\'';
    nstring += ' ';
    nstring += "not defined in:";
    nstring += ' ';
    nstring += *string2 ? string2 : classname;
  }  
  Output(nstring);  
  
  if ( !err_code )                                    LEAVESEQ
    
  if ( name1 )
    gvtxbts(string1,name1,ID_SIZE);
  if ( name2 )
    gvtxbts(string2,name2,ID_SIZE);
  if ( name3 )
    gvtxbts(string3,name3,ID_SIZE);
  if ( name4 )
    gvtxbts(string4,name4,ID_SIZE);
  
  if ( err_code )
  {
    OQLEV1(string1,UNDEF);
    OQLEV2(string2,UNDEF);
    OQLEV3(string3,UNDEF);
    OQLEV4(string4,UNDEF);
    OQLError().WriteError();
    Output(OQLError().GetText());  
    
//  OQLError().DisplayMessage(err_code,string1,string2,string3,string4);
    OQLISET(err_code);
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  err_code - 
\param  obj_id - 
\param  mod_id - 
\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowError"

void OPBase :: ShowError (int32 err_code, char *obj_id, char *mod_id, BNFData *oper_bnf )
{

  OQLError().SetError(err_code,obj_id,NULL);
  OQLError().SetError(err_code,NULL,mod_id);

  ShowError(oper_bnf);

}

/******************************************************************************/
/**
\brief  Source - 



\return op_node - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Source"

OPBase *OPBase :: Source ( )
{

  return ( source );

}

/******************************************************************************/
/**
\brief  SourceNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SourceNode"

node *OPBase :: SourceNode ( )
{

  return( source ? source->Value() : NULL );

}

/******************************************************************************/
/**
\brief  Stack - 



\return parameters - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stack"

NodeStack *OPBase :: Stack ( )
{

  return(oper_env->Stack());

}

/******************************************************************************/
/**
\brief  StoreValue - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreValue"

logical OPBase :: StoreValue ( )
{
  node                   *srce_node = SourceNode();
  node                   *nodeptr = Value();
  DBFieldDef             *fielddef = GetDescription();
  logical                 term = NO;
BEGINSEQ
  if ( fielddef->get_by_reference() )                LEAVESEQ
    
  if ( !nodeptr || !srce_node )                      ERROR
  
// das sollte vorerst nur für attribute gemacht werden (s. ACOperand::Store)
  srce_node->SetValue(nodeptr,YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ToTop - 



\return term - 

\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToTop"

logical OPBase :: ToTop (logical recursive )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  TraceCalls - 




\param  exec_rc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceCalls"

void OPBase :: TraceCalls (ExecReturnCodes exec_rc )
{
  static  int  active = AUTO;   // später wieder auf AUTO setzen
  OPDecl      *op_decl;
  char         classname[ID_SIZE+1];
  char         name[ID_SIZE+1];
  char         header[1024];
  char        * line = "";
  char        *exec_str;
  char        *svar;

BEGINSEQ
  if ( active == AUTO )
    if ( svar = GetSysVariable("OSI_CALLS") )
      active = *svar == 'Y' || *svar == 'y';
    else
      active = NO;
  
  if ( active != YES)                                     LEAVESEQ
  
  *classname = 0;
  strcpy(name,"Unknown");
  if ( op_decl = Declaration() )
  {
    if ( op_decl->OPName() && *op_decl->OPName() )
      gvtxbts(name,op_decl->OPName(),ID_SIZE);
    
    if ( op_decl->Scope() )
      gvtxbts(classname,op_decl->Scope()->smcbname,ID_SIZE);
  }

  switch ( exec_rc )
  {
    case ERC_success     : exec_str = "SUCCESS  "; break;
    case ERC_break       : exec_str = "BREAK    "; break;
    case ERC_leave       : exec_str = "LEAVE    "; break;
    case ERC_continue    : exec_str = "CONTINUE "; break;
    case ERC_return      : exec_str = "RETURN   "; break;
    case ERC_error       : exec_str = "ERROR    "; break;
    case ERC_terminate   : exec_str = "TERMINATE"; break;
    default              : exec_str = "UNKNOWN  "; 
  }

  if ( operand_bnf )
    line = operand_bnf->GetCurrentLine();
  memset(header,0,sizeof(header));
  sprintf(header,"%s::%s, row(%i), column(%i): %s [          ]",classname,name,row,column,line);
  memcpy(header+strlen(header)-10,exec_str,9);
  
  OQLError().OutputMessage("OQL","Trace",header);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Value - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Value"

node *OPBase :: Value ( )
{

  return(value.get_nodeptr());

}

/******************************************************************************/
/**
\brief  Variables - 



\return variables - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Variables"

OPParmList *OPBase :: Variables ( )
{

  return(oper_env->Variables());

}

/******************************************************************************/
/**
\brief  ~OPBase - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPBase"

     OPBase :: ~OPBase ( )
{

  SetBreakPoint(NO);
  Set_OPName(NULL);
  
  delete parmlist;
  parmlist = NULL;

  if ( env_owner )
    delete oper_env;
  oper_env = NULL;

  last_co.Close();
opnode_count--;
}


