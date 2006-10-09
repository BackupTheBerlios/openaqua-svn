/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    ACElmView



\date     $Date: 2006/05/09 12:57:36,10 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACElmView"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <skcb.hpp>
#include  <snode.hpp>
#include  <svinti.hpp>
#include  <sACElmView.hpp>


/******************************************************************************/
/**
\brief  ACElmView

-------------------------------------------------------------------------------
\brief  i0


\param  obhandle - Database Object handle
\param  extdef - Internal extent definition
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACElmView"

     ACElmView :: ACElmView (ACObject *obhandle, DBExtend *extdef, PIACC accopt )
                     : ACNode (obhandle,NULL,extdef,NULL,accopt),
  struct_def(NULL),
  nodevinti(NULL),
  nodecur_is_valid(YES),
  field_def(NULL),
  temp_struct(YES)
{

BEGINSEQ
  nodetype = NT_ACViewNode;
  if ( !(nodeinst = nodevinti = new vinti(this,nodefield->GetDBStruct(),NULL)) )
                                                     SDBERR(95)
                                                     SDBCERR
  Bnodeinst->OpenEvent();
  is_collection = YES;
RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  i1


\param  elmview_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACElmView"

     ACElmView :: ACElmView (ACElmView &elmview_ref )
                     : ACNode (elmview_ref),
  struct_def(NULL),
  nodevinti(NULL),
  nodecur_is_valid(YES),
  field_def(NULL),
  temp_struct(NO)
{

}

/******************************************************************************/
/**
\brief  i2


\param  obhandle - Database Object handle
\param  nodeptr - 
\param  proppath - 
\param  accopt - Access mode
\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACElmView"

     ACElmView :: ACElmView (ACObject *obhandle, node *nodeptr, char *proppath, PIACC accopt, char *strnames_w )
                     : ACNode (obhandle,nodeptr,NULL,NULL,accopt),
  struct_def(NULL),
  nodevinti(NULL),
  nodecur_is_valid(YES),
  field_def(NULL),
  temp_struct(YES)
{
  Dictionary *dictptr = nodeptr  ? nodeptr->GetDictionary()  :
                        obhandle ? obhandle->GetDictionary() : NULL;
  CTX_Base   *highctx;
  char        string[ID_SIZE+1];
BEGINSEQ
  SDBRESET
  
  SDBEV1(proppath,UNDEF)
  if ( !dictptr )                                    SDBERR(99)
  
  nodetype = NT_ACViewNode;

  if ( strnames_w && *strnames_w > ' ' )
  {
    temp_struct = NO;
    struct_def  = GetDictionary()->GetStructDef(strnames_w);
  }
  else 
    strnames_w = dictptr->GetTempName(string);
  
  if ( *proppath && strcmp(proppath,"*") )
  {
    if ( !struct_def )
    {
      if ( nodeptr )
        if ( !(struct_def = nodeptr->GetCurrentTypeDef()) )
          struct_def = nodeptr->GetFieldDef()->GetDBStruct();
      if ( !(struct_def = dictptr->CreateTempStruct(struct_def,proppath,strnames_w)) )
                                                     SDBERR(20)
    }
    if ( nodeptr && !Tnodeptr )                      SDBERR(99)
  }
  else // local view ("" or "*")
  {
    if ( !nodeptr || !Tnodeptr )                     SDBERR(99)
    if ( !struct_def &&
         !(struct_def = dictptr->CreateTempStruct(nodeptr->GetFieldDef(),strnames_w)) )
                                                     SDBERR(20)
    proppath = nodeptr->get_prop_path();
  }
  
  set_prop_path(proppath);
  field_def = new DBFieldDef("path_node",struct_def->smcbname,
                             RL_reference,struct_def->GetInstLength(NO),UNDEF,
                             UNDEF,struct_def,"PI",NO,NULL,NULL,NULL);
  nodefield = field_def;
  
  highctx = nodeptr && Tnodeptr 
            ? (CTX_Base *)Tnodeptr->get_nodeinst()->GetContext() 
            : (CTX_Base *)obhandle->get_ocontext();
  if ( Open(obhandle,nodeptr ? Tnodeptr : NULL,nodefield,highctx,accopt) )
                                                     ERROR
  if ( !(nodeinst = nodevinti = new vinti(this,struct_def,nodeptr ? Tnodeptr : NULL)) )
                                                     SDBERR(95)
                                                     SDBCERR
  Bnodeinst->OpenEvent();
  is_collection = YES;
RECOVER
ENDSEQ
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

void *ACElmView :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  int16      talevel = 0;
  char      *instptr = NULL;
BEGINSEQ
  if ( Check(YES) )                                   ERROR
  if ( CheckAccess(PI_Write) )                        ERROR
  if ( Switch(AUTO) )	                              ERROR

  talevel = StartTA();
  nodevinti->Initialize(initinst);  // inti erzeugt Init-Event sowohl füe base als auch für attr!
  
  if ( idkey )
    skey = idkey;
  if ( !skey )
  {
    if ( !initinst )                                 SDBERR(81)
    if ( !(skey = ACNode::ExtractKey(NULL,initinst,NO)) )    SDBERR(99)
  }
  
  if ( !LocateKey(skey,YES,NO) )                     SDBERR(64)
  
  if ( nodevinti->Add(skey,global_add) )             ERROR
  instptr = nodevinti->get_iselarea();
  nodecur = 0;
  nodewrit = YES;
RECOVER
  Cancel();
  instptr = NULL;
ENDSEQ
  if ( talevel )
    if ( StopTA(instptr == NULL) )
      instptr = NULL;
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

logical ACElmView :: Cancel (logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode )
  {
    if ( Check(NO,NO) )                              ERROR
    nodecur_is_valid = YES;
    nodevinti->Cancel();
    nodecur = AUTO;
    nodewrit = NO;  
  }
  else
    nodevinti->Reset();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateCopyNode

\return nodeptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCopyNode"

node *ACElmView :: CreateCopyNode ( )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  if ( !(nodeptr = new ACElmView(*this) ) )          SDBERR(95)
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
\brief  ExtractKey

\return keyptr - 

\param  keyptr - 
\param  kcbptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *ACElmView :: ExtractKey (char *keyptr, kcb *kcbptr, void *instptr )
{
  char        *key;
BEGINSEQ
  if ( !kcbptr->scbsmcb->smcbsts.stsclck() )   // no identity-componets
    return ( ACNode::ExtractKey(keyptr,kcbptr,instptr) );

  if ( instptr && (!nodeinst || instptr != nodeinst->get_iselarea()) )
                                                     ERROR
  if ( !instptr )
    if ( !(instptr = IsPositioned() || nodeinst->stscini()
                     ? nodeinst->get_iselarea()
                     : Get(AUTO,YES)) )              ERROR

  key = GetKeyArea();  
  if ( nodevinti->ExtractKey(key) )                  ERROR

  if ( !keyptr )
    keyptr = key;
  else
    memcpy(keyptr,key,kcbptr->kcbklng());
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
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

char *ACElmView :: FirstKey (logical chknode )
{
  char                   *keyptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  Save(AUTO,NO,NO);
  if ( nodevinti->First() )                          ERROR
  nodecur = 0;
  nodecur_is_valid = YES;

  keyptr = ACNode::ExtractKey(NULL,NULL);
RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
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

void *ACElmView :: Get (int32 indx0, logical chknode )
{
  char                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                          ERROR
  
  if ( !(indx0 == AUTO && nodecur != AUTO) )
  {
    if ( indx0 == AUTO || (!nodecur_is_valid && indx0 != LAST_INSTANCE) )
      indx0 = FIRST_INSTANCE;
    
    switch ( indx0 )
    {
      case FIRST_INSTANCE : if ( nodevinti->First()) ERROR
                            nodecur = FIRST_INSTANCE;
                            nodecur_is_valid = YES;
                            break;
      case LAST_INSTANCE  : if ( nodevinti->Last() ) ERROR
                            nodecur = LAST_INSTANCE;
                            nodecur_is_valid = YES;
                            break;
      default             : if ( nodevinti->Position(indx0) ) 
                                                     ERROR
                            nodecur = indx0;
    }
  }
  if ( nodevinti->Get() )                            ERROR
  instptr = nodevinti->get_iselarea();
  
  if ( nodeacc > PI_Read )
    nodewrit = YES;

  if ( nodesel && CheckExpression() )
    instptr = NULL;

RECOVER
  Cancel();
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

void *ACElmView :: Get (char *skey, logical chknode )
{
  char                   *instptr = NULL;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  
  if ( LocateKey(skey,YES,NO) )                      ERROR
  if ( nodevinti->Get() )                            ERROR
  instptr = nodevinti->get_iselarea();
  
  if ( nodeacc > PI_Read )
    nodewrit = YES;

  if ( nodesel && CheckExpression() )                ERROR
    instptr = NULL;


RECOVER
  Cancel();
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetCount

\return count

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACElmView :: GetCount (logical chknode )
{
  int32          count = ERIC;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
  
  count = nodevinti->GetCount();
RECOVER

ENDSEQ
  return(count);
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

logical ACElmView :: LocateKey (char *skey, logical exact, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  nodecur_is_valid = NO;
  
  Save(NO,NO,NO);
  if ( nodevinti->LocateKey(skey,exact) )            ERROR
  nodecur = LAST_INSTANCE/2;
  nodecur_is_valid = YES;

RECOVER
  Cancel();
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

void *ACElmView :: Modify (logical chknode )
{
  char                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR

  if ( nodevinti->Modify() )                         ERROR
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
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

char *ACElmView :: NextKey (char *skey, int16 switch_level )
{
  int32                    next;
  void                   *instptr;
  char                   *keyptr = NULL;
BEGINSEQ
  if ( Check(YES) )                                  ERROR
  
  if ( skey )
  {
    Switch(AUTO);
    if ( LocateKey(skey,NO,NO) )                     ERROR
    if ( !CompareKey(skey,ACNode::ExtractKey(NULL,NULL),NO) )
      if ( nodevinti->Next(1) )                      ERROR
  }
  else
  { 
    if ( (next = nodecur) != AUTO )
    {
      Save(NO,NO,NO);
      if ( nodevinti->Next(1) )                      ERROR
      // etwas ineffizient, besser wie bei Get()
      if ( nodecur_is_valid )
        nodecur = next + 1;
    }
    else
      if ( !(keyptr = FirstKey(NO)) )                ERROR
  }
  
  if ( nodesel )
  {
    if ( !GetKeySMCB() )                             SDBERR(174)
    next = nodecur;
    while ( !(instptr = Get(next++,NO)) && nodecur ) ;
    if ( !instptr || !(keyptr = ACNode::ExtractKey(NULL,nodeinst->get_iselarea(),NO)) )
                                                     ERROR
  }
  
  keyptr = ACNode::ExtractKey(NULL,NULL);
RECOVER
  Cancel();
  keyptr = NULL;
ENDSEQ
  return(keyptr);
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

logical ACElmView :: Save (logical switchopt, logical overwrite, logical chknode )
{
  int16    talevel = 0;
  logical  term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  talevel = StartTA();

  if ( nodeinst->Save(switchopt,overwrite,NO) )      ERROR

  if ( switchopt )
  {
    nodecur = AUTO;
    nodewrit = NO;
    nodecur_is_valid = YES;
  }

RECOVER
  Cancel();
  term = YES;
ENDSEQ
  if ( talevel )
    term = StopTA(term);
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

logical ACElmView :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  logical    term = NO;
BEGINSEQ
  if ( Check(YES) )                                  ERROR

  Save(AUTO,NO,NO);
  if ( nodevinti->GetTopNode()->SetOrder(strnames,attrtype,attrstr) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACElmView


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACElmView"

     ACElmView :: ~ACElmView ( )
{
  if ( nodeidnt == NODE_ID )
    ACNode::Close();
  
  nodevinti = NULL;

  if ( temp_struct && !origin && struct_def )
  {
    GetDictionary()->RemoveStructDef(struct_def->smcbname);
    delete struct_def;
    struct_def = NULL;
  }

  delete field_def;
  field_def = NULL;
}


