/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynIf

\brief    


\date     $Date: 2006/03/12 19:21:03,79 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynIf"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPSynIf.hpp>


/******************************************************************************/
/**
\brief  CreateStatements - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatements"

logical OPSynIf :: CreateStatements ( )
{
  BNFData                *bstmt;
  int32                   index = 0;
  logical                 term = NO;
BEGINSEQ
// if_block     := _if condition bstatement [ else_stmt ] 
// else_stmt    := [debug_opt] _else bstatement
// condition    := '(' doperand ')'
// bstatement   := block | statement
  
// init source
  if ( !(source = CreateDOperand(operand_bnf->GetElement(1)->GetElement(1))) )
                                                     ERROR
// init parm0
  if ( ProvideBStatement(operand_bnf->GetElement(2)) ) 
                                                     ERROR
// init parm1
  if ( bstmt = operand_bnf->GetElement(3) ) // else
  {
    if ( bstmt->GetElement(0)->IsSymbol("debug_opt") )
      index = 1;
    if ( ProvideBStatement(bstmt->GetElement(index+1)) )
                                                     ERROR
    if ( index )
      Parmlist()->GetLast()->SetBreakPoint(bstmt->GetElement(0));
  }    
    

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

ExecReturnCodes OPSynIf :: Execute ( )
{
  int                stmt = 1;
  ExecReturnCodes    rc = ERC_undefined;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  switch ( rc = ExecuteSource() )
  {
    case ERC_success   : stmt = source->GetValue()->IsTrue() ? 0 : 1;
                         break;
    case ERC_terminate : ERROR
    default            : stmt = 1;  // else
  }
  
  if ( (rc = ExecuteStatement(stmt)) == ERC_undefined ) // no statements: if (...) ;
    rc = ERC_success;             
  
  if ( rc == ERC_success )
    RegisterLastValue();

  if ( rc == ERC_null )
    rc = ERC_success;
RECOVER
  ResetValue();
  rc = ERC_terminate;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term

\param  ini_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPSynIf :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( CreateStatements() )              ERROR
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPSynIf - 


\return term

\param  oper_bnf -
\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynIf"

                        OPSynIf :: OPSynIf (BNFData *oper_bnf, OPBase *parent_node )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL)
{

  op_type = NT_OPSynIf;

  SetOPName("if");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynIf - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynIf"

                        OPSynIf :: ~OPSynIf ( )
{



}


