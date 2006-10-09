/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    ACOPSelect

\brief    


\date     $Date: 2006/04/17 14:05:46,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACOPSelect"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDBStructDef.hpp>
#include  <sOperEnvironment.hpp>
#include  <snode.hpp>
#include  <sACOPSelect.hpp>


/******************************************************************************/
/**
\brief  ACOPSelect - 


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
#define    MOD_ID  "ACOPSelect"

                        ACOPSelect :: ACOPSelect (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt )
                     : ACOperation (obhandle,nodeptr,structdef,operenv)
{


  nodetype = NT_ACOPSelect;


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
#define    MOD_ID  "ACOPSelect"

                        ACOPSelect :: ACOPSelect (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{


BEGINSEQ
  nodetype = NT_ACOPSelect;
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
#define    MOD_ID  "ACOPSelect"

                        ACOPSelect :: ACOPSelect (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w )
                     : ACOperation (obhandle,nodeptr,NULL,operenv)
{


BEGINSEQ
  nodetype = NT_ACOPSelect;
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


\param  selnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACOPSelect"

                        ACOPSelect :: ACOPSelect (ACOPSelect &selnode_ref )
                     : ACOperation (selnode_ref)
{


  nodetype = NT_ACOPSelect;


}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACOPSelect :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACOPSelect(*this) ) )         SDBERR(95)
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
\brief  InitStructure

\return term - Termination code

\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitStructure"

logical ACOPSelect :: InitStructure (char *strnames_w )
{
  logical     term = NO;
BEGINSEQ
  if ( !oper_bnf )                                   LEAVESEQ
    
  if ( nodenode && !nodenode->GetStructDef() )       SDBERR(99)
  
  if ( !(struct_def = CreateStruct("select",strnames_w)) )
                                                     ERROR
  is_collection = YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACOPSelect - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACOPSelect"

                        ACOPSelect :: ~ACOPSelect ( )
{

  if ( nodeidnt == NODE_ID )
    Close();




}


