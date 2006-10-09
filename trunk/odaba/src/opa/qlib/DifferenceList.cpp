/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DifferenceList

\brief    


\date     $Date: 2006/03/12 19:17:23,54 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DifferenceList"

#include  <popa7.h>
#include  <idbd.h>
#include  <sDBFieldDef.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sDiffListEntry.hpp>
#include  <sDifferenceList.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sRefAccess.hpp>
#include  <sacb.hpp>
#include  <seb_RootBase.hpp>
#include  <sexd.hpp>
#include  <sexdBuffer.hpp>
#include  <sref.hpp>
#include  <sDifferenceList.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i00


\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical DifferenceList :: Add (DifferenceList *dlist_ptr )
{
  DiffListEntry     *dl_entry;
  logical            extlock = stsclck();
  int32               indx0   = 0;
  logical            term    = NO;
BEGINSEQ
  if ( ws_level && Lock() )                          ERROR
  if ( dlist_ptr->GetCount() <= 0 )                  LEAVESEQ
    
  if ( ProvideWS0List() )                            ERROR
    
  while ( dl_entry = dlist_ptr->GetEntry(indx0++) )
    if ( UpdateEntry(dl_entry,ws_number) )
      term = YES;

  if ( ws0_list )
    if ( ws0_list->Save() )                          ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( ws_level && Unlock(extlock) )  
    term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  dlist_ptr -
\param  skey1 -
\param  skey2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical DifferenceList :: Add (DifferenceList *dlist_ptr, char *skey1, char *skey2 )
{
  logical            term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  AddEntry - 


\return dl_entry -
-------------------------------------------------------------------------------
\brief i00


\param  skey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEntry"

DiffListEntry *DifferenceList :: AddEntry (char *skey )
{

  work_entry->Init(ws_number,skey,mvlsrt->srtkln());
  
  return ( AddEntry(work_entry,ws_number) );


}

/******************************************************************************/
/**
\brief i01


\param  dl_entry -
\param  wsnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEntry"

DiffListEntry *DifferenceList :: AddEntry (DiffListEntry *dl_entry, int32 wsnumber )
{
  int32             lindx;
BEGINSEQ
  if ( wsnumber == AUTO )
    wsnumber = ws_number;
    
  if ( !mvlchk(AUTO) )                               ERROR
    
  if ( !(lindx = mvlsrt->srtkad(dl_entry)) )         ERROR
    
  dl_entry = GetEntry(lindx-1);
  dl_entry->set_ws_number(wsnumber);
  Modify();

RECOVER
  dl_entry = NULL;
ENDSEQ
  return(dl_entry);
}

/******************************************************************************/
/**
\brief  AddIndexOperation - 


\return term - Termination code

\param  skey -
\param  entnr -
\param  operation -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddIndexOperation"

logical DifferenceList :: AddIndexOperation (char *skey, EB_Number entnr, int16 operation )
{
  logical            term = NO;
BEGINSEQ
  work_entry->Init(ws_number,skey,mvlsrt->srtkln());
  switch ( operation )
  {
    case '+' : work_entry->get_add_ebi() = entnr;
               break;
    case '-' : work_entry->get_del_ebi() = entnr;
               break;
    default  : SDBERR(99)
  }
  
  if ( UpdateEntry(work_entry,ws_number) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckOperation - 


\return term - Termination code

\param  skey -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckOperation"

logical DifferenceList :: CheckOperation (char *skey, EB_Number entnr )
{
  DifferenceList    *dlist = this;
  DiffListEntry     *dl_entry;
  logical            term = NO;
BEGINSEQ
  if ( !(dl_entry = ws0_list->GetEntry(skey)) )      LEAVESEQ
    
  while ( dlist && dlist->get_ws_level() != 1 )
  {
    if ( dlist->get_ws_number() == dl_entry->get_ws_number() )
                                                     LEAVESEQ
    dlist = dlist->get_prev_list();
  }
  
  reference->SetKeyErrorVariables(skey);
  SDBERR(340)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Consolidate - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Consolidate"

logical DifferenceList :: Consolidate ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( ws_level != 2 )
  {
    if ( prev_list )     
    {
      if ( prev_list->Consolidate(this) )            ERROR
    }
    else if ( !ob_handle->HasWorkspace() ) // top TA and no WS
      Store(this);
  }
  else
    if ( ws0_list->Consolidate(this) )               ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Consolidate"

logical DifferenceList :: Consolidate (DifferenceList *dlist_ptr )
{

  return ( ws_level == 1 ? Store(dlist_ptr) : Add(dlist_ptr) );


}

/******************************************************************************/
/**
\brief  Deinitialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void DifferenceList :: Deinitialize ( )
{

  delete work_entry;
  work_entry = NULL;
  
  mvlrmv();

}

/******************************************************************************/
/**
\brief  DeleteEntry - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEntry"

logical DifferenceList :: DeleteEntry ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( refcuri == AUTO )                             ERROR
  if ( mvlsrt->srtidl(refcuri+1) )                   ERROR

  Modify();
RECOVER
  term = YES;
ENDSEQ
  refcuri = AUTO;
  return(term);
}

/******************************************************************************/
/**
\brief  Difference - 


\return diff -

\param  skey -
\param  recursiv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Difference"

int32 DifferenceList :: Difference (char *skey, logical recursiv )
{
  DiffListEntry        *dl_entry;
  int32                  endpos;
  int32                  lindx0 = 0;
  int32                  diff = 0;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  Refresh();
  
  if ( !skey || !(endpos = mvlsrt->srtbsr(skey)) )
    endpos = mvlsrt->srtcnt();
  else
    if ( mvlsrt->stscerr() )             // key not found
      endpos--;
  
  while ( lindx0 < endpos )
  {
    if ( !(dl_entry = GetEntry(lindx0++)) )          SDBERR(99)
    diff += dl_entry->IndexDifference();
  }
  
  if ( recursiv && prev_list )
    diff += prev_list->Difference(skey,recursiv);
RECOVER

ENDSEQ
  return(diff);
}

/******************************************************************************/
/**
\brief  DifferenceList - 


-------------------------------------------------------------------------------
\brief i0


\param  refptr -
\param  wslevel -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DifferenceList"

                        DifferenceList :: DifferenceList (ref *refptr, uint8 wslevel )
                     : mvl(refptr->get_ob_handle(),refptr->get_refrex(),
    0,IDB_MVLF,UNDEF,UNDEF,refptr->get_refsakcb(),YES),
  prev_list(NULL),
  ws0_list(NULL),
  ws_level(wslevel),
ws_number(refptr->get_ob_handle()->get_local_dbhandle()->GetWorkspaceNumber(wslevel)),
  reference(refptr),
  work_entry(NULL),
  local_exd(NO),
  local_index_def(NO),
  ref_orgtype(UNDEF),
  field_def(NULL)
{

BEGINSEQ
  if ( Initialize() )                                ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i01


\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DifferenceList"

                        DifferenceList :: DifferenceList (DifferenceList *dlist_ptr )
                     : mvl(dlist_ptr->get_ob_handle(),NULL,
  0,IDB_MVLF,UNDEF,UNDEF,dlist_ptr->get_refsakcb(),YES),    prev_list(dlist_ptr),
  ws0_list(NULL),
  ws_level(0),
  ws_number(AUTO),
  reference(NULL),
  work_entry(NULL),
  local_exd(YES),
  local_index_def(NO),
  ref_orgtype(UNDEF),
  field_def(NULL)
{

BEGINSEQ
  if ( Initialize() )                                ERROR
      
  if ( !(exd_area = new exd(ob_handle,NULL,UNDEF,CUR_VERSION)) )
                                                     SDBERR(95)
  exd_area->set_exdebsn(dlist_ptr->GetEBINumber());

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i02


\param  lobhandle -
\param  wslevel -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DifferenceList"

                        DifferenceList :: DifferenceList (LACObject *lobhandle, uint8 wslevel )
                     : mvl(lobhandle,NULL,0,IDB_MVLF,UNDEF,UNDEF,NULL,YES),
  prev_list(NULL),
  ws0_list(NULL),
  ws_level(wslevel),
ws_number(lobhandle->get_local_dbhandle()->GetWorkspaceNumber(wslevel)),
  reference(NULL),
  work_entry(NULL),
  local_exd(NO),
  local_index_def(NO),
  ref_orgtype(UNDEF),
  field_def(NULL)
{




}

/******************************************************************************/
/**
\brief i03


\param  lobhandle -
\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DifferenceList"

                        DifferenceList :: DifferenceList (LACObject *lobhandle, exd *exdptr )
                     : mvl(lobhandle,NULL,0,IDB_MVLF,UNDEF,UNDEF,NULL,YES),
  prev_list(NULL),
  ws0_list(NULL),
  ws_level(exdptr->get_exdacb()->get_ws_level()),
ws_number(lobhandle->get_local_dbhandle()->GetWorkspaceNumber(exdptr->get_exdacb()->get_ws_level())),
  reference(NULL),
  work_entry(NULL),
  local_exd(NO),
  local_index_def(YES),
  ref_orgtype(UNDEF),
  field_def(NULL)
{
  int16         keynum;
  int8          max_aligned = 1;
  acb          *acbptr = exdptr->get_exdacb();
  kcb          *kcbptr;
  DBStructDef  *struct_def;
BEGINSEQ
  exd_area = exdptr;
//  if ( !(exd_area = new exd(lobhandle,acbptr)) )      SDBERR(95)
      
  keynum = acbptr->get_acbieh().get_iehsid();
  
  if ( !(struct_def = GetStructDef(GetEBINumber())) )ERROR
  if ( !(kcbptr = struct_def->GetKCB(keynum)) )      SDBERR(99)
  
  if ( !(refsakcb = new DBIndex(kcbptr,acbptr->get_acbieh().get_iehver() ? NO : YES,
                                NO,YES,UNDEF,UNDEF,SET_undefined,NO,ref_orgtype)) )    
                                                     SDBERR(95)
  
  field_def = new DBFieldDef("__DiffListField",struct_def->smcbname,SYS_NSID,RL_reference,UNDEF,UNDEF,UNDEF,
                             struct_def,"",NO,NULL,NULL,refsakcb);
  field_def->fmcbesu(struct_def,0,1,max_aligned);

  Initialize();
  SetupTable();
  
  if ( ws_level > 2 )
    ProvidePrevList(NO);
  else
    ProvideWS0List();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i04


\param  dlist_ptr -
\param  lobhandle -
\param  db_index -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DifferenceList"

                        DifferenceList :: DifferenceList (DifferenceList *dlist_ptr, LACObject *lobhandle, DBIndex *db_index, EB_Number entnr )
                     : mvl(lobhandle,NULL,0,IDB_MVLF,UNDEF,UNDEF,db_index,
    YES),
  prev_list(dlist_ptr),
  ws0_list(NULL),
  ws_level(0),
  ws_number(AUTO),
  reference(NULL),
  work_entry(NULL),
  local_exd(YES),
  local_index_def(NO),
  ref_orgtype(UNDEF),
  field_def(NULL)
{

BEGINSEQ
  if ( Initialize() )                                ERROR
      
  if ( !(exd_area = new exd(ob_handle,NULL,UNDEF,CUR_VERSION)) )
                                                     SDBERR(95)
  exd_area->set_exdebsn(entnr);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  FromPIF - 


\return term - Termination code

\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

logical DifferenceList :: FromPIF (exd *exdarea )
{
  DiffListEntry          *diffl_ent;    
  int32                    lindx = 1;
  int32                    count;
  logical                 term = NO;
  if ( !exdarea )
    exdarea = exd_area;

  if ( exdarea->IsPIF() )
  {
    count = mvlsrt->srtcnt();
    mvlsrt->srtsett(exdarea->GetInstance());
    mvlsrt->srtsete(exdarea->GetLength());
    while ( diffl_ent = (DiffListEntry *)mvlsrt->srtigt(lindx++) )
      diffl_ent->FromPIF();
    exdarea->ResetPIF();
    mvlsrt->srtsett(exd_area->GetInstance());
    mvlsrt->srtsetc(count);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  GetEBINumber - 


\return entnr -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBINumber"

EB_Number DifferenceList :: GetEBINumber ( )
{
  EB_Number        entnr;
BEGINSEQ
  if ( exd_area ) 
    entnr = exd_area->get_exdebsn();

  if ( !reference || !reference->get_refrex() )      LEAVESEQ
    
  if ( entnr.IsEmpty(ob_handle->get_pif()) && 
       !reference->get_refrex()->IsEmpty(ob_handle->get_pif()) )
  {
    exd_area->get_exdacb()->set_ebsnum(*reference->get_refrex());
    if ( exd_area->get_exd_buffer() )
      exd_area->get_exd_buffer()->Setup(entnr,*reference->get_refrex());
    entnr = exd_area->get_exdebsn();
  }
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetEntry - 


\return dl_entry -
-------------------------------------------------------------------------------
\brief i00


\param  skey -
\param  recursiv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

DiffListEntry *DifferenceList :: GetEntry (char *skey, logical recursiv )
{
  DiffListEntry   *dl_entry = NULL;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  Refresh();
  
  if ( !(dl_entry = GetEntry(mvlsrt->srtssr(skey)-1)) && recursiv && prev_list )
    dl_entry = prev_list->GetEntry(skey,recursiv);
ENDSEQ
  return(dl_entry);
}

/******************************************************************************/
/**
\brief i01


\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

DiffListEntry *DifferenceList :: GetEntry (int32 lindx0 )
{
  DiffListEntry   *dl_entry = NULL;

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  Refresh();
  
  if ( !(dl_entry = (DiffListEntry *)mvlsrt->srtigt(lindx0+1)) )
                                                     ERROR
  refcuri = lindx0;
RECOVER
  refcuri = AUTO;
ENDSEQ
  return(dl_entry);
}

/******************************************************************************/
/**
\brief  GetKey - 


\return keyptr -

\param  lindx0 -
\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *DifferenceList :: GetKey (int32 lindx0, char *keyptr )
{
  DiffListEntry   *dl_entry;

BEGINSEQ
  if ( !keyptr )                                   SDBERR(99)
  
  if ( lindx0 == AUTO )
  {
    if ( refcuri == AUTO )                         ERROR
    lindx0 = refcuri;
  }
  
  if ( !(dl_entry = GetEntry(lindx0)) )            ERROR

  memcpy(keyptr,dl_entry->GetKey(),mvlsrt->srtkln());

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  GetPlusDiffEntry - 


\return dl_entry -

\param  skey -
\param  difference -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPlusDiffEntry"

DiffListEntry *DifferenceList :: GetPlusDiffEntry (char *skey, int32 difference )
{
  int32                    indx0;
  DiffListEntry          *dl_entry = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( !skey ) 
    indx0 = 0;
  else
  {
    if ( (indx0 = GetIndex(skey,0,YES)) != AUTO )
      indx0++;
    else if ( (indx0 = GetIndex(skey,0,NO)) == AUTO )
      indx0 = 0;
  }
  
  while ( difference )
  {
    if ( !(dl_entry = GetEntry(indx0++)) )           ERROR
    difference -= dl_entry->IndexDifferencePlus();
  }

RECOVER
  dl_entry = NULL;
ENDSEQ
  return(dl_entry);
}

/******************************************************************************/
/**
\brief  GetStructDef - 


\return struct_def - Pointer to generel structure definition

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructDef"

DBStructDef *DifferenceList :: GetStructDef (EB_Number entnr )
{
  int16         sid = 0;
  DBStructDef  *struct_def = NULL;
  ieh          *iehptr;
BEGINSEQ
  if ( !struct_access )
  {
    if ( entnr.IsEmpty(ob_handle->get_pif()) )       SDBERR(99)
    acb      acbenty(entnr,0);
    if ( !(iehptr = (ieh *)ob_handle->get_local_dbhandle()->get_shadow_rb()->GetEntryHeader(&acbenty)) ) 
                                                     SDBERR(99)
    ref_orgtype = iehptr->get_iehtyp();
  
    if ( !(struct_access = (RefAccess *)ob_handle->GetStructAccess(iehptr->get_iehsid())) )
                                                     SDBERR(99)
  }
  struct_def = struct_access->get_struct_def();

RECOVER

ENDSEQ
  return(struct_def);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical DifferenceList :: Initialize ( )
{
  kcb      *kcbptr = refsakcb->get_key_def();
  int16     klen   = kcbptr ? kcbptr->scbsmcb->GetInstLength(NO) : 0;
  int16     elen   = DIFFLISTENTRY+klen;
  logical   term   = NO;
BEGINSEQ
  if ( mvlcrt(elen,DIFFLISTENTRY+1,kcbptr) )
                                                     ERROR
  if ( !(work_entry = (DiffListEntry *)new char[elen])) SDBERR(95)  
  work_entry->Init(ws_number,NULL,klen);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ListSetup - 


\return term - Termination code

\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListSetup"

logical DifferenceList :: ListSetup (DifferenceList *dlist_ptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( GetEBINumber() == dlist_ptr->GetEBINumber() ) LEAVESEQ

  Reset();
  
  if ( refsakcb != dlist_ptr->refsakcb )
    SetupMVL(dlist_ptr->refsakcb);

  if ( ProvideTable(dlist_ptr->GetEBINumber()) )     ERROR
  Read(YES);  // term kann nicht ausgewertet werden, da YES für noch nicht vorhanden
  SetupTable();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LockEntry - 


\return term - Termination code

\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockEntry"

logical DifferenceList :: LockEntry (char *keyptr )
{
  logical                 term    = NO;
BEGINSEQ
  if ( !shared_ref )                                 LEAVESEQ
    
  if ( ob_handle->LockKey(exd_area->get_exdebsn(),refsakcb,keyptr,GetThreadID()) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvidePrevList - 


\return term - Termination code

\param  recursiv -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvidePrevList"

logical DifferenceList :: ProvidePrevList (logical recursiv )
{
  logical                 term = NO;
BEGINSEQ
  if ( ws_level <= 2 )                               LEAVESEQ
    
  if ( reference )
  {
    if ( prev_list )
      prev_list->Setup(reference->get_refrex(),0,0);
    else
    {
      if ( !(prev_list = new DifferenceList(reference,ws_level-1)) )
                                                     SDBERR(95)
                                                     SDBCERR
    }
    if ( prev_list->Refresh() )                      ERROR
  }
  else
  {
    if ( !prev_list )
    {
      if ( !(prev_list = new DifferenceList(ob_handle,ws_level-1)) )
                                                     SDBERR(95)
                                                     SDBCERR
    }
    if ( prev_list->ListSetup(this) )                ERROR
  }
    
  if ( recursiv )
    if ( prev_list->ProvidePrevList() )              ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideTable - 


\return term - Termination code

\param  ebsnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideTable"

logical DifferenceList :: ProvideTable (EB_Number ebsnum )
{
  logical    term = NO;
BEGINSEQ
  if ( !exd_area )
  {
    mod_count  = 0;
//    if ( ebsnum.IsEmpty(ob_handle->get_pif()) )    LEAVESEQ
      
    if ( !(exd_area = ob_handle->ProvideDiffListEXD(ebsnum,ws_level)) )
                                                     ERROR
    exd_area->GetIEH()->set_iehsid(refsakcb ? refsakcb->GetKeyNum() : 0);
    exd_area->GetIEH()->set_iehver(!refsakcb || !refsakcb->get_unique() ? 1 : 0);

    ReserveReference();
  }
  
  if ( exd_area->get_exdacb()->get_ws_number() != ws_number )
  {
    exd_area->get_exdacb()->ResetACB();
    exd_area->get_exdacb()->set_ws_level(ws_level,ws_number);
    exd_area->SetLength(0);
  }



RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideWS0List - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideWS0List"

logical DifferenceList :: ProvideWS0List ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !ob_handle->HasWorkspace() )                  LEAVESEQ
  
  if ( !ws0_list ) 
  {
    ws0_list = new DifferenceList(ob_handle,1);      SDBCERR
  }
  ws0_list->ListSetup(this);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical DifferenceList :: Refresh ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( ws_number < 0 )                               LEAVESEQ // transactionslisten
  
  if ( exd_area && exd_area->get_exdacb()->get_ws_number() != ws_number )
    ReleaseReference();

  term = mvl::Refresh();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RefreshAll - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshAll"

logical DifferenceList :: RefreshAll ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !reference )                                  LEAVESEQ
    
  Setup(reference->get_refrex(),0,0);
  Refresh();
  ProvidePrevList(YES);
  
  if ( ws_level > 1 )
  {
    if ( ws0_list )
      ws0_list->Setup(reference->get_refrex(),0,0);
    else
    {
      if ( !(ws0_list = new DifferenceList(reference,1)) )
                                                     SDBERR(95)
                                                     SDBCERR
    }
    if ( ws0_list->Refresh() )                       ERROR
  }
  else if ( ws_level == 1 )
    ws0_list = this;

RECOVER
  term = YES;
ENDSEQ
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

logical DifferenceList :: Reset ( )
{
  exd           *save_exd_area = exd_area;
  logical        term = NO;
  Save();
  
  if ( prev_list )
    prev_list->Reset();
    
  if ( ws0_list && ws0_list != this )
    ws0_list->Reset();  
  
  mvl::Reset();

  if ( local_exd )
    exd_area = save_exd_area;

  return(term);
}

/******************************************************************************/
/**
\brief  SetupMVL - 


\return term - Termination code

\param  akcbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupMVL"

logical DifferenceList :: SetupMVL (DBIndex *akcbptr )
{
  logical                 term = NO;
  Deinitialize();
  
  refsakcb = akcbptr;
  ref::Initialize(akcbptr);

  Initialize();
  return(term);
}

/******************************************************************************/
/**
\brief  Store - 


\return term - Termination code

\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical DifferenceList :: Store (DifferenceList *dlist_ptr )
{
  DiffListEntry     *dl_entry;
  ref               *refptr  = NULL;
  EB_Number          entnr   = GetEBINumber();
  db_RootBase       *rb;
  ieh               *iehptr;
  logical            extlock = stsclck();
  int32               indx0   = 0;
  logical            pif     = ob_handle->get_pif();
  logical            term    = NO;
BEGINSEQ
  if ( ws_level && Lock() )                          ERROR
    
  if ( ProvideWS0List() )                            ERROR
  
  if ( entnr.IsEmpty(pif) )                          SDBERR(99)
  if ( !(rb = ob_handle->get_local_dbhandle()->GetRootBase((uint8)0)) )
                                                     SDBERR(99)
  acb      acbenty(entnr,0);
  if ( !(iehptr = (ieh *)rb->Locate(&acbenty,IEH)) ) SDBERR(99)
  if ( !(refptr = ref::refcrt(ob_handle,&entnr,0,refsakcb,NO,NULL)) )
                                                     SDBERR(99)
  refptr->Lock();
  refptr->Refresh();  // hier wird direct von der Rootbase gelesen - ws_level in ACB = 0
  
  while ( dl_entry = dlist_ptr->GetEntry(indx0++) )
  {
    if ( !dl_entry->get_del_ebi().IsEmpty(pif) )
      refptr->DelKey(dl_entry->GetKey(),dl_entry->get_del_ebi());
    if ( !dl_entry->get_add_ebi().IsEmpty(pif) )
      refptr->AddExt(dl_entry->get_add_ebi(),dl_entry->GetKey(),AUTO);
    
    if ( dlist_ptr->get_ws_number() > 0 )
      if ( !StoreEntry(dl_entry) )
        term = YES;
  }

  refptr->Unlock(NO);
  delete refptr;

RECOVER
  term = YES;
ENDSEQ
  if ( ws_level && Unlock(extlock) )  
    term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  StoreEntry - 


\return dl_entry -

\param  dl_entry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreEntry"

DiffListEntry *DifferenceList :: StoreEntry (DiffListEntry *dl_entry )
{
  DiffListEntry          *my_entry;
 int32                    lindx;
BEGINSEQ
  if ( !(my_entry = GetEntry(dl_entry->GetKey())) )  SDBERR(99)
    
  if ( dl_entry->get_ws_number() == my_entry->get_ws_number() )
  {
    if ( DeleteEntry() )                             ERROR
  }
  else
  {
    if ( dl_entry->get_add_ebi() == my_entry->get_add_ebi() )  
      my_entry->get_add_ebi() = 0;
    if ( dl_entry->get_del_ebi() == my_entry->get_del_ebi() )  
      my_entry->get_del_ebi() = 0;
  }
  Modify();

RECOVER
  dl_entry = NULL;
ENDSEQ
  return(dl_entry);
}

/******************************************************************************/
/**
\brief  SumList - 


\return term - Termination code

\param  dlist_ptr -
\param  w_skey1 -
\param  w_skey2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SumList"

logical DifferenceList :: SumList (DifferenceList *dlist_ptr, char *w_skey1, char *w_skey2 )
{
  DiffListEntry          *dl_entry;
  kcb                    *kcbptr = refsakcb->get_key_def();
  int32                    lindx0 = 0;
  logical                 term   = NO;
  if ( dlist_ptr->get_prev_list() )
    SumList(dlist_ptr->get_prev_list(),w_skey1,w_skey2);
    
  while ( dl_entry = dlist_ptr->GetEntry(lindx0++) )
    if ( (!w_skey1 || kcbptr->CompareKeys(w_skey1,dl_entry->GetKey()) <= 0) &&
         (!w_skey2 || kcbptr->CompareKeys(dl_entry->GetKey(),w_skey2) <= 0)    )
      UpdateEntry(dl_entry,AUTO);
  return(term);
}

/******************************************************************************/
/**
\brief  ToPIF - 


\return term - Termination code

\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

logical DifferenceList :: ToPIF (exd *exdarea )
{
  DiffListEntry          *diffl_ent;    
  exd                    *exdptr;
  int32                    lindx = 1;
  int32                    count;
  logical                 term = NO;
  if ( !exdarea )
    exdarea = exd_area;
  
  if ( !exdarea->IsPIF() )
  {
    count = mvlsrt->srtcnt();
    exdptr = exdarea->ProvidePIF();
    mvlsrt->srtsett(exdptr->GetInstance());
    mvlsrt->srtsete(exdptr->GetLength());
    while ( diffl_ent = (DiffListEntry *)mvlsrt->srtigt(lindx++) )
      diffl_ent->ToPIF();
    exdptr->SetPIF();
    mvlsrt->srtsett(exd_area->GetInstance());
    mvlsrt->srtsetc(count);
  }
  else
    exdarea->SetPIF();

  return(term);
}

/******************************************************************************/
/**
\brief  UnlockEntries - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockEntries"

logical DifferenceList :: UnlockEntries ( )
{
  DiffListEntry          *dl_entry;
  int32                   indx0 = 0;
  logical                 term = NO;
  while ( dl_entry = GetEntry(indx0++) )
    UnlockEntry(dl_entry->GetKey());
  return(term);
}

/******************************************************************************/
/**
\brief  UnlockEntry

\return term - Termination code

\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockEntry"

logical DifferenceList :: UnlockEntry (char *keyptr )
{
  logical                 term    = NO;
BEGINSEQ
  if ( !shared_ref )                                 LEAVESEQ
    
  if ( ob_handle->UnlockKey(exd_area->get_exdebsn(),refsakcb,keyptr,GetThreadID()) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateEntry

\return term - Termination code

\param  dl_entry -
\param  wsnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateEntry"

logical DifferenceList :: UpdateEntry (DiffListEntry *dl_entry, int32 wsnumber )
{
  DiffListEntry          *my_entry;
  DiffListEntry          *prev_entry = NULL;
  EB_Number               del_num;
  EB_Number               add_num;
  logical                 del_opt = NO;
  logical                 pif = ob_handle->get_pif();
  logical                 term    = NO;
BEGINSEQ
  if ( !(my_entry = GetEntry(dl_entry->GetKey())) )
  {
    if ( wsnumber != AUTO )       // not a sum-list
      if ( LockEntry(dl_entry->GetKey()) )           ERROR
    if ( !(my_entry = AddEntry(dl_entry,wsnumber)) ) 
    {
      if ( wsnumber != AUTO )     // not a sum-list
        UnlockEntry(dl_entry->GetKey());               
      ERROR
    }
  }
  else
  {
    if ( my_entry->get_add_ebi() == dl_entry->get_del_ebi() )
      my_entry->get_add_ebi() = 0;
    else
      del_num = dl_entry->get_del_ebi();

    if ( my_entry->get_del_ebi() == dl_entry->get_add_ebi() )
      my_entry->get_del_ebi() = 0;
    else
      add_num = dl_entry->get_add_ebi();
      
    if ( !del_num.IsEmpty(pif) )
    {
      if ( del_num != my_entry->get_del_ebi() && 
           !my_entry->get_del_ebi().IsEmpty(pif) )   ERROR
      my_entry->get_del_ebi() = del_num;
    }
    if ( !add_num.IsEmpty(pif) )
    {
      if ( add_num != my_entry->get_add_ebi() && 
           !my_entry->get_add_ebi().IsEmpty(pif) )   ERROR
      my_entry->get_add_ebi() = add_num;
    }
    
    if ( ws_level <= 1 ||
         !(del_opt = (my_entry->get_del_ebi().IsEmpty(pif) && 
           my_entry->get_add_ebi().IsEmpty(pif))) )
    {  
      if ( ws_level == 1 )
        my_entry->set_ws_number(wsnumber);
      Modify();
    }
    else
      if ( DeleteEntry() )                           ERROR
  }

  if ( local_exd || ws_level <= 1 )                  LEAVESEQ
    
  if ( del_opt )
  {
    if ( ProvidePrevList(YES) )                      ERROR
    if ( !prev_list || !(prev_entry = prev_list->GetEntry(dl_entry->GetKey(),YES)) )
    {
      if ( ws0_list->GetEntry(dl_entry->GetKey()) )  
        if ( ws0_list->DeleteEntry() )               ERROR
      LEAVESEQ
    }
  }
  if ( ws0_list->UpdateEntry(dl_entry,prev_entry ? prev_entry->get_ws_number() : ws_number) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateWSNumber - 


\return term - Termination code

\param  dl_entry -
\param  wsnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateWSNumber"

logical DifferenceList :: UpdateWSNumber (DiffListEntry *dl_entry, int32 wsnumber )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  set_ws_number


\param  wsnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ws_number"

void DifferenceList :: set_ws_number (int32 wsnumber )
{

  ws_number = wsnumber;

}

/******************************************************************************/
/**
\brief  ~DifferenceList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DifferenceList"

                        DifferenceList :: ~DifferenceList ( )
{

  if ( reference )
  {
    delete prev_list;
    prev_list = NULL;
  }
  Deinitialize();
  
  if ( local_exd )
  {
    delete exd_area;
    exd_area = NULL;
  }

  delete field_def;
  field_def = NULL;

}


