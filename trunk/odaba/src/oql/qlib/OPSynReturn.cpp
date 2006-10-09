/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynReturn

\brief    


\date     $Date: 2006/03/12 19:21:04,51 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynReturn"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPSynReturn.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynReturn :: Execute ( )
{
  ExecReturnCodes         exec_rc = ERC_undefined;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( ExecuteStatement(0) == ERC_terminate )        ERROR
  exec_rc = ERC_return;

RECOVER
  exec_rc = ERC_terminate;
ENDSEQ
  return(exec_rc);
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

logical OPSynReturn :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( parm_bnf->IsSymbol("operand") )
                if ( SetupParameters() )             ERROR
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPSynReturn - 


\return term

\param  parent_node -
\param  parm_bnf -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynReturn"

                        OPSynReturn :: OPSynReturn (OPBase *parent_node, BNFData *parm_bnf )
                     : OPOperation (NULL,FT_undefined,NULL,parent_node,parm_bnf)
{

  op_type = NT_OPSynReturn;

  SetOPName("return");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynReturn - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynReturn"

                        OPSynReturn :: ~OPSynReturn ( )
{



}


