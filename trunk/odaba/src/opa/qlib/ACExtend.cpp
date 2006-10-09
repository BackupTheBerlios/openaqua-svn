/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACExtend

\brief    


\date     $Date: 2006/08/29 20:00:17,89 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACExtend"

#include  <popa7.h>
#ifndef   DLL_ACExtend_HPP
#define   DLL_ACExtend_HPP
#include  <sACExtend.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_ACNode_HPP
#define   DLL_ACNode_HPP
#include  <sACNode.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_ACTopNode_HPP
#define   DLL_ACTopNode_HPP
#include  <sACTopNode.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_DBExtend_HPP
#define   DLL_DBExtend_HPP
#include  <sDBExtend.hpp>
#include  <sDLL.h>
#endif
#include  <sACExtend.hpp>
#include  <sACNode.hpp>
#include  <sACRelationship.hpp>
#include  <sACTopNode.hpp>
#include  <sDBExtend.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sbinti.hpp>
#include  <sbnode.hpp>
#include  <seb_RootBase.hpp>
#include  <sinti.hpp>
#include  <sisel.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <srefTable.hpp>
#include  <sACExtend.hpp>


/******************************************************************************/
/**
\brief  ACExtend - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  lobhandle - 
\param  dbextdef - Extent definition
\param  ac_baseext - 
\param  accopt - Access mode
\param  extadd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACExtend"

     ACExtend :: ACExtend (LACObject *lobhandle, DBExtend *dbextdef, ACExtend *ac_baseext, PIACC accopt, logical extadd )
                     : TypeKey(dbextdef->GetNameKey()),
  extend_path(NULL),
  accmode(accopt),
  extend_node(NULL),
  base_extend(NULL),
  deri_extend(NULL),
  root_extend(NULL),
  int_extref(),
  topnode_list(NULL),
  object_ref(NULL),
  extent_lock(YES),
  high_extent(NULL),
  acrel_node(NULL)
{

  Open(lobhandle,dbextdef,ac_baseext,accopt,extadd);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  base_node - 
\param  extname - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACExtend"

     ACExtend :: ACExtend (bnode *base_node, char *extname )
                     : TypeKey(),
  extend_path(NULL),
  accmode(base_node->get_nodeacc()),
  extend_node(NULL),
  base_extend(NULL),
  deri_extend(NULL),
  root_extend(NULL),
  int_extref(),
  topnode_list(NULL),
  object_ref(NULL),
  extent_lock(YES),
  high_extent(NULL),
  acrel_node(NULL)
{
  node     *nodeptr = NULL;
  ACExtend *baseext = NULL;
  char      string[ID_SIZE+1];
BEGINSEQ
  extend_path = strdup(gvtxbts(string,extname,ID_SIZE));
  
  object_ref = base_node->get_object_ref()->GetLocalACObject();
  if ( !(nodeptr = base_node->CreateCopyNode()) )      ERROR
  extend_node = (ACNode *)nodeptr;
  nodeptr->SetPIRef((PropertyHandle *)&extend_node);  // kann sich selbst Nullen. 18.9.00, geht nicht, wenn basis pi vor extent gelöscht wird - 3.10.00
  
  switch ( base_node->get_nodetype() )
  {
    case NT_ACRelationship : baseext = ((ACRelationship *)base_node)->get_system_node();
                             *extend_path = '.';  // local extent
                             break;
    case NT_ACTopNode      : baseext = ((ACTopNode *)base_node)->get_system_node();
                             break;
    default                : ;
  }

  root_extend = baseext ? baseext->get_root_extend() : this;

  if ( !(topnode_list = new DLL(ACNode))   ||
       !(deri_extend  = new DLL(ACExtend)) ||
       !(base_extend  = new DLL(ACExtend)) )         SDBERR(95)

  if ( extend_node->Check(YES,NO) )                  ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



\param  lobhandle - 
\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACExtend"

     ACExtend :: ACExtend (LACObject *lobhandle, char *extnames )
                     : TypeKey(),
  extend_path(NULL),
  accmode(lobhandle->get_access_mode()),
  extend_node(NULL),
  base_extend(NULL),
  deri_extend(NULL),
  root_extend(NULL),
  int_extref(),
  topnode_list(new DLL(ACNode)),
  object_ref(lobhandle),
  extent_lock(YES),
  high_extent(NULL),
  acrel_node(NULL)
{
  char     string[ID_SIZE+1];
BEGINSEQ
  Initialize(lobhandle->GetDictionary(),extnames);
  
  extend_path = strdup(gvtxbts(string,extnames,ID_SIZE));
  
  lobhandle->AddACExtent(this);

  if ( !(deri_extend = new DLL(ACExtend)) )          SDBERR(95)
  if ( !(base_extend = new DLL(ACExtend)) )          SDBERR(95)

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i2 - 



\param  extent_path - 
\param  accopt - Access mode
\param  acrelptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACExtend"

     ACExtend :: ACExtend (char *extent_path, PIACC accopt, ACRelationship *acrelptr )
                     : TypeKey(),
  extend_path(NULL),
  accmode(accopt),
  extend_node(NULL),
  base_extend(new DLL(ACExtend)),
  deri_extend(new DLL(ACExtend)),
  root_extend(NULL),
  int_extref(),
  topnode_list(NULL),
  object_ref(acrelptr->get_object_ref()->GetLocalACObject()),
  extent_lock(YES),
  high_extent(NULL),
  acrel_node(acrelptr)
{

BEGINSEQ
  extend_path = strdup(extent_path);

  if ( accmode == PI_Write )
    accmode = PI_Update;

//  if ( Check() )                                     ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Add - 



\return term - Termination code

\param  bintiptr - 
\param  kchkopt - 
\param  read_opt - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical ACExtend :: Add (binti *bintiptr, logical kchkopt, logical read_opt, logical global_add )
{
  logical        root_ilocked = 255;
  logical        extlock      = GetRootLock(global_add);
  ACExtend      *subext;
  logical        exist        = NO;
  logical        term         = NO;
BEGINSEQ
  root_ilocked = ILockRoot();
  
  if ( PositionTop(NO) )                             SDBERR(225)
  if ( Check() )                                     ERROR
  
  if ( !(extlock = GetRootLock(global_add)) && 
       LockRoot(global_add)                   )      ERROR  
    
  if ( !kchkopt )
    exist = !GetID(bintiptr).IsEmpty();
  else
    if ( CheckAdd(bintiptr) )                        ERROR

  if ( Provide(bintiptr,read_opt,global_add).IsEmpty() )
                                                     ERROR
  if ( exist )                                       LEAVESEQ
  
  if ( GetExtentDef()->get_union_set() )    // echter Vereinigung
    if ( subext = deri_extend->GetHead() )
      subext->Add(bintiptr,NO,NO,global_add);
    
  deri_extend->GoTop();
  while ( subext = deri_extend->GetNext() )
    if ( subext->GetExtentDef()->get_intersect() )
      if ( subext->CheckIntersect(bintiptr) )         ERROR

RECOVER
  term = YES;
ENDSEQ
  UnlockRoot(extlock,global_add);
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  AddGenericRef - 



\return term - Termination code

\param  fldname - 
\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGenericRef"

logical ACExtend :: AddGenericRef (char *fldname, binti *bintiptr )
{
  logical        root_ilocked = 255;
  ACExtend      *subext;
  logical        term         = NO;
BEGINSEQ
  if ( IsLocal() )                                   LEAVESEQ
  root_ilocked = ILockRoot();
  
  if ( bintiptr->get_struct_def()->smcbsts.stscusr1() )  // generischen Schlüssel
  {
    base_extend->GoTop();
    while ( subext = base_extend->GetNext() )
      if ( subext->AddGenericRef(fldname,bintiptr) )  
        term = YES;
    if ( extend_node->get_noderefl()->AddGenericRef(fldname,bintiptr,bintiptr->GetID(AUTO)) )
                                                     ERROR
  }
  //darf nur einmal gemacht werden
  if ( bintiptr->AddGenericRef(fldname) )             ERROR
RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  AddGlobal - 



\return term - Termination code

\param  bintiptr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobal"

logical ACExtend :: AddGlobal (binti *bintiptr, logical read_opt )
{
  LACObject              *sys_object;
  eb_RootBase            *workspace;
  ACExtend               *sys_ext;
  binti                  *sys_binti;
  logical                 root_locked = IsRootLocked();
  logical                 newinst;
  EB_Number               entnr;
  logical                 term = NO;
BEGINSEQ
  if ( !(sys_object = object_ref->ReserveGlobalObject()) )
                                                     ERROR
  if ( root_locked )   // jetzt dürfen wir nicht mehr in den Error-Block springen
    UnlockRoot(NO);
  
  if ( (sys_ext = sys_object->ProvideACExtend(extend_path,PI_Write)) &&
       (sys_binti = sys_ext->GetInstance()) )
  {
    sys_ext->get_extend_node()->Cancel();
    sys_ext->get_extend_node()->StartTA();
    sys_binti->CopyGlobalInst(bintiptr);
    sys_ext->get_extend_node()->set_nodewrit(AUTO);
    if ( !(entnr = sys_ext->Provide(sys_binti,read_opt,NO)).IsEmpty() )
      sys_binti->Cancel();
    sys_ext->get_extend_node()->set_nodewrit(NO);
//  workspace = object_ref->get_local_dbhandle()->ResetWorkspace();
    term = sys_ext->get_extend_node()->StopTA(term);
    if ( !term && root_extend == this )
      object_ref->AddDelInstEntry(extend_path,entnr);
//  object_ref->get_local_dbhandle()->SetWorkspace(workspace);
  }
  else term = YES;
  
  if ( root_locked )
    LockRoot();
    
  newinst = bintiptr->stscold() ? NO : YES;
  term = Get(bintiptr,YES);
  if ( newinst )
    bintiptr->stsrold();
  object_ref->ReleaseGlobalObject();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddTopNode - 



\return term - Termination code

\param  acnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddTopNode"

logical ACExtend :: AddTopNode (ACNode *acnodeptr )
{
  logical                 root_ilocked = ILockRoot();
  logical                 term = NO;
  if ( topnode_list && !topnode_list->Find(acnodeptr) )
    topnode_list->AddTail(acnodeptr);
    

  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  Check - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ACExtend :: Check ( )
{
  node           *nodeptr = NULL;
  ACExtend       *baseext;
  logical         locked = NO;
  logical         term = NO;
BEGINSEQ
  if ( extend_node )
  {
    if ( !IsLocal() || !extend_node->get_moveable_instance() )
                                                     LEAVESEQ
    
    if ( !HasNodeChanged(extend_node) )              LEAVESEQ
    
    // das ist vielleicht zu simple, wenn der root_extent mehrfach gelockt ist
    if ( locked = root_extend ? root_extend->get_extent_lock().IsLocked() : NO )
      IUnlockRoot(YES);
    
    delete extend_node;
    extend_node = NULL;
    root_extend = NULL;
    nodeptr     = NULL;
  }
  
  if ( !(nodeptr = acrel_node->ProvideExtentNode(extend_path)) )
                                                     SDBERR(225)
  if ( nodeptr->get_nodetype() != NT_ACRelationship )
                                                     SDBERR(305)
  nodeptr->ChangeMode(accmode);
  
  extend_node = (ACNode *)nodeptr;
  extend_node->ResetUseCount();                       // mark as internal node
  nodeptr->SetPIRef((PropertyHandle *)&extend_node);  // kann sich selbst Nullen. 18.9.00, geht niicht, wenn basis pi vor extent gelöscht wird - 3.10.00
  
  if ( extend_node->Check(YES,NO) )                  ERROR
  baseext = ((ACRelationship *)nodeptr)->get_system_node();
  root_extend = baseext ? baseext->get_root_extend() : this;
  if ( locked ) 
    ILockRoot();

RECOVER
  delete nodeptr;
  extend_node = NULL;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckAdd - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAdd"

logical ACExtend :: CheckAdd (binti *bintiptr )
{
  logical    term = NO;
BEGINSEQ
  if ( int_extref.IsEmpty(object_ref->IsPIF()) && object_ref->get_access_mode() == PI_Update )
    if ( SetupExtentRef() )                          ERROR

  if ( extend_node->get_noderefmain() && 
       extend_node->get_noderefmain()->WSCheckNewID(extend_node->GetKeyInstance(bintiptr,NULL),0) ) 
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDelete - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDelete"

logical ACExtend :: CheckDelete (binti *bintiptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( GetExtentDef()->get_intersect() )             SDBERR(164)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDisjunct - 



\return term - Termination code

\param  bintiptr - 
\param  acextent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDisjunct"

logical ACExtend :: CheckDisjunct (binti *bintiptr, ACExtend *acextent )
{
  logical        root_ilocked = 255;
  ACExtend      *ac_extent;
  logical        term         = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( Get(bintiptr,NO) )                             LEAVESEQ

  deri_extend->GoTop();
  while ( ac_extent = deri_extend->GetNext() )
    if ( ac_extent != acextent && !ac_extent->Get(bintiptr,NO) )
    {
      if ( ac_extent->Delete(bintiptr,NO,YES,NO) )    ERROR
//      SDBEV1(ac_extent->get_extend_path(),ID_SIZE)      SDBERR(166)
    }
RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckIntersect - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckIntersect"

logical ACExtend :: CheckIntersect (binti *bintiptr )
{
  logical        root_ilocked = 255;
  ACExtend      *ac_extent;
  logical        term         = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( !Get(bintiptr,NO) )                            LEAVESEQ

  base_extend->GoTop();
  while ( ac_extent = base_extend->GetNext() )
    if ( ac_extent->Get(bintiptr,NO) )                LEAVESEQ

  if ( Provide(bintiptr,NO).IsEmpty() )               ERROR
RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  CheckModify - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckModify"

logical ACExtend :: CheckModify (binti *bintiptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  CheckUnion - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckUnion"

logical ACExtend :: CheckUnion (binti *bintiptr )
{
  logical        root_ilocked = 255;
  ACExtend      *ac_extent;
  logical        term         = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( Get(bintiptr,NO) )                             LEAVESEQ

  deri_extend->GoTop();
  while ( ac_extent = deri_extend->GetNext() )
    if ( !ac_extent->Get(bintiptr,NO) )               LEAVESEQ
      
  if ( Delete(bintiptr,YES,YES,NO) )                  ERROR
RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACExtend :: Close ( )
{
  logical          root_ilocked;
  ACExtend        *extptr;
  if ( root_extend && root_extend->IsLocal() &&
       extend_node && extend_node->stscold()    )  // der root_extend wird mit dem extend_node freigegeben
    root_extend = NULL;
  root_ilocked  = ILockRoot();
  
  CloseTopNodes();
  CloseExtentNode(NO);
      
  object_ref->RemoveACExtent(this);
  
  if ( !IsLocal() && base_extend )
  {
    if ( base_extend->GetCount() )
    {
      base_extend->GoTop();
      while ( extptr = base_extend->GetNext() )
        if ( extptr->get_deri_extend()->Find(this) )
          extptr->get_deri_extend()->RemoveAt();
    }
  }
  delete base_extend;
  base_extend = NULL;
  
  if ( deri_extend )
  {
    if ( deri_extend->GetCount() )
      while ( extptr = deri_extend->GetTail() )
        delete extptr;
    delete deri_extend;
    deri_extend = NULL;
  }

  delete extend_node;
  extend_node = NULL;

  IUnlockRoot(root_ilocked);
  return(NO);
}

/******************************************************************************/
/**
\brief  CloseExtentNode - 



\return term - Termination code

\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseExtentNode"

logical ACExtend :: CloseExtentNode (logical del_opt )
{
  logical                 term = NO;
  if ( extend_node && extend_node->IsValid() )
  {
    if ( IsLocal() || del_opt )
    {
      delete extend_node;
      extend_node = NULL;
    }
    else
      extend_node->RemoveReference();
  }
  else 
    extend_node = NULL;

  return(term);
}

/******************************************************************************/
/**
\brief  CloseTopNodes - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseTopNodes"

logical ACExtend :: CloseTopNodes ( )
{
  ACNode          *nodeptr;
  DLL(ACNode)     *nodelist;
  logical          term = NO;
  ReleaseCache();
  
  if ( nodelist = topnode_list )
  {
    topnode_list = NULL;
    while ( nodeptr = nodelist->RemoveTail() )
    {
      nodeptr->Switch(AUTO);
      delete nodeptr;
    }
    delete nodelist;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  CreateInti - 



\return intiptr - 

\param  nodeptr - 
\param  strdef_ptr - Internal data structure definition
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *ACExtend :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  logical   locked;
  inti     *bintiptr;
  inti     *newinti;

  locked = ILockObject();
  bintiptr = extend_node->get_nodeinst();
  
  newinti = extend_node->CreateInti(nodeptr,strdef_ptr,instptr,init_nodes);
  
// nur zum eintragen des struct_access ins EntryHandle des isel  
  extend_node->SetCurrentInti(newinti);
  extend_node->SetCurrentInti(bintiptr);

  IUnlockObject(locked);
  return(newinti);
}

/******************************************************************************/
/**
\brief  DelGenericRef - 



\return term - Termination code

\param  fldname - 
\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelGenericRef"

logical ACExtend :: DelGenericRef (char *fldname, binti *bintiptr )
{
  logical        root_ilocked = 255;
  ACExtend      *subext;
  logical        term         = NO;
BEGINSEQ
  if ( IsLocal() )                                   LEAVESEQ
  root_ilocked = ILockRoot();
  
  if ( bintiptr->get_struct_def()->smcbsts.stscusr1() )  // generischen Schlüssel
  {
    deri_extend->GoTop();
    while ( subext = deri_extend->GetNext() )
      if ( subext->DelGenericRef(fldname,bintiptr) )  
        term = YES;
  
    if ( extend_node->get_noderefl()->DelGenericRef(fldname,bintiptr,bintiptr->GetID(AUTO)) )
                                                     ERROR
  }
  if ( bintiptr->DelGenericRef(fldname) )             ERROR

RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code

\param  bintiptr - 
\param  kchkopt - 
\param  del_dep - 
\param  switch_opt - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACExtend :: Delete (binti *bintiptr, logical kchkopt, logical del_dep, logical switch_opt, logical del_inst )
{
  logical   root_ilocked = 255;
  ACExtend *sysnode;
  logical   extlock      = AUTO;
  inti     *oldinti;
  ACExtend *subext;
  ACExtend *topext;
  exd      *exdptr;
  logical   siw          = AUTO;
  logical   term         = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
  oldinti      = extend_node->get_nodeinst();
  root_ilocked = ILockRoot();
  
  if ( IsLocal() )                               
  {
    if ( !GetID(bintiptr).IsEmpty() )
    {
      if ( extend_node->get_nodefield()->get_weak_typed() )
        extend_node->SetType(bintiptr->get_struct_def()->smcbname);
      extend_node->SetCurrentInti(bintiptr);
      
      if ( IsRoot() )  // root extend
        term = extend_node->DeleteInstance(bintiptr,extend_path,IsRoot(),del_dep,switch_opt);
      else if ( sysnode = extend_node->GetSystemNode() )
      {
        if ( sysnode->IsLocal() )
          term = sysnode->Delete(bintiptr,kchkopt,del_dep,switch_opt);
        else
          term = sysnode->get_root_extend()->Delete(bintiptr,kchkopt,del_dep,switch_opt);
      }
      else                                           SDBERR(99)
      
      extend_node->SetCurrentInti(oldinti);
      if ( extend_node->get_nodefield()->get_weak_typed() )
        extend_node->SetType(oldinti->get_struct_def()->smcbname,NO);
    }
    else // Instanz kann schon aus dem Index gelöscht sein, da Basismenge schon gepflegt 
    {    // 29.5.2003
      if ( IsRoot() )  // root extend
        term = bintiptr->Delete(extend_path,YES,extend_node->get_nodefield()->get_owning());
      else if ( sysnode = extend_node->GetSystemNode() )
        term = sysnode->Delete(bintiptr,kchkopt,del_dep,switch_opt);
    }
    if ( term )                                      ERROR
                                                     LEAVESEQ
  }
  
  extlock = GetRootLock();
  if ( !extlock && LockRoot() )                    ERROR
  if ( kchkopt && CheckDelete(bintiptr) )          ERROR
 
  deri_extend->GoTop();
  while ( subext = deri_extend->GetNext() )
    if ( subext->Delete(bintiptr,NO,del_dep,NO) )
                                                     ERROR
  if ( !GetID(bintiptr).IsEmpty() )
  {
    extend_node->SetCurrentInti(bintiptr);
    if ( extend_node->DeleteInstance(bintiptr,extend_path,IsRoot(),del_dep,switch_opt,del_inst) )
                                                     ERROR
      
    base_extend->GoTop();
    while ( topext = base_extend->GetNext() )
      if ( topext->GetExtentDef()->get_union_set() )
        if ( topext->CheckUnion(bintiptr) )          ERROR
  }
  else // Fehlerbehebung
  {
    if ( base_extend->GetCount() > 0 )             LEAVESEQ
    extend_node->get_noderefl()->DeleteID(bintiptr->GetID());
    if ( exdptr = bintiptr->GetEXD() )
      siw = bintiptr->SetInWork(YES);
    bintiptr->Delete(extend_path,IsRoot(),extend_node->get_nodefield()->get_owning());
    if ( siw != 255 )
      bintiptr->SetInWork(siw);
  }

RECOVER
  term = YES;
ENDSEQ
  if ( extlock != AUTO )
    UnlockRoot(extlock);
  extend_node->SetCurrentInti(oldinti);
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteGlobal - 



\return term - Termination code

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteGlobal"

logical ACExtend :: DeleteGlobal (EB_Number entnr )
{
  logical   root_ilocked = 255;
  ACExtend *sysnode;
  logical   extlock      = AUTO;
  inti     *oldinti      = extend_node->get_nodeinst();
  ACExtend *subext;
  ACExtend *topext;
  int32     lindx0;
  logical   term         = NO;
BEGINSEQ
  if ( IsLocal() )                                   LEAVESEQ
  root_ilocked = ILockRoot();
  
  extend_node->DisableContext();
  
  extlock = GetRootLock();
  if ( !extlock && LockRoot() )                      ERROR
 
// der geht am workspace vorbei!  
  lindx0 = extend_node->LocatePosition(entnr);
  if ( lindx0 <= 0 )                                 ERROR
  if ( !extend_node->Get(lindx0,NO) )                ERROR
      
  Delete((binti *)extend_node->get_nodeinst(),NO,YES,YES);

  extend_node->ToTop();
RECOVER
  term = YES;
ENDSEQ
  extend_node->EnableContext();
  if ( extlock != AUTO )
    UnlockRoot(extlock);
  extend_node->SetCurrentInti(oldinti);
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteIndex - 



\return term - Termination code

\param  bintiptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteIndex"

logical ACExtend :: DeleteIndex (binti *bintiptr, EB_Number entnr )
{
  logical   root_ilocked = 255;
  ACExtend *sysnode;
  logical   extlock      = AUTO;
  inti     *oldinti      = extend_node->get_nodeinst();
  ACExtend *subext;
  ACExtend *topext;
  logical   term         = NO;
BEGINSEQ
  if ( IsLocal() )                                   LEAVESEQ
  root_ilocked = ILockRoot();
  
  extlock = GetRootLock();
  if ( !extlock && LockRoot() )                      ERROR
 
  deri_extend->GoTop();
  while ( subext = deri_extend->GetNext() )
    if ( subext->DeleteIndex(bintiptr,entnr) )       ERROR
      
  if ( !GetID(bintiptr).IsEmpty() )
  {
    extend_node->SetCurrentInti(bintiptr);
    extend_node->DeleteID(bintiptr,NULL,entnr);
  }

RECOVER
  term = YES;
ENDSEQ
  if ( extlock != AUTO )
    UnlockRoot(extlock);
  extend_node->SetCurrentInti(oldinti);
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 



\return term - Termination code

\param  bintiptr - 
\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical ACExtend :: Get (binti *bintiptr, logical read_opt )
{
  logical   root_ilocked = 255;
  EB_Number entnr;
  logical   term = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( (entnr = GetID(bintiptr)).IsEmpty() )         ERROR
  
  if ( extend_node->IsVariableType() )
    if ( bintiptr->GetSID(entnr) != bintiptr->get_struct_def()->smcbityp )
                                                     SDBERR(529)
                                                     
  if ( !read_opt )                                   LEAVESEQ
  if ( bintiptr->Get(entnr) )                        ERROR
RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  GetBaseInstID - 



\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseInstID"

EB_Number ACExtend :: GetBaseInstID ( )
{
  node                   *baseinst_pi;
  EB_Number               entnr = 0;
BEGINSEQ
  if ( !IsLocal() )                                  ERROR
  if ( !extend_node )                                SDBERR(225)

  if ( extend_node->PositionTop() )                  ERROR
  
  baseinst_pi = extend_node->get_nodenode();
  baseinst_pi = ((bnode *)baseinst_pi)->ValidatePosition(NO);
  if ( !baseinst_pi->get_nodenode()->IsPositioned() )
                                                     ERROR
  entnr = baseinst_pi->GetID(FIRST_INSTANCE);
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetCount - 



\return ecnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACExtend :: GetCount ( )
{
  logical   root_ilocked = 255;
  int32     count        = ERIC;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  count = extend_node->GetCount();
RECOVER

ENDSEQ
  IUnlockRoot(root_ilocked);
  return(count);
}

/******************************************************************************/
/**
\brief  GetExtendName - 



\return extent_path - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtendName"

char *ACExtend :: GetExtendName ( )
{

  if (extend_path) return extend_path;
  return "" ;

}

/******************************************************************************/
/**
\brief  GetExtentDef - 



\return dbextdef - Extent definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentDef"

DBExtend *ACExtend :: GetExtentDef ( )
{

  return(   !IsLocal() && extend_node->get_nodefield() 
          ? (DBExtend *)extend_node->get_nodefield() : NULL);

}

/******************************************************************************/
/**
\brief  GetExtentNode - 



\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentNode"

bnode *ACExtend :: GetExtentNode ( )
{

  if ( this )
    Check();
    
  return ( this ? extend_node : NULL );


}

/******************************************************************************/
/**
\brief  GetGlobalID - 



\return entnr - 

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGlobalID"

EB_Number ACExtend :: GetGlobalID (binti *bintiptr )
{
  ACExtend   *snode;
  inti     *oldinti;
  EB_Number   entnr;
BEGINSEQ
  if ( IsLocal() )
  {
    if ( Check() )                                   ERROR
    if ( PositionTop(YES) )                          ERROR
  }    
  entnr = (root_extend ? root_extend : this)->GetID(bintiptr,YES);

  if ( entnr.IsEmpty() && IsLocal() )
  {
    oldinti = extend_node->get_nodeinst();
    if ( extend_node->get_nodefield()->get_weak_typed() )
      extend_node->SetType(bintiptr->get_struct_def()->smcbname);
   
    if ( snode = extend_node->GetSystemNode() )
      entnr = snode->GetGlobalID(bintiptr);
      
    if ( extend_node->get_nodefield()->get_weak_typed() )
      extend_node->SetType(oldinti->get_struct_def()->smcbname,NO);
  }
RECOVER

ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetID - 



\return entnr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  bintiptr - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACExtend :: GetID (binti *bintiptr, logical pif_opt )
{
  logical       root_ilocked = 255;
  EB_Number     entnr;
  EB_Number    *entnr_pt;
  char         *skey;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( IsLocal() )
    if ( PositionTop(YES) )                          ERROR

  if ( extend_node->get_noderefp() &&
       extend_node->get_noderefp()->get_refsakcb()->get_key_def() &&
       extend_node->get_noderefp()->get_refsakcb()->get_key_def()->scbsmcb->smcbsts.stscnof() )
  {
    if ( entnr_pt = bintiptr->GetIdentity() ) 
      entnr = *entnr_pt;
    else
    {
      entnr = bintiptr->GetID();
      entnr.FromPIF(object_ref->get_pif());
    }
    skey = (char *)&entnr;
  }
  else
    skey = extend_node->ExtractSortKey(NULL,bintiptr->get_iselarea(),NO);
    
  if ( !skey && extend_node->get_id_key() )
    skey = extend_node->ExtractKey(NULL,bintiptr->get_iselarea(),NO);
    
  if ( skey )
    if ( (entnr = extend_node->GetID(skey,YES,pif_opt)).IsEmpty() && high_extent )
      entnr = high_extent->GetID(bintiptr,pif_opt);

RECOVER

ENDSEQ
  IUnlockRoot(root_ilocked);
  return(entnr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  lindx0 - 
\param  pif_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACExtend :: GetID (int32 lindx0, logical pif_opt )
{
  logical       root_ilocked = 255;
  EB_Number      entnr;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( IsLocal() )
    if ( PositionTop(YES) )                          SDBERR(255)
    
  entnr = extend_node->GetID(lindx0,YES,pif_opt);
RECOVER

ENDSEQ
  IUnlockRoot(root_ilocked);
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetInstance - 



\return bintiptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

binti *ACExtend :: GetInstance ( )
{

BEGINSEQ
  if ( !extend_node )                                ERROR
    
  if ( !extend_node->get_nodeinst() )
    extend_node->Check(YES,NO);

RECOVER

ENDSEQ
  return ( extend_node ? (binti *)extend_node->get_nodeinst()
                       : NULL);

}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 ACExtend :: GetMainBase ( )
{
  ACExtend  *baseext;
  int16      mbnumber;
BEGINSEQ
  if ( !extend_node && Check() )                     ERROR
  
  if ( IsLocal() )
    mbnumber = extend_node ? extend_node->GetMainBase() : UNDEF;
  else
  {
    if ( (mbnumber = GetExtentDef()->get_mb_number()) != TEMP_MAIN )
                                                     LEAVESEQ
    mbnumber = AUTO;
  
    if ( !extend_node->get_nodefield()->get_log_reference() &&
         (baseext = base_extend->GetHead())         ) // auto correction for extent hierarchies
      mbnumber = baseext->GetMainBase();
    else  
      mbnumber = extend_node->get_object_ref()->get_db_handle()->GetTempMain();
  
    GetExtentDef()->set_mb_number(mbnumber);
  }

RECOVER

ENDSEQ
  return(mbnumber);
}

/******************************************************************************/
/**
\brief  GetRootExtent - 



\return extent - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRootExtent"

ACExtend *ACExtend :: GetRootExtent ( )
{
  ACExtend         *extent = NULL;
  logical           changed = NO;
  node             *nodeptr;
BEGINSEQ
  if ( !(extent = root_extend) )                     ERROR

  nodeptr = extent->get_extend_node();
//  if ( !nodeptr->get_movable_instance() )            LEAVESEQ

//  while ( nodeptr !=
RECOVER
  extent = NULL;
ENDSEQ
  return(extent);
}

/******************************************************************************/
/**
\brief  GetRootLock - 



\return cond - 

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRootLock"

logical ACExtend :: GetRootLock (logical global_add )
{
  ACNode         *nodeptr = extend_node;

  if ( !(global_add && IsLocal()) )
    nodeptr = root_extend ? root_extend->get_extend_node() : NULL;
  
  return( nodeptr && nodeptr->get_noderefl() &&
          nodeptr->get_noderefl()->stsclck()    );

}

/******************************************************************************/
/**
\brief  HasNodeChanged - 



\return cond - 

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasNodeChanged"

logical ACExtend :: HasNodeChanged (node *nodeptr )
{
  logical                 cond = YES;
BEGINSEQ
  // the topnode is the only copy node in the extent path
  if ( !nodeptr->IsCopyNode() )
    if ( HasNodeChanged(nodeptr->get_nodenode()) )   LEAVESEQ
  
  if ( Bnodeptr->iChanged() )                        LEAVESEQ
  if ( nodeptr != extend_node && !nodeptr->IsPositioned() )
    nodeptr->Get(FIRST_INSTANCE);

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ILockObject - 



\return root_locked - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILockObject"

logical ACExtend :: ILockObject ( )
{
  logical            locked = NO;
  if ( object_ref ) 
  {
    object_ref->ILock(YES);
    locked = YES;
  }

  return(locked);
}

/******************************************************************************/
/**
\brief  ILockRoot - 



\return locked - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILockRoot"

logical ACExtend :: ILockRoot ( )
{

  return( ILockObject() );
/*
  if ( root_extend )                  
    root_extend->get_extent_lock().ILock();
  else
    extent_lock.ILock();
*/
  return(root_extend ? YES : NO);
}

