/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynSwitch

\brief    


\date     $Date: 2006/03/12 19:21:04,75 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynSwitch"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPSynSwitch.hpp>


/******************************************************************************/
/**
\brief  CreateStatements - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStatements"

logical OPSynSwitch :: CreateStatements ( )
{
  int32                   indx0 = 0;
  OPBase                 *op_node;
  BNFData                *bdata;
  logical                 term = NO;
BEGINSEQ
// case_block   := _switch condition  '{' [ case_stmt(*) ] [ other_stmt ] '}'
// condition    := '(' doperand ')'
  
// init source
  if ( !(source = CreateDOperand(operand_bnf->GetElement(1)->GetElement(1))) )
                                                     ERROR
// init parameters (case blocks
  indx0 = 3; // first case or other
  while ( bdata = operand_bnf->GetElement(indx0++) )
    if ( bdata->IsSymbol("case_stmt") || 
         bdata->IsSymbol("other_stmt")   )
    {
      if ( !(op_node = CreateCase(bdata)) )          ERROR
      Parmlist()->Add(op_node);
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

ExecReturnCodes OPSynSwitch :: Execute ( )
{
  ExecReturnCodes    rc = ERC_undefined;
  OPBase            *switch_op = source;
  OPBase            *case_node;
  int32              indx0 = 0;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( (rc = ExecuteSource()) == ERC_success )
  {
    while ( case_node = Parmlist()->GetAt(indx0++) )
    {
      case_node->SetSource(switch_op);
      switch ( rc = ExecuteTrace(case_node) )
      {
        case ERC_terminate : ERROR
        case ERC_success   : 
        case ERC_continue  : switch_op = NULL;
        case ERC_undefined : break;
        case ERC_break     : rc = ERC_success;
        default            : LEAVESEQ
      }
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

logical OPSynSwitch :: Initialize (int32 ini_opt )
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
\brief  OPSynSwitch - 


\return term

\param  oper_bnf -
\param  parent_node -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynSwitch"

                        OPSynSwitch :: OPSynSwitch (BNFData *oper_bnf, OPBase *parent_node )
                     : OPOperation (NULL,FT_undefined,oper_bnf,parent_node,NULL)
{

  op_type = NT_OPSynSwitch;

  SetOPName("switch");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynSwitch - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynSwitch"

                        OPSynSwitch :: ~OPSynSwitch ( )
{



}


