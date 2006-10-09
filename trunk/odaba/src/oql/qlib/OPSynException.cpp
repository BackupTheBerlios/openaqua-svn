/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynException

\brief    


\date     $Date: 2006/03/12 19:21:03,14 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynException"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPSynException.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynException :: Execute ( )
{
  OPBase                 *op_node;
  ExecReturnCodes         exec_rc = ERC_success;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( ExecuteParameter(0) != ERC_success )          ERROR
  
  if ( op_node = Parmlist()->GetAt(0) )
    InitLastExceptionCode(op_node->GetValue()->GetInt());
    
  exec_rc = ERC_terminate;


RECOVER
  exec_rc = ERC_terminate;
ENDSEQ
  return(exec_rc);
}

/******************************************************************************/
/**
\brief  InitLastExceptionCode - 



\param  err_code -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitLastExceptionCode"

void OPSynException :: InitLastExceptionCode (int32 err_code )
{
  PropertyHandle       *err;
   if ( !(err = DictHandle()->GetGlobalVariable("_LastExceptionCode")) )
   {
     PropertyHandle    ph((int32)0);
     err = DictHandle()->CreateGlobalVariable(ph,"_LastExceptionCode");
   }

   if ( err )
     *err = err_code;


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

logical OPSynException :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt); 
    
  switch ( re_open )
  {
    case -1 : if ( parm_bnf->IsSymbol("operand") )
                if ( SetupParameters() )             ERROR
              InitLastExceptionCode(0);
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPSynException - 



\param  parent_node -
\param  parm_bnf -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynException"

                        OPSynException :: OPSynException (OPBase *parent_node, BNFData *parm_bnf )
                     : OPOperation (NULL,FT_undefined,NULL,parent_node,parm_bnf)
{

  op_type = NT_OPSynException;

  SetOPName("exception");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynException - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynException"

                        OPSynException :: ~OPSynException ( )
{



}


