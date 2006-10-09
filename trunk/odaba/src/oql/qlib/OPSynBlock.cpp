/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|14:26:45,35}|(REF)
\class    OPSynBlock

\brief    


\date     $Date: 2006/04/06 15:58:55,10 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynBlock"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPSynBlock.hpp>


/******************************************************************************/
/**
\brief  CreateStatements

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatements"

logical OPSynBlock :: CreateStatements ( )
{
  logical                 term = NO;
BEGINSEQ
// block         := '{' [statement(*)] '}' 
// stmt_operlist := foperand [stoplist_ext(*)] 
  
  if ( operand_bnf->IsA("stmt_operlist") 
       ? ProvideStatementOperands(operand_bnf)
       : ProvideStatements(operand_bnf,0) )          ERROR

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

ExecReturnCodes OPSynBlock :: Execute ( )
{
  ExecReturnCodes         rc = ERC_undefined;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( (rc = ExecuteStatements(0)) == ERC_terminate )
                                                     ERROR
  if ( rc == ERC_undefined )      // no statements: { } ;
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

OQL_CodeBlock OPSynBlock :: GetBlockType ( )
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

logical OPSynBlock :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( CreateStatements() )              OQLERR(145)
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPSynBlock - 


\return term

\param  oper_bnf - 
\param  parent_node - 
\param  blktype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynBlock"

                        OPSynBlock :: OPSynBlock (BNFData *oper_bnf, OPBase *parent_node, OQL_CodeBlock blktype )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL),
  block_type(blktype)

{

  op_type = NT_OPSynBlock;

  SetOPName("Block");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynBlock - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynBlock"

                        OPSynBlock :: ~OPSynBlock ( )
{



}


