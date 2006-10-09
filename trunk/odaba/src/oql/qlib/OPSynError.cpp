/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPSynError

\brief    


\date     $Date: 2006/03/12 19:21:02,78 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPSynError"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sDictionary.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sOPSynError.hpp>


/******************************************************************************/
/**
\brief  Execute - 


\return exec_rc -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

ExecReturnCodes OPSynError :: Execute ( )
{
  OPBase                 *op_node;
  ExecReturnCodes         exec_rc = ERC_undefined;
BEGINSEQ
  if ( CheckCO() )                                   ERROR
  
  if ( ExecuteParameter(0) != ERC_success )          ERROR
  
  if ( op_node = Parmlist()->GetAt(0) )
    InitLastErrorCode(op_node->GetValue()->GetInt());
    
  exec_rc = ERC_error;


RECOVER
  exec_rc = ERC_terminate;
ENDSEQ
  return(exec_rc);
}

/******************************************************************************/
/**
\brief  InitLastErrorCode - 



\param  err_code -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitLastErrorCode"

void OPSynError :: InitLastErrorCode (int32 err_code )
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

logical OPSynError :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( parm_bnf->IsSymbol("operand") )
                if ( SetupParameters() )             ERROR
              InitLastErrorCode(0);
    default : re_open = 0;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPSynError - 


\return term

\param  parent_node -
\param  parm_bnf -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPSynError"

                        OPSynError :: OPSynError (OPBase *parent_node, BNFData *parm_bnf )
                     : OPOperation (NULL,FT_undefined,NULL,parent_node,parm_bnf)
{

  op_type = NT_OPSynError;

  SetOPName("error");
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPSynError - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPSynError"

                        OPSynError :: ~OPSynError ( )
{



}


