/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    ACTransientReference



\date     $Date: 2006/04/29 20:55:59,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACTransientReference"

#include  <popa7.h>
#ifndef   DPA_inti_HPP
#define   DPA_inti_HPP
#include  <sinti.hpp>
#include  <sDPA.h>
#endif
#include  <cNodeTypes.h>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <snode.hpp>
#include  <sACTransientReference.hpp>


/******************************************************************************/
/**
\brief  ACTransientReference

-------------------------------------------------------------------------------
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTransientReference"

     ACTransientReference :: ACTransientReference ( )
                     : bnode (),
  property_handle()
{
  nodetype = NT_ACTransientReference;
}

/******************************************************************************/
/**
\brief  i01


\param  actnode_ref
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTransientReference"

     ACTransientReference :: ACTransientReference (ACTransientReference &actnode_ref )
                     : bnode (actnode_ref),
  property_handle(actnode_ref.get_property_handle())
{
  nodetype = NT_ACTransientReference;

}

/******************************************************************************/
/**
\brief  i02


\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTransientReference"

     ACTransientReference :: ACTransientReference (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
                     : bnode (nodeptr ? Bnodeptr->get_object_ref() : NULL,
       nodeptr,dbfield_ptr,highctx,accopt),
  property_handle()
{
BEGINSEQ
  nodetype = NT_ACTransientReference;

  if ( nodefield )
    if ( !nodefield->fmcbityp &&
         !nodefield->GetDBStruct(object_ref->GetDictionary()) )
                                                     ERROR

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  i03


\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTransientReference"

     ACTransientReference :: ACTransientReference (node *nodeptr )
                     : bnode (Bnodeptr->get_object_ref(),
       nodeptr->get_nodenode(),
       Bnodeptr->get_nodefield(),
       nodeptr->get_nodenode()->GetInstContext(),
       Bnodeptr->get_nodeacc()),
  property_handle()
{
//  Transienter node für weak-typed collections in Elementary views
  delete type_inti;
  type_inti = NULL;

  nodetype = NT_ACTransientReference;
  sk_index = Bnodeptr->get_sk_index();
  
  property_handle.RegisterNode(nodeptr);
  
  if ( nodeptr->stscold() )
    stssold();

}

/******************************************************************************/
/**
\brief  Add

\return instptr - 

\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
\param  global_add
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACTransientReference :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  void         *instptr = NULL;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  if ( !(instptr = GetNode()->Add(lindx0,skey,idkey,initinst,global_add)) )
                                                     ERROR
  instptr = CopyData();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Cancel

\return term - Termination code

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical ACTransientReference :: Cancel (logical chknode )
{

  return( Switch(AUTO) );

}

/******************************************************************************/
/**
\brief  Check

\return term - Termination code

\param  autoini
\param  acccheck
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ACTransientReference :: Check (logical autoini, logical acccheck )
{
  logical                 term = NO;
//  bnode::Check();
  
  if ( acccheck && !stscfil() )
  {
    stssfil();
    GenerateEvent(DBO_Refresh);
  }


  return(term);
}

/******************************************************************************/
/**
\brief  Close

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACTransientReference :: Close ( )
{
  logical         term = NO;
  if ( nodeinst )
  {
    Switch(AUTO);
    delete nodeinst;
    nodeinst = NULL;
  }
  term = property_handle.Close();

  bnode::Close();
  return(term);
}

/******************************************************************************/
/**
\brief  CopyData

\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyData"

void *ACTransientReference :: CopyData ( )
{
  bnode                  *nodeptr;
  void                   *instptr = NULL;
  smcb                   *smcbptr = nodefield->fmcbsmcb;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  nodeptr = (bnode *)GetNode();
  if ( nodeinst )
  {
    instptr = nodeptr->get_nodeinst()->get_iselarea();

    Bnodeinst->CopySubnodes((binti *)nodeptr->get_nodeinst());
    
    ((isel *)nodeinst)->set_exd_area(((isel *)nodeptr->get_nodeinst())->get_exd_area());

    instptr = nodeinst->get_iselarea();
  }
  else
    SetArea(nodeptr->GetArea());
    
  nodecur = nodeptr->get_nodecur();
  objid   = nodeptr->get_objid();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACTransientReference :: CreateCopyNode ( )
{
  node    *nodeptr;
BEGINSEQ
  if ( !(nodeptr = new ACTransientReference(*this))) SDBERR(95)
                                                     SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateInti

\return intiptr - 

\param  nodeptr - 
\param  strdefptr - 
\param  instptr - 
\param  init_nodes
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *ACTransientReference :: CreateInti (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical init_nodes )
{
  node     *bnodeptr = GetNode();
  isel     *intiptr = NULL;
  intiptr = new isel(NULL,strdefptr,instptr,NO);
  
  if ( init_nodes )
  {
    if ( !bnodeptr->get_nodeinst() )
      bnodeptr->Check(YES);
    if ( bnodeptr->get_nodeinst() )
      intiptr->CopySubnodes((binti *)bnodeptr->get_nodeinst());
  }
  return(intiptr);
}

/******************************************************************************/
/**
\brief  FirstKey

\return keyptr - 

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

char *ACTransientReference :: FirstKey (logical chknode )
{

  return( GetNode() ? GetNode()->FirstKey(chknode) : NULL );


}

/******************************************************************************/
/**
\brief  Get

\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG


\param  indx0 - Position in collection
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACTransientReference :: Get (int32 indx0, logical chknode )
{
  void         *instptr = NULL;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( !(instptr = GetNode()->Get(indx0,chknode)) )  ERROR
  instptr = CopyData();

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1


\param  skey - 
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACTransientReference :: Get (char *skey, logical chknode )
{
  void         *instptr = NULL;
BEGINSEQ
  if ( !(instptr = GetNode()->Get(skey,chknode)) )  ERROR
  instptr = CopyData();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);

}

/******************************************************************************/
/**
\brief  GetAt

\return rindx0 - 

\param  lindx0 - 
\param  direction
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

int32 ACTransientReference :: GetAt (int32 lindx0, int16 direction, logical chknode )
{

BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( (lindx0 = GetNode()->GetAt(lindx0,direction,chknode)) != AUTO )
    CopyData();

RECOVER

ENDSEQ
  return(lindx0);
}

/******************************************************************************/
/**
\brief  GetCount

\return ecnt - 

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACTransientReference :: GetCount (logical chknode )
{

  return( IsValid() ? GetNode()->GetCount(chknode) : ERIC );


}

/******************************************************************************/
/**
\brief  GetNode

\return nodeptr - 

\param  autoini
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNode"

node *ACTransientReference :: GetNode (logical autoini )
{

  return ( this ? property_handle.get_nodeptr() : NULL );

}

/******************************************************************************/
/**
\brief  GetNodePtr

\return pnodeptr

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNodePtr"

node **ACTransientReference :: GetNodePtr ( )
{

  return this ? (node **)&property_handle : NULL;
}

/******************************************************************************/
/**
\brief  Init

\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Init"

logical ACTransientReference :: Init (void *instptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( InitInti(nodefield->GetDBStruct(),instptr) )  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsPositioned

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical ACTransientReference :: IsPositioned ( )
{
  logical            term;
BEGINSEQ
  if ( !IsValid() )                                        ERROR
  
  term = GetNode()->IsPositioned();
  
  if ( nodeinst )
  {
    if ( term && nodecur == AUTO )
      CopyData();
  
    if ( !term && nodecur >= 0 )
      Switch(AUTO);
  }
RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsSelected

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSelected"

logical ACTransientReference :: IsSelected ( )
{
  logical            term;
BEGINSEQ
  if ( !IsValid() )                                        ERROR
  
  term = GetNode()->IsSelected();
  
  if ( nodeinst )
  {
    if ( term && nodecur == AUTO )
      CopyData();
  
    if ( !term && nodecur >= 0 )
      Switch(AUTO);
  }
RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsTransient

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTransient"

logical ACTransientReference :: IsTransient ( )
{

  return ( YES );

}

/******************************************************************************/
/**
\brief  IsValid

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical ACTransientReference :: IsValid ( )
{

  return ( node::IsValid() && GetNode() ? YES : NO );

}

/******************************************************************************/
/**
\brief  LocateKey

\return term - Termination code

\param  skey - 
\param  exact - 
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical ACTransientReference :: LocateKey (char *skey, logical exact, logical chknode )
{

  return( GetNode() ? GetNode()->LocateKey(skey,exact,chknode) : YES );



}

/******************************************************************************/
/**
\brief  NextKey

\return keyptr - 

\param  skey - 
\param  switch_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextKey"

char *ACTransientReference :: NextKey (char *skey, int16 switch_level )
{

  return( GetNode() ? GetNode()->NextKey(skey,switch_level) : NULL );


}

/******************************************************************************/
/**
\brief  Open

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i00


\param  nodeptr - 
\param  dbfield_ptr - Property definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACTransientReference :: Open (node *nodeptr, DBFieldDef *dbfield_ptr )
{
  logical    term = NO;
  nodenode = nodeptr;
  nodeidnt = NODE_ID;
  SDBRESET

  if ( dbfield_ptr )
  {
    if ( dbfield_ptr->fmcbrlev == R_REFR ) 
    {
      CopyDescription(dbfield_ptr);
      Dereference(NULL);
  
      if ( dbfield_ptr->fmcbityp == T_MEMO )
      {
        fldfmcb->fmcbbyte = (fldfmcb->fmcbsize = dbfield_ptr->fmcbsize)+1;
        fldfmcb->fmcbityp = T_STRING;
        fldfmcb->fmcbsmcb = NULL;
        gvtxstb(fldfmcb->fmcbtype,"STRING",ID_SIZE);
      }
    }
    else
      SetFMCB(dbfield_ptr);
  }
  Connect(nodeptr);
  return(term);
}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACTransientReference :: Open ( )
{
  logical                 term = NO;
  nodeidnt = NODE_ID;
  SDBRESET

  // ggf. inti aus datarea setzen!!
  return(term);
}

/******************************************************************************/
/**
\brief  PositionTop_intern

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionTop_intern"

node *ACTransientReference :: PositionTop_intern ( )
{

  return ( this && !property_handle.PositionTop() ? this : NULL );

}

/******************************************************************************/
/**
\brief  Provide

\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEKP


\param  skey - 
\param  global_add
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACTransientReference :: Provide (char *skey, logical global_add )
{
  void         *instptr = NULL;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( !(instptr = GetNode()->Provide(skey,global_add)) )  ERROR
  instptr = CopyData();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1


\param  lindx0 - 
\param  global_add
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACTransientReference :: Provide (int32 lindx0, logical global_add )
{
   void         *instptr = NULL;
BEGINSEQ
  if ( !(instptr = GetNode()->Provide(lindx0,global_add)) )  ERROR
  instptr = CopyData();
RECOVER
  instptr = NULL;
ENDSEQ
   return(instptr);

}

/******************************************************************************/
/**
\brief  ResetNode

\return term - Termination code

\param  reset_all
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetNode"

logical ACTransientReference :: ResetNode (logical reset_all )
{
  logical                  reset;
  if ( reset = stscfil() )
  {
    stsrfil();
    GenerateEvent(DBO_Reset);
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  Save

\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ACTransientReference :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical        term = NO;

BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( SaveData() )                                  ERROR

  term = GetNode()->Save(switchopt,overwrite,chknode);

  if ( switchopt && nodeinst )
  {
    ((isel *)nodeinst)->set_exd_area(NULL);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SaveData

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveData"

logical ACTransientReference :: SaveData ( )
{
  bnode                  *nodeptr;
  smcb                   *smcbptr = nodefield->fmcbsmcb;
  logical                 term = NO;
BEGINSEQ
  if ( nodeinst )
  {
    nodeptr = (bnode *)GetNode();
    if ( stscsav() || nodeinst->stscmod() )
    {
      smcbptr->CopyInstance(nodeptr->get_nodeinst()->get_iselarea(),smcbptr,nodeinst->get_iselarea(),REPL_GUID);
      if ( nodeptr->Modify() )                       ERROR
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetOrder

\return term - Termination code

\param  strnames - Type name
\param  attrtype
\param  attrstr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical ACTransientReference :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  node            *nodeptr;
  logical          term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  nodeptr = GetNode();  
  if ( nodeptr->SetOrder(strnames,attrtype,attrstr) )
                                                     ERROR
  sk_index = Bnodeptr->get_sk_index();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetTransientProperty - 


\return term - Termination code

\param  nodptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransientProperty"

logical ACTransientReference :: SetTransientProperty (node *nodptr )
{
  ACTransientReference  *copy_node;
  node                  *old_node;
  logical                 term = NO;
BEGINSEQ
  old_node = property_handle.get_nodeptr();
  if ( nodptr == old_node )                          LEAVESEQ
    
  if ( origin )
    origin->SetTransientProperty(nodptr);
  else
  {
    if ( old_node->IsValid() )
      old_node->set_parent(NULL);
    
    property_handle.RegisterNode(nodptr);
    if ( copies )
    {
      copies->GoTop();
      PropertyHandle   cph(nodptr);
      while ( copy_node = (ACTransientReference *)copies->GetNext() ) 
        copy_node->get_property_handle().CopyHandle(cph);
    }
    
    if ( fldfmcb->fmcbrlev == R_REFR && GetArea() )
      *(node **)GetArea() = nodptr;
    if ( nodptr && !nodefield->get_by_reference() )
      nodptr->set_parent(this);
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Switch

\return term - Termination code

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Switch"

logical ACTransientReference :: Switch (int32 indx0 )
{
  logical          term = NO;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( nodeinst )
    if ( indx0 != nodecur && nodecur != AUTO )
      term = Save(YES,NO,NO);
  
  if ( GetNode()->Switch(indx0) )                    ERROR
  
  nodecur = GetNode()->get_nodecur();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ValidateNode

\return new_node

\param  crt_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ValidateNode"

node *ACTransientReference :: ValidateNode (logical crt_opt )
{
  node         *nodeptr = this;
  property_handle.ValidateNode(YES);
  return(this);
}

/******************************************************************************/
/**
\brief  ~ACTransientReference

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACTransientReference"

     ACTransientReference :: ~ACTransientReference ( )
{

  if ( nodeidnt == NODE_ID )
    Close();


}


