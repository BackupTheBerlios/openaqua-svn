/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACOPProduct



\date     $Date: 2006/04/17 14:04:48,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOPProduct"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDBExtend.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sOperEnvironment.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbinti.hpp>
#include  <sinti.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <sACOPProduct.hpp>


/******************************************************************************/
/**
\brief  ACOPProduct

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
#define    MOD_ID  "ACOPProduct"

                        ACOPProduct :: ACOPProduct (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,structdef,operenv)
{

  nodetype = NT_ACOPProduct;


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
#define    MOD_ID  "ACOPProduct"

                        ACOPProduct :: ACOPProduct (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{

BEGINSEQ
  nodetype = NT_ACOPProduct;
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
#define    MOD_ID  "ACOPProduct"

                        ACOPProduct :: ACOPProduct (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{

BEGINSEQ
  nodetype = NT_ACOPProduct;
  set_prop_path(bnf_data->GetStringValue(NULL,NULL));  
  
  nodeacc  = accopt;
  oper_bnf = bnf_data;

  if ( InitStructure(strnames_w) )                   ERROR
  

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04


\param  prodnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPProduct"

                        ACOPProduct :: ACOPProduct (ACOPProduct &prodnode_ref )
                     : ACOperation (prodnode_ref)
{

  nodetype = NT_ACOPProduct;


}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACOPProduct :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACOPProduct(*this) ) )        SDBERR(95)
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

logical ACOPProduct :: InitStructure (char *strnames_w )
{
  DBFieldDef      *fielddef;
  int32            indx = 0;
  logical          term  = NO;
BEGINSEQ
  if ( !object_ref || (nodenode && !nodenode->IsValid()) )
                                                     SDBERR(99)
  if ( !(struct_def = CreateStruct("from",strnames_w)) )
                                                     ERROR
  while ( fielddef = struct_def->GetEntry(++indx) )
  {
    fielddef->set_static_field(YES);    
    fielddef->fmcbbstr = YES;           // consider as base structure
    fielddef->fmcbrlev = RL_direct;
  }
  is_collection = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOPProduct


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOPProduct"

                        ACOPProduct :: ~ACOPProduct ( )
{

  if ( nodeidnt == NODE_ID )
    ACOperation::Close();


}


