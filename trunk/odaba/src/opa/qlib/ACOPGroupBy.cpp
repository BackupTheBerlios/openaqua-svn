/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACOPGroupBy

\brief    


\date     $Date: 2006/04/17 14:04:33,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOPGroupBy"

#include  <popa7.h>
#include  <sACOPGroupBy.hpp>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBStructDef.hpp>
#include  <sOPExpressionDecl.hpp>
#include  <sOperEnvironment.hpp>
#include  <snode.hpp>
#include  <sACOPGroupBy.hpp>


/******************************************************************************/
/**
\brief  ACOPGroupBy

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
#define    MOD_ID  "ACOPGroupBy"

                        ACOPGroupBy :: ACOPGroupBy (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,structdef,operenv)
{

  nodetype = NT_ACOPGroupBy;


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
#define    MOD_ID  "ACOPGroupBy"

                        ACOPGroupBy :: ACOPGroupBy (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{

BEGINSEQ
  nodetype = NT_ACOPGroupBy;
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
#define    MOD_ID  "ACOPGroupBy"

                        ACOPGroupBy :: ACOPGroupBy (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{

BEGINSEQ
  nodetype = NT_ACOPGroupBy;
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


\param  groupnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPGroupBy"

                        ACOPGroupBy :: ACOPGroupBy (ACOPGroupBy &groupnode_ref )
                     : ACOperation (groupnode_ref)
{

  nodetype = NT_ACOPGroupBy;


}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACOPGroupBy :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACOPGroupBy(*this) ) )        SDBERR(95)
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
\brief  CreateFields - 


\return fieldlist - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFields"

DBFieldList *ACOPGroupBy :: CreateFields ( )
{
  Dictionary             *dictionary  = GetDictionary();
  DBFieldList            *dbfieldlist = NULL;
  node                   *nodeptr     = nodenode;
  node                   *top_node    = NULL;
  node                  **pnodeptr;
  DBFieldDef             *fielddef;
  BNFData                *bnf_data    = oper_bnf;
  BNFData                *path_element;
  BNFData                *bdata;
  int32                   curindx     = 0;
BEGINSEQ
// called by ACOperation::CreateStruct

  if ( bnf_data->IsA("operand_list") )
    bnf_data = bnf_data->GetElement(1);
  if ( !bnf_data->IsA("categories") )                SDBERR(777)
  bnf_data = bnf_data->GetSymbol("categories");
  
  grouping_op = new OPExpressionDecl(oper_env,nodenode->GetPH(),bnf_data);
  
  if ( !(dbfieldlist = new DBFieldList(2)))          SDBERR(95)
                                                     SDBCERR
  fielddef  = dbfieldlist->GetEntry(1);
  nodeptr = grouping_op->Value();
  *fielddef = *Bnodeptr->get_nodefield();
  gvtxbts(fielddef->fmcbname,"value",ID_SIZE);
  
  fielddef  = dbfieldlist->GetEntry(2);
  DBFieldDef tdbfd("partition",Bnodeptr->get_nodefield()->fmcbsmcb->smcbname,
                          Bnodeptr->get_nodefield()->fmcbsmcb->smcbnsid,
                          RL_reference,UNDEF,UNDEF,UNDEF,
                          Bnodeptr->get_nodefield()->fmcbsmcb,NULL,NO,NULL,NULL,NULL);
  *fielddef = tdbfd;
  dbfieldlist->srtsetc(2);

RECOVER

ENDSEQ
  if ( top_node )
    delete top_node;
  return(NULL);
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

logical ACOPGroupBy :: InitStructure (char *strnames_w )
{
  logical          term  = NO;
BEGINSEQ
  if ( !object_ref || (nodenode && !nodenode->IsValid()) )
                                                     SDBERR(99)
  if ( !(struct_def = CreateStruct("group",strnames_w)) )
                                                     ERROR
  is_collection = YES;


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOPGroupBy


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOPGroupBy"

                        ACOPGroupBy :: ~ACOPGroupBy ( )
{

  if ( nodeidnt == NODE_ID )
    ACOperation::Close();


}


