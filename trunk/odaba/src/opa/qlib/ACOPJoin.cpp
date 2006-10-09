/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACOPJoin



\date     $Date: 2006/04/17 14:04:38,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOPJoin"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBStructDef.hpp>
#include  <sOperEnvironment.hpp>
#include  <snode.hpp>
#include  <sACOPJoin.hpp>


/******************************************************************************/
/**
\brief  ACOPJoin

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
#define    MOD_ID  "ACOPJoin"

                        ACOPJoin :: ACOPJoin (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,structdef,operenv)
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
#define    MOD_ID  "ACOPJoin"

                        ACOPJoin :: ACOPJoin (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
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
#define    MOD_ID  "ACOPJoin"

                        ACOPJoin :: ACOPJoin (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{

BEGINSEQ
  nodetype = NT_ACOPJoin;
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


\param  joinnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPJoin"

                        ACOPJoin :: ACOPJoin (ACOPJoin &joinnode_ref )
                     : ACOperation (joinnode_ref)
{

  nodetype = NT_ACOPJoin;

}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACOPJoin :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACOPJoin(*this) ) )           SDBERR(95)
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

DBFieldList *ACOPJoin :: CreateFields ( )
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
  if ( !bnf_data->IsA("access_path") )               SDBERR(777)
  bnf_data = bnf_data->GetSymbol("access_path");
  
  if ( !(dbfieldlist = new DBFieldList(bnf_data->GetElementCount())))
                                                     SDBERR(95)
                                                     SDBCERR
  
  path_element  = bnf_data->GetElement(curindx++);  
  while ( path_element )
  {
    prop_path = path_element->GetStringValue(NULL,NULL);
    if ( !nodeptr )
      top_node = nodeptr = object_ref->CreateNode(prop_path,nodeacc);
    else
      if ( pnodeptr = GetNodePtr(prop_path) )
        nodeptr = *pnodeptr;
    
    if ( !nodeptr )                                  ERROR
      
    fielddef = dbfieldlist->GetEntry(curindx);
    *fielddef = *Bnodeptr->get_nodefield();
    fielddef->fmcbrlev  = RL_direct;
    fielddef->set_static_field(YES);    
    fielddef->fmcbbstr  = YES;           // consider as base structure
    fielddef->fmcbtrans = YES;           // consider as subnode
    
    path_element = (bdata = bnf_data->GetElement(curindx++)) 
                   ? bdata->GetElement(1)
                   : NULL;
  } 
  dbfieldlist->srtsetc(curindx-1);

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

logical ACOPJoin :: InitStructure (char *strnames_w )
{
  logical                 term = NO;
BEGINSEQ
  if ( !object_ref || (nodenode && !nodenode->IsValid()) )
                                                     SDBERR(99)
  if ( !(struct_def = CreateStruct("join",strnames_w)) )
                                                     ERROR
  is_collection = YES;


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOPJoin


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOPJoin"

                        ACOPJoin :: ~ACOPJoin ( )
{

  if ( nodeidnt == NODE_ID )
    ACOperation::Close();


}


