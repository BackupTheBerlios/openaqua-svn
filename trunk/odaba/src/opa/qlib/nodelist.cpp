/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    nodelist

\brief    


\date     $Date: 2006/03/12 19:19:17,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "nodelist"

#include  <popa7.h>
#include  <sCTX_Property.hpp>
#include  <sbnode.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <snodelist.hpp>


/******************************************************************************/
/**
\brief  DeleteNodes - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteNodes"

void nodelist :: DeleteNodes ( )
{
  node   *nodeptr;
  if ( IsOwner() )
    while ( nodeptr = RemoveTail() )
      if ( nodeptr->get_nodeidnt() == NODE_ID )
        delete nodeptr;


}

/******************************************************************************/
/**
\brief  GetNextBNode - 


\return bnodeptr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextBNode"

bnode *nodelist :: GetNextBNode ( )
{
  node     *nodeptr = GetNext();

  return(nodeptr ? (bnode *)nodeptr : NULL);
}

/******************************************************************************/
/**
\brief  GetNode - 


\return nodeptr -
-------------------------------------------------------------------------------
\brief i0


\param  fldname -
\param  highprop_ctx -
\param  recursiv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNode"

node *nodelist :: GetNode (char *fldname, CTX_Property *highprop_ctx, logical recursiv )
{
  node         **pnodeptr = NULL;
  pnodeptr = GetNodePtr(fldname,highprop_ctx,recursiv);
  return(pnodeptr ? *pnodeptr : NULL);
}

/******************************************************************************/
/**
\brief i1


\param  fldname -
\param  proppath -
\param  recursiv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNode"

node *nodelist :: GetNode (char *fldname, char *proppath, logical recursiv )
{
  node         **pnodeptr = NULL;

  pnodeptr = GetNodePtr(fldname,proppath,recursiv);
  return(pnodeptr ? *pnodeptr : NULL);
}

/******************************************************************************/
/**
\brief  GetNodePtr - 


\return nodeptr -
-------------------------------------------------------------------------------
\brief i0


\param  fldname -
\param  highprop_ctx -
\param  recursiv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node **nodelist :: GetNodePtr (char *fldname, CTX_Property *highprop_ctx, logical recursiv )
{
  node          *nodeptr  = NULL;
  node         **pnodeptr = NULL;
  char          *p = NULL;
  char           name[ID_SIZE+1];
BEGINSEQ
  gvtxbts(name,fldname,ID_SIZE);
  if ( !(p = strchr(name,'(')) )
    gvtxstb(name,name,ID_SIZE);
  
  GoTop();
  while ( (pnodeptr = &GetNext()) && (nodeptr = *pnodeptr) )
  {
    if ( (!p && !memcmp(nodeptr->get_fldfmcb()->fmcbname,name,ID_SIZE)) ||
         (p && !strcmp(name,nodeptr->get_prop_path()))                   )
      if ( !highprop_ctx || !nodeptr->GetContext() || 
           !nodeptr->GetContext()->FindContext(highprop_ctx) )
                                                     LEAVESEQ
    if ( recursiv )
      if ( pnodeptr = nodeptr->get_nodeinst()->GetPropNodePtr(fldname,highprop_ctx) )
                                                     LEAVESEQ
  }
  pnodeptr = NULL;
ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief i1


\param  fldname -
\param  proppath -
\param  recursiv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node **nodelist :: GetNodePtr (char *fldname, char *proppath, logical recursiv )
{
  node          *nodeptr  = NULL;
  node         **pnodeptr = NULL;
  char           name[ID_SIZE];
BEGINSEQ
  gvtxstb(name,fldname,sizeof(name));
  
  GoTop();
  while ( (pnodeptr = &GetNext()) && (nodeptr = *pnodeptr) )
  {
    if ( !memcmp(nodeptr->get_fldfmcb()->fmcbname,name,ID_SIZE) )
    {
      if ( !proppath ||
           (nodeptr->get_prop_path() && !strcmp(proppath,nodeptr->get_prop_path())) )
                                                     LEAVESEQ
    }
    
    if ( recursiv )
      if ( pnodeptr = nodeptr->get_nodeinst()->GetPropNodePtr(fldname,proppath) )
                                                     LEAVESEQ
  }

  pnodeptr = NULL;
ENDSEQ
  return(pnodeptr);
}

/******************************************************************************/
/**
\brief  Modify - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

logical nodelist :: Modify ( )
{
  node      *nodeptr;
  logical    term = NO;
  GoTop();
  while ( nodeptr = GetNext() )
    if ( nodeptr->get_nodeinst()->IsPositioned() && nodeptr->IsWrite() && !nodeptr->Modify() )
      term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  nodelist - 


-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "nodelist"

                        nodelist :: nodelist ( )
                     : DLL(node) ()
{



}

/******************************************************************************/
/**
\brief i1


\param  nlist_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "nodelist"

                        nodelist :: nodelist (nodelist &nlist_ref )
                     : DLL(node) (nlist_ref)
{



}

/******************************************************************************/
/**
\brief  operator= - 


\return nlist_ref -

\param  nlist_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

nodelist &nodelist :: operator= (nodelist &nlist_ref )
{

  DeleteNodes();
  
  *((DLL(node) *)this) = *((DLL(node) *)&nlist_ref);
  return(*this);
}

/******************************************************************************/
/**
\brief  ~nodelist - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~nodelist"

                        nodelist :: ~nodelist ( )
{

  if ( IsOwner() )
    DeleteNodes();


}


