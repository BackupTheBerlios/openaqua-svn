/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPDecl

\brief    


\date     $Date: 2006/08/27 20:13:08,32 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPDecl"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
//#include  <sOqlExtentList.hpp>
#include  <sNodeStack.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPVariableSpec.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSDB_Member.hpp>
#include  <sSchemaResources.hpp>
#include  <snode.hpp>
#include  <sOPDecl.hpp>


/******************************************************************************/
/**
\brief  CallDecl - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  operenv - 
\param  co - 
\param  parm_list - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CallDecl"

logical OPDecl :: CallDecl (OperEnvironment *operenv, PropertyHandle *co, ParmList *parm_list, int8 set_operation )
{
  OperEnvironment        *prevenv = oper_env->get_prev_env();
  logical                 term = NO;
  oper_env->SetPreviousEnvironment(operenv);
  
  term = Call(co,parm_list,set_operation);

  oper_env->SetPreviousEnvironment(prevenv);

  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  operenv - 
\param  co - 
\param  call_parms - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CallDecl"

logical OPDecl :: CallDecl (OperEnvironment *operenv, PropertyHandle *co, OPParmList *call_parms, int8 set_operation )
{
  OperEnvironment        *prevenv = oper_env->get_prev_env();
  logical                 term = NO;
  oper_env->SetPreviousEnvironment(operenv);
  
  term = Call(co,call_parms,set_operation);
  
  oper_env->SetPreviousEnvironment(prevenv);

  return(term);
}

/******************************************************************************/
/**
\brief  CallIntern - 



\return term - 

\param  co - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CallIntern"

logical OPDecl :: CallIntern (PropertyHandle *co, int8 set_operation )
{
  logical                 term = NO;
BEGINSEQ
  SetupEnvironment();
  if ( !co ) 
    co = CO();
  PushCO(co);
  
  if ( CallIntern2(co,set_operation) )               ERROR
RECOVER
  term = YES;
ENDSEQ
  PopCO();
  return(term);
}

/******************************************************************************/
/**
\brief  CallIntern2 - 



\return term - 

\param  co - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CallIntern2"

logical OPDecl :: CallIntern2 (PropertyHandle *co, int8 set_operation )
{
  ExecReturnCodes         rc = ERC_success;  
  PropertyHandle          result;
  int32                   indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  switch ( set_operation )
  { 
    case NO   : if ( fldfmcb && !fldfmcb->fmcbstat && 
                     !co->IsPositioned() && co->AutoLocate() )  
                {
                  rc = ERC_null;
                  ResetValue();
                  break;
                }   
    case AUTO : if ( (rc = Execute()) == ERC_null )
                  ResetValue();
                if ( co != CO() && *co != CO() )
                  co->CopyHandle(CO());
                break;
    case YES  : co->ToTop();
                while ( co->Get(indx0++) )
                  if ( (rc = Execute()) == ERC_terminate )
                    break;
                break;
  }
  
  SetLastValue(NULL);
  if ( rc == ERC_terminate )                         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Check - 



\return term - 

\param  retval - 
\param  co - 
\param  parm_list - 
\param  convopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical OPDecl :: Check (PropertyHandle *retval, PropertyHandle *co, ParmList *parm_list, logical convopt )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  CreatPrototypeParmList - 



\return parmlist - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatPrototypeParmList"

ParmList *OPDecl :: CreatPrototypeParmList ( )
{
  ParmList          *parmlist = new ParmList(NO);
  int32              indx0      = 0;
  OPBase            *op_node    = NULL;
  logical            term       = NO;
  parmlist->Clear();
  while ( op_node = Parameters()->GetAt(indx0) )
  {
    op_node->Initialize(-1); // init variable specification
    parmlist->AddParm(&get_value());
    indx0++;
  }
  return(parmlist);
}

/******************************************************************************/
/**
\brief  CreateDecl - 



\return term - 

\param  impl_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDecl"

logical OPDecl :: CreateDecl (PropertyHandle *impl_ph )
{
  PropertyHandle  *fct_ph     = impl_ph->GetParentProperty();
  PropertyHandle  *parm_ph    = impl_ph->GPH("parameters");
  Dictionary      *dictionary = DictHandle();
  DBFieldDef      *fielddef   = NULL;
  OPBase          *op_node    = NULL;
  int32            indx0      = 0;
  logical          term       = NO;
BEGINSEQ
  if ( !impl_ph->Exist() )                           OQLSERR(99)
  
  SetOPName(fct_ph->ExtractKey());
  memcpy(impl_name,impl_ph->ExtractKey(),ID_SIZE);
  
  fielddef = ProvideDescription();
  fielddef->FillFunction(*fct_ph,dictionary,0);
  value.Open(fielddef,NULL);

  Parmlist()->Clear();
  while ( parm_ph->Get(indx0++) )
  {
    if ( *((SDB_Member *)parm_ph->Get().GetData())->get_ddetype() <= ' ' )
                                                     OQLSERR(99)
    fielddef = new DBFieldDef();
    fielddef->FillVariable(*parm_ph,dictionary,0);
   
    op_node = new OPVariableSpec(fielddef,this);
    op_node->fldfalos(YES);
    
    Parameters()->Add(op_node);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateMember - 



\return op_node - 

\param  btype - 
\param  bdecl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateMember"

OPBase *OPDecl :: CreateMember (BNFData *btype, BNFData *bdecl )
{
  DictionaryHandle        dictionary(DictHandle());
  DBFieldDef             *fielddef;
  OPBase                 *op_node = NULL;
  BNFData                *ini_bnf = NULL;
  int32                   index = 0;
BEGINSEQ
  fielddef = new DBFieldDef();
  if ( Schema()->GetTypeSpec(fielddef,btype,NO) )      ERROR
  if ( Schema()->CreateMember(fielddef,bdecl,NULL,Scope(),index,NO) )
                                                       ERROR
  op_node = new OPVariableSpec(fielddef,this);
  op_node->fldfalos(YES);

RECOVER
  delete op_node;
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief  CreateVariable - 



\return term - 

\param  bdata - 
\param  is_global - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateVariable"

logical OPDecl :: CreateVariable (BNFData *bdata, logical is_global )
{
  DictionaryHandle        dictionary(DictHandle());
  OPBase                 *op_node;
  BNFData                *type_spec;
  BNFData                *declarator;
  int32                   index = 0;
  logical                 term = NO;
BEGINSEQ
// var_def        := [_global] type_spec declarators  // OSI
// member         := [_global] type_spec declarators ';'
// declarators    := declarator [declarator_suc(*)]
// declarator_suc := ',' declarator

  if ( bdata->GetElement(0)->IsSymbol("_global") )
    is_global = YES;
  
  type_spec = bdata->GetElement("type_spec");
  
  bdata = bdata->GetElement("declarators");
  declarator = bdata->GetElement(index);
  while ( declarator )
  {
    if ( !(op_node = CreateMember(type_spec,declarator)) )
                                                     ERROR
    if ( !is_global )
      Variables()->Add(op_node);
    else
    {
      op_node->CreateGlobalVariable();
      delete op_node;
    }
    
    declarator = NULL;
    if ( bdata->GetElement(++index) )
      declarator = bdata->GetElement(index)->GetElement(1);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeInitParameters - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeInitParameters"

logical OPDecl :: DeInitParameters ( )
{
  OPBase              *op_node;
  int16                indx0 = 0;
  logical              term = NO;
  while ( op_node = Parameters()->GetAt(indx0++) )
    op_node->Initialize(11); // de-initialize variable specification
  return(term);
}

/******************************************************************************/
/**
\brief  InitParameters - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  call_parms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitParameters"

logical OPDecl :: InitParameters (OPParmList *call_parms )
{
  int32              indx0      = 0;
  OPBase            *op_node    = NULL;
  int16              parm_count = call_parms ? call_parms->GetSize() : 0;
  node              *parm_val   = NULL;
  logical            term       = NO;
  while ( op_node = Parameters()->GetAt(indx0) )
  {
    op_node->Initialize(10); // init variable specification
    if ( indx0 < parm_count )
      if ( parm_val = call_parms->GetAt(indx0)->Value() )
        if ( !op_node->CheckSourceValue(parm_val) )
          op_node->SetValueOrReference(parm_val);
    indx0++;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  parm_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitParameters"

logical OPDecl :: InitParameters (ParmList *parm_list )
{
  int32              indx0      = 0;
  OPBase            *op_node    = NULL;
  int16              parm_count = parm_list ? parm_list->GetSize() : 0;
  node              *parm_val   = NULL;
  logical            term       = NO;
  while ( op_node = Parameters()->GetAt(indx0) )
  {
    op_node->Initialize(10); // init variable specification
    if ( indx0 < parm_count )
      if ( parm_val = parm_list->GetAt(indx0)->get_nodeptr() )
        if ( !op_node->CheckSourceValue(parm_val) )
          op_node->SetValueOrReference(parm_val);
    indx0++;
  }
  return(term);
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

logical OPDecl :: InitResult (PropertyHandle *co )
{
  logical                 term = NO;
BEGINSEQ
  if ( !CO() || (co && co->GetNode() != CO()->GetNode()) )
    SetCO(co);

  if ( InitResult() )                                ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical OPDecl :: InitResult ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  IsAccessPath - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAccessPath"

logical OPDecl :: IsAccessPath ( )
{

  return(  op_type == NT_OPAccessPathDecl ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsExpression - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExpression"

logical OPDecl :: IsExpression ( )
{

  return(  op_type == NT_OPExpressionDecl ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsFunction - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFunction"

logical OPDecl :: IsFunction ( )
{

  return(  op_type == NT_OPFunctionDecl ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsVirtual - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsVirtual"

logical OPDecl :: IsVirtual ( )
{

  return(NO);

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

logical OPDecl :: ListCallStack (int32 count )
{
  int32                   level = 0;
  OperEnvironment        *operenv = oper_env;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  PrintCallStack(++level);
  
  while ( operenv && --count )
    if ( operenv = operenv->get_prev_env() )
      if ( operenv->get_prev_env() )      // not top environment
        operenv->GetExpressionDecl()->PrintCallStack(++level);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPDecl - 



\return term - 

\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPDecl"

     OPDecl :: OPDecl (OPBase *parent_node )
                     : OPBase (NULL,parent_node)
{

  memset(impl_name,0,sizeof(impl_name));
  memset(type_name,0,sizeof(type_name));
  
  op_type = NT_OPDecl;



}

/******************************************************************************/
/**
\brief  Position - 



\return term - 

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical OPDecl :: Position (int32 count )
{

  return( value.Position(count) );

}

/******************************************************************************/
/**
\brief  PrintCallStack - 



\return term - 

\param  level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrintCallStack"

logical OPDecl :: PrintCallStack (int32 level )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  Output("  (%i) %s\n",level,GetCurrentLine());
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OPDecl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPDecl"

     OPDecl :: ~OPDecl ( )
{



}


