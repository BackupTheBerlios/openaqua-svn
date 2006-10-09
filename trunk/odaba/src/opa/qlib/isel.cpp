/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    isel

\brief    


\date     $Date: 2006/07/16 12:27:45,01 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "isel"

#include  <popa7.h>
#include  <sACGenericAttr.hpp>
#include  <sACObject.hpp>
#include  <sACShareBase.hpp>
#include  <sACStructure.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <iNetConversion.h>
#include  <sStructAccess.hpp>
#include  <s__OBJECT.hpp>
#include  <sexd.hpp>
#include  <sexdBBuffer.hpp>
#include  <sguid.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <sisel.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical isel :: Add (logical global_add )
{
  logical   term    = NO;
BEGINSEQ
  if ( cluster_crtopt )
    cluster_number = AUTO;
    
  if ( !CreateInstance(field_def->fmcbityp == T_MEMO ? field_def->fmcbsize+1 : UNDEF) )
                                                     ERROR
  if ( before_add() )                                ERROR
  stsrini();
  
  if ( SetupNewInst(global_add) )                    ERROR
  SetTimeStamp();
  CreateGUID(NULL);
  if ( PutInstance(iselarea,field_def->fmcbityp == T_MEMO ? field_def->fmcbsize+1 : UNDEF,YES,NO) )
                                                     ERROR
  
  objid = PIFToLong(GetID().get_ebsnum(),struct_access->get_pif());
  if ( iselarea )
    SetIdentity();
  
  Setup();
  after_add();
RECOVER
  if ( exd_area )
  {
    exd_area->ReleaseInstance(active_handle);
    exd_area = NULL;
  }
  GenerateEvent(DBO_NotCreated);
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  AddGenericRef - 


\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGenericRef"

logical isel :: AddGenericRef (char *fldname )
{
  nodelist  cursor(node_rshp);
  node     *nodeptr;
  exd      *exdptr;
  logical   term    = NO;  

BEGINSEQ
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( ((ACRelationship *)nodeptr)->AddInversGenRef(fldname) )         ERROR

  (cursor = node_base).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( !nodeptr->get_nodeinst()->SetInWork(YES) )
    {
      exdptr = ((isel *)nodeptr->get_nodeinst())->get_exd_area();
      term = ((ACShareBase *)nodeptr)->AddGenericRef(fldname);
      exdptr->SetInWork(NO);
      if ( term )                                    ERROR
    }
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical isel :: Cancel ( )
{
  logical   term = NO;
BEGINSEQ
// hier muss zuerst das Cancel für References, GenAttrs und Relationships erfolgen,
// dann das ExtToInt und dann das Cancel für die BaseStructures
// z.Z. geht das alles im binti::Cancel (s.u), das muss geteilt werden!!  
  if ( stscsav() && exd_area )
  {
    struct_access->get_struct_def()->ExtToInt(iselarea,exd_area->GetInstance(),struct_access->get_pif());
    if ( Save(NO,YES,NO) )                             ERROR
  }

  binti::Cancel();
  Reset();
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CheckDBInstance - 


\return term - Termination code

\param  nresult - 
\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBInstance"

logical isel :: CheckDBInstance (NString &nresult, CheckOptions check_opts )
{
  nodelist                cursor(node_base);
  node                   *nodeptr;
  logical                 term = NO;
  if ( check_opts.guids )
    term = ob_handle->get_local_dbhandle()->CheckDBGUID(
                exd_area->get_exdacb(),nresult,
                check_opts.repair_all,check_opts.show_warnings,UNDEF);
                
  (cursor = node_genattr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( ((LNode *)nodeptr)->CheckDBCollection(nresult,check_opts) )
      term = YES;

  (cursor = node_refr).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( ((LNode *)nodeptr)->CheckDBCollection(nresult,check_opts) )
      term = YES;

  (cursor = node_rshp).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( ((ACRelationship *)nodeptr)->CheckDBCollection(nresult,check_opts) )
      term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return wpmode - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

uint8 isel :: CheckWProtect ( )
{

  return ( exd_area ? exd_area->CheckWProtect() : NO);


}

/******************************************************************************/
/**
\brief  Close - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical isel :: Close ( )
{

  GenerateEvent(DBO_Close);
  
  binti::Close();                //  DeleteSubNodes();
  
  Reset();
  return(NO);
}

/******************************************************************************/
/**
\brief  CopyBufferInstance - 


\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyBufferInstance"

logical isel :: CopyBufferInstance (inti *intiptr )
{
  isel                   *iselptr = (isel *)intiptr;
  logical                 term = NO;
  binti::CopyBufferInstance(intiptr);

  SetInstance(iselptr->get_exd_area());
  
  mb_number      = iselptr->get_mb_number();
  cluster_number = iselptr->get_cluster_number();
  version        = iselptr->get_version();


  return(term);
}

/******************************************************************************/
/**
\brief  CreateGUID - 


\return term - Termination code

\param  _guid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGUID"

logical isel :: CreateGUID (guid *_guid )
{
  int32               pos;
  LACObject         *sys_object;
  LNode             *guid_node;
  binti             *base_binti;
  char               type[ID_SIZE];
  logical            term = NO;
BEGINSEQ
  if ( ob_handle->get_access_mode() == PI_Read )     SDBERR(347)
  if ( (pos = struct_def->GetGUIDPosition()) == AUTO )   
                                                     ERROR
  if ( !_guid )
  {
    _guid = (guid *)(iselarea+pos);
    _guid->AutoCorrection();
    if ( !_guid->GetSID() && struct_def->get_global_identity() )    // auto-guid
      BuildGUID(_guid);
    if ( !_guid->GetSID() )                          LEAVESEQ
  }

  memcpy(iselarea+pos,_guid,sizeof(guid));      
  if ( !(base_binti = GetBaseBinti(gvtxstb(type,"__OBJECT",sizeof(type)),NO)) )
  {
    SDBEV1(_guid->GetString(type),UNDEF)
    SDBERR(99)
  }
  
  if ( !(sys_object = ob_handle->GetLocalACObject()->ReserveGlobalObject()) )
                                                     ERROR
  // das führt im Cancelfall dazu, dass GUIDs mit ungültigen Instanzen stehenbleiben 
  guid_node = (LNode *)sys_object->get_guid_pi().get_nodeptr();
  if ( stscini() || guid_node->GetID((char *)_guid).IsEmpty() )
    if ( term = guid_node->AddID(base_binti,GetID(),AUTO) )
    {
      if ( guid_node->GetID((char *)_guid) == GetID() )
        term = NO;
      else
      {
        BuildGUID(_guid);
        term = guid_node->AddID(base_binti,GetID(),AUTO);
      }
    }
  ob_handle->GetLocalACObject()->ReleaseGlobalObject();
  if ( term )                                        SDBERR(99)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DelGenericRef - 


\return term - Termination code

\param  fldname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelGenericRef"

logical isel :: DelGenericRef (char *fldname )
{
  nodelist  cursor(node_rshp);
  node     *nodeptr;
  exd      *exdptr;
  logical   term    = NO;  

BEGINSEQ
  cursor.GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( ((ACRelationship *)nodeptr)->DelInversGenRef(fldname) )         ERROR

  (cursor = node_base).GoTop();
  while ( nodeptr = cursor.GetNext() )
    if ( nodeptr->Exist() && !nodeptr->get_nodeinst()->SetInWork(YES) )
    {
      exdptr = ((isel *)nodeptr->get_nodeinst())->get_exd_area();
      term = ((ACShareBase *)nodeptr)->DelGenericRef(fldname);
      exdptr->SetInWork(NO);
      if ( term )                                    ERROR
    }
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  extnames - Extent name
\param  is_root - 
\param  delopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical isel :: Delete (char *extnames, logical is_root, int16 delopt )
{
  logical          term = NO;
BEGINSEQ
  // called in case of error, only
  
  DeleteRelationships(extnames,is_root,delopt,YES);
  DeleteReferences(extnames,is_root,delopt,YES);
  if ( delopt )
    if ( DeleteInstance() )                          ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteInstance - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteInstance"

logical isel :: DeleteInstance ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( struct_def->get_based_on_object() )    // GUID
    RemoveGUID();
    
  if ( exd_area )
  {
    if ( exd_area->Delete(stsclck()) )               ERROR
    SetInWork(NO); 
  }
  if ( stscwpt() == 3 )
    stsswpt(2);
  Reset();
  RecursiveEvents(DBO_Deleted);

RECOVER
  GenerateEvent(DBO_NotDeleted);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical isel :: Get (EB_Number entnr )
{
  logical   update = NO;
  logical   term   = NO;

BEGINSEQ
 if ( entnr.IsEmpty() )                             ERROR
  
  if ( exd_area && exd_area->get_exdebsn() == entnr )
                                                     LEAVESEQ
  Release();
    
  if ( GenerateEvent(DBP_Read) )                     ERROR
  
  ResetSubNodes();

  if ( GetInstance(iselarea,entnr,field_def->fmcbityp == T_MEMO ? field_def->fmcbsize+1 : UNDEF,&update) )
                                                     ERROR
  if ( SetupInst(update) )                           ERROR

RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  i1 - 


\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical isel :: Get (char *extinst )
{
  node     *nodeptr;
  logical   term = NO;
BEGINSEQ
  if ( !exd_area )
    if ( !(exd_area = new exd(ob_handle->GetLocalACObject(),NULL,
                              struct_access->GetInstLength())) )
                                                     ERROR
//wer gibt den wieder frei und wo kommen Angaben wie sid usw, her
  exd_area->set_write(NO);
  
//klären, ob mit oder ohne ieh
  memcpy(exd_area->GetInstance(),extinst,(int)exd_area->GetLength());
  if ( struct_access->get_struct_def()->ExtToInt(iselarea,exd_area->GetInstance(),struct_access->get_pif()) )
                                                     ERROR
  node_base.GoTop();
  while ( nodeptr = node_base.GetNext() )
  {
    if ( nodeptr->SetupNode((logical)NO,NO) )        ERROR
    if ( !nodeptr->Get(FIRST_INSTANCE,NO) )          ERROR
  }

//  SetupSubNodes(NO);     
  ResetSubNodes();
  Setup();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetClusterNumber - 


\return clnumb - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClusterNumber"

EB_Number isel :: GetClusterNumber ( )
{

  return(cluster_number);

}

/******************************************************************************/
/**
\brief  GetData - 


\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

logical isel :: GetData (node *nodeptr )
{
/*  char         *instarea;
  uint16        sversion   = field_def->get_dir_to_ref()->get_schema_ver();
  isel         *highisel   = (isel *) ( nodeptr->get_nodenode() 
                                        ? nodeptr->get_nodenode()->get_nodeinst() 
                                        : NULL );
  logical       p_update = NO;
*/  logical       term     = NO;
BEGINSEQ
SDBERR(99)
/*  
  if ( !highisel )                                   ERROR
  
  Release();
  
  instarea   = *(char **)(highisel->get_exd_area()->GetInstance()+nodeptr->get_nodefield()->get_offset_ext());
  if ( struct_def->get_schema_ver() > sversion )
  {
    if ( !struct_def->GetStrDefVersion(ob_handle->GetDictionary(),sversion) )
                                                     SDBERR(99)
    if ( struct_def->ConvInstVersion(ob_handle,instarea,sversion,&p_update) )
                                                     ERROR
  }
  struct_def->ExtToInt(iselarea,struct_def->get_ext_area(),struct_access->get_pif());

  stssusr2();
  if ( SetupInst(p_update) )                         ERROR
*/
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetExtInst - 


\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInst"

char *isel :: GetExtInst ( )
{

  return ( exd_area ? exd_area->GetInstance() : NULL );

}

/******************************************************************************/
/**
\brief  GetID - 


\return entnr - 

\param  w_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number isel :: GetID (int32 w_indx0 )
{
  EB_Number     entnr = 0;
  if ( exd_area )
    entnr = exd_area->get_exdebsn();

  return(entnr);
}

/******************************************************************************/
/**
\brief  GetMBNumber - 


\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBNumber"

int16 isel :: GetMBNumber ( )
{

  return( exd_area 
          ? exd_area->get_exdacb()->get_mb_number()
          : mb_number );

}

/******************************************************************************/
/**
\brief  GetModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 isel :: GetModCount ( )
{
  int16                   modcount = UNDEF;
BEGINSEQ
  if ( !exd_area )                                 LEAVESEQ
  
  modcount = mod_count;
  if ( mod_count != exd_area->get_mod_count() || 
       exd_area->IsModified() == YES            )
    modcount++;
ENDSEQ
  return(modcount);
}

/******************************************************************************/
/**
\brief  GetOBHandle - 


\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOBHandle"

ACObject *isel :: GetOBHandle ( )
{

  return(ob_handle);

}

/******************************************************************************/
/**
\brief  GetOldInst - 


\return instptr - 

\param  oldinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOldInst"

char *isel :: GetOldInst (void *oldinst )
{
  nodelist  cursor(node_base);
  bnode    *bnode_ptr;
BEGINSEQ
  SDBRESET
  
  if ( !oldinst )
    if ( !(oldinst = struct_access->get_instarea()) ) ERROR
  
  if ( !struct_access->GetInstance(oldinst,exd_area)) ERROR

  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( !bnode_ptr->get_bnodeinst()->GetOldInst(((char *)oldinst)+bnode_ptr->get_nodefield()->fmcbposn) )           
                                                      ERROR
  (cursor = node_genattr).GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( ((ACGenericAttr *)bnode_ptr)->get_attr_type() )
      if ( !bnode_ptr->get_bnodeinst()->GetOldInst(((char *)oldinst)+((ACGenericAttr *)bnode_ptr)->get_inst_off()) )           
                                                     SDBCERR
  if ( iselarea && identity_pos != AUTO )
  {
    SetIdentity();
    memcpy(((char *)oldinst)+identity_pos,iselarea+identity_pos,sizeof(EB_Number));
  }
RECOVER
  if ( oldinst && isel_init)
    struct_def->CopyInstance((char *)oldinst,struct_def,isel_init,REPL_GUID,UNDEF);  // 30.3.00
//  memcpy(oldinst,isel_init,GetInstLength());
  oldinst = NULL;
ENDSEQ
  return((char *)oldinst);
}

/******************************************************************************/
/**
\brief  GetSID - 


\return sid - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSID"

int16 isel :: GetSID (EB_Number entnr )
{
  acb           tempacb(entnr,0);

  ob_handle->GetLocalACObject()->GetUsedLength(&tempacb);
  
  return (   tempacb.NewEntry() 
           ? AUTO 
           : tempacb.get_acbieh().get_iehsid() );



}

/******************************************************************************/
/**
\brief  GetStructAccess - 


\return struct_access - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructAccess"

StructAccess *isel :: GetStructAccess ( )
{

  return(struct_access);

}

/******************************************************************************/
/**
\brief  GetVersion - 


\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 isel :: GetVersion ( )
{

  return (exd_area ? exd_area->get_version() : CUR_VERSION);

}

/******************************************************************************/
/**
\brief  IsInWork - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInWork"

logical isel :: IsInWork ( )
{

  return(this && exd_area ? exd_area->IsInWork() : NO);

}

/******************************************************************************/
/**
\brief  IsNewInstance - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNewInstance"

logical isel :: IsNewInstance ( )
{
  logical                 cond = NO;
BEGINSEQ
  if ( !exd_area )                                   ERROR

  cond = exd_area->get_exdacb()->NewEntry();
RECOVER

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical isel :: IsPositioned ( )
{

  return( stscusr2() || exd_area ? YES : NO);

}

/******************************************************************************/
/**
\brief  IsReserved - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReserved"

int8 isel :: IsReserved ( )
{
  logical                 cond = YES;
  if ( stscwpt(2) )
    cond = 2;                        // reserved by this
  else if ( exd_area && exd_area->stscwpt() ) // not reserveed or reserved by other user, Check LockInternal fehlt
    cond = 1;                        // reserved by other
  else
    cond = 0;                        // not reserved

  return(cond);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical isel :: Lock ( )
{
  logical  term = NO;
BEGINSEQ
  if ( stsclck() || !exd_area )                       LEAVESEQ

  if ( exd_area->Lock() )                             ERROR

  stsslck();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MoveInstance - 


\return term - Termination code

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveInstance"

logical isel :: MoveInstance (inti *intiptr )
{
  isel                   *iselptr = (isel *)intiptr;
  logical                 term = NO;
  SetInstance(iselptr->get_exd_area());
  
  mb_number      = iselptr->get_mb_number();
  cluster_number = iselptr->get_cluster_number();
  version        = iselptr->get_version();

  binti::MoveInstance(intiptr);

  Setup();
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveGUID - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveGUID"

logical isel :: RemoveGUID ( )
{
  int32               pos;
  guid              *_guid;
  LACObject         *sys_object;
  LNode             *guid_node;
  binti             *base_binti;
  char               type[ID_SIZE];
  logical            term = NO;
BEGINSEQ
  if ( ob_handle->get_access_mode() == PI_Read )     SDBERR(347)
  if ( (pos = struct_def->GetGUIDPosition()) == AUTO )   
                                                     ERROR
  _guid = (guid *)(iselarea + pos);
  if ( !_guid->GetSID() )                            LEAVESEQ
    
  if ( !(base_binti = GetBaseBinti(gvtxstb(type,"__OBJECT",sizeof(type)),NO)) )
                                                     SDBERR(99)
  
  if ( !(sys_object = ob_handle->GetLocalACObject()->ReserveGlobalObject()) )
                                                     ERROR
  guid_node = (LNode *)sys_object->get_guid_pi().get_nodeptr();
  
  term = guid_node->DeleteID(base_binti,NULL,GetID()); 
  ob_handle->GetLocalACObject()->ReleaseGlobalObject();
  if ( term )                                        SDBERR(99)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reserve - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical isel :: Reserve ( )
{

BEGINSEQ
  if ( !exd_area || stscwpt() )                         LEAVESEQ
  if ( (context && context->IsReadOnly()) || exd_area->Reserve(NO) )
    stsswpt(1);
  else 
    stsswpt(2);
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void isel :: Reset ( )
{

BEGINSEQ
  if ( stsclck() )
    Unlock();

  if ( exd_area && exd_area->get_exd_buffer() )
  {
//    if ( flush )   (war mal ein parameter, muß jetzt anders kommen, da Funktion virtuell) 
//      exd_area->FlushCluster();

    if ( stscwpt() >= 2 )
      if ( exd_area->Reset() )                     ERROR

    EntryHandle::ResetEntry();
  }
  cluster_number = 0;
  binti::Reset();
  stssusr3();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetReferences - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetReferences"

logical isel :: ResetReferences ( )
{
  logical   term = NO;
BEGINSEQ
  binti::ResetReferences();
  
  if ( stscsav() && exd_area )
    if ( PutInstance(iselarea,field_def->fmcbityp == T_MEMO ? field_def->fmcbsize+1 : UNDEF,
                     YES,NO) )                         ERROR
  stsrsav();
  stsrmod();
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ResetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical isel :: ResetWProtect ( )
{
  logical     term = NO;
BEGINSEQ
  if ( !exd_area || exd_area->ResetWProtect() )      ERROR

  Reserve();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical isel :: Save (logical switchopt, logical overwrite, logical refresh_opt )
{
  nodelist  cursor(node_base);
  logical   term    = NO;  
  logical   siw;
  bnode    *bnode_ptr;
  exd      *exdptr;
BEGINSEQ
  if ( stscusr2() )                                  LEAVESEQ
    
  if ( exd_area && ( stscmod() || stscsav() ) )
    if ( StructureEvents(DBP_Store) )                ERROR
  
  if ( binti::Save(switchopt,overwrite,refresh_opt) ) ERROR
    
  siw = SetInWork(YES);
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
    if ( (exdptr = bnode_ptr->get_bnodeinst()->GetEXD()) &&
         !bnode_ptr->get_nodeinst()->SetInWork(YES)      )
    {
      term = bnode_ptr->SaveNode(switchopt,overwrite);
      exdptr->SetInWork(NO);
      if ( term )                                    break;
    }
  SetInWork(siw);
  if ( term )                                        ERROR
    
  if ( exd_area )
  {
    if ( stscmod() || stscsav() )
    {
      if ( !GetGUID(YES) )  // auto correction for late GUIDs
        CreateGUID(NULL);
      SetTimeStamp();
      
      if ( PutInstance(iselarea,field_def->fmcbityp == T_MEMO ? field_def->fmcbsize+1 : UNDEF,
                       overwrite,refresh_opt) )      ERROR
      stsrsav();
//    stsrold();     9.5.00, sonst werden referenzen von BaseStructures manchmal doch kopiert
      stsrmod();
      StructureEvents(DBO_Stored);
    }
  }
  
  if ( switchopt )
    ResetReferences();
RECOVER
//GenerateEvent(DBO_NotStored);  kommt später, vielleicht
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  SetClusterNumber - 



\param  clnumb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClusterNumber"

void isel :: SetClusterNumber (EB_Number clnumb )
{

  cluster_number = clnumb;

}

/******************************************************************************/
/**
\brief  SetExtInstType - 



\param  iactyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetExtInstType"

void isel :: SetExtInstType (int8 iactyp )
{

  if ( exd_area )
    exd_area->GetIEH()->set_iehtyp(iactyp);


}

/******************************************************************************/
/**
\brief  SetInWork - 


\return workopt - 

\param  workopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInWork"

logical isel :: SetInWork (logical workopt )
{

  return(this && exd_area ? exd_area->SetInWork(workopt) : NO);

}

/******************************************************************************/
/**
\brief  SetMBNumber - 



\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMBNumber"

void isel :: SetMBNumber (int16 mbnumber )
{

  mb_number = mbnumber;

}

/******************************************************************************/
/**
\brief  SetStructAccess - 



\param  structacc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStructAccess"

void isel :: SetStructAccess (StructAccess *structacc )
{

  struct_access = structacc;

}

/******************************************************************************/
/**
\brief  SetTimeStamp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTimeStamp"

void isel :: SetTimeStamp ( )
{
  int32       pos;
  if ( (pos = struct_def->GetGUIDPosition()) > AUTO )   
    if ( ob_handle->get_update_timestamp() )
      ((__OBJECT *)(iselarea+pos))->SetTimeStamp();    


}

/******************************************************************************/
/**
\brief  SetVersion - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void isel :: SetVersion (uint16 version_nr )
{

  binti::SetVersion(version_nr);
  EntryHandle::SetVersion(version_nr);  




}

/******************************************************************************/
/**
\brief  SetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical isel :: SetWProtect ( )
{
  logical     term = NO;
BEGINSEQ
  if ( !exd_area || exd_area->SetWProtect() )        ERROR

  stsrwpt();
  Reserve();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup - 


-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

void isel :: Setup ( )
{

  if ( !stscusr2() )
  {
    cluster_number = exd_area->get_exdcln();
    mb_number = ob_handle->get_db_handle()->GetLocalDBHandle()->GetMainBase(exd_area->get_exdacb());
  }
  stssfil();
//  stsrini();  wegen folgendem Add noch gebraucht. Muss beim Reset zurückgesetzt werden
  objid = PIFToBig(GetID().get_ebsnum(),struct_access->get_pif());

  binti::Setup();

}

/******************************************************************************/
/**
\brief  i1 - 


\param  clnumb - 
\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

void isel :: Setup (EB_Number clnumb, int16 mbnumber )
{

  cluster_number = clnumb;
  mb_number = mbnumber;
  stssfil();
//  stsrini();  wegen folgendem Add noch gebraucht. Muss beim Reset zurückgesetzt werden


}

/******************************************************************************/
/**
\brief  SetupInst - 


\return term - Termination code

\param  update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInst"

logical isel :: SetupInst (logical update )
{
  nodelist  cursor(node_base);
  bnode    *bnode_ptr;
  logical   ro;
  logical   term   = NO;
BEGINSEQ
  ro = context->IsReadOnly();
  
  cursor.GoTop();
  while ( bnode_ptr = cursor.GetNextBNode() )
  {
    if ( bnode_ptr->SetupNode((logical)NO,NO) )      ERROR
    if ( !bnode_ptr->Get(FIRST_INSTANCE,NO) )    
    {
      SDBCERR 
      if ( ((ACShareBase *)bnode_ptr)->get_noderefp()->GetCount() )
        SDBERR(147)
    }
    if ( !bnode_ptr->get_nodewrit() )
      stsswpt(1);
//     bnode_ptr->Event(DBO_Read); 30.3.01 kommt eigentlich schon im LNode::Get
  }

  Setup();
  binti::SetupInst(update);
  
  if ( ro != context->IsReadOnly() )
    SetupReadOnly();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical isel :: Unlock ( )
{
  logical  term = NO;
BEGINSEQ
  if ( !stsclck() || !exd_area )                      LEAVESEQ

  if ( exd_area->Unlock() )                           ERROR

  stsrlck();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  isel - 


-------------------------------------------------------------------------------
\brief  ISEL_ - 


\param  nodeptr - 
\param  strdefptr - 
\param  instptr - 
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isel"

     isel :: isel (node *nodeptr, DBStructDef *strdefptr, void *instptr, logical crt_opt )
                     : binti(nodeptr,NULL,strdefptr,instptr,crt_opt),
EntryHandle(
        nodeptr ? Lnodeptr->get_object_ref()->GetLocalACObject() : NULL,
        nodeptr ? Lnodeptr->GetMainBase() : 0,0,
        nodeptr ? &Lnodeptr->get_act_handle() : NULL)
{

  if ( nodeptr )
    version = ((ACNode *)nodeptr)->get_version();
  stssusr3();


}

/******************************************************************************/
/**
\brief  ISEL_X - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isel"

     isel :: isel ( )
                     : binti (),
EntryHandle()
{

  stssusr3();

}

/******************************************************************************/
/**
\brief  i02 - 


\param  strdefptr - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "isel"

     isel :: isel (DBStructDef *strdefptr, void *instptr )
                     : binti(NULL,NULL,strdefptr,instptr,NO),
EntryHandle()
{

  struct_def->CreateBaseNodes(this,iselarea);
  stssusr3();

}

/******************************************************************************/
/**
\brief  ~isel - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~isel"

     isel :: ~isel ( )
{

  Close();

}