/******************************************************************************/
/**
\brief  IUnlockObject - 



\return term - Termination code

\param  locked - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlockObject"

logical ACExtend :: IUnlockObject (logical locked )
{

  if ( locked && object_ref )                  
    object_ref->IUnlock();

  return(NO);

}

/******************************************************************************/
/**
\brief  IUnlockRoot - 



\return term - Termination code

\param  root_locked - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlockRoot"

logical ACExtend :: IUnlockRoot (logical root_locked )
{
  logical    term = NO;
BEGINSEQ
  return( root_locked == YES ? IUnlockObject(root_locked) : NO );
/*
  if ( root_locked == 255 )                          LEAVESEQ
    
  if ( root_locked )
    root_extend->get_extent_lock().IUnlock();
  else
    extent_lock.IUnlock();
*/
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  IdentityAdd - 



\return term - Termination code

\param  bintiptr - 
\param  keyname - 
\param  kchkopt - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IdentityAdd"

logical ACExtend :: IdentityAdd (binti *bintiptr, char *keyname, logical kchkopt, logical global_add )
{
  logical    root_ilocked = 255;
  logical    extlock      = YES;
  inti      *oldinti;
  int16      attrtype     = UNDEF;
  char      *fname;
  EB_Number *entnr_pt;
  logical    term         = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
  oldinti      = extend_node->get_nodeinst();
  root_ilocked = ILockRoot();
  extlock      = GetRootLock(global_add);
  
  if ( !extlock && LockRoot(global_add) )            ERROR
  
  if ( !keyname )                                    SDBERR(184)
  if ( !memcmp(keyname,"__IDENTITY ",11) )
  {
    if ( !(entnr_pt = bintiptr->GetIdentity()) )     SDBERR(184)
    if ( !entnr_pt->IsEmpty() )
    {
      if ( Get(bintiptr,YES) )                       SDBERR(239)
      if ( kchkopt )                                 SDBERR(64)
      LEAVESEQ
    }
  }

  extend_node->ResetInstance();
  extend_node->SetCurrentInti(bintiptr);
  
  // neu 4.6.98: Einstellen des Indexes für generische Sortierungen anhand des attribute-Wertes
  if ( fname = extend_node->get_noderefp()->GetGenAttribute() )  // generischen Index initialisieren
    bintiptr->GetPropNode(fname,(CTX_Property *)NULL)->ExtractKey((char *)&attrtype,bintiptr->get_iselarea(),NO);

  term = extend_node->SetOrder(keyname,attrtype,NULL);
  extend_node->SetCurrentInti(oldinti);
  if ( term )                                        ERROR
  
  if ( !Get(bintiptr,YES) )
  {
    if ( kchkopt )                                   SDBERR(64)
    LEAVESEQ
  }
  
  if ( this != root_extend )                         SDBERR(184)
  if ( Add(bintiptr,kchkopt,YES,global_add) )        ERROR

RECOVER
  term = YES;
ENDSEQ
  extend_node->SetMainRef();
  UnlockRoot(extlock,global_add);
  IUnlockRoot(root_ilocked);
  return(term);

}

