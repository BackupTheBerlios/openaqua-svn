/********************************* Class Source Code ***************************/
/**
\package  OQL - 
\class    OPLocalVariable

\brief    


\date     $Date: 2006/08/25 14:50:04,46 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPLocalVariable"

#include  <poql.h>
#include  <sBNFData.hpp>
#include  <sOPParmList.hpp>
#include  <sParmList.hpp>
#include  <snode.hpp>
#include  <sOPLocalVariable.hpp>


/******************************************************************************/
/**
\brief  Initialize - 



\return term - 

\param  ini_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OPLocalVariable :: Initialize (int32 ini_opt )
{
  PropertyHandle         *ph = NULL;
  logical                 term = NO;
BEGINSEQ
  SetReopen(ini_opt);
    
  switch ( re_open )
  {
    case -1 : if ( !(source = Variables()->Get(opname)) )
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
\brief  OPLocalVariable - 



\return term - 

\param  oper_bnf - 
\param  parent_node - 
\param  parm_bnf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPLocalVariable"

     OPLocalVariable :: OPLocalVariable (BNFData *oper_bnf, OPBase *parent_node, BNFData *parm_bnf )
                     : OPVariable (NULL,oper_bnf,parent_node,parm_bnf)
{

  op_type = NT_OPLocalVariable;
  
  SetOPName(oper_bnf->StringValue());
  Initialize(0);

}

/******************************************************************************/
/**
\brief  ~OPLocalVariable - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPLocalVariable"

     OPLocalVariable :: ~OPLocalVariable ( )
{



}


