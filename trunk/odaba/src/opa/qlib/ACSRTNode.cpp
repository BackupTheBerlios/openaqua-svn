/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACSRTNode

\brief    


\date     $Date: 2006/04/03 14:20:03,31 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACSRTNode"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBStructDef.hpp>
#include  <sbinti.hpp>
#include  <sinti.hpp>
#include  <sksrt.hpp>
#include  <slinti.hpp>
#include  <snode.hpp>
#include  <sACSRTNode.hpp>


/******************************************************************************/
/**
\brief  ACSRTNode - 



\param  obhandle - Database Object handle
\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACSRTNode"

                        ACSRTNode :: ACSRTNode (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr )
                     : bnode (obhandle,nodeptr,dbfield_ptr,highctx,PI_Write),
  list(NULL)
{
  DBIndex         *indexdef;
  int32            count = dbfield_ptr->fmcbdim;
  DBStructDef     *strdef = dbfield_ptr->GetDBStruct();
BEGINSEQ
  SDBEV1(dbfield_ptr->fmcbtype,ID_SIZE)
  
  if ( !(indexdef = dbfield_ptr->GetIndexDef((int16)0)) )
    id_key = indexdef->get_key_def();
  
  list = new ksrt(id_key,count ? count : 100,
                  dbfield_ptr->fmcbbyte,UNDEF,UNDEF,'K',YES);

  if ( instptr )
    if ( CreateInti(this,strdef,instptr,YES) )       ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Add - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  i0


\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACSRTNode :: Add (int32 lindx0, logical global_add )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( GenerateEvent(DBO_Inserted) )                 ERROR
  
  if ( !nodeinst->get_iselarea() )
    nodeinst->set_iselarea(Bnodeinst->get_isel_init());
  if ( lindx0 >= 0 )
    lindx0 = list->srtcnt();
  if ( list->srtiad(lindx0+1,nodeinst->get_iselarea()) )
                                                     ERROR
  nodecur = lindx0;
  instptr = SetupInstance(DBO_Created);
  GenerateEvent(DBO_Inserted);
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1


\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACSRTNode :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  logical                 user_inst = NO;
  void                   *instptr = NULL;
BEGINSEQ
  if ( Check(YES) )                                   ERROR
  if ( GenerateEvent(DBP_Insert) )                    ERROR

  if ( lindx0 == LAST_INSTANCE )
    lindx0 = GetCount();

  if ( initinst || nodeinst->stscini() )                            // vorinitialisierte instanz
    user_inst = YES;
  Initialize_intern(initinst);
  if ( id_key && (skey || idkey) )
    id_key->kcbkpt(GetKeyInstance(nodeinst,NULL),skey ? skey : idkey );

  instptr = Add(lindx0,NO);
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical ACSRTNode :: Cancel (logical chknode )
{
  logical                 term = NO;
  nodecur = AUTO;
  SetupInstance(DBO_Reset);
  return(term);
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

logical ACSRTNode :: Check (logical autoini, logical acccheck )
{
  logical                 term = NO;
BEGINSEQ
  if ( autoini )
  {
    if ( InitInti(nodefield->GetDBStruct(object_ref->GetDictionary()),NULL) )  ERROR
  }
  
  if ( bnode::Check(autoini,acccheck) )             ERROR


RECOVER
  term = YES;
ENDSEQ
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

logical ACSRTNode :: Close ( )
{
  logical                 term = NO;

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

inti *ACSRTNode :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  linti                   *lintiptr = NULL;
BEGINSEQ
  lintiptr = new linti(nodeptr,strdef_ptr,instptr);    SDBCERR



RECOVER
  delete lintiptr;
  lintiptr = NULL;
ENDSEQ
  return(lintiptr);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  NODEID


\param  indx0 - Position in collection
\param  chknode - 
\param  del_dep - 
\param  del_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACSRTNode :: Delete (int32 indx0, logical chknode, logical del_dep, logical del_inst )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( indx0 == AUTO )
    indx0 = nodecur;
  if ( indx0 == AUTO )                               ERROR
    
  nodecur = indx0;
  SetupInstance(DBP_Delete);
  
  Bnodeinst->DeleteReferences(NULL,YES);
  Bnodeinst->DeleteRelationships(NULL,YES);
  list->srtidl(indx0+1);
  
  nodecur = AUTO;
  SetupInstance(DBO_Deleted);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical ACSRTNode :: Delete (char *skey, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( !Get(skey) )                                  ERROR
  
  Delete(AUTO,NO);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Duplicate - 


\return instptr - 

\param  keyptr - 
\param  db_replace - Replace option
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Duplicate"

void *ACSRTNode :: Duplicate (char *keyptr, PIREPL db_replace, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( nodecur == AUTO )                             ERROR
  if ( !(instptr = SetupInstance(DB_undefined)) )    ERROR

  if ( !LocateKey(keyptr) )   // key already exists
  {
    if ( !db_replace )                               SDBERR(64)
    SetupInstance(DB_undefined);
    memcpy(nodeinst->get_iselarea(),instptr,nodefield->fmcbbyte);
    id_key->SetKey(nodeinst->get_iselarea(),keyptr);
  }
  else
  {
    GetInitInstance(NO);
    memcpy(nodeinst->get_iselarea(),instptr,nodefield->fmcbbyte);
    Add(nodecur,keyptr,NULL,nodeinst->get_iselarea(),NO);
  }


RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  FirstKey - 


\return keyptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

char *ACSRTNode :: FirstKey (logical chknode )
{
  char                   keyarea[1025];
  char                  *keyptr = NULL;
BEGINSEQ
  if ( !Get(FIRST_INSTANCE) )                        ERROR

  list->ExtractKey(nodeinst->get_iselarea(),keyarea);
  keyptr = keyarea;

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  Get - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG


\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACSRTNode :: Get (int32 indx0, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  nodecur = indx0;
  instptr = Get();


RECOVER
  nodecur = AUTO;
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACSRTNode :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( LocateKey(skey,YES,chknode) )                 ERROR
  
  instptr = Get();
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACSRTNode :: Get ( )
{
  void                   *instptr = NULL;
  if ( instptr = SetupInstance(DBO_Read) )        
    GenerateEvent(DBO_Read);

  return(instptr);
}

/******************************************************************************/
/**
\brief  GetCount - 


\return ecnt - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACSRTNode :: GetCount (logical chknode )
{

  return(this && list ? list->srtcnt() : ERIC);

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

EB_Number ACSRTNode :: GetID (int32 indx0, logical chknode, logical pif_opt )
{
  EB_Number               ebsnum;

  return(ebsnum);
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

EB_Number ACSRTNode :: GetID (char *keyptr, logical chknode, logical pif_opt )
{
  EB_Number               ebsnum;

  return(ebsnum);
}

/******************************************************************************/
/**
\brief  GetInitInstance - 


\return instptr - 

\param  set_init - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInitInstance"

void *ACSRTNode :: GetInitInstance (logical set_init )
{
  void                   *instptr = NULL;
BEGINSEQ
  if ( nodeinst->stscini() )                         LEAVESEQ
    
  nodeinst->set_iselarea(NULL);
  nodeinst->InitArea(NULL);
  nodeinst->Initialize(NULL,set_init);
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetInstModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstModCount"

int16 ACSRTNode :: GetInstModCount ( )
{
  int16                   modcount;

  return(modcount);
}

/******************************************************************************/
/**
\brief  GetKey - 


\return key_val - 

\param  lindx0 - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *ACSRTNode :: GetKey (int32 lindx0, logical chknode )
{
  char                   keyarea[1025];
  char                  *keyptr = NULL;
BEGINSEQ
  if ( !Get(lindx0) )                            ERROR

  list->ExtractKey(nodeinst->get_iselarea(),keyarea);
  keyptr = keyarea;

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  GetRefModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefModCount"

int16 ACSRTNode :: GetRefModCount ( )
{
  int16                   modcount;

  return(modcount);
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

logical ACSRTNode :: Locate (EB_Number entnr, logical read_opt )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  LocateKey - 


\return term - Termination code

\param  skey - 
\param  exact - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical ACSRTNode :: LocateKey (char *skey, logical exact, logical chknode )
{
  int32       indx = 0;
  logical     term = NO;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  
  if ( !(indx = list->srtbsr(skey)) )                ERROR

  if ( list->stscerr() && exact )                    ERROR

  nodecur = indx-1;
RECOVER
  nodecur = AUTO;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Move - 


\return targinst - 

\param  srcenode - 
\param  db_replace - Replace option
\param  w_newkey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Move"

void *ACSRTNode :: Move (node *srcenode, PIREPL db_replace, char *w_newkey, logical chknode )
{
  void                   *targinst = NULL;

  return(targinst);
}

/******************************************************************************/
/**
\brief  MoveDown - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

logical ACSRTNode :: MoveDown ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  MoveUp - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

logical ACSRTNode :: MoveUp ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  NextKey - 


\return keyptr - 

\param  skey - 
\param  switch_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextKey"

char *ACSRTNode :: NextKey (char *skey, int16 switch_level )
{
  char                   *keyptr = NULL;

  return(keyptr);
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

logical ACSRTNode :: Open (ACObject *obhandle, node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, PIACC accopt )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Position - 


\return rindx0 - 

\param  count - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

int32 ACSRTNode :: Position (int32 count, logical chknode )
{
  int32                  indx0 = AUTO;

  return(indx0);
}

/******************************************************************************/
/**
\brief  Provide - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEKP


\param  skey - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACSRTNode :: Provide (char *skey, logical global_add )
{
  void                   *instptr = NULL;

  return(instptr);
}

/******************************************************************************/
/**
\brief  i1


\param  lindx0 - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACSRTNode :: Provide (int32 lindx0, logical global_add )
{
  void                   *instptr = NULL;

  return(instptr);
}

/******************************************************************************/
/**
\brief  i2


\param  datarea - 
\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

void *ACSRTNode :: Provide (void *datarea, logical global_add )
{
  void                   *instptr = NULL;

  return(instptr);
}

/******************************************************************************/
/**
\brief  Rename - 


\return term - Termination code

\param  identkey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Rename"

logical ACSRTNode :: Rename (char *identkey, logical chknode )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical ACSRTNode :: Reset ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ACSRTNode :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Select - 


\return term - Termination code

\param  nodeptr - 
\param  expression - Expression
\param  min_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Select"

logical ACSRTNode :: Select (node *nodeptr, char *expression, int32 min_inst )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetOrder - 


\return term - Termination code

\param  strnames - Type name
\param  attrtype - 
\param  attrstr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical ACSRTNode :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupInstance - 


\return instptr - 

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInstance"

void *ACSRTNode :: SetupInstance (DB_Event intevent )
{
  void                   *instptr = NULL;

  instptr = list->srtigt(nodecur+1);
  nodeinst->set_iselarea(instptr);
  
  if ( intevent )
    nodeinst->StructureEvents(intevent);

  return(instptr);
}

/******************************************************************************/
/**
\brief  ~ACSRTNode - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACSRTNode"

                        ACSRTNode :: ~ACSRTNode ( )
{



}