/******************************************************************************/
/**
\brief  InitExtendRef - 



\return term - Termination code

\param  extadd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitExtendRef"

logical ACExtend :: InitExtendRef (logical extadd )
{
  logical      root_ilocked = ILockRoot();
  TypeKey     &tkey = GetExtentDef()->GetNameKey();
  LACObject   *sys_object;
  EB_Number   *ext_ref      = NULL;
  int16        mbnumber     = 0;
  logical      term         = NO;
  int16        index        = 0;
BEGINSEQ
  if ( GetExtentDef()->get_acctype() == AT_ODABA )
  {
    if ( object_ref->get_access_mode() != PI_Read  &&
         !GetExtentDef()->IsTempExtent(object_ref) && 
         !object_ref->get_is_global_object()       &&
         object_ref->get_db_handle()->get_net_option() )
    {                                                                  // extents müssen immer außerhalb der Transaktion angelegt werden.
      if ( !(sys_object = object_ref->ReserveGlobalObject()) )
                                                     SDBERR(99)
      term = !sys_object->ProvideACExtend(tkey,PI_Write,extadd);
      object_ref->ReleaseGlobalObject();
      if ( term )                                    ERROR
      if ( !(ext_ref = object_ref->GetExtendRef(tkey)) && 
           object_ref->get_access_mode() == PI_Write       )
                                                     SDBERR(99)
    }
    else if ( !(ext_ref = object_ref->GetExtendRef(tkey)) )
    {
      SDBCERR
      if ( object_ref->get_access_mode() == PI_Read && !IsTemporary() )
      {
        if ( extadd )
          extend_node->stsserr();
        LEAVESEQ
      }
      if ( object_ref->get_access_mode() == PI_Write )
        if ( !(ext_ref = object_ref->AddExtendRef(GetExtentDef())) )
                                                     ERROR
    }
  }
  if ( extend_node->InitReference() )                ERROR

  if ( GetExtentDef()->get_acctype() == AT_ODABA && !object_ref->IsXMLBase() )
    if ( GetExtentDef()->fmcbityp != T_VOID )   
      if ( !extend_node->get_noderefp() || 
           !extend_node->get_noderefp()->get_refsakcb() ||
           !extend_node->get_noderefp()->get_refsakcb()->get_key_def() )
                                                     SDBERR(377)
  if ( ext_ref )
    int_extref = *ext_ref;  
  
  if ( (mbnumber = GetExtentDef()->GetMainBase(object_ref)) == AUTO )       
                                                     SDBERR(169)
  if ( extend_node->get_noderefl()->Setup(&int_extref,0,mbnumber,extend_node->get_nodeacc(),YES) )  
                                                     ERROR
  extend_node->stssfil();
RECOVER
  int_extref = 0;
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  IsLocal - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLocal"

logical ACExtend :: IsLocal ( )
{

  return ( this && extend_path && *extend_path == '.' ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsRoot - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRoot"

logical ACExtend :: IsRoot ( )
{

  return ( this == root_extend ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsRootLocked - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRootLocked"

logical ACExtend :: IsRootLocked ( )
{

  return ( root_extend && root_extend->get_extend_node()->stsclck() 
           ? YES : NO);

}

/******************************************************************************/
/**
\brief  IsTemporary - Is extent temporary extent?



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTemporary"

logical ACExtend :: IsTemporary ( )
{

  return( extend_node 
          ? extend_node->get_nodefield()->get_log_reference()
          : NO );

}

/******************************************************************************/
/**
\brief  LockRoot - 



\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockRoot"

logical ACExtend :: LockRoot (logical global_add )
{
  logical  term = NO;
BEGINSEQ
  if ( !root_extend )                                SDBERR(99)
  
  if ( global_add && IsLocal() )
  {
    extend_node->Check(NO,NO);
    if ( extend_node->LockSet(NO) )                  ERROR
  }
  else
  {
    root_extend->get_extend_node()->Check(NO,NO);
    if ( root_extend->get_extend_node()->LockSet(NO) ) ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  NotCreated - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NotCreated"

logical ACExtend :: NotCreated ( )
{

  return( !extend_node || extend_node->stscerr() );

}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  lobhandle - 
\param  dbextdef - Extent definition
\param  ac_baseext - 
\param  accopt - Access mode
\param  extadd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ACExtend :: Open (LACObject *lobhandle, DBExtend *dbextdef, ACExtend *ac_baseext, PIACC accopt, logical extadd )
{
  logical       root_ilocked = ILockRoot();
  int16         mbnumber = 0;
  int16         index  = 0;
  char          string[ID_SIZE+1];
  logical       term = NO;
BEGINSEQ
  object_ref = lobhandle;
  if ( !(extend_node = (ACNode *)lobhandle->CreateNode(dbextdef,accopt)) )
                                                     ERROR
  extend_node->stssusr1();
  extend_path = strdup(gvtxbts(string,dbextdef->fmcbname,ID_SIZE));
  
  lobhandle->AddACExtent(this);
  
  if ( !(topnode_list = new DLL(ACNode))   ||
       !(deri_extend  = new DLL(ACExtend)) ||
       !(base_extend  = new DLL(ACExtend)) )         SDBERR(95)

  if ( InitExtendRef(extadd) )                       ERROR
  if ( Upgrade(ac_baseext) )                         ERROR
  
  if ( extend_node->InitInti(dbextdef->GetDBStruct(),NULL) )      
                                                     ERROR
  SetVersion(lobhandle->get_version());
  if ( extend_node->SetupIndex() )                   ERROR

  if ( *extend_path != '#' && lobhandle->GetHighObject() && dbextdef->get_acctype() == AT_ODABA )
    high_extent = lobhandle->GetHighObject()->GetLocalACObject()->ProvideACExtend(extend_path,accopt,extadd);

RECOVER
  object_ref->RemoveACExtent(this);
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  PositionTop - 



\return term - Termination code

\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionTop"

logical ACExtend :: PositionTop (logical chk_opt )
{
  node                   *nodeptr = extend_node;
  ACExtend               *extent;
  logical                 term = NO;
BEGINSEQ
  if ( !IsLocal() )                                  LEAVESEQ

  while ( !nodeptr->IsCopyNode() )
    nodeptr = nodeptr->get_nodenode();
  nodeptr = nodeptr->get_nodenode();
  
  if ( !nodeptr->IsPositioned() )
  {
    Bnodeptr->ValidatePosition(NO); // position above topnode of extent
    nodeptr->Get(nodeptr->get_nodecur() < 0 ? FIRST_INSTANCE
                                            : nodeptr->get_nodecur() );
  }
    
  if ( chk_opt )
    if ( Check() )                                   ERROR
  
  extend_node->PositionTop();
  if ( extent = extend_node->GetSystemNode() )
    extent->PositionTop(chk_opt);
    
  if ( !extend_node->get_nodenode()->IsPositioned()) ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Provide - 



\return pifent - 

\param  bintiptr - 
\param  read_opt - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

EB_Number ACExtend :: Provide (binti *bintiptr, logical read_opt, logical global_add )
{
  logical   root_ilocked = 255;
  inti     *oldinti;
  ACExtend *ac_extent;
  logical   newinst      = NO;
  logical   term         = NO;
  EB_Number pifent;

BEGINSEQ
  if ( Check() )                                     ERROR
  oldinti      = extend_node->get_nodeinst();
  root_ilocked = ILockRoot();
  
  if ( !Get(bintiptr,read_opt) )
  {
    pifent = bintiptr->GetID();
    LEAVESEQ
  }
  SDBCERR
    
  if ( IsLocal() )
  {
  if ( !extend_node )                                SDBERR(225)
    if ( extend_node->get_nodefield()->get_weak_typed() )
      extend_node->SetType(bintiptr->get_struct_def()->smcbname);
    extend_node->SetCurrentInti(bintiptr);
    
    if ( !(term = extend_node->Add(AUTO,global_add) ? NO : YES) )
      pifent = bintiptr->GetID();
    extend_node->GenerateEvent(term ? DBO_NotInserted : DBO_Inserted);
     
    extend_node->SetCurrentInti(oldinti);
    if ( extend_node->get_nodefield()->get_weak_typed() )
      extend_node->SetType(oldinti->get_struct_def()->smcbname);
    
    if ( term )                                      ERROR
                                                     LEAVESEQ
  }

/*  
  if ( global_add && 
       object_ref->IsExternalTA() && object_ref->get_db_handle()->get_net_option() )
//       ( (object_ref->IsExternalTA() && object_ref->get_db_handle()->get_net_option()) ||
//         object_ref->get_db_handle()->GetLocalDBHandle()->get_root_base()->IsWorkspace() ) )
  {
    if ( AddGlobal(bintiptr,read_opt) )              ERROR
    pifent = bintiptr->GetID();
    LEAVESEQ
  }
*/

  if ( base_extend->GetCount() > 0 )
  {
    base_extend->GoTop();
    while ( ac_extent = base_extend->GetNext() )
      if ( ac_extent->Provide(bintiptr,read_opt).IsEmpty() ) 
                                                     ERROR
  }  
  else
  {
    if ( !bintiptr->IsPositioned() )
    {
      if ( !extend_node->get_nodefield()->get_owning() )
                                                     SDBERR(170)
      if ( bintiptr->Add() )                         ERROR
      newinst  = YES;
    }  
  }

  if ( Get(bintiptr,NO) )  
  {
    if ( bintiptr != oldinti )
    {
      extend_node->ResetInstance();
      extend_node->SetCurrentInti(bintiptr);
    }
    term = extend_node->AddID(AUTO);
    if ( bintiptr != oldinti )
      extend_node->SetCurrentInti(oldinti);
    if ( term )                                      ERROR
  }

  if ( base_extend->GetCount() > 0 )
  {
    base_extend->GoTop();
    while ( ac_extent = base_extend->GetNext() )
      if ( ac_extent->GetExtentDef()->get_disjunct() )
        if ( ac_extent->CheckDisjunct(bintiptr,this)) ERROR
  }  
  
  pifent = bintiptr->GetID();
  if ( newinst )
    bintiptr->stsrold();
