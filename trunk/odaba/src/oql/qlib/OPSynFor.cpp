/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynFor

\brief    


\date     $Date: 2006/03/12 19:21:03,45 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynFor"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPSynFor.hpp>


/******************************************************************************/
/**
\brief  CreateStatements - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatements"

logical OPSynFor :: CreateStatements ( )
{
  logical                 term = NO;
BEGINSEQ
// for_block    := _for '(' basic_stmt basic_stmt stmt_operlist ')' bstatement 
// bstatement   := block | statement

// ini code       -> parmlist[0]  
  if ( ProvideStatementOpList(operand_bnf->GetElement(2)->GetElement(0)) ) 
                                                     ERROR
// loop condition -> source  
  if ( !(source = CreateStatementOpList(operand_bnf->GetElement(3)->GetElement(0))) ) 
                                                     ERROR
// statements     -> parmlist[1]  
  if ( ProvideBStatement(operand_bnf->GetElement(6)) ) 
                                                     ERROR
// term code      -> parmlist[2]  
  if ( ProvideStatementOpList(operand_bnf->GetElement(4)) ) 
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

ExecReturnCodes OPSynFor :: Execute ( )
{
  ExecReturnCodes    rc = ERC_undefined;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
// ini code : parmlist[0]  
  if ( (rc = ExecuteStatement(0)) != ERC_success )   ERROR
    
// loop condition : source  
  while ( (rc = ExecuteSource()) == ERC_success )
  {
    if ( !source->GetValue()->IsTrue() )             LEAVESEQ
    // statements : parmlist[1]  
    switch ( rc = ExecuteStatement(1) )
    {
      case ERC_terminate :                           ERROR
      case ERC_null      :
      case ERC_success   :                           break;
      case ERC_undefined : // no statements
      case ERC_continue  : rc = ERC_success;         break;
      case ERC_break     : rc = ERC_success; 
      default            :                           LEAVESEQ
    }    
    // term code : parmlist[2]  
    // term code : parmlist[2]  
    if ( (rc = ExecuteStatement(2)) != ERC_success ) ERROR
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

logical OPSynFor :: Initialize (int32 ini_opt )
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
\brief  OPSynFor - 


\return term

\param  oper_bnf -
\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynFor"

                        OPSynFor :: OPSynFor (BNFData *oper_bnf, OPBase *parent_node )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL)
{

  op_type = NT_OPSynWhile;

  SetOPName("for");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynFor - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynFor"

                        OPSynFor :: ~OPSynFor ( )
{



}


