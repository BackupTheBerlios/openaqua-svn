/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACShareBase

\brief    


\date     $Date: 2006/03/29 21:17:25,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACShareBase"

#include  <popa7.h>
#include  <sACExtend.hpp>
#include  <sACProperty.hpp>
#include  <sACStructure.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sisel.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <srefs.hpp>
#include  <sACShareBase.hpp>


/******************************************************************************/
/**
\brief  ACShareBase - 


-------------------------------------------------------------------------------
\brief  i0


\param  nodeptr - 
\param  sysnode - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  extoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACShareBase"

                        ACShareBase :: ACShareBase (node *nodeptr, ACExtend *sysnode, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, PIACC accopt )
                     : ACRelationship(nodeptr,sysnode,dbfield_ptr,highctx,extoff,accopt),
  autoid_key(NO)
{

BEGINSEQ
  nodetype = NT_ACShareBase;
  
  if ( InitReference() )                               ERROR
  
  if ( InitIsel(system_node->GetMainBase(),instptr) )  ERROR
    
  if ( Bnodeinst->HasBaseAutoIdKey() || HasBaseAutoIdKey() )
    autoid_key = YES;
      

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03


\param  dbfield_ptr - Property definition
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACShareBase"

                        ACShareBase :: ACShareBase (DBFieldDef *dbfield_ptr, void *instptr )
                     : ACRelationship (),
  autoid_key(NO)
{

  nodetype = NT_ACShareBase;
  nodefield = dbfield_ptr;
  
  node::Open(NULL,dbfield_ptr);

  nodeinst = new isel(dbfield_ptr->GetDBStruct(),instptr);


}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACShareBase"

                        ACShareBase :: ACShareBase ( )
                     : ACRelationship (),
  autoid_key(NO)
{

  nodetype = NT_ACShareBase;


}

/******************************************************************************/
/**
\brief  i2


\param  basenode_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACShareBase"

                        ACShareBase :: ACShareBase (ACShareBase &basenode_ref )
                     : ACRelationship (basenode_ref),
  autoid_key(basenode_ref.get_autoid_key())
{



}

/******************************************************************************/
/**
\brief  Add - 


\return instptr - 

\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACShareBase :: Add (int32 lindx0, logical global_add )
{
  ACRelationship  *nodeptr = NULL;
  ACExtend        *sysnode;
  binti           *bintiptr = Bnodenode->get_bnodeinst();
  logical          siw = AUTO;
  logical          term = NO;
  int16            talevel = 0;
  logical          extlock = noderefl->stsclck();
  logical          release_node = YES;
  void            *instptr;
BEGINSEQ
  if ( !extlock && LockSet(NO) )                     ERROR
  
  talevel = StartTA();
  
  if ( !(instptr = ProvideInstance(lindx0,global_add)) )
                                                     ERROR
  
  siw = bintiptr->SetInWork(YES);
  if ( (!nodeinst->SetInWork(NO) || nodeinst->GetID() == bintiptr->GetID())
       && (nodeptr = GetInverse(NO)) )
  {
//    nodeptr->set_nodewrit(AUTO); wuerde im SetType_intern das switch verhindern, aber unklar ist, welcher Fehler damit behoben werden sollte!
    if ( nodeptr->IsVariableType() )
      if ( nodeptr->SetType(nodenode->GetCurrentType()) )
                                                     ERROR
    
//  if ( !(term = nodeptr->LNode::AddID(bintiptr,bintiptr->GetID())) )   
    if ( !(term = nodeptr->LNode::AddID(Bnodeinst,bintiptr->GetID())) )    // rk 22.1.06
      if ( (sysnode = ((LNode *)nodenode)->GetSystemNode()) && // Instanz liegt im Extent
           sysnode != nodeptr->GetSystemNode() && nodeptr->get_system_node() )
        term = nodeptr->GetKeySMCB()->smcbsts.stscnof() 
               ?  nodeptr->get_system_node()->IdentityAdd(bintiptr,nodeptr->GetSortKeySMCB()->smcbname,NO)
               :  nodeptr->get_system_node()->Add(bintiptr,NO,NO);
    nodeptr->ReleaseField();
    release_node = NO;
    
    if ( term )                                      SDBERR(152)
    Save(NO,NO,NO);
  }
  else
    if ( SDBERROR == 74 )                            ERROR
RECOVER
  if ( SDBERROR )
    StructFieldError();
  instptr = NULL;
  if ( nodeptr )
    nodeptr->set_nodewrit(NO);
ENDSEQ
  if ( nodeptr && release_node )
    nodeptr->ReleaseField();
  if ( siw != 255 )
    bintiptr->SetInWork(siw);
  if ( UnlockSet(extlock,NO) )
    instptr = NULL;
  if ( talevel )
    if ( StopTA(!instptr) )
      instptr = NULL;
  return(instptr);
}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACShareBase :: Close ( )
{

  ACRelationship::Close();

  return(NO);
}

/******************************************************************************/
/**
\brief  CreateCopyNode - 


\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACShareBase :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACShareBase(*this) ) )        SDBERR(95)
                                                     SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum - 
-------------------------------------------------------------------------------
\brief  NODEGID


\param  indx0 - Position in collection
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACShareBase :: GetID (int32 indx0, logical chknode, logical pif_opt )
{

  return(nodenode->GetID(indx0,chknode,pif_opt));

}

/******************************************************************************/
/**
\brief  NODEGID_


\param  keyptr - 
\param  chknode - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACShareBase :: GetID (char *keyptr, logical chknode, logical pif_opt )
{

  return(nodenode->GetID(keyptr,chknode,pif_opt));

}

/******************************************************************************/
/**
\brief  HasBaseAutoIdKey - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasBaseAutoIdKey"

logical ACShareBase :: HasBaseAutoIdKey ( )
{


  return (   system_node->get_root_extend()->get_extend_node()->
                          get_noderefl()
           ? system_node->get_root_extend()->get_extend_node()->
                          get_noderefl()->get_autoid_key() 
           : NO );

}

/******************************************************************************/
/**
\brief  Locate - 


\return term - Termination code

\param  entnr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

logical ACShareBase :: Locate (EB_Number entnr, logical read_opt )
{
  logical                 term = NO;
BEGINSEQ
  if ( entnr.get_ebsnum() != LNode::GetID(0).get_ebsnum() ) 
                                                     ERROR
  if ( !IsPositioned() && read_opt )
    if ( !Get(0) )                                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetAutoIdent - 


\return cond_setting - 

\param  kcbptr - 
\param  attrtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoIdent"

char ACShareBase :: SetAutoIdent (kcb *kcbptr, int attrtype )
{
  char       cond_setting = NO;
BEGINSEQ
  if ( !autoid_key )                                 LEAVESEQ
  if ( cond_setting = Bnodeinst->SetAutoIdent(kcbptr,attrtype) ) 
                                                     LEAVESEQ
  cond_setting = system_node->SetAutoIdent(Bnodeinst,kcbptr,attrtype);

ENDSEQ
  return(cond_setting);
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

logical ACShareBase :: SetupNode (logical create_ref, logical retain_mod )
{

  ResetNode(stscfil());
  return ( ACRelationship::SetupNode(create_ref,retain_mod) );

}

/******************************************************************************/
/**
\brief  ~ACShareBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACShareBase"

                        ACShareBase :: ~ACShareBase ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


