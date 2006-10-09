/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    ACGenericAttr



\date     $Date: 2006/05/09 15:35:14,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACGenericAttr"

#include  <popa7.h>
#include  <sACProperty.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <srefTable.hpp>
#include  <sACGenericAttr.hpp>


/******************************************************************************/
/**
\brief  ACGenericAttr

-------------------------------------------------------------------------------
\brief  i0


\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  extoff - 
\param  intoff - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACGenericAttr"

     ACGenericAttr :: ACGenericAttr (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, int32 extoff, int32 intoff, PIACC accopt )
                     : ACReference (nodeptr,dbfield_ptr,highctx,extoff,accopt),
  attr_type(UNDEF),
  inst_off(intoff),
  no_modify(NO)
{
BEGINSEQ
  nodetype = NT_ACGenericAttr;
  
  nodeacc = accopt;        // zurücknehmen PI_Read aus SubNode-Konstruktor
  if ( InitReference() )                               ERROR
//  if ( InitIsel(GetMainBase(),instptr) )               ERROR
  if ( InitIsel(0,instptr) )                           ERROR

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  i1


\param  acgnoderef
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACGenericAttr"

     ACGenericAttr :: ACGenericAttr (ACGenericAttr &acgnoderef )
                     : ACReference (acgnoderef),
  attr_type(acgnoderef.get_attr_type()),
  inst_off(acgnoderef.get_inst_off()),
  no_modify(NO)
{
}

/******************************************************************************/
/**
\brief  i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACGenericAttr"

     ACGenericAttr :: ACGenericAttr ( )
                     : ACReference (),
  attr_type(UNDEF),
  inst_off(0),
  no_modify(NO)
{
  nodetype = NT_ACGenericAttr;

}

/******************************************************************************/
/**
\brief  Add

\return instptr - 

\param  lindx0 - 
\param  global_add
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACGenericAttr :: Add (int32 lindx0, logical global_add )
{
  int                     attrtype = CS_U;
  smcb                   *cs_smcb  = NULL;
  char                    string[ID_SIZE+1];
  void                   *instptr  = nodeinst->get_iselarea();
BEGINSEQ
  ExtractKey((char *)&attrtype,instptr,NO);
  cs_smcb = GetKeySMCB()->GetEntry(1)->fmcbsmcb;
  if ( !cs_smcb->smcbacc->Access(attrtype,string,sizeof(string)) )
                                                    ERROR
//  if ( SetGenAttribute(attrtype,NULL) )            ERROR

  instptr = ACReference::Add(lindx0,global_add);
  if ( ((LNode *)nodenode)->AddGenericRef(nodefield->fmcbname) )
                                                     ERROR
  if ( highnod && 
       highnod->get_nodeinst()->get_struct_def()->GetGUIDPosition() >= 0 )
    highnod->Modify();
    

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  AddGenAttribute

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGenAttribute"

logical ACGenericAttr :: AddGenAttribute ( )
{
  logical                 term = NO;
BEGINSEQ
// nur zum Initialisieren von Instanzen beim isel-Add

  noderefp->InitialWrite();
  SetGenAttribute(nodeinst->get_iselarea());
  
  if ( attr_type <= 0 )   
    InitInstance(nodeinst->get_iselarea());
  else
    if ( !LNode::Add(AUTO,(char *)&attr_type,NULL,nodeinst->get_iselarea()) )  
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyReference

\return term - Termination code

\param  srceinti - 
\param  db_replace - Replace option
\param  copy_type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyReference"

logical ACGenericAttr :: CopyReference (inti *srceinti, PIREPL db_replace, PIREPL copy_type )
{

  return(LNode::CopyReference(srceinti,db_replace,copy_type));

}

/******************************************************************************/
/**
\brief  CopySet

\return count

\param  srcenode - 
\param  check_inverse
\param  db_replace - Replace option
\param  copy_type
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySet"

int32 ACGenericAttr :: CopySet (node *srcenode, logical check_inverse, PIREPL db_replace, PIREPL copy_type, logical chknode )
{
  int32    count    = ERIC;
  int      attrtype = attr_type;
  attr_type = UNDEF;
  
  count = ACReference::CopySet(srcenode,check_inverse,db_replace,copy_type,chknode);

  attr_type = attrtype;
  return(count);
}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACGenericAttr :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACGenericAttr(*this) ) )      SDBERR(95)
                                                     SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  Delete

\return term - Termination code

\param  lindx0 - 
\param  chknode
\param  del_dep - 
\param  del_inst
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACGenericAttr :: Delete (int32 lindx0, logical chknode, logical del_dep, logical del_inst )
{
  int16                   talevel = 0;
  logical                 extlock;
  logical                 term    = NO;
BEGINSEQ
  if ( (extlock = CheckDel(lindx0,chknode)) == ERIC ) ERROR

  talevel = StartTA();
  nodeinst->Save(YES,NO);  
  
  ((LNode *)nodenode)->DelGenericRef(nodefield->fmcbname); // muß nicht unbedingt klappen, kann schon gelöscht sein
                                                     
  if ( DeleteInstance(nodeinst,NULL,NO,del_dep,YES,del_inst) )   ERROR
  ResetInstance();  


RECOVER
  term = YES;
ENDSEQ
  if ( UnlockSet(extlock,NO) )
    term = YES;
  if ( talevel )
    term = StopTA(term);
  return(term);
}

/******************************************************************************/
/**
\brief  GetGenAttrType

\return attrtype

\param  attrstr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttrType"

int ACGenericAttr :: GetGenAttrType (char *attrstr )
{
  smcb      *cs_smcb;
  int32      attrtype = UNDEF;
BEGINSEQ
  attrtype = attr_type;
  
  if ( attrstr )
  {
    cs_smcb = GetKeySMCB()->GetEntry(1)->fmcbsmcb;
    cs_smcb->smcbacc->Access(attrstr,attrtype);
    if ( attrtype == CS_U )                          ERROR
  }
RECOVER
  attrtype = UNDEF;
ENDSEQ
  return(attrtype);
}

/******************************************************************************/
/**
\brief  GetID

\return ebsnum - 
-------------------------------------------------------------------------------
\brief  NODEGID


\param  indx0 - Position in collection
\param  chknode
\param  pif_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACGenericAttr :: GetID (int32 indx0, logical chknode, logical pif_opt )
{

//  return(nodenode->GetID(indx0,chknode,pif_opt));
  return(ACReference::GetID(indx0,chknode,pif_opt));


}

/******************************************************************************/
/**
\brief  NODEGID_


\param  keyptr - 
\param  chknode
\param  pif_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number ACGenericAttr :: GetID (char *keyptr, logical chknode, logical pif_opt )
{

//  return(nodenode->GetID(keyptr,chknode,pif_opt));
  return(ACReference::GetID(keyptr,chknode,pif_opt));


}

/******************************************************************************/
/**
\brief  Initialize

\return term - Termination code

\param  instptr - 
\param  set_init
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ACGenericAttr :: Initialize (void *instptr, logical set_init )
{
  logical                 term = NO;
BEGINSEQ
  if ( Check(YES,NO) )                               ERROR

  if ( !instptr || instptr == nodeinst->get_iselarea() )
  {
    SetGenKey();
    instptr = nodeinst->get_iselarea();
  }
  
  if ( Initialize_intern(instptr,set_init) )         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Modify

\return instptr - 

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void *ACGenericAttr :: Modify (logical chknode )
{
  char   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES,NO) )                    ERROR
  
  instptr = nodeinst->get_iselarea();
  // ein Versuch, Recursive Aufrufe zu verhindern (über highnod am Ende
  // kann aber dazu führen, dass bei weiteren Modify keine events erzeugt werden
  if ( stscmod() )                                   LEAVESEQ
  
  if ( no_modify )
  {
    no_modify = NO;                                  LEAVESEQ
  }
    
  if ( chknode && CheckModify() )                    ERROR
  
  if ( nodeacc > PI_Read && !IsPositioned() && nodenode->IsPositioned() )
    SetGenAttribute(attr_type,NULL);
  
  if ( !nodeinst->IsPositioned() && !nodeinst->stscini())
  {
    if ( chknode )                                   SDBERR(76)
    LEAVESEQ
  }
  if ( !IsWrite() && !nodeinst->stscini() )          SDBERR(28)

  if ( attr_type && attr_type != *(int32 *)ExtractKey(NULL,nodeinst->get_iselarea(),NO) ) // ist fuer nodeinst->stscini ev. zu viel
                                                     SDBERR(66)
  if ( !nodeinst->stscini() )
    if ( nodeinst->Modify() )                        ERROR
  if ( stscmod() )                                   LEAVESEQ
  
  stssmod();
  if ( highnod && !highnod->Modify() )               ERROR

RECOVER
  Reset();
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  PrepareGenAttribute

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrepareGenAttribute"

logical ACGenericAttr :: PrepareGenAttribute ( )
{
  int             attrtype;
  logical         term = NO;
BEGINSEQ
  if ( !nodenode->get_nodeinst()->IsPositioned() )   LEAVESEQ
    
  no_modify = NO;
  ExtractKey((char *)&attrtype,nodeinst->get_iselarea(),NO);
  if ( attrtype != AUTO )   
  {
    if ( !stscmod() && !stscsav() )
      no_modify = YES;
  }
  else
    if ( SetGenAttribute(attr_type,NULL) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetGenAttribute

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetGenAttribute"

logical ACGenericAttr :: ResetGenAttribute ( )
{
  int             attrtype;
  logical         term = NO;
BEGINSEQ
  if ( !nodeinst->IsPositioned() && !nodeinst->stscini() ) 
                                                     LEAVESEQ
    
  ExtractKey((char *)&attrtype,nodeinst->get_iselarea(),NO);
  if ( attrtype == attr_type )                       LEAVESEQ
  
  if ( (nodecur != AUTO || nodeinst->stscini()) &&
       (attrtype == AUTO || !attrtype)               )
    SetGenKey();
  else                                               SDBERR(66)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetGenAttribute

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  attrtype
\param  attrstr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical ACGenericAttr :: SetGenAttribute (int attrtype, char *attrstr )
{
  int         old_attr;
  logical     term = NO;
BEGINSEQ
  if ( attrstr )
    attrtype = GetGenAttrType(attrstr);

  if ( attrtype == AUTO )   
    attrtype = attr_type;

  if ( !attrtype )   
  {
    Switch(AUTO);
    InitInstance(nodeinst->get_iselarea());
    LEAVESEQ
  }

  if ( !nodenode->IsSelected() )
  {
    attr_type = attrtype;
    LEAVESEQ
  }

  if ( nodenode->IsWrite() && attrtype != CS_U )
  {
    if ( nodecur != AUTO )
    {
      ExtractKey((char *)&old_attr,nodeinst->get_iselarea());
      if ( old_attr != attr_type )
        SetGenKey(); 
    }
    if ( attrtype != attr_type )
      Switch(AUTO);
    if ( ACReference::GetID((char *)&attrtype).IsEmpty() )
    {
      SDBCERR
//      ACReference::Initialize(NULL);               kann anstelle naechster zeile, wenn Funktion virtuell
      if ( Initialize_intern(NULL) )                 ERROR
      attr_type = attrtype;
      SetGenKey();
//      if ( !LNode::Add(AUTO,(char *)&attrtype,NULL,nodeinst->get_iselarea()) )
//      {
//        Switch(AUTO);
//        InitInstance(nodeinst->get_iselarea());
//        ERROR
//      }
    }
    else
      if ( !Get((char *)&attrtype) )                 ERROR
  }
  else
    if ( !(attrtype != CS_U ? Get((char *)&attrtype) : Get(FIRST_INSTANCE)) )      
      InitInstance(nodeinst->get_iselarea());
  
  attr_type = attrtype;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i03


\param  fldnames - Property name
\param  attrtype
\param  attrstr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical ACGenericAttr :: SetGenAttribute (char *fldnames, int attrtype, char *attrstr )
{
  logical     term = NO;
  int16       talevel = 0;
  talevel = StartTA();
  
  term =  fldnames 
          ? LNode::SetGenAttribute(fldnames,attrtype,attrstr)
          : SetGenAttribute(attrtype,attrstr);

  if ( talevel )
    term = StopTA(term);
  return(term);
}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical ACGenericAttr :: SetGenAttribute ( )
{
  logical     term = NO;
  if ( (attr_type <= 0    && attr_type != CS_U )       ||
       (attr_type > 0     && !Get((char *)&attr_type)) ||
       (attr_type == CS_U && !Get(FIRST_INSTANCE))         )
    InitInstance(nodeinst->get_iselarea());
    
  no_modify = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  i2


\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenAttribute"

logical ACGenericAttr :: SetGenAttribute (void *instptr )
{
  int         attrtype;

  ExtractKey((char *)&attrtype,instptr,NO);
  if ( attrtype <= 0 )
    attrtype = attr_type;
  else
    attr_type = attrtype;

  return(NO);
}

/******************************************************************************/
/**
\brief  SetGenKey

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGenKey"

logical ACGenericAttr :: SetGenKey ( )
{
  logical                 term = NO;
  if ( nodeinst )
    fldfmcb->fmcbsmcb->smcbidky->kcbkpt(nodeinst->get_iselarea(),(char *)&attr_type);

  return(term);
}

/******************************************************************************/
/**
\brief  SetupNode

\return term - Termination code

\param  create_ref
\param  retain_mod
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupNode"

logical ACGenericAttr :: SetupNode (logical create_ref, logical retain_mod )
{

  ResetNode(stscfil());
  return ( ACReference::SetupNode(create_ref,retain_mod) );

}

/******************************************************************************/
/**
\brief  ~ACGenericAttr


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACGenericAttr"

     ACGenericAttr :: ~ACGenericAttr ( )
{
  if ( nodeidnt == NODE_ID )
    Close();
}