RECOVER
  if ( newinst )
  {
    int  saverr = SDBERROR;
    bintiptr->Cancel();
    extend_node->ResetNode(NO);
    SDBISET(saverr);
  }
  pifent = 0;
ENDSEQ
  if ( object_ref->get_is_global_object() )
    extend_node->ToTop();
  IUnlockRoot(root_ilocked);
  return(pifent);
}

/******************************************************************************/
/**
\brief  Refresh - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical ACExtend :: Refresh ( )
{
  logical    root_ilocked = ILockRoot();
  DBExtend  *dbextdef     = GetExtentDef();
  logical    term         = NO;
//  term = extend_node->Refresh();
  
//  hier wollen wir wohl Bina-Nodes und so erfrischen. Das sollen die mal selber tun  
  Close();
  term = Open(object_ref,GetExtentDef(),NULL,
              extend_node->get_nodeacc(),NO);
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseCache - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseCache"

void ACExtend :: ReleaseCache ( )
{
  logical            root_ilocked = ILockRoot();
  node              *nodeptr;

  while ( node_cache.GetSize() > 0 )
    if ( nodeptr = node_cache.Pop() )
      delete nodeptr;

  IUnlockRoot(root_ilocked);

}

/******************************************************************************/
/**
\brief  ReleaseNode - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseNode"

logical ACExtend :: ReleaseNode (node *nodeptr )
{
  logical                 root_ilocked = ILockRoot();
  logical                 term = NO;
BEGINSEQ
  if ( !object_ref->get_handle_cache() )             ERROR
    
  nodeptr->ToTop();
  node_cache.Push(nodeptr);

RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveTopNode - 



\return term - Termination code

\param  acnodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveTopNode"

logical ACExtend :: RemoveTopNode (ACNode *acnodeptr )
{
  logical                 root_ilocked = ILockRoot();
  char                    extname[ID_SIZE];
  Dictionary             *dictptr;
  logical                 term = NO;
BEGINSEQ
  if ( topnode_list && topnode_list->Find(acnodeptr) )
    topnode_list->RemoveAt();

  if ( IsTemporary() && topnode_list && topnode_list->GetCount() == 0 )
  {
    extend_node->get_object_ref()->GetLocalACObject()->RemoveACExtent(this);
    dictptr = extend_node->GetDictionary();
    IUnlockRoot(root_ilocked);
    delete this;   
    LEAVESEQ   
    
//  Whenn wir Extents in verschiedenen Objekten anlegen, wird die ExtDef zu früh freigegeben
//    if ( dictptr )
//    {    
//      dictptr->RemoveExtentDef(extname);
//    }    
  }
  
  IUnlockRoot(root_ilocked);
  

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveNode - 



\return nodeptr - 

\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveNode"

node *ACExtend :: ReserveNode (PIACC accopt )
{
  logical                 root_ilocked = ILockRoot();
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( node_cache.GetSize() > 0 && (nodeptr = node_cache.Pop()) )
  {
    if ( nodeptr->GetMode() != accopt )
      if ( nodeptr->ChangeMode(accopt) == PI_undefined )
      {
        node_cache.Push(nodeptr);                    ERROR
      }
  }
  else
    nodeptr = new ACTopNode(this,accopt);


RECOVER
  nodeptr = NULL;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Save - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ACExtend :: Save (binti *bintiptr )
{
  logical    root_ilocked = ILockRoot();
  logical    extlock      = GetRootLock();
  logical    term         = NO;
BEGINSEQ
  if ( IsLocal() )                                   LEAVESEQ
  
//  if ( IsLocal() )                   // neu 9.1.00
//    PositionTop();      // 
  
  if ( !extlock && LockRoot() )                        ERROR

  if ( root_extend->Update(bintiptr) )                  ERROR
RECOVER
  term = YES;
ENDSEQ
  UnlockRoot(extlock);
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ACExtend :: Save ( )
{
  logical     root_ilocked = ILockRoot();
  ACNode     *nodeptr;
  logical     term = NO;
  topnode_list->GoTop();
  while ( nodeptr = topnode_list->GetNext() )
    nodeptr->Save(NO,NO,YES);


  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  SaveReference - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveReference"

logical ACExtend :: SaveReference ( )
{
  logical    root_ilocked = ILockRoot();
  logical    term         = NO;
  term =  extend_node && extend_node->get_noderefl()
          ? extend_node->get_noderefl()->Save() 
          : NO;
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  SetAutoIdent - 



\return cond_setting - 

\param  bintiptr - 
\param  kcbptr - 
\param  attrtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoIdent"

char ACExtend :: SetAutoIdent (binti *bintiptr, kcb *kcbptr, int attrtype )
{
  logical    root_ilocked = 255;
  char       cond_setting = NO;
  ACExtend  *topext;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( IsLocal() )
    PositionTop(root_ilocked);
  if ( !extend_node )                                SDBERR(225)
    
  if ( cond_setting = extend_node->GetAutoIdent(bintiptr,kcbptr,attrtype) )
                                                     LEAVESEQ
  base_extend->GoTop();
  while ( topext = base_extend->GetNext() )
    if ( cond_setting = topext->get_extend_node()->GetAutoIdent(bintiptr,kcbptr,attrtype) )
                                                     LEAVESEQ
                                     
  if ( bintiptr->HasBaseAutoIdKey() &&
       (cond_setting = bintiptr->SetAutoIdent(kcbptr,attrtype)) ) LEAVESEQ
      
  cond_setting = root_extend->get_extend_node()->get_noderefl()->
                                SetAutoIdent(root_extend->get_extend_node()->GetKeyInstance(bintiptr,NULL));

RECOVER
  cond_setting = ERIC;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(cond_setting);
}

/******************************************************************************/
/**
\brief  SetType - 



\return term - Termination code

\param  strnames - Type name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical ACExtend :: SetType (char *strnames )
{
  logical    root_ilocked = 255;
  ACExtend  *baseext;
  logical    term = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
//  root_ilocked = ILockRoot();
  
  if ( !IsLocal() )                                  LEAVESEQ
  if ( !extend_node )                                ERROR
  if ( !extend_node->IsVariableType() )              LEAVESEQ

  term = extend_node->SetType(strnames);

  baseext = ((ACRelationship *)extend_node)->get_system_node();
  root_extend = baseext ? baseext->get_root_extend() : this;

RECOVER
  term = YES;
ENDSEQ
//  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  SetVersion - 




\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void ACExtend :: SetVersion (uint16 version_nr )
{
  logical          root_ilocked = 255;
  refTable        *reftabl;
  ACNode          *nodeptr;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  
  if ( !extend_node )                                LEAVESEQ
    
  extend_node->SetVersion(version_nr);
  if ( reftabl = extend_node->get_noderefl() )
    reftabl->SetVersion(version_nr);
  InitExtendRef(NO);

  topnode_list->GoTop();
  while ( nodeptr = topnode_list->GetNext() )
    if ( nodeptr->get_version() == CUR_VERSION )
      nodeptr->Reset();

RECOVER

ENDSEQ
  IUnlockRoot(root_ilocked);

}

/******************************************************************************/
/**
\brief  SetupExtentRef - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupExtentRef"

logical ACExtend :: SetupExtentRef ( )
{
  logical      root_ilocked = ILockRoot();
  TypeKey     &tkey = GetExtentDef()->GetNameKey();
  LACObject   *sys_object;
  EB_Number   *ext_ref      = NULL;
  int16        mbnumber     = 0;
  logical      term         = NO;

BEGINSEQ
  if ( !(ext_ref = object_ref->GetExtendRef(tkey)) )
  {
    if ( !(sys_object = object_ref->ReserveGlobalObject()) )
                                                     SDBERR(99)
    sys_object->AddExtendRef(GetExtentDef());
    object_ref->ReleaseGlobalObject();
    if ( !(ext_ref = object_ref->GetExtendRef(tkey)) )
                                                     SDBERR(99)
  }
  int_extref = *ext_ref;  
  
  mbnumber = GetExtentDef()->GetMainBase(object_ref);       
  if ( extend_node->get_noderefl()->Setup(&int_extref,0,mbnumber,extend_node->get_nodeacc(),YES) )  
                                                     ERROR

RECOVER
  int_extref = 0;
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  SetupRootExt - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupRootExt"

void ACExtend :: SetupRootExt ( )
{
  ACExtend    *acext;

  if ( acext = base_extend->GetHead() )
    root_extend = acext->get_root_extend();
  else
    root_extend = this;


}

/******************************************************************************/
/**
\brief  UnlockRoot - 



\return term - Termination code

\param  extlock - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockRoot"

logical ACExtend :: UnlockRoot (logical extlock, logical global_add )
{
  int16    saverr = SDBERROR;
  logical  term   = NO;
BEGINSEQ
  if ( !root_extend )                                SDBERR(99)
  
  if ( global_add && IsLocal() )
  {
    if ( extend_node->UnlockSet(extlock,NO) )        ERROR
  }
  else
    if ( root_extend->get_extend_node()->UnlockSet(extlock,NO) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( saverr )
    SDBISET(saverr);
  return(term);
}

/******************************************************************************/
/**
\brief  Update - 



\return term - Termination code

\param  bintiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical ACExtend :: Update (binti *bintiptr )
{
  logical   root_ilocked = ILockRoot();
  inti     *oldinti      = extend_node->get_nodeinst();
  char     *skey;
  ACExtend *subext;
  EB_Number entnr;
  logical   term = NO;
BEGINSEQ
  if ( IsLocal() || extend_node->get_nodefield()->fmcbityp == T_VOID)
                                                     LEAVESEQ
  if ( !extend_node->get_noderefp() )
    extend_node->Check(YES,NO);
        
  if ( GetExtentDef()->get_acctype() == AT_ODABA     &&
       extend_node->get_noderefp()->get_refsakcb()->get_key_def()->scbsmcb->smcbsts.stscnof() )
  {
    entnr = bintiptr->GetID();
    skey = (char *)&entnr;
  }
  else
    skey = extend_node->ExtractSortKey(NULL,bintiptr->GetOldInst(NULL),NO);
  
  if ( !skey || extend_node->GetID(skey,NO).IsEmpty() )
                                                     LEAVESEQ
  deri_extend->GoTop();
  while ( subext = deri_extend->GetNext() )
    if ( subext->Update(bintiptr) )                  ERROR

  extend_node->SetCurrentInti(bintiptr);
  term = extend_node->UpdateID();
  extend_node->SetCurrentInti(oldinti);

RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  Upgrade - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  ac_baseext - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Upgrade"

logical ACExtend :: Upgrade (ACExtend *ac_baseext, PIACC accopt )
{
  logical    root_ilocked = 255;
  logical    term         = NO;
BEGINSEQ
  if ( Check() )                                     ERROR
  root_ilocked = ILockRoot();
  if ( !extend_node )                                SDBERR(225)

  if ( IsLocal() && accopt == PI_Write )
    accopt = PI_Update;   // local extents werden höchstens auf Update gesetzt
  
  if ( accopt <= extend_node->get_nodeacc() )     
  {
    if ( !IsLocal() )
      SetupRootExt();
    LEAVESEQ
  }

  extend_node->SetMode(accopt);
  if ( Upgrade(ac_baseext) )                         ERROR

RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  ac_baseext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Upgrade"

logical ACExtend :: Upgrade (ACExtend *ac_baseext )
{
  logical    root_ilocked = ILockRoot();
  LACObject *lobhandle     = extend_node->get_object_ref()->GetLocalACObject();
  DBExtend  *extend       = GetExtentDef();
  DBExtend  *subext;
  ACExtend  *acext;
  PIACC      accopt = extend_node->get_nodeacc();
  logical    term   = NO;
BEGINSEQ
  if ( !extend || IsLocal() )                     LEAVESEQ
    
  extend->get_base_extend()->GoTop();
  while ( subext = extend->get_base_extend()->GetNext() )
  {
    if ( !(acext = lobhandle->ProvideACExtend(subext,NULL,accopt)) )
                                                  ERROR
    if ( !base_extend->Find(acext) )
      base_extend->AddTail(acext);
    if ( !acext->get_deri_extend()->Find(this) )
      acext->get_deri_extend()->AddTail(this);
  }

  extend_node->get_nodefield()->set_mb_number(GetMainBase());
  SetupRootExt();  
  
  extend->get_derived_extends()->GoTop();
  while ( subext = extend->get_derived_extends()->GetNext() )
  {
    if ( !(acext = lobhandle->ProvideACExtend(subext,this,accopt)) )
                                                  ERROR
    if ( !deri_extend->Find(acext) )
      deri_extend->AddTail(acext);
    if ( !acext->get_base_extend()->Find(this) )
      acext->get_base_extend()->AddTail(this);
  }
RECOVER
  term = YES;
ENDSEQ
  IUnlockRoot(root_ilocked);
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACExtend - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACExtend"

     ACExtend :: ~ACExtend ( )
{
  node      *nodeptr;
  Close();

  if ( extend_path )
    free(extend_path);
  extend_path = NULL;



}


