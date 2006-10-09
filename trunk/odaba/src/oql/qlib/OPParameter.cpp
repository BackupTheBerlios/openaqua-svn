/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPParameter

\brief    


\date     $Date: 2006/08/25 14:50:30,92 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPParameter"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPBase.hpp>
#include  <sOPParmList.hpp>
#include  <sParmList.hpp>
#include  <snode.hpp>
#include  <sOPParameter.hpp>


/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPParameter :: Initialize (int32 ini_opt )
{
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( !(source = Parameters()->Get(opname)) )
                                                     OQLSERR(99)
              value.RegisterNode(source->Value());             
              SetDescription(source->GetDescription());
              if ( SetupParameters() )               ERROR
    default : re_open = 0;
  }  


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OPParameter - 



\return term - 

\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPParameter"

     OPParameter :: OPParameter (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (NULL,oper_bnf,parent_node,parm_bnf)
{

  op_type = NT_OPParameter;
  
  SetOPName(oper_bnf->StringValue());
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPParameter - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPParameter"

     OPParameter :: ~OPParameter ( )
{



}


