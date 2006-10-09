/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    refs

\brief    


\date     $Date: 2006/06/26 13:31:19,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "refs"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sDiffListEntry.hpp>
#include  <sDifferenceList.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <iNetConversion.h>
#include  <sRefAccess.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <sref.hpp>
#include  <srefs.hpp>
#include  <srefs.hpp>


/******************************************************************************/
/**
\brief  DLGetIndex - 


\return lindx0 - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  dlist_ptr - 
\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLGetIndex"

int32 refs :: DLGetIndex (DifferenceList *dlist_ptr, char *skey, EB_Number ebsnum, logical exact )
{
  logical                 pif = ob_handle->IsPIF();
  DiffListEntry          *dl_entry;
  logical                 dl_found = NO;
BEGINSEQ
  if ( !refrex || !dlist_ptr )
  {
    if ( (ws_curri = GetIndex(skey,ebsnum,exact)) == AUTO )
                                                     ERROR 
    ws_entnr = GetID(ws_curri);                      
    LEAVESEQ
  }
  
  if ( (ws_curri = GetIndex(skey,ebsnum,YES)) != AUTO )
  {
    if ( dl_entry = dlist_ptr->GetEntry(skey,YES) )
      if ( !dl_entry->get_del_ebi().IsEmpty(pif) &&
           dl_entry->get_add_ebi().IsEmpty(pif) && exact )  
                                                     ERROR
    ws_curri += dlist_ptr->Difference(skey,YES);
  }
  else
  {
    SDBCERR
    dl_found = ((dl_entry = dlist_ptr->GetEntry(skey,YES)) &&
                !dl_entry->get_add_ebi().IsEmpty(pif)) ? YES : NO;     
    if ( !dl_found && exact )                        ERROR
    
    if ( (ws_curri = GetIndex(skey,ebsnum,NO)) == AUTO )
    {
      SDBCERR
      ws_curri = GetCount();
    }
    ws_curri += dlist_ptr->Difference(skey,YES) - dl_found; 
  }
  
  ws_entnr = dl_entry        ? dl_entry->get_add_ebi() :
             refcuri != AUTO ? GetID(refcuri)          : 0;

  if ( !ebsnum.IsEmpty(pif) && ws_entnr != ebsnum )      SDBERR(99)
RECOVER
  ws_curri = AUTO;
  ws_entnr = 0;
ENDSEQ
  return(ws_curri);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLGetIndex"

int32 refs :: DLGetIndex (EB_Number ebsnum )
{
  char                    keyarea[MAX_KEYLEN];
  DiffListEntry          *dl_entry;
  int32                   lindx0 = AUTO;
BEGINSEQ
  lindx0 = GetIndex(ebsnum);
  if ( lindx0 != AUTO )
  {
    GetKey(lindx0,keyarea);
    lindx0 = WSGetIndex(keyarea,0,YES);
  } 
  else
  {
    RefreshDiffList(YES); 
    SetupSumList(NULL,NULL);
    
    while ( dl_entry = sum_list->GetEntry(++lindx0) )
      if ( dl_entry->get_add_ebi() == ebsnum )
        break;
    if ( !dl_entry )                                 ERROR
    lindx0 = WSGetIndex(dl_entry->GetKey(),0,YES);
  }

RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);
}

/******************************************************************************/
/**
\brief  DLGetKey - 


\return skey - 

\param  lindx0 - 
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLGetKey"

char *refs :: DLGetKey (int32 lindx0, char *keyptr )
{
  DiffListEntry          *dl_entry;
  int32                   curpos = AUTO;
  char                    lastkey[MAX_KEYLEN];
  int                     keylen;
  int32                   ref_curpos;
  int32                   ws_curpos  = AUTO;
  int32                   ws_lastpos = AUTO;
  int32                   diff_indx;
  int                     direction  = UNDEF;
  char                   *low_key;
  char                   *high_key;
  char                   *skey = NULL;
BEGINSEQ
  RefreshDiffList(YES);
  
  if ( lindx0 == AUTO ) 
    lindx0 = ws_curri;
  if ( lindx0 == AUTO )                              ERROR 
  
  keylen = refsakcb->get_key_def()->GetKeyLength();
  if ( !(skey = GetKey(ref_curpos = lindx0,keyptr)) )
    skey = GetKey(ref_curpos = (GetCount()-1),keyptr);
    
  if ( (ws_curpos = WSGetIndex(skey,0,YES)) == AUTO )
  {
    ref_curpos = AUTO;
    while ( skey = GetKey(++ref_curpos,keyptr) )
      if ( (ws_curpos = WSGetIndex(skey,0,YES)) != AUTO )
        break;
  }
      
  if ( skey )  
  {
    direction = ws_curpos > lindx0 ? BACKWARD : FOREWARD;
    while ( ws_curpos != lindx0 )
    {
      memcpy(lastkey,skey,keylen);
      ws_lastpos = ws_curpos;
      
      skey = NULL;
      while ( (ref_curpos += direction) >= 0 && (skey = GetKey(ref_curpos,keyptr)) )
        if ( (ws_curpos = WSGetIndex(skey,0,YES)) != AUTO )
          break;
      
      if ( !skey || ws_curpos == AUTO )
        break;
      
      ws_curpos = WSGetIndex(skey,0,YES);
      if ( (ws_curpos > lindx0 ? BACKWARD : FOREWARD) != direction )
        break;
    }
  }
  
  if ( ws_curpos == lindx0 )                          LEAVESEQ
  ws_curri = lindx0;
  ws_entnr = GetID(ref_curpos);

  low_key   = direction == FOREWARD         ? lastkey           : 
              direction == BACKWARD         ? skey              : NULL;  
  high_key  = direction == FOREWARD         ? skey              : 
              direction == BACKWARD         ? lastkey           : NULL;  
  diff_indx = direction == FOREWARD         ? lindx0-ws_lastpos : 
              direction == BACKWARD && skey ? lindx0-ws_curpos  : lindx0 + 1;  
  
  SetupSumList(low_key,high_key);
  if ( !(dl_entry = sum_list->GetPlusDiffEntry(low_key,diff_indx)) )
                                                     ERROR
  skey     = dl_entry->GetKey();
  ws_entnr = dl_entry->get_add_ebi();
  if ( keyptr )
    skey = (char *)memcpy(keyptr,skey,keylen);  
 
  

RECOVER
  ws_curri  = AUTO;
  ws_entnr  = 0;
  skey      = NULL;
ENDSEQ
  PIFToIdentity(skey);
  return(skey);
}

/******************************************************************************/
/**
\brief  DeleteDiffListReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteDiffListReference"

logical refs :: DeleteDiffListReference ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !refrex || refrex->IsEmpty(ob_handle->get_pif()) )
                                                     LEAVESEQ
  RefreshDiffList(YES);
  
  ob_handle->get_local_dbhandle()->ActivateShadowBase();
  SetupShadowRef();
  shadow_ref->DeleteReference();
  ob_handle->get_local_dbhandle()->DeactivateShadowBase();
// besser wäre statt dessen ein direktes DeleteReference (mit hochholen in den Workspace und write_shaddow). 
// das problem ist nur, dass der EXD ggf. von shadow-exd nach write-shadow-exd geändert werden muss. 
// DeleteReference();

  if ( diff_list )
    diff_list->DeleteReference();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetIdent - 


\return ebsnum - 

\param  skey - 
\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdent"

EB_Number refs :: GetIdent (char *skey, EB_Number ebsnum )
{
  int32  lindx0;
  logical   extlock = stsclck();

BEGINSEQ
  if ( Lock() )                                       ERROR

  if ( (lindx0 = GetIndex(skey,ebsnum)) == AUTO )     ERROR
  ebsnum = GetID(lindx0);

RECOVER

ENDSEQ
  Unlock(extlock);
  return(ebsnum);

}

/******************************************************************************/
/**
\brief  GetModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 refs :: GetModCount ( )
{
  int16      modcount = UNDEF;
  if ( !exd_area )
    Refresh();
  
  modcount = mod_count;
  if ( exd_area && 
       (mod_count != exd_area->get_mod_count() ||
        exd_area->IsModified() == YES )           )
    modcount++;
  return(modcount);
}

/******************************************************************************/
/**
\brief  InitKeyValue - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  keyarea - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitKeyValue"

logical refs :: InitKeyValue (inti *intiptr, void *oldinst, char *keyarea, EB_Number entnr )
{
  EB_Number               ebsnum;
  kcb                    *kcbptr = refsakcb->get_key_def();
  char                   *skey;
  char                   *instptr;
  void                   *koldinst = NULL;
  logical                 term     = NO;
  if ( !intiptr )
    instptr = (char *)oldinst; 
  else
  {
    instptr = GetKeyInstance(intiptr);
    if ( oldinst )
      koldinst = GetOldKeyInstance(intiptr,oldinst);
  }
  
  if ( IsIdentityOrder() )
  {
    skey = (char *)&entnr;
    if ( !entnr.IsEmpty(struct_access->get_pif()) )
    {
      ebsnum = entnr.FromPIF(struct_access->get_pif());
      memcpy(keyarea,&ebsnum,sizeof(ebsnum));
    }
  }
  else 
    skey = kcbptr->GetKey(koldinst ? (char *)koldinst : instptr,keyarea);

  return(term);
}

/******************************************************************************/
/**
\brief  InitSumList - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSumList"

logical refs :: InitSumList ( )
{
  DifferenceList          *dlist_ptr = diff_list;
  logical                  term = NO;
  if ( !sum_list )
  {  
    if ( !dlist_ptr && !ob_handle->HasWorkspace() )
      dlist_ptr = ob_handle->GetTADiffList(*refrex,YES);
    
    sum_list = new DifferenceList(dlist_ptr);
  }
  sum_list->mvlsrt->srtres();
  return(term);
}

/******************************************************************************/
/**
\brief  RefreshDiffList - 


\return term - Termination code

\param  refresh_all - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshDiffList"

logical refs :: RefreshDiffList (logical refresh_all )
{
  LDBHandle          *dbhandle = ob_handle->get_local_dbhandle();
  uint8               wslevel;
  int32                wsnumber;
  logical             term = NO;
BEGINSEQ
  wslevel  = dbhandle->GetWorkspaceLevel();
  wsnumber = dbhandle->GetWorkspaceNumber(wslevel);
  if ( diff_list && diff_list->get_ws_number() != wsnumber )
  {
    delete diff_list;
    diff_list = NULL;
  }
  
  if ( !diff_list )
  {
    if ( !HasWorkspace() )                           LEAVESEQ
    if ( !(diff_list = new DifferenceList(this,wslevel)) )
                                                     SDBERR(95)
                                                     SDBCERR
    refresh_all = YES;
  }
  
  if ( diff_list && refresh_all )
    diff_list->RefreshAll();
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

logical refs :: Reset ( )
{

  EntryHandle::ResetEntry();
  reset_ws_curri();

  return(ref::Reset());

}

/******************************************************************************/
/**
\brief  SRAddExt - 


\return lindx0 - 

\param  entnr - 
\param  skey - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRAddExt"

int32 refs :: SRAddExt (EB_Number entnr, char *skey, int32 lindx0 )
{

BEGINSEQ
  if ( !refrex )                                     ERROR 
  if ( refrex->IsEmpty(ob_handle->get_pif()) )
  {
    lindx0 = AddExt(entnr,skey,lindx0);              LEAVESEQ
  }

  if ( SRUpdateDiff(skey,entnr,'+') )                ERROR
  lindx0 = SRGetIndex(skey,entnr,YES);
RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);
}

/******************************************************************************/
/**
\brief  SRAddID - 


\return term - Termination code

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRAddID"

logical refs :: SRAddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  char                    keyarea[MAX_KEYLEN];
  logical                 term = NO;
BEGINSEQ
  if ( !refrex )                                     ERROR
  if ( refrex->IsEmpty(ob_handle->get_pif()) )
  {
    term = AddID(intiptr,entnr,lindx0);              LEAVESEQ
  }

  InitKeyValue(intiptr,NULL,keyarea,entnr);    
  
  if ( SRUpdateDiff(keyarea,entnr,'+') )             ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SRCheckNewID - 


\return term - Termination code

\param  instptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRCheckNewID"

logical refs :: SRCheckNewID (void *instptr, EB_Number entnr )
{
  kcb                    *kcbptr;
  char                    keyarea[MAX_KEYLEN]; 
  logical                 term = NO;
BEGINSEQ
  if ( !refrex )                                     ERROR 

  InitKeyValue(NULL,instptr,keyarea,entnr);
  
  if ( (kcbptr = refsakcb->get_key_def()) && refsakcb->get_no_empty() )
    if ( kcbptr->scbsmcb->IsEmpty(keyarea) )         SDBERR(209)

  if ( SRGetIndex(keyarea,entnr,YES) != AUTO )
  {
    SetKeyErrorVariables(keyarea);                   SDBERR(64)
  }           

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SRDelKey - 


\return term - Termination code

\param  skey - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRDelKey"

logical refs :: SRDelKey (char *skey, EB_Number entnr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !refrex )                                     ERROR
  if ( refrex->IsEmpty(ob_handle->get_pif()) )
  {
    term = DelKey(skey,entnr);                       LEAVESEQ
  }

  if ( SRUpdateDiff(skey,entnr,'-') )                ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SRDeleteID - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRDeleteID"

logical refs :: SRDeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  EB_Number               ebsnum;
  char                    keyarea[MAX_KEYLEN]; 
  logical                 term     = NO;
BEGINSEQ
  if ( !refrex )                                     ERROR
  if ( refrex->IsEmpty(ob_handle->get_pif()) )
  {
    term = DeleteID(intiptr,oldinst,entnr);          LEAVESEQ
  }

  InitKeyValue(intiptr,oldinst,keyarea,entnr);    
  
  if ( SRUpdateDiff(keyarea,entnr,'-') )             ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SRGetCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRGetCount"

int32 refs :: SRGetCount ( )
{
  DifferenceList          *dlist_ptr;
  int32                    count = 0;
BEGINSEQ
  count = GetCount();  
  if ( !refrex )                                     LEAVESEQ
  if ( count == ERIC )                               ERROR
  
  if ( dlist_ptr = ob_handle->GetTADiffList(*refrex,YES) )
    count += dlist_ptr->Difference(NULL,YES);
RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  SRGetID - 


\return entnr - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRGetID"

EB_Number refs :: SRGetID (int32 lindx0 )
{
  char        keyarea[MAX_KEYLEN];
  if ( lindx0 != ws_curri || ws_entnr.IsEmpty(ob_handle->get_pif()) )
    SRGetKey(lindx0,keyarea);


  return(ws_entnr);
}

/******************************************************************************/
/**
\brief  SRGetIndex - 


\return lindx0 - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRGetIndex"

int32 refs :: SRGetIndex (EB_Number ebsnum )
{
  DifferenceList          *dlist_ptr;
  int32                    lindx0 = AUTO;
  lindx0 = GetIndex(ebsnum);
  
  dlist_ptr = ob_handle->GetTADiffList(*refrex,YES);
  if ( refrex && dlist_ptr )
    lindx0 = DLGetIndex(ebsnum);

  return(lindx0);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRGetIndex"

int32 refs :: SRGetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  DifferenceList          *dlist_ptr;
  dlist_ptr = ob_handle->GetTADiffList(*refrex,YES);
  DLGetIndex(dlist_ptr,skey,ebsnum,exact);

  return(ws_curri);
}

/******************************************************************************/
/**
\brief  SRGetKey - 


\return skey - 

\param  lindx0 - 
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRGetKey"

char *refs :: SRGetKey (int32 lindx0, char *keyptr )
{
  DifferenceList          *dlist_ptr;
  char                   *skey = NULL;
BEGINSEQ
  dlist_ptr = ob_handle->GetTADiffList(*refrex,YES);
  if ( !refrex || !dlist_ptr )
  {
    if ( !(skey = GetKey(lindx0,keyptr)) )         ERROR
    ws_curri = lindx0;
    ws_entnr = GetID(lindx0);                    
    PIFToIdentity(skey);
  }
  else
    skey = DLGetKey(lindx0,keyptr);   

RECOVER
  ws_curri  = AUTO;
  ws_entnr  = 0;
  skey      = NULL;
ENDSEQ
  return(skey);
}

/******************************************************************************/
/**
\brief  SRSetAutoIdent - 


\return cond_setting - 

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRSetAutoIdent"

char refs :: SRSetAutoIdent (void *instptr )
{
  DifferenceList  *dlist_ptr;
  kcb             *kcbptr = refsakcb->get_key_def(); 
  char             keyarea[MAX_KEYLEN];
  int32            count;
  uint32           autoident;
  uint32           newident;
  char             cond_setting = NO;
BEGINSEQ
  autoident = *(int32 *)kcbptr->kcbkgt((char *)instptr,keyarea);
  dlist_ptr = ob_handle->GetTADiffList(*refrex,YES);
  
  if ( !refrex || !dlist_ptr )
  {
    cond_setting = SetAutoIdent(instptr);                  
    LEAVESEQ
  }
  
  if ( (count = SRGetCount()) < 0 )              ERROR
  if ( count > 0 )
  {
    if ( !WSGetKey(count-1,(char *)&newident) )  ERROR
    if ( newident > autoident ) 
      autoident = newident;
  }      

  autoident++;
  kcbptr->kcbkpt((char *)instptr,(char *)&autoident);
  cond_setting = YES;

RECOVER
  cond_setting = ERIC;
ENDSEQ
  return(cond_setting);
}

/******************************************************************************/
/**
\brief  SRUpdateDiff - 


\return term - Termination code

\param  skey - 
\param  entnr - 
\param  op_char - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SRUpdateDiff"

logical refs :: SRUpdateDiff (char *skey, EB_Number entnr, char op_char )
{
  DifferenceList         *dlist_ptr;
  logical                 term = NO;
BEGINSEQ
  if ( Refresh() )                                   ERROR
  
  if ( !(dlist_ptr = ob_handle->ProvideTADiffList(refsakcb,*refrex,shared_ref)) )
                                                     ERROR    
  if ( dlist_ptr->AddIndexOperation(skey,entnr,op_char) )
                                                     ERROR
  ws_curri = SRGetIndex(skey,entnr,YES);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupShadowRef - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupShadowRef"

logical refs :: SetupShadowRef ( )
{
  logical                 term = NO;
  if ( !shadow_ref )
    shadow_ref = refcrt(ob_handle,refrex,UNDEF,refsakcb,refglob,NULL);
  else
    shadow_ref->Setup(refrex,UNDEF);

  shadow_ref->Refresh();


  return(term);
}

/******************************************************************************/
/**
\brief  SetupSumList - 


\return term - Termination code

\param  w_skey1 - 
\param  w_skey2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupSumList"

logical refs :: SetupSumList (char *w_skey1, char *w_skey2 )
{
  DifferenceList         *ta_diff_list;
  logical                 term = NO;
BEGINSEQ
  if ( !refrex )                                     LEAVESEQ
  InitSumList();

  if ( diff_list )
    sum_list->SumList(diff_list,w_skey1,w_skey2);
  
  if ( ta_diff_list = ob_handle->GetTADiffList(*refrex,YES) )
    sum_list->SumList(ta_diff_list,w_skey1,w_skey2);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SharedCollInTA - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SharedCollInTA"

logical refs :: SharedCollInTA ( )
{

  return ( shared_ref && ob_handle->IsExternalTA() );
//       ( (object_ref->IsExternalTA() && object_ref->get_db_handle()->get_net_option()) ||
//         object_ref->get_db_handle()->GetLocalDBHandle()->get_root_base()->IsWorkspace() ) )



}

/******************************************************************************/
/**
\brief  WSAddExt - 


\return lindx0 - 

\param  entnr - 
\param  skey - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSAddExt"

int32 refs :: WSAddExt (EB_Number entnr, char *skey, int32 lindx0 )
{
  DifferenceList         *dlist_ptr;
  EB_Number               ebsnum;
  logical                 locked = NO;
  logical                 term   = NO;
BEGINSEQ
  if ( !ebsnum.IsEmpty(struct_access->get_pif()) && IsIdentityOrder() )
  {
    ebsnum = entnr.FromPIF(struct_access->get_pif());
    skey = (char *)&ebsnum;
  }
  
  if ( SharedCollInTA() )
    return( SRAddExt(entnr,skey,lindx0) );

  if ( !HasWorkspace() )
    return ( AddExt(entnr,skey,lindx0) );

  if ( !refrex )                                     ERROR
  if ( Lock() )                                      ERROR
  locked = YES;
  if ( RefreshDiffList(YES) )                        ERROR
    
  // sollte vielleicht nach WSCheckNewID
  if ( diff_list->CheckOperation(skey,entnr) )       ERROR
  
  ob_handle->get_local_dbhandle()->ActivateShadowBase();
  SetupShadowRef();
  if ( !(term = (shadow_ref->AddExt(entnr,skey,lindx0) == AUTO)) )
    shadow_ref->Save();
  ob_handle->get_local_dbhandle()->DeactivateShadowBase();
  
  if ( term )                                        ERROR
    
  if ( !(dlist_ptr = ob_handle->ProvideTADiffList(diff_list)) )
    dlist_ptr = diff_list;
  
  dlist_ptr->AddIndexOperation(skey,entnr,'+');

  ws_curri = WSGetIndex(skey,entnr,YES);
RECOVER
  ws_curri = AUTO;
  ws_entnr = 0;
ENDSEQ
  if ( locked )
    Unlock(NO);
  return(ws_curri);
}

/******************************************************************************/
/**
\brief  WSAddID - 


\return term - Termination code

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSAddID"

logical refs :: WSAddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  DifferenceList         *dlist_ptr;
  char                    keyarea[MAX_KEYLEN];
  logical                 locked = NO;
  logical                 term = NO;
BEGINSEQ
  if ( SharedCollInTA() )
    return( SRAddID(intiptr,entnr,lindx0) );

  if ( !HasWorkspace() )
    return ( AddID(intiptr,entnr,lindx0) );

  if ( !refrex )                                     ERROR
  if ( Lock() )                                      ERROR
  locked = YES;
  if ( RefreshDiffList(YES) )                        ERROR
    
  InitKeyValue(intiptr,NULL,keyarea,entnr);    
    
  if ( diff_list->CheckOperation(keyarea,entnr) )    ERROR
  
  ob_handle->get_local_dbhandle()->ActivateShadowBase();
  SetupShadowRef();
  if ( !(term = shadow_ref->AddID(intiptr,entnr,lindx0)) )
    shadow_ref->Save();
  ob_handle->get_local_dbhandle()->DeactivateShadowBase();
  if ( term )                                        ERROR
    
  if ( !(dlist_ptr = ob_handle->ProvideTADiffList(diff_list)) )
    dlist_ptr = diff_list;
  
  dlist_ptr->AddIndexOperation(keyarea,entnr,'+');

  ws_curri = WSGetIndex(keyarea,entnr,YES);
RECOVER
  term = YES;
ENDSEQ
  if ( locked )
    Unlock(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  WSCheckNewID - 


\return term - Termination code

\param  instptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSCheckNewID"

logical refs :: WSCheckNewID (void *instptr, EB_Number entnr )
{
  logical                 term = NO;
BEGINSEQ
  if ( SharedCollInTA() )
    return( SRCheckNewID(instptr,entnr) );

  if ( !HasWorkspace() )
    return ( CheckNewID(instptr,entnr) );
    
  if ( !refrex )                                     ERROR
  if ( RefreshDiffList(YES) )                        ERROR 
  
  ob_handle->get_local_dbhandle()->ActivateShadowBase();
  SetupShadowRef();
  term = shadow_ref->CheckNewID(instptr,entnr);
  ob_handle->get_local_dbhandle()->DeactivateShadowBase();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WSDelKey - 


\return term - Termination code

\param  skey - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSDelKey"

logical refs :: WSDelKey (char *skey, EB_Number entnr )
{
  char                    identity[4];
  DifferenceList         *dlist_ptr;
  logical                 locked = NO;
  logical                 term = NO;
BEGINSEQ
  skey = IdentityToPIF(skey,identity);
  
  if ( SharedCollInTA() )
    return( SRDelKey(skey,entnr) );
  
  if ( !HasWorkspace() )
    return ( DelKey(skey,entnr) );

  if ( !refrex )                                     ERROR
  if ( Lock() )                                      ERROR
  locked = YES;
  if ( RefreshDiffList(YES) )                        ERROR
  
  if ( diff_list->CheckOperation(skey,entnr) )       ERROR
  
  ob_handle->get_local_dbhandle()->ActivateShadowBase();
  SetupShadowRef();
  if ( !(term = shadow_ref->DelKey(skey,entnr)) )
    shadow_ref->Save();
  ob_handle->get_local_dbhandle()->DeactivateShadowBase();
  
  if ( term )                                        ERROR
    
  if ( !(dlist_ptr = ob_handle->ProvideTADiffList(diff_list)) )
    dlist_ptr = diff_list;
  
  dlist_ptr->AddIndexOperation(skey,entnr,'-');
RECOVER
  term = YES;
ENDSEQ
  if ( locked )
    Unlock(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  WSDeleteID - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSDeleteID"

logical refs :: WSDeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  DifferenceList         *dlist_ptr;
  char                    keyarea[MAX_KEYLEN];
  logical                 locked   = NO;
  logical                 term     = NO;
BEGINSEQ
  if ( SharedCollInTA() )
    return( SRDeleteID(intiptr,oldinst,entnr) );
  
  if ( !HasWorkspace() )
    return ( DeleteID(intiptr,oldinst,entnr) );

  if ( !refrex )                                     ERROR
  if ( Lock() )                                      ERROR
  locked = YES;
  if ( RefreshDiffList(YES) )                        ERROR
  
  InitKeyValue(intiptr,oldinst,keyarea,entnr);    
  
  if ( diff_list->CheckOperation(keyarea,entnr) )    ERROR
  
  ob_handle->get_local_dbhandle()->ActivateShadowBase();
  SetupShadowRef();
  if ( !(term = shadow_ref->DeleteID(intiptr,oldinst,entnr)) )
    shadow_ref->Save();
  ob_handle->get_local_dbhandle()->DeactivateShadowBase();
  if ( term )                                        ERROR
    
  if ( !(dlist_ptr = ob_handle->ProvideTADiffList(diff_list)) )
    dlist_ptr = diff_list;
  
  dlist_ptr->AddIndexOperation(keyarea,entnr,'-');
RECOVER
  term = YES;
ENDSEQ
  if ( locked )
    Unlock(NO);
  return(term);
}

/******************************************************************************/
/**
\brief  WSGetCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetCount"

int32 refs :: WSGetCount ( )
{
  DifferenceList         *start_diff_list;
  int32                   count = 0;
BEGINSEQ
  if ( SharedCollInTA() )
    return( SRGetCount() );
  
  if ( !HasWorkspace() )
    return ( GetCount() );

  if ( !refrex )                                     LEAVESEQ
  RefreshDiffList(YES);
  
  if ( !diff_list || diff_list->get_ws_level() == 1 )
    return ( GetCount() );
  
  if ( !(start_diff_list = ob_handle->GetTADiffList(*refrex,YES)) )
    start_diff_list = diff_list;
  
  if ( (count = GetCount()) != ERIC )
    count += start_diff_list->Difference(NULL,YES);
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  WSGetID - 


\return entnr - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetID"

EB_Number refs :: WSGetID (int32 lindx0 )
{
  char        keyarea[MAX_KEYLEN];

  if ( SharedCollInTA() )
    return( SRGetID(lindx0) );
  
  if ( !HasWorkspace() )
    return ( GetID(lindx0) );

  if ( lindx0 != ws_curri || ws_entnr.IsEmpty(ob_handle->get_pif()) )
    WSGetKey(lindx0,keyarea);

  return(ws_entnr);
}

/******************************************************************************/
/**
\brief  WSGetIndex - 


\return lindx0 - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetIndex"

int32 refs :: WSGetIndex (EB_Number ebsnum )
{

  if ( SharedCollInTA() )
    return( SRGetIndex(ebsnum) );
  
  if ( !HasWorkspace() )
    return ( GetIndex(ebsnum) );

  return( DLGetIndex(ebsnum) );



}

/******************************************************************************/
/**
\brief  i01 - 


\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetIndex"

int32 refs :: WSGetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  DifferenceList         *start_diff_list;
  logical                 pif = NO;
  DiffListEntry          *dl_entry;
  EB_Number               entnr;
  char                    identity[4];
  logical                 dl_found = NO;
  if ( struct_access && struct_access->get_pif() )
    pif = YES;
    
  if ( !ebsnum.IsEmpty(pif) && IsIdentityOrder() )
  {
    entnr = ebsnum.FromPIF(pif);
    skey = (char *)&entnr;
  }
    
//  if ( pif )
//    skey = IdentityToPIF(skey,identity);
  
  if ( SharedCollInTA() )
    return( SRGetIndex(skey,ebsnum,exact) );
  
  if ( !HasWorkspace() )
    return ( GetIndex(skey,ebsnum,exact) );

  RefreshDiffList(YES);
  if ( !(start_diff_list = ob_handle->GetTADiffList(*refrex,YES)) )
    start_diff_list = diff_list;
  
  DLGetIndex(start_diff_list,skey,ebsnum,exact);
  return(ws_curri);
}

/******************************************************************************/
/**
\brief  WSGetKey - 


\return skey - 

\param  lindx0 - 
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetKey"

char *refs :: WSGetKey (int32 lindx0, char *keyptr )
{
  DiffListEntry          *dl_entry;
  int32                   curpos = AUTO;
  char                    lastkey[MAX_KEYLEN];
  int                     keylen;
  int32                   ref_curpos;
  int32                   ws_curpos  = AUTO;
  int32                   ws_lastpos = AUTO;
  int32                   diff_indx;
  int                     direction  = UNDEF;
  char                   *low_key;
  char                   *high_key;
  char                   *skey = NULL;
BEGINSEQ
  if ( SharedCollInTA() )
    return( SRGetKey(lindx0,keyptr) );
  
  if ( !HasWorkspace() )
  {
    skey = GetKey(lindx0,keyptr);                 
    LEAVESEQ
  }
  
  RefreshDiffList(YES);
  
  if ( !refrex || !diff_list || diff_list->get_ws_level() == 1 )
  {
    if ( !(skey = GetKey(lindx0,keyptr)) )         ERROR
    ws_curri = lindx0;
    ws_entnr = GetID(lindx0);                    
    PIFToIdentity(skey);
  }
  else
    skey = DLGetKey(lindx0,keyptr);
RECOVER
  ws_curri  = AUTO;
  ws_entnr  = 0;
  skey      = NULL;
ENDSEQ
  return(skey);
}

/******************************************************************************/
/**
\brief  WSSetAutoIdent - 


\return cond_setting - 

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSSetAutoIdent"

char refs :: WSSetAutoIdent (void *instptr )
{
  kcb             *kcbptr = refsakcb->get_key_def(); 
  char             keyarea[MAX_KEYLEN];
  DifferenceList  *ta_diff_list;
  int32            count;
  uint32           autoident;
  uint32           newident;
  logical          locked       = NO;
  char             cond_setting = NO;
BEGINSEQ
  if ( !kcbptr->scbsmcb->smcbsts.stscold() )         LEAVESEQ

  if ( autoident = *(int32 *)kcbptr->kcbkgt((char *)instptr,keyarea) )
                                                     LEAVESEQ
  if ( SharedCollInTA() )
    return( SRSetAutoIdent(instptr) );
  
  if ( !HasWorkspace() )
    return ( SetAutoIdent(instptr) );
  
  if ( !refrex )                                     ERROR
  if ( Lock() )                                      ERROR
  locked = YES;
  if ( RefreshDiffList(YES) )                        ERROR
    
  if ( !diff_list || diff_list->get_ws_level() == 1 )
  {
    cond_setting = SetAutoIdent(instptr);                  
    LEAVESEQ
  }
  ob_handle->get_local_dbhandle()->ActivateShadowBase();
  SetupShadowRef();
  if ( (count = shadow_ref->GetCount()) < 0 )
    cond_setting = ERIC;
  else if ( count > 0 )
    if ( !shadow_ref->GetKey(count-1,(char *)&autoident) )
      cond_setting = ERIC;
  ob_handle->get_local_dbhandle()->DeactivateShadowBase();
  if ( cond_setting == ERIC )                        ERROR
    
  SDBRESET
  if ( (count = diff_list->get_ws0_list()->GetCount()) < 0 )
  {
    SDBCERR
    count = 0;
  }
    
  if ( count > 0 )
  {
    if ( !diff_list->get_ws0_list()->GetKey(count-1,(char *)&newident) )
                                                     ERROR
    if ( newident > autoident ) 
      autoident = newident;
  }      
    
  if ( ta_diff_list = ob_handle->GetTADiffList(*refrex,YES) )
  {
    if ( (count = WSGetCount()) < 0 )                ERROR
    if ( count > 0 )
    {
      if ( !WSGetKey(count-1,(char *)&newident) )    ERROR
      if ( newident > autoident ) 
        autoident = newident;
    }      
  }

  autoident++;
  kcbptr->kcbkpt((char *)instptr,(char *)&autoident);
  cond_setting = YES;
RECOVER
  cond_setting = ERIC;
ENDSEQ
  if ( locked )
    Unlock(NO);
  return(cond_setting);
}

/******************************************************************************/
/**
\brief  refs - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  otyp - 
\param  akcbptr - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refs"

     refs :: refs (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, char otyp, DBIndex *akcbptr, logical globind )
                     : ref(lobhandle,extref,clnumb,akcbptr,globind),
  refsotyp(otyp),
  temp_rex(0),
  shared_ref(NO),
  diff_list(NULL),
  sum_list(NULL),
  ws_curri(AUTO),
  ws_entnr(),
  shadow_ref(NULL)
{
  logical      net_opt = NO;
  if ( lobhandle )
    net_opt = lobhandle->get_db_handle()->get_net_option();  
  
  if ( globind && net_opt )
    stsssav();

  if ( net_opt && refsakcb && refsakcb->get_field_def() &&
       refsakcb->get_field_def()->get_shared() )
    shared_ref = YES;



}

/******************************************************************************/
/**
\brief  refsdel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refsdel"

logical refs :: refsdel ( )
{


  Unlock(NO);
  Refresh();

  if ( exd_area )
    exd_area->ResetEBI();
  
  Reset();
  return(NO);

}

/******************************************************************************/
/**
\brief  refskck - 


\return term - Termination code

\param  newkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refskck"

logical refs :: refskck (char *newkey )
{
  char      oldkey[MAX_KEYLEN];
  logical   term = NO;

BEGINSEQ
  if ( !refsakcb->get_unique() )                        LEAVESEQ
  
  if ( GetKey(AUTO,oldkey) )
    if ( !refsakcb->get_key_def()->kcbkcp(newkey,oldkey) )     
                                                        LEAVESEQ
  if ( GetIndex(newkey,0) != AUTO )                     SDBERR(65)
  GetIdent(oldkey,0);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  refsren - 


\return term - Termination code

\param  oldkey - 
\param  newkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refsren"

logical refs :: refsren (char *oldkey, char *newkey )
{
  EB_Number ebsnum;
  logical   extlock = stsclck();
  logical   term    = NO;

BEGINSEQ
  if ( Lock() )                                         ERROR

  ebsnum = GetID(GetIndex(oldkey,0));

  SDBRESET
  
  if ( AddExt(ebsnum,newkey,AUTO) == AUTO )             ERROR 
  if ( DelKey(oldkey,ebsnum) )                          ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  reset_ws_curri - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "reset_ws_curri"

void refs :: reset_ws_curri ( )
{

  ws_curri = AUTO;
  ws_entnr = 0;

}

/******************************************************************************/
/**
\brief  set_shared_ref - 



\param  shared_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_shared_ref"

void refs :: set_shared_ref (logical shared_opt )
{

  shared_ref = shared_opt;

}

/******************************************************************************/
/**
\brief  ~refs - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~refs"

     refs :: ~refs ( )
{

  refs::Reset();

}


