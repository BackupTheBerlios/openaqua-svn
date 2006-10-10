/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OPAccessPathDecl

\brief    


\date     $Date: 2006/04/20 20:49:44,23 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPAccessPathDecl"

#include  <poql.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <sOqlExtentList.hpp>
#include  <sOPAccessPath.hpp>
#include  <sOPParmList.hpp>
#include  <sOperEnvironment.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <snode.hpp>
#include  <sOPAccessPathDecl.hpp>


/******************************************************************************/
/**
\brief  Call - 


\return term
-------------------------------------------------------------------------------
\brief  i0


\param  co - 
\param  call_parms - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPAccessPathDecl :: Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation )
{
  logical     intern_opt = IsIntern();
  logical     term = NO;
  if ( !intern_opt )
    InitParameters(call_parms);
  
  term = CallIntern(co,set_operation);

  if ( !intern_opt )
    DeInitParameters();
  

  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  co - 
\param  parm_list - 
\param  set_operation - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Call"

logical OPAccessPathDecl :: Call (PropertyHandle *co, ParmList *parm_list, int8 set_operation )
{
  logical     intern_opt = IsIntern();
  logical     term = NO;
  if ( !intern_opt )
    InitParameters(parmlist);
  
  term = CallIntern(co,set_operation);

  if ( !intern_opt )
    DeInitParameters();
  

  return(term);
}

/******************************************************************************/
/**
\brief  Create - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical OPAccessPathDecl :: Create ( )
{
  OPAccessPath           *acpath;
  logical                 term = NO;
BEGINSEQ
  if ( !CO() )
    SetUpperCO();

  acpath = new OPAccessPath(Scope(),operand_bnf,this,NULL,0,NO);
                                                     OQLCERR
  value.RegisterNode(acpath->GetLastNode());

  source = acpath;
RECOVER
  term = YES;
ENDSEQ
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

ExecReturnCodes OPAccessPathDecl :: Execute ( )
{
  ExecReturnCodes      rc = ERC_success;
  int32                indx0 = 0;
BEGINSEQ
  if ( !source || CheckCO() )                        ERROR
  
  rc = source->Execute();
  
  value.RegisterNode(source->Value());
  if ( !Value() )
  {
    rc = ERC_null;                                  ERROR
  }

  if ( rc != ERC_success )                          ERROR
RECOVER
  ResetValue();
  if ( rc != ERC_null )
    rc = ERC_terminate;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  OPAccessPathDecl - 


\return term
-------------------------------------------------------------------------------
\brief  i0


\param  dictptr
\param  resobj - 
\param  obhandle - 
\param  scope_str - 
\param  co - 
\param  expr_string - 
\param  operenv_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPAccessPathDecl"

                        OPAccessPathDecl :: OPAccessPathDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, char *expr_string, OperEnvironment *operenv_w )
                     : OPDecl (NULL)
{

BEGINSEQ
  op_type = NT_OPAccessPathDecl;

  OQLRESET
  
  if ( !expr_string )                                OQLSERR(99)
  if ( CreateEnvironment(dictptr,resobj,scope_str,NULL,obhandle,co,this) )
                                                     ERROR
  if ( operenv_w )
    CopyEnvironment(operenv_w,YES);
   
  if ( !(operand_bnf = oper_env->SetExpression(expr_string,NULL)) )
                                                     ERROR
  Set_OPName(oper_env->get_expression());
  
  class_ref = scope_str;
  if ( Create() )                                    ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01


\param  operenv - 
\param  co - 
\param  oper_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPAccessPathDecl"

                        OPAccessPathDecl :: OPAccessPathDecl (OperEnvironment *operenv, PropertyHandle *co, BNFData *oper_bnf )
                     : OPDecl (NULL)
{

BEGINSEQ
  op_type = NT_OPAccessPathDecl;

  OQLRESET
  if ( CreateEnvironment(NULL,NULL,NULL,oper_bnf,NULL,co,this) )
                                                     ERROR
  CopyEnvironment(operenv,YES);
    
  if ( !(operand_bnf = oper_bnf->GetSymbol("OQLSelect")) )
    operand_bnf = oper_bnf->GetSymbol("access_path");
  if ( !operand_bnf )                                OQLERR(99)
  
  class_ref = Scope();
  if ( Create() )                                    ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03


\param  dictptr
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
#define    MOD_ID  "OPAccessPathDecl"

                        OPAccessPathDecl :: OPAccessPathDecl (Dictionary *dictptr, ACObject *resobj, ACObject *obhandle, DBStructDef *scope_str, PropertyHandle *co, BNFData *oper_bnf, OperEnvironment *operenv_w, char *expr_dup_w )
                     : OPDecl (NULL)
{

BEGINSEQ
  op_type = NT_OPAccessPathDecl;

  OQLRESET
  
  if ( expr_dup_w )
    Set_OPName(expr_dup_w);
    
  if ( CreateEnvironment(dictptr,resobj,scope_str,oper_bnf,obhandle,co,this,expr_dup_w) )
                                                     ERROR
  if ( operenv_w )
    CopyEnvironment(operenv_w,YES);
   
   if ( !(operand_bnf = oper_bnf) )                   OQLSERR(99)
  class_ref = scope_str;
  if ( Create() )                                    ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Position - 


\return term

\param  count
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

logical OPAccessPathDecl :: Position (int32 count )
{
  logical                 term = NO;
BEGINSEQ
  if ( source->Position(count) )                     ERROR

  value.RegisterNode(source->Value());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OPAccessPathDecl - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPAccessPathDecl"

                        OPAccessPathDecl :: ~OPAccessPathDecl ( )
{
  Dictionary            *dictptr;
  if ( opname )
    if ( dictptr = DictHandle() )
      dictptr->RemoveExpression(this,Scope());


}


