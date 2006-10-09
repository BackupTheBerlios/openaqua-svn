/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    Workspace

\brief    Workspace
          A  workspace is implemented  as overlay rootbase  on top of a database
          or another workspace.

\date     $Date: 2006/05/31 18:30:10,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Workspace"

#include  <popa7.h>
#include  <idbd.h>
#include  <sDBHandle.hpp>
#include  <sDifferenceList.hpp>
#include  <sEBI.hpp>
#include  <sEB_RBHeader.hpp>
#include  <sLDBHandle.hpp>
#include  <iNetConversion.h>
#include  <sOPAGlobals.hpp>
#include  <sWSList.hpp>
#include  <sacb.hpp>
#include  <seb_RootBase.hpp>
#include  <sexd.hpp>
#include  <ssrt.hpp>
#include  <sWorkspace.hpp>


/******************************************************************************/
/**
\brief  CheckEBI

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical Workspace :: CheckEBI (acb *acbptr )
{
  logical                 term = NO;
  term = ExistEBI(acbptr) 
         ? eb_RootBase::CheckEBI(acbptr)
         : root_base->CheckEBI(acbptr);

  return(term);
}

/******************************************************************************/
/**
\brief  Check_WProtect

\return wptmode - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check_WProtect"

uint8 Workspace :: Check_WProtect (acb *acbptr )
{
  uint8        wptmode = NO;
  wptmode =   ExistEBI(acbptr) 
            ? eb_RootBase::Check_WProtect(acbptr)
            : root_base->Check_WProtect(acbptr);

  return(wptmode);
}

/******************************************************************************/
/**
\brief  Close

\return rootbase - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

db_RootBase *Workspace :: Close ( )
{
  extern OPAGlobals       opa_globals;
  EB_Number               entnr;
  acb                    *acbptr = NULL;
  int32                    instlen;
  db_RootBase            *rootbase = root_base;
  logical                 term = NO;
BEGINSEQ
  if ( is_empty )
  {
    if ( !(entnr = rb_header->get_work_spaces()).IsEmpty() )
    {
      acb     acbenty(entnr,0);
      eb_RootBase::Locate(&acbenty,IEH);
      instlen = acbenty.GetLength();
      acbptr = acb::Create(instlen+sizeof(acb));
      *acbptr = acbenty;
      eb_RootBase::Locate(acbptr,instlen+IEH);
    }

    rb_header->Reset();
    ResetSize(0);
        
    if ( acbptr )
    {
      acbptr->ResetACB();
      acbptr->SetPosition(0);
      eb_RootBase::Create(acbptr);
      eb_RootBase::Update(acbptr,instlen+IEH,AUTO);
      rb_header->get_work_spaces() = entnr;
      acbptr->Remove();
    }
    rb_header->stssmod();
    rb_header->Write();
  }
  
  if ( !this )                                       ERROR

  if ( --use_count <= 0 )                            // last user
  {                         
    opa_globals.ILockGlobal();
    if ( opa_globals.RootBaseShared() )            // shared rootbase
      opa_globals.UnregisterRootBase(this);
    eb_RootBase::Close();
    use_count = 0;
    root_base = NULL;
    opa_globals.IUnlockGlobal();
  }

RECOVER
  rootbase = NULL;
ENDSEQ
  return(rootbase);
}

/******************************************************************************/
/**
\brief  CloseRecursive

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseRecursive"

logical Workspace :: CloseRecursive ( )
{
  db_RootBase            *rootbase;
  logical                 term = NO;
  delete ws_list;
  ws_list = NULL;
  
  if ( root_base )
  {
    if (root_base->IsWorkspace() )
      ((Workspace *)root_base)->CloseRecursive();
    else
      root_base->Close();
    if ( rootbase = Close() )
      rootbase->DeleteRB();
  }
  eb_RootBase::Close();

  return(term);
}

/******************************************************************************/
/**
\brief  Consolidate - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Consolidate"

logical Workspace :: Consolidate ( )
{
  db_RootBase    *rootbase = level > 1 ? root_base : GetRootBase(0);
  exd            *exdarea  = NULL;
  EB_Number       entnr(BigToPIF(1,pif));
  acb            *acbptr;
  logical         term     = NO;
BEGINSEQ
  if ( !(exdarea = new exd(NULL,NULL,1024L * 63,0)) ) 
                                                     SDBERR(95)
  acbptr = exdarea->get_exdacb();
  if ( SaveBuffer() )                                ERROR
    
  while ( !(entnr = GetNextEBNumber(entnr)).IsEmpty() )
  {
    if ( entnr == rb_header->get_work_spaces() )
      continue;
      
    acbptr->ResetACB();
    acbptr->set_ebsnum(entnr);
    
/*  von RootBaseTA, aber dann werden gelöschte Entries neu belebt (CheckEBI liefert YES) ???
    if ( eb_RootBase::CheckEBI(acbptr) )
      if ( Create(acbptr).IsEmpty() ) 
        term = YES;
*/            
    eb_RootBase::CheckEBI(acbptr);
    
    if ( acbptr->stscdel() )
      DeleteWSEntry(acbptr);
    else
    {
      if ( !exdarea->ChangeSize() )                ERROR
      acbptr = exdarea->get_exdacb();
      if ( !eb_RootBase::Locate(acbptr,AUTO) )
        term = YES;
      else
      {
        if ( acbptr->get_acbieh().get_iehtyp() == IDB_MVLF )
          term = ConsolidateDiffList(exdarea);
        else
          term = ConsolidateWSEntry(exdarea);
      }
    }
  }
  SDBCERR
  if ( !term )
    is_empty = YES;
