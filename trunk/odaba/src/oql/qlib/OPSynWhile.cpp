/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynWhile

\brief    


\date     $Date: 2006/03/12 19:21:05,03 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynWhile"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPSynWhile.hpp>


/******************************************************************************/
/**
\brief  CreateStatements - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatements"

logical OPSynWhile :: CreateStatements ( )
{
  logical                 term = NO;
BEGINSEQ
// while_block  := _while condition bstatement 
// condition    := '(' doperand ')'
// bstatement   := block | statement
  
// init source
  if ( !(source = CreateDOperand(operand_bnf->GetElement(1)->GetElement(1))) ) 
                                                     ERROR
// init parmlist
  if ( ProvideBStatement(operand_bnf->GetElement(2)) ) 
                                                     ERROR

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

ExecReturnCodes OPSynWhile :: Execute ( )
{
  ExecReturnCodes    rc = ERC_undefined;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  while ( (rc = ExecuteSource()) == ERC_success )
  {
    if ( !source->GetValue()->IsTrue() )             LEAVESEQ
    switch ( rc = ExecuteStatement(0) )
    {
      case ERC_terminate :                           ERROR
      case ERC_null      :
      case ERC_success   :                           break;
      case ERC_undefined : // no statements
      case ERC_continue  : rc = ERC_success;         break;
      case ERC_break     : rc = ERC_success; 
      default            :                           LEAVESEQ
    }    
  }


RECOVER
  ResetValue();
  rc = ERC_terminate;
ENDSEQ
  if ( rc != ERC_terminate )
    RegisterLastValue();
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

logical OPSynWhile :: Initialize (int32 ini_opt )
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
\brief  OPSynWhile - 


\return term

\param  oper_bnf -
\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynWhile"

                        OPSynWhile :: OPSynWhile (BNFData *oper_bnf, OPBase *parent_node )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL)
{

  op_type = NT_OPSynWhile;

  SetOPName("while");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynWhile - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynWhile"

                        OPSynWhile :: ~OPSynWhile ( )
{



}


