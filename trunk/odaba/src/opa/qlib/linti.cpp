/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    linti

\brief    


\date     $Date: 2006/07/16 12:27:38,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "linti"

#include  <popa7.h>
#include  <sACSRTNode.hpp>
#include  <sDBStructDef.hpp>
#include  <snode.hpp>
#include  <slinti.hpp>


/******************************************************************************/
/**
\brief  CreateSubNodes - 


\return term - Termination code

\param  nodeptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubNodes"

logical linti :: CreateSubNodes (node *nodeptr, void *instptr )
{
  ACSRTNode   *srtnode;
  DBFieldDef  *fielddef;
  int16        last;
  int16        i;
  logical                 term = NO;
BEGINSEQ
  if ( !instptr )
    instptr = iselarea;
    
  for (i=1; i<=struct_def->get_base_info().get_count(); i++)
  {
    fielddef = struct_def->GetEntry(i);
    if ( !(srtnode = new ACSRTNode(NULL,nodeptr,fielddef,GetContext(),
                                   ((char *)instptr)+fielddef->fmcbposn)) )
                                                      SDBERR(95)
                                                      SDBCERR
    node_attr.AddTail(srtnode);
  }
 
  for (last = i; i<last+struct_def->get_attr_info().get_count(); i++)
  {
    fielddef = struct_def->GetEntry(i);
    if ( !(srtnode = new ACSRTNode(NULL,nodeptr,fielddef,GetContext(),
                                 ((char *)instptr)+fielddef->fmcbposn)) )
                                                      SDBERR(95)
                                                      SDBCERR
    node_attr.AddTail(srtnode);
  }

  for (last = i; i<last+struct_def->get_refr_info().get_count(); i++)
  {
    fielddef = struct_def->GetEntry(i);
    if ( !(srtnode = new ACSRTNode(NULL,nodeptr,fielddef,GetContext(),NULL)) )
                                                      SDBERR(95)
                                                      SDBCERR
    node_refr.AddTail(srtnode);
    SetPI(srtnode,((char *)instptr));
  }

  for (last = i; i<last+struct_def->get_rshp_info().get_count(); i++)
  {
    fielddef = struct_def->GetEntry(i);
    if ( !(srtnode = new ACSRTNode(NULL,nodeptr,fielddef,GetContext(),NULL)) )
                                                      SDBERR(95)
                                                      SDBCERR
    node_rshp.AddTail(srtnode);
    SetPI(srtnode,((char *)instptr));
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  linti - 



\param  nodeptr - 
\param  strdef - Structure definition
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "linti"

     linti :: linti (node *nodeptr, DBStructDef *strdef, void *instptr )
                     : binti (nodeptr,NULL,strdef,NULL,NO)
{

  if ( strdef && strdef->smcbstyp != ST_CODE)
    CreateSubNodes(nodeptr,instptr);
  


}

/******************************************************************************/
/**
\brief  ~linti - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~linti"

     linti :: ~linti ( )
{



}


