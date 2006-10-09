/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|14:26:45,35}|(REF)
\class    OPSynCase

\brief    


\date     $Date: 2006/04/06 18:16:19,25 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynCase"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPSynCase.hpp>


/******************************************************************************/
/**
\brief  CreateStatements - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatements"

logical OPSynCase :: CreateStatements ( )
{
  BNFData                *oper;
  int32                   index = 0;
  logical                 term = NO;
BEGINSEQ
// case_stmt  := [debug_opt] _case simple_op ':' statement(*)
// other_stmt := [debug_opt] _default ':' statement(*)
  
  if ( operand_bnf->GetElement(0)->IsSymbol("debug_opt") )
  {
    SetBreakPoint(operand_bnf->GetElement(0));
    index = 1;
  }
  
  oper = operand_bnf->GetElement(index);
  switch ( oper->GetSymbolCode("_default","_case") )
  {
    case 1 : block_type = CB_DefaultBlock;
             break;
    case 2 : block_type = CB_CaseBlock;
             if ( ProvideSimpleOp(operand_bnf->GetElement(index+1)) )
                                                     ERROR
             break;
    default: OQLSERR(99)
  }
  if ( ProvideBlock(operand_bnf,block_type) )        ERROR

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

ExecReturnCodes OPSynCase :: Execute ( )
{
  int32              indx0 = 0;
  ExecReturnCodes    rc    = ERC_undefined;

BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( (block_type == CB_CaseBlock) )
  {
    if ( !source )                                   OQLSERR(99)
    if ( ExecuteParameter(0) != ERC_success )        ERROR
    
    if ( *source->GetValue() != *Parmlist()->GetAt(0)->GetValue() )
                                                     LEAVESEQ
    indx0 = 1;
  }
  if ( (rc = ExecuteStatements(indx0)) == ERC_undefined ) // no statements in case
    rc = ERC_success;
  RegisterLastValue();
RECOVER
  ResetValue();
  rc = ERC_terminate;
ENDSEQ
  return(rc);
}

/******************************************************************************/
/**
\brief  GetBlockType - 


\return blktype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBlockType"

OQL_CodeBlock OPSynCase :: GetBlockType ( )
{

  return(block_type);

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

logical OPSynCase :: Initialize (int32 ini_opt )
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
\brief  OPSynCase - 


\return term

\param  oper_bnf - 
\param  parent_node - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynCase"

                        OPSynCase :: OPSynCase (BNFData *oper_bnf, OPBase *parent_node )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL),
  block_type(CB_undefined)
{

  op_type = NT_OPSynCase;

  SetOPName("case");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynCase - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynCase"

                        OPSynCase :: ~OPSynCase ( )
{

  source = NULL;

}


