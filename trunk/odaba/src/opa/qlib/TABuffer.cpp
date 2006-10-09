/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    TABuffer

\brief    


\date     $Date: 2006/03/12 19:18:13,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TABuffer"

#include  <popa7.h>
#include  <sACExtend.hpp>
#include  <sDBHandle.hpp>
#include  <sDelInstEntry.hpp>
#include  <sDiffListList.hpp>
#include  <sDifferenceList.hpp>
#include  <sError.hpp>
#include  <sInternalTA.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sTABuffer.hpp>
#include  <sacb.hpp>
#include  <seb_RootBase.hpp>
#include  <sexd.hpp>
#include  <sexdBBuffer.hpp>
#include  <sTABuffer.hpp>


/******************************************************************************/
/**
\brief  AddGlobalInstance - 



\param  extnames - Extent name
\param  ebsnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGlobalInstance"

void TABuffer :: AddGlobalInstance (char *extnames, EB_Number ebsnum )
{

  new_global_instances = new DelInstEntry(extnames,ebsnum,new_global_instances);

}

/******************************************************************************/
/**
\brief  AppendDIList - 



\param  di_entry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AppendDIList"

void TABuffer :: AppendDIList (DelInstEntry *di_entry )
{
  DelInstEntry         *last_entry;
  if ( last_entry = di_entry->GetLast() )
  {
    last_entry->set_next(new_global_instances);
    new_global_instances = di_entry;
  }

}

/******************************************************************************/
/**
\brief  Cancel - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical TABuffer :: Cancel ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  low_ta -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical TABuffer :: Check (TABuffer *low_ta )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  CheckEBI - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical TABuffer :: CheckEBI (exd *exdptr )
{

  return(GetEBI(exdptr));

}

/******************************************************************************/
/**
\brief  CheckEntry - 


\return term - Termination code

\param  exdptr -
\param  ta_exd -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEntry"

logical TABuffer :: CheckEntry (exd *exdptr, exd *ta_exd )
{
  logical                 term = NO;
BEGINSEQ
  if ( exdptr->get_shadow_base() != ta_exd->get_shadow_base() )
                                                     ERROR 
  if ( exdptr->get_exdacb()->get_locate_exact() &&
       exdptr->get_exdacb()->get_ws_level() != ta_exd->get_exdacb()->get_ws_level() )
                                                     SDBERR(99)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return wpmode

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

uint8 TABuffer :: CheckWProtect (exd *exdptr )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  ConsolidateDlists - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConsolidateDlists"

logical TABuffer :: ConsolidateDlists ( )
{
  DifferenceList         *ws_dlist = NULL;
  DifferenceList         *dlist_ptr;
  LACObject              *lobhandle;
  int                     indx     = 0;
  logical                 term     = NO;
BEGINSEQ
  if ( !dl_list || !(dlist_ptr = dl_list->Locate(1)) )  
                                                     LEAVESEQ
  lobhandle = dlist_ptr->get_ob_handle();
  if ( !high_TA && lobhandle->HasWorkspace() )
    ws_dlist = new DifferenceList(lobhandle,
                                  lobhandle->get_local_dbhandle()->get_root_base()->get_level());
  
  while ( dlist_ptr = dl_list->Locate(++indx) )
  {
    if ( high_TA || !ws_dlist )
    {
      if ( dlist_ptr->Consolidate() )
        term = YES;
    }
    else   // top TA and WS
    {
      if ( ws_dlist->ListSetup(dlist_ptr)   ||
           ws_dlist->Consolidate(dlist_ptr)    )
        term = YES;
      ws_dlist->Reset();
    }
  }
  delete ws_dlist;

  ReleaseDlists();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical TABuffer :: Delete (exd *exdptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  GetCount - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 TABuffer :: GetCount ( )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetDiffList - 


\return dlist_ptr -

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDiffList"

DifferenceList *TABuffer :: GetDiffList (EB_Number entnr )
{

  return ( dl_list ? dl_list->Locate(entnr) : NULL );

}

/******************************************************************************/
/**
\brief  GetEBI - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

logical TABuffer :: GetEBI (exd *exdptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  GetLength - 


\return longlen -

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 TABuffer :: GetLength (acb *acbptr )
{


  return(0);
}

/******************************************************************************/
/**
\brief  GetTop - 


\return tabuffer -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTop"

TABuffer *TABuffer :: GetTop ( )
{
    TABuffer   *tabuffer = this;
  while ( tabuffer && tabuffer->get_high_TA() )
    tabuffer = tabuffer->get_high_TA();
  return(tabuffer);
}

/******************************************************************************/
/**
\brief  GetUsedLength - 


\return longlen -

\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedLength"

int32 TABuffer :: GetUsedLength (acb *acbptr )
{


  return(0);
}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical TABuffer :: IsEmpty ( )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Locate - 


\return buffer -
-------------------------------------------------------------------------------
\brief i0


\param  entnum -
\param  clnumb -
\param  otyp -
\param  instlen -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *TABuffer :: Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief i1


\param  entnr -
\param  shadow_opt -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *TABuffer :: Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  LocateBuffer - 


\return tabptr -
-------------------------------------------------------------------------------
\brief i0


\param  tanumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateBuffer"

TABuffer *TABuffer :: LocateBuffer (int32 tanumber )
{
  TABuffer   *tabuffer = this;

  while ( tabuffer && tabuffer->get_ta_count() != tanumber )
    tabuffer = tabuffer->get_high_TA();
  return(tabuffer);
}

/******************************************************************************/
/**
\brief i1


\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateBuffer"

TABuffer *TABuffer :: LocateBuffer (exd *exdptr )
{
  TABuffer   *tabuffer = this;
  EB_Number   entnr    = exdptr->get_exdebsn();
BEGINSEQ
  if ( exdptr->get_ta_count() )
    if ( tabuffer = LocateBuffer(exdptr->get_ta_count()) )
                                                     LEAVESEQ
  
  while ( tabuffer && tabuffer->LocateEntry(entnr,exdptr->get_shadow_base(),exdptr->get_reqversion()) )
    tabuffer = tabuffer->get_high_TA();
  
  exdptr->set_ta_count(tabuffer ? tabuffer->get_ta_count() : 0);

ENDSEQ
  return(tabuffer);
}

/******************************************************************************/
/**
\brief  LocateEntry - 


\return term - Termination code

\param  entnr -
\param  shadow_opt -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateEntry"

logical TABuffer :: LocateEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  ProvideDiffList - 


\return dlist_ptr -
-------------------------------------------------------------------------------
\brief i0


\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDiffList"

DifferenceList *TABuffer :: ProvideDiffList (DifferenceList *dlist_ptr )
{
  EB_Number           entnr = dlist_ptr->GetEBINumber();
  DifferenceList     *dlistptr;
BEGINSEQ
  if ( !dl_list )
    dl_list = new DiffListList(ob_handle,this);
  
  if ( dlistptr = dl_list->Locate(entnr) )           LEAVESEQ

  if ( high_TA )
    if ( !(dlist_ptr = high_TA->ProvideDiffList(dlist_ptr)) )
                                                     ERROR
  
  dlistptr = new DifferenceList(dlist_ptr);          SDBCERR
  dl_list->Add(dlistptr);
RECOVER
  dlistptr = NULL;
ENDSEQ
  return(dlistptr);
}

/******************************************************************************/
/**
\brief i01


\param  db_index -
\param  entnr -
\param  shared_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDiffList"

DifferenceList *TABuffer :: ProvideDiffList (DBIndex *db_index, EB_Number entnr, logical shared_opt )
{
  DifferenceList     *dlist_ptr = NULL;
BEGINSEQ
  if ( !dl_list )
    dl_list = new DiffListList(ob_handle,this);
  
  if ( dlist_ptr = dl_list->Locate(entnr) )          LEAVESEQ

  if ( high_TA )
    if ( !(dlist_ptr = high_TA->ProvideDiffList(db_index,entnr,shared_opt)) )
                                                     ERROR
  
  dlist_ptr = new DifferenceList(dlist_ptr,ob_handle,db_index,entnr);          
                                                     SDBCERR
  dlist_ptr->set_shared_ref(shared_opt);
  if ( this == ob_handle->get_internal_ta() )
    dlist_ptr->set_ws_number(-2);               // dlist for internal TA
  else
    dlist_ptr->set_ws_number(-3);               // dlist for application TA
  
  dl_list->Add(dlist_ptr);
RECOVER
  dlist_ptr = NULL;
ENDSEQ
  return(dlist_ptr);
}

/******************************************************************************/
/**
\brief  Read - 


\return term - Termination code

\param  exdptr -
\param  w_instlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical TABuffer :: Read (exd *exdptr, int32 w_instlen )
{
  logical     term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseDlists

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseDlists"

logical TABuffer :: ReleaseDlists ( )
{
  DifferenceList         *dlist_ptr;
  int                     indx     = 0;
  logical                 term = NO;
  if ( dl_list )
  {
    while ( dlist_ptr = dl_list->Locate(++indx) )
      dlist_ptr->UnlockEntries();
    
    dl_list->Clear();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseEntry - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

logical TABuffer :: ReleaseEntry (exd *exdptr )
{
  exd            *exdarea = exdptr;
  DLL(PCSHandle) *pcs_hdl;
  logical         pif;
  logical         reserved;
  logical         term    = NO;
  if ( !exdptr->stscnof() )
    if ( !(exdarea = ob_handle->GetEXD(exdptr)) )
      exdarea = exdptr;
    
// hier werden z.Z. noch keinne Collection-Events für Copy- und Top-Nodes erzeugt,
// da diese mit geborgten Referenzen arbeiten und nicht registriert sind
  if ( exdptr->get_ta_count() ) // Save (und nicht Cancel)
    ob_handle->AddEvent( exdptr->get_exdacb(), exdptr->stscdel() ? SE_Delete : SE_Update );

  if ( exdarea->stscnof() )
  {
    exdarea->UnlockInternal();
    exdarea->set_ta_count(0);
    exdarea->stsrnof();
    if ( exdarea != exdptr )
    {
      exdarea->set_ta_count(exdptr->get_ta_count());
//      if ( !exdptr->get_ta_count() )
      
      *exdarea->get_exdacb() = exdptr->get_exdacb();
/* war früher statt acb = acb, 2.11.2004
      pcs_hdl = exdarea->get_exdacb()->get_active_handles().get_conn_handle();
      pif = exdarea->IsPIF();
      reserved = exdarea->get_exdacb()->get_reserved();
      memcpy(exdarea->get_exdacb(),exdptr->get_exdacb(),sizeof(acb)-sizeof(ieh));
      exdarea->get_exdacb()->set_reserved(reserved);
      exdarea->SetPIF(pif);
      exdarea->get_exdacb()->get_active_handles().set_conn_handle(pcs_hdl);
*/
    }
  }
  else
    ob_handle->UnlockInternal(exdarea);

  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseFields - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseFields"