RECOVER
  term = YES;
ENDSEQ
  delete exdarea;
  return(term);
}

/******************************************************************************/
/**
\brief  ConsolidateDiffList

\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConsolidateDiffList"

logical Workspace :: ConsolidateDiffList (exd *exdptr )
{
  logical term    = NO;
BEGINSEQ
  DifferenceList   diff_list(ob_handle,exdptr);      SDBCERR
  
  if ( diff_list.Consolidate() )                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ConsolidateWSEntry

\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConsolidateWSEntry"

logical Workspace :: ConsolidateWSEntry (exd *exdptr )
{
  acb          *acbptr = exdptr->get_exdacb();
  int32          len  = acbptr->get_entry_length();
  uint8         wpt  = acbptr->stscwpt(1) ? YES : NO;
  db_RootBase  *rb   = root_base->get_level() == 1 ? ((Workspace *)root_base)->get_root_base() : root_base;
  logical       term = NO;
BEGINSEQ
  acbptr->ResetACB();
  rb->ProvideWSEntry(acbptr,NO);
  
  if ( wpt )
    acbptr->SetWProtect();
  else
    acbptr->ResetWProtect();
          
  if ( rb->Update(acbptr,len,AUTO) )                 SDBERR(242)
  ClearEBI(acbptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create

\return entnr - 
-------------------------------------------------------------------------------
\brief  i0


\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number Workspace :: Create (acb *acbptr )
{
  EB_Number      entnr;
BEGINSEQ
  if ( root_base->Create(acbptr).IsEmpty() )         ERROR

  if ( level > 1 )
    if ( ProvideWSEntry(acbptr,NO) )                 ERROR
RECOVER

ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  i01


\param  clnumb
\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number Workspace :: Create (EB_Number clnumb, int16 mbnumber, uint16 sbnumber, uint16 version_nr )
{
  EB_Number               entnr = 0;
BEGINSEQ
  if ( (entnr = root_base->Create(clnumb,mbnumber,sbnumber,version_nr)).IsEmpty() )
                                                     ERROR
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  Delete

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical Workspace :: Delete (acb *acbptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( level == 1 )    // WS0
    root_base->Delete(acbptr);
  else
  {
    if ( ProvideWSEntry(acbptr,YES) )                ERROR
    if ( !acbptr->stscdel() )
      if ( eb_RootBase::Delete(acbptr) )              ERROR
    is_empty = NO;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteWSEntry

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteWSEntry"

logical Workspace :: DeleteWSEntry (acb *acbptr )
{
  db_RootBase  *rb;
  logical       term = NO;
BEGINSEQ
  acbptr->ResetACB();
  
  if ( level > 2 )
  {
    if ( root_base->ProvideWSEntry(acbptr,YES) )     SDBERR(316)
    if ( !acbptr->stscdel() )
    {
      acbptr->ResetWProtect();
      if ( eb_RootBase::Delete(acbptr) )              ERROR
    }
  }
  else
  {
    rb = ((Workspace *)root_base)->get_root_base();
    if ( !rb->GetEBI(acbptr) )                       ERROR
    rb->ReleaseWSEntry(acbptr);
    rb->Delete(acbptr);
  }

RECOVER
  term = YES;
ENDSEQ
  ClearEBI(acbptr);
  return(term);
}

/******************************************************************************/
/**
\brief  Discard - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Discard"

logical Workspace :: Discard ( )
{
  exd                    *exdarea = NULL;
  EB_Number               entnr(BigToPIF(1,pif));
  acb                    *acbptr;
  logical                 extlock = UNDEF;
  logical                 term = NO;
BEGINSEQ
  if ( !ws_list )                                    SDBERR(99)
  extlock = ws_list->stsclck();
  if ( ws_list->Lock() )                             ERROR
  if ( ws_list->GetCount() > 0 )                     SDBERR(322)

  if ( !(exdarea = new exd(NULL,NULL,0,0)) ) 
                                                     SDBERR(95)
  acbptr = exdarea->get_exdacb();
    
  while ( !(entnr = GetNextEBNumber(entnr)).IsEmpty() )
  {
    acbptr->ResetACB();
    acbptr->set_ebsnum(entnr);
    GetEBI(acbptr);
            
    root_base->ReleaseWSEntry(acbptr);
    ClearEBI(acbptr);
  }
  SDBCERR
  is_empty = YES;
RECOVER
  term = YES;
ENDSEQ
  if ( ws_list )
    ws_list->Unlock(extlock);
  return(term);
}

/******************************************************************************/
/**
\brief  ExistEBI

\return cond

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistEBI"

logical Workspace :: ExistEBI (acb *acbptr )
{
  logical        cond = YES;
BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_number() != ws_number )
                                                     ERROR
  if ( !acbptr->get_locate_exact() && acbptr->get_ws_number() == ws_number )
                                                     LEAVESEQ
    
  acb        test_acb(acbptr->get_ebsnum(),0,level,ws_number,acbptr->get_locate_exact(),acbptr->get_version_number());
  if ( cond = eb_RootBase::ExistEBI(&test_acb) )
    *acbptr = &test_acb;

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Flush

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical Workspace :: Flush ( )
{

  return(root_base->Flush());

}

/******************************************************************************/
/**
\brief  GetEBI

\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

EBI *Workspace :: GetEBI (acb *acbptr )
{
  EBI               *ebiptr;
  ebiptr = ExistEBI(acbptr) 
           ? eb_RootBase::GetEBI(acbptr)
           : root_base->GetEBI(acbptr);

  return(ebiptr);
}

/******************************************************************************/
/**
\brief  GetMBNumber

\return mbnumber - MainBase number

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBNumber"

int16 Workspace :: GetMBNumber (EB_Number entnr )
{

  return ( root_base->GetMBNumber(entnr) );

}

/******************************************************************************/
/**
\brief  GetRootBase

\return rootbase - 

\param  wslevel
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRootBase"

db_RootBase *Workspace :: GetRootBase (uint8 wslevel )
{

  return(wslevel == level ? this : root_base->GetRootBase(wslevel));

}

/******************************************************************************/
/**
\brief  Get_Length

\return size - Field size

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Length"

int32 Workspace :: Get_Length (acb *acbptr )
{
  int32         size = 0;
  size = ExistEBI(acbptr) 
         ? eb_RootBase::Get_Length(acbptr)
         : root_base->Get_Length(acbptr);

  return(size);
}

/******************************************************************************/
/**
\brief  Get_Mod

\return modcnt - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Mod"

uint8 Workspace :: Get_Mod (acb *acbptr )
{
  uint8                    modcnt;
  modcnt = ExistEBI(acbptr) 
           ? eb_RootBase::Get_Mod(acbptr)
           : root_base->Get_Mod(acbptr);

  return(modcnt);
}

/******************************************************************************/
/**
\brief  IsEmpty

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical Workspace :: IsEmpty ( )
{
  EB_Number               entnr;
  logical                 cond = YES;
BEGINSEQ
  if ( !(entnr = GetNextEBNumber(entnr)).IsEmpty() )
    if ( entnr != rb_header->get_work_spaces() )     ERROR
  
  if ( !(entnr = GetNextEBNumber(entnr)).IsEmpty() ) ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsWorkspace

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWorkspace"

logical Workspace :: IsWorkspace ( )
{

  return(YES);
}

/******************************************************************************/
/**
\brief  Locate - 


\return area

\param  acbptr - 
\param  entlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *Workspace :: Locate (acb *acbptr, int32 entlen )
{
  void       *area = NULL;
  area = ExistEBI(acbptr) 
         ? eb_RootBase::Locate(acbptr,entlen)
         : root_base->Locate(acbptr,entlen);


  return(area);
}

/******************************************************************************/
/**
\brief  Lock

\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical Workspace :: Lock (acb *acbptr, logical wait )
{

  return( root_base->Lock(acbptr,wait) );




}

/******************************************************************************/
/**
\brief  LockInternal

\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical Workspace :: LockInternal (acb *acbptr, logical wait )
{

  return( ExistEBI(acbptr) 
          ? eb_RootBase::LockInternal(acbptr,wait)
          : root_base->LockInternal(acbptr,wait)   );



}

/******************************************************************************/
/**
\brief  ProvideWSEntry

\return term - Termination code

\param  acbptr - 
\param  del_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideWSEntry"

logical Workspace :: ProvideWSEntry (acb *acbptr, logical del_opt )
{
  char                    wpt;
  db_RootBase            *rb;
  int32                    len;
  logical                 term = NO;
BEGINSEQ
  if ( level == 1 )    // WS0
    root_base->ProvideWSEntry(acbptr,del_opt);
  else
  {
    acbptr->ResetACB();
    acb    acbenty(*acbptr);
    if ( CheckEBI(&acbenty) || acbenty.get_ws_level() < level )  // um acb nicht kaputt zu machen
    {
      rb = GetRootBase(acbptr->get_ws_level());
      if ( (wpt = Check_WProtect(&acbenty)) & 2 )  // intern gelockt
        UnlockInternal(&acbenty);
      if ( rb = GetRootBase(acbptr->get_ws_level()) )
        rb->ReleaseEntry(acbptr);
      
      len = MAX(acbptr->get_entry_length(),acbptr->GetLength()+IEH);
      acb    newacb(acbptr->get_ebsnum(),0,acbptr->get_version_number());
      newacb.set_ws_level(level,ws_number);
      if ( eb_RootBase::Create(&newacb).IsEmpty() )  ERROR
      newacb.UpdateModCount(MAX(1,acbptr->get_mod_count()-1));
      *acbptr = &newacb;                          // jetzt acb in WS
      if ( del_opt )
        term = eb_RootBase::Delete(acbptr);
      else
        term = eb_RootBase::Update(acbptr,len,AUTO);
      root_base->ReserveWSEntry(acbptr);
    
      eb_RootBase::ReserveEntry(acbptr);
      if ( wpt & 2 )                              // intern gelockt
        LockInternal(&newacb,YES);
    }
    
    SDBRESET
    CheckEBI(acbptr);                                SDBCERR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseEntry

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

logical Workspace :: ReleaseEntry (acb *acbptr )
{

  return( ExistEBI(acbptr) 
          ? eb_RootBase::ReleaseEntry(acbptr)
          : root_base->ReleaseEntry(acbptr)   );






}

/******************************************************************************/
/**
\brief  ReleaseWSEntry

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseWSEntry"

logical Workspace :: ReleaseWSEntry (acb *acbptr )
{

  return( ExistEBI(acbptr)
          ? eb_RootBase::ReleaseWSEntry(acbptr)
          : root_base->ReleaseWSEntry(acbptr)   );


}

/******************************************************************************/
/**
\brief  Remove

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical Workspace :: Remove ( )
{
  logical                 term = NO;
  remove(root_path);
  return(term);
}

/******************************************************************************/
/**
\brief  Reserve

\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical Workspace :: Reserve (acb *acbptr, logical wait )
{

  return( ExistEBI(acbptr) 
          ? eb_RootBase::Reserve(acbptr,wait)
          : root_base->Reserve(acbptr,wait)   );




}

/******************************************************************************/
/**
\brief  ReserveEntry

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEntry"

logical Workspace :: ReserveEntry (acb *acbptr )
{

  return( ExistEBI(acbptr) 
          ? eb_RootBase::ReserveEntry(acbptr)
          : root_base->ReserveEntry(acbptr)   );





}

/******************************************************************************/
/**
\brief  ReserveWSEntry

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveWSEntry"

logical Workspace :: ReserveWSEntry (acb *acbptr )
{

  return( ExistEBI(acbptr)
          ? eb_RootBase::ReserveWSEntry(acbptr)
          : root_base->ReserveWSEntry(acbptr)   );


}

/******************************************************************************/
/**
\brief  SaveBuffer

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveBuffer"

logical Workspace :: SaveBuffer ( )
{

  return(root_base->SaveBuffer());

}

/******************************************************************************/
/**
\brief  Unlock

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical Workspace :: Unlock (acb *acbptr )
{

  return( root_base->Unlock(acbptr) );



}

/******************************************************************************/
/**
\brief  UnlockInternal

\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical Workspace :: UnlockInternal (acb *acbptr )
{

  return( ExistEBI(acbptr) 
          ? eb_RootBase::UnlockInternal(acbptr)
          : root_base->UnlockInternal(acbptr)   );


}

/******************************************************************************/
/**
\brief  Update

\return term - Termination code

\param  acbptr - 
\param  entlen - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical Workspace :: Update (acb *acbptr, int32 entlen, int32 offset )
{
  logical                 term = NO;
BEGINSEQ
  if ( acbptr->get_locate_exact() )
  {
    if ( level != acbptr->get_ws_level() )           SDBERR(99) // kann später wieder raus
    if ( !eb_RootBase::ExistEBI(acbptr) )
      if ( eb_RootBase::Create(acbptr).IsEmpty() )   ERROR
    
    term = eb_RootBase::Update(acbptr,entlen,offset);
    is_empty = NO;
  }
  else
  {
    if ( level == 1 )    // WS0
      root_base->Update(acbptr,entlen,offset);
    else
    {
      if ( ProvideWSEntry(acbptr,NO) )               ERROR
    
      term = eb_RootBase::Update(acbptr,entlen,offset);
      is_empty = NO;
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Workspace - Constructor


\return term - Termination code

\param  dbhandle - Database handle
\param  ws_names
\param  cpath - Complete path
\param  exclusive
\param  ws_level
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Workspace"

     Workspace :: Workspace (DBHandle *dbhandle, char *ws_names, char *cpath, logical exclusive, uint8 ws_level )
                     : TABuffer (dbhandle->GetLocalDBHandle(),NULL,UNDEF),
eb_RootBase (!exclusive,RootBaseShared()),
  root_base(dbhandle->GetLocalDBHandle()->get_root_base()),
  ws_name(NULL),
  is_empty(NO)
{
  logical sys_pif = NO;
BEGINSEQ
  level = ws_level;
  
  ws_name = strdup(ws_names);
  
  if ( dbhandle->GetLocalDBHandle()->get_pif() )
  {
    sys_pif = TestSysVariable("PLATFORM_INDEPENDENT","YES");
    SetSysVariable("PLATFORM_INDEPENDENT","YES");
  }
  if ( eb_RootBase::Provide(cpath,PI_Write,exclusive,AUTO) )
                                                     ERROR
  ws_number = dbhandle->GetLocalDBHandle()->GetWorkspaceNumber(ws_names);

  if ( dbhandle->GetLocalDBHandle()->get_pif() && !sys_pif )
    SetSysVariable("PLATFORM_INDEPENDENT","NO");
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~Workspace - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Workspace"

     Workspace :: ~Workspace ( )
{
  eb_RootBase   *rootbase;
  CloseRecursive();
  
  if ( ws_name )
    free(ws_name);
  ws_name = NULL;

}


