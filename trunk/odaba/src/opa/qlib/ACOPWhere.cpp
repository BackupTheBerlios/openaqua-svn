/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACOPWhere



\date     $Date: 2006/04/17 14:06:00,85 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOPWhere"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDBStructDef.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOperEnvironment.hpp>
#include  <snode.hpp>
#include  <sACOPWhere.hpp>


/******************************************************************************/
/**
\brief  ACOPWhere

-------------------------------------------------------------------------------
\brief  i01


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  structdef - 
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPWhere"

                        ACOPWhere :: ACOPWhere (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,structdef,operenv),
  condition(NULL)
{

  nodetype = NT_ACOPJoin;


}

/******************************************************************************/
/**
\brief  i02


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  proppath - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPWhere"

                        ACOPWhere :: ACOPWhere (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv),
  condition(NULL)
{

BEGINSEQ
  nodetype = NT_ACOPJoin;
  set_prop_path(proppath);
  
  nodeacc  = accopt;
  
  if ( InitOperandBNF(proppath) )                    ERROR
  if ( InitStructure(strnames_w) )                   ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  bnf_data - 
\param  operenv - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPWhere"

                        ACOPWhere :: ACOPWhere (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv),
  condition(NULL)
{

BEGINSEQ
  set_prop_path(bnf_data->GetStringValue(NULL,NULL));  
  
  nodetype = NT_ACOPJoin;
  nodeacc  = accopt;
  oper_bnf = bnf_data;

  if ( InitStructure(strnames_w) )                   ERROR
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04


\param  joinnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPWhere"

                        ACOPWhere :: ACOPWhere (ACOPJoin &joinnode_ref )
                     : ACOperation (joinnode_ref),
  condition(NULL)
{

  nodetype = NT_ACOPJoin;

  CreateCondition();

}

/******************************************************************************/
/**
\brief  CreateCondition - 


\return term - Termination code

\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCondition"

logical ACOPWhere :: CreateCondition (char *strnames_w )
{
  BNFData         *bnf_data    = oper_bnf;
  logical          term  = NO;
BEGINSEQ
// .where(operand) (path) or where condition (oql)
  if ( !nodenode || !nodenode->IsValid() )           SDBERR(99)
  
  if ( bnf_data->IsA("operand_list") || bnf_data->IsA("condition"))
    bnf_data = bnf_data->GetElement(1);
  if ( !bnf_data->IsA("operand") )                   SDBERR(777)
  bnf_data = bnf_data->GetSymbol("operand");
  condition = new OPExpressionDecl(oper_env,nodenode->GetPH(),bnf_data);
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACOPWhere :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACOPWhere(*this) ) )          SDBERR(95)
                                                     SDBCERR
  if ( nodefield->get_weak_typed() || !memcmp(nodefield->fmcbname,"VOID ",5) )
    nodeptr->SetType(GetCurrentType());

RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  InitStructure - 


\return term - Termination code

\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitStructure"

logical ACOPWhere :: InitStructure (char *strnames_w )
{
  logical          term  = NO;
BEGINSEQ
  if ( !nodenode || !nodenode->IsValid() )           SDBERR(99)
  
  if ( CreateCondition() )                           ERROR
  nodefield = Bnodenode->get_nodefield();
  nodeinst  = nodenode->get_nodeinst();
  
  is_collection = YES;


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOPWhere


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOPWhere"

                        ACOPWhere :: ~ACOPWhere ( )
{

  nodefield = NULL;
  nodeinst  = NULL;
  
  if ( nodeidnt == NODE_ID )
    ACOperation::Close();

  delete condition;
  condition = NULL;

}