void TABuffer :: ReleaseFields ( )
{

  ob_handle->ReleaseFields();

}

/******************************************************************************/
/**
\brief  ReserveEntry - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEntry"

logical TABuffer :: ReserveEntry (exd *exdptr )
{
  int        tacount = exdptr->get_ta_count();
  logical    term = NO;
BEGINSEQ
  if ( exdptr->get_exdacb()->stscold() )             SDBERR(179)
  
  SetupEntry(exdptr);
  
//  if ( tacount )                                   LEAVESEQ
       
  if ( exdptr->LockInternal(YES) )                   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetDIList - 


\return term - Termination code

\param  term - Termination code
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetDIList"

logical TABuffer :: ResetDIList (logical term )
{
  ACExtend        *extent;
  LACObject       *sys_object;
  DelInstEntry    *di_entry = new_global_instances;
BEGINSEQ
  if ( term == NO )
  {
    if ( high_TA )
      high_TA->AppendDIList(new_global_instances);
    else
      delete new_global_instances;
    new_global_instances = NULL;
  }
  else
  {
    if ( !(sys_object = ob_handle->ReserveGlobalObject()) )
                                                     SDBERR(99)
    while ( di_entry )
    {
      if ( extent = sys_object->GetACExtend(di_entry->get_extent_name()) )
        extent->DeleteGlobal(di_entry->get_entnr());
      di_entry = di_entry->get_next();
    }
    delete new_global_instances;
    new_global_instances = NULL;
    
    ob_handle->ReleaseGlobalObject();
  }

RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  ResetEntry - 


\return term - Termination code

\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetEntry"

logical TABuffer :: ResetEntry (exd *exdarea )
{
  exd       *exdptr = exdarea;
  logical    term = NO;
BEGINSEQ
  if ( exdptr->stscnof() || (exdptr = ob_handle->GetEXD(exdarea)) )
  {
    exdptr->set_ta_count(0);
    exdptr->stssold();
    if ( exdptr->get_use_count() )
    {
      exdptr->stsrdel();                  // 8.6.98, damit auch die gelöschten Entries wieder eingelesen werden
      exdptr->Read(AUTO);
      if ( !exdptr->get_ta_count() )
        ReleaseEntry(exdarea);
      LEAVESEQ
    }
//    else if ( ta_level == 1 )            // 17.6.03, um anzuzeigen, dass exd letzte Transaktion verlassen hat
//      exdptr->stsrnof();                 // 21.10.04 wieder raus, ReleaseEntry sollte vollst. laufen
  }
  exdarea->set_ta_count(0);
  if ( !high_TA || !high_TA->LocateBuffer(exdarea) )
    ReleaseEntry(exdarea);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetError - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetError"

void TABuffer :: ResetError ( )
{

  ta_error = NO;

}

/******************************************************************************/
/**
\brief  RestoreError - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreError"

void TABuffer :: RestoreError ( )
{
  Error      *err;
BEGINSEQ
  if ( !last_error || !last_error->CheckError() )  LEAVESEQ
    
  if ( last_error->get_meta_error() == CONTEXT_ERROR )
  {
    CTXError() = *last_error;
    SDBError().SetError(CONTEXT_ERROR,last_error->objid,last_error->modid);
  }
  else 
    SDBError() = *last_error;

  last_error->ResetError();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical TABuffer :: Save ( )
{
  logical    term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetError - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetError"

void TABuffer :: SetError ( )
{

  ta_error = YES;

}

/******************************************************************************/
/**
\brief  SetLastError - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastError"

void TABuffer :: SetLastError ( )
{
  Error      *err;
  if ( !last_error )
    last_error = new Error();
    
  if ( (err = &CTXError()) && err->CheckError() )
    *last_error = *err; 
  else if ( (err = &SDBError()) && err->CheckError() )
    *last_error = *err; 
  else
    last_error->ResetError();


}

/******************************************************************************/
/**
\brief  SetupEntry - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupEntry"

logical TABuffer :: SetupEntry (exd *exdptr )
{

  exdptr->set_ta_count(ta_count);
  exdptr->stssnof();
  return(NO);
}

/******************************************************************************/
/**
\brief  Start - 


\return term - Termination code

\param  highTABuf -
\param  tanumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical TABuffer :: Start (TABuffer *highTABuf, int32 tanumber )
{

  ta_level    = highTABuf ? highTABuf->get_ta_level()+1 : 1;
  high_TA  = ta_level > 1 ? highTABuf : NULL;  // kleine autokorrektur, da manchmal irgendwo ein TA hängenbleibt. Kann später wieder raus
  ta_count = tanumber;
  return(NO);
}

/******************************************************************************/
/**
\brief  Stop - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

logical TABuffer :: Stop ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  TABuffer - 



\param  lobhandle -
\param  highTABuf -
\param  tanumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TABuffer"

                        TABuffer :: TABuffer (LACObject *lobhandle, TABuffer *highTABuf, int32 tanumber )
                     :   ob_handle(lobhandle),
  high_TA(highTABuf),
  ta_level(highTABuf ? highTABuf->get_ta_level()+1 : 1),
  ta_count(tanumber),
  ta_error(NO),
  dl_list(NULL),
  new_global_instances(NULL),
  last_error(NULL)

{



}

/******************************************************************************/
/**
\brief  UpdateEntry - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateEntry"

logical TABuffer :: UpdateEntry (exd *exdptr )
{
  exd            *exdarea = exdptr;
  DLL(PCSHandle) *pcs_hdl;
  logical         pif;
  logical         term = NO;
  if ( !exdptr->stscnof()                    &&    // Pool oder RB-TA-EXD
       (exdarea = ob_handle->GetEXD(exdptr))    )  // und in Structure-Buffer
  {
    exdarea->set_ta_count(exdptr->get_ta_count());
    *exdarea->get_exdacb() = exdptr->get_exdacb(); // 2.11.2004
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Write - 


\return term - Termination code

\param  exdptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical TABuffer :: Write (exd *exdptr )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ~TABuffer - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TABuffer"

                        TABuffer :: ~TABuffer ( )
{

  delete dl_list;
  dl_list = NULL;

  delete last_error;
  last_error = NULL;

}


