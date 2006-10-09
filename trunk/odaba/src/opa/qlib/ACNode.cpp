/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACNode

\brief    


\date     $Date: 2006/08/30 12:59:48,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACNode"

#include  <popa7.h>
#ifndef   DLL_ACNode_HPP
#define   DLL_ACNode_HPP
#include  <sACNode.hpp>
#include  <sDLL.h>
#endif
#ifndef   DPA_inti_HPP
#define   DPA_inti_HPP
#include  <sinti.hpp>
#include  <sDPA.h>
#endif
#include  <sACGenericAttr.hpp>
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sInstBuffer.hpp>
#include  <sPropertyHandle.hpp>
#include  <sacb.hpp>
#include  <sdbf.hpp>
#include  <sexd.hpp>
#include  <sgmvl.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <srefTable.hpp>
#include  <sACNode.hpp>


/******************************************************************************/
/**
\brief  ACNode - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACNode"

     ACNode :: ACNode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
                     : LNode (),
  version(CUR_VERSION)
{

  nodetype = NT_ACNode;
  
  Open(obhandle,nodeptr,dbfield_ptr,highctx,accopt);
  


}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACNode"

     ACNode :: ACNode ( )
                     : LNode (),
  version(CUR_VERSION)
{

  nodetype = NT_ACNode;
  


}

/******************************************************************************/
/**
\brief  i2 - 



\param  acnode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACNode"

     ACNode :: ACNode (ACNode &acnode_ref )
                     : LNode (acnode_ref),
  version(acnode_ref.get_version())
{



}

/******************************************************************************/
/**
\brief  Check - 



\return term - Termination code

\param  autoini - 
\param  acccheck - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ACNode :: Check (logical autoini, logical acccheck )
{
  logical   term = NO;

BEGINSEQ
//  SDBRESET  kommt in bnode
  if ( stscusr1() )                                  LEAVESEQ
  if ( stscerr() )                                   ERROR

  if ( autoini )
    if ( Init(NULL) )                                ERROR
  
  if ( LNode::Check(autoini,acccheck) )              ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CreateCopyNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACNode :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACNode(*this) ) )            SDBERR(95)
                                                    SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  obhandle - Database Object handle
\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACNode :: Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
{
  logical                 term = NO;
BEGINSEQ
  if ( LNode::Open(obhandle,nodeptr,dbfield_ptr,highctx,accopt) )
                                                     ERROR
  version = nodenode && nodefield && nodefield->fmcbrlev != R_REFR
            ? ((ACNode *)nodenode)->get_version()
            : CUR_VERSION;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PrevVersion - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrevVersion"

logical ACNode :: PrevVersion ( )
{

  return( SetVersion(GetVersion()-1) );


}

/******************************************************************************/
/**
\brief  SetVersion - 



\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical ACNode :: SetVersion (uint16 version_nr )
{
  int32       lindx0     = AUTO;
  logical     positioned = NO;            
  uint16      count;
  logical     term       = NO;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  
  if ( positioned = nodeinst->IsPositioned() )
  {
    lindx0 = GetCurrentIndex();
    Save(YES,YES,NO);
  }  

  if ( type_inti )
  {
    count = type_inti->GetSize();
    while ( count-- )
      (*type_inti)[count]->SetVersion(version_nr);
  }
  
  if ( inti_buffer )
    inti_buffer->SetVersion(version_nr);
  
  if ( !type_inti && !inti_buffer && nodeinst )
    nodeinst->SetVersion(version_nr);
  
  version = version_nr;
  
  if ( positioned )
    Get(lindx0);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupNode - 



\return term - Termination code

\param  create_ref - 
\param  retain_mod - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNode"

logical ACNode :: SetupNode (logical create_ref, logical retain_mod )
{
  node       *nodeptr;
  logical     is_ini = nodeinst ? nodeinst->stscini() : NO;
  logical     is_mod = nodeinst ? nodeinst->stscmod() : NO;
  logical     is_coll_mod = stscmod();
  logical     term = NO;
BEGINSEQ
  if ( stscerr() )                                   LEAVESEQ
  
  if ( !noderefp ) 
  {
    if ( !create_ref )                               LEAVESEQ
    if ( InitReference() )                           ERROR
  }  
   
// Das wird jetzt für ShareBase und GenAttr explizit im SetupNode gemacht. 
// Für die anderen macht es entweder binti::SetupSubNodes oder ResetSubNodes   
//  ResetNode();

  if ( copies )
  {
    copies->GoTop();
    while ( nodeptr = copies->GetNext() )
      nodeptr->SetupNode(create_ref,NO);
  }
  
  if ( retain_mod && nodecur == AUTO )
  {
    if ( is_ini )
      nodeinst->stssini();
    if ( is_mod )
      nodeinst->stssmod();
    if ( is_coll_mod )
      SetMod();
  }
//  stssfil();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateCurIndex - 



\return term - Termination code

\param  setup - 
\param  overwrite - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateCurIndex"

logical ACNode :: UpdateCurIndex (logical setup, logical overwrite )
{
  int16     talevel = 0;
  exd      *exdptr;
  gmvl     *refptr;
  logical   siw;
  char     *keyptr;
  logical   term    = NO;

BEGINSEQ
  if ( exdptr = Bnodeinst->GetEXD() )
  {
    siw = nodeinst->SetInWork(YES);
    term = ACNode::Save(!setup,overwrite,NO);
    exdptr->SetInWork(siw);
    if ( term )                                      ERROR
  }
  else
    if ( ACNode::Save(!setup,overwrite,NO) )         ERROR

  if ( setup && noderefp && noderefp->stscusr1() )             // generic index
  {
    refptr = (gmvl *)noderefl->GetReference((char *)noderefp->get_refsakcb()->GetKeyName());
    if ( refptr->GetReference(get_bnodeinst()->GetGenAttrNode(refptr->GetGenAttribute(),NULL)->get_attr_type(),YES) != noderefp )
      setup = NO;
  }
  
  if ( setup && (keyptr = ExtractSortKey(NULL,nodeinst->get_iselarea(),NO)) )
    if ( (nodecur = noderefp->WSGetIndex(keyptr,nodeinst->GetID(),YES)) == AUTO )
    {
      if ( !noderefp->IsTemporary() )                ERROR
      noderefp->stssold();
      if ( SetupIndex(YES) )                         ERROR
      if ( (nodecur = noderefp->WSGetIndex(keyptr,nodeinst->GetID(),YES)) == AUTO )
                                                     ERROR
    }
RECOVER
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
  return(term);

}

/******************************************************************************/
/**
\brief  ~ACNode - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACNode"

     ACNode :: ~ACNode ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


