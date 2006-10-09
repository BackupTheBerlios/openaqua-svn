/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    eb_RootBase

\brief    


\date     $Date: 2006/06/25 16:20:24,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "eb_RootBase"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sEBI.hpp>
#include  <sEBMainBase.hpp>
#include  <sEBRootBase.hpp>
#include  <sEB_Header.hpp>
#include  <sEB_RBHeader.hpp>
#include  <sEntryEvent.hpp>
#include  <sInstanceDescriptor.hpp>
#include  <sKeyCache.hpp>
#include  <sKeyCacheFile.hpp>
#include  <sOPAGlobals.hpp>
#include  <sObjectEntry.hpp>
#include  <sObjectEntryList.hpp>
#include  <sSDB_Workspace.hpp>
#include  <sWSList.hpp>
#include  <sWorkspace.hpp>
#include  <sacb.hpp>
#include  <seb_MainBase.hpp>
#include  <seb_RootBase.hpp>
#include  <sexd.hpp>
#include  <sieh.hpp>
#include  <seb_RootBase.hpp>


/******************************************************************************/
/**
\brief  CheckEBI - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical eb_RootBase :: CheckEBI (acb *acbptr )
{
  eb_MainBase  *mainbase;
  ObjectEntry  *ob_entry = NULL;
  logical       term = NO;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  if ( shared_rootbase )
  {
    if ( !(ob_entry = object_entries->ReserveEntry(acbptr,YES)) )
                                                     SDBERR(99)
  }
  
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
    
  if ( mainbase->CheckEBI(acbptr) )                  ERROR
  
  if ( shared_rootbase )
    ob_entry->Initialize(acbptr);

RECOVER
  term = YES;
ENDSEQ
  if ( ob_entry )
    object_entries->ReleaseEntry(acbptr);
  return(term);
}

/******************************************************************************/
/**
\brief  Check_WProtect - 


\return wptmode - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check_WProtect"

uint8 eb_RootBase :: Check_WProtect (acb *acbptr )
{
  eb_MainBase         *mainbase;
  InstanceDescriptor  *inst_descriptor;
  ObjectEntry         *obj_entry;
  uint8                wptmode = 3;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  if ( shared_rootbase )
  {
    if ( inst_descriptor = object_entries->ProvideEntry(acbptr,YES) )
    {
      if ( acbptr->stscdel() )                     SDBERR(3)
      if ( acbptr->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y") )
        wptmode = 1; // persistent lock
      else if ( obj_entry = object_entries->GetEntry(acbptr) )
      {
        if ( obj_entry->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y") )
          wptmode = 2;
        else
          wptmode = 0;
      }
    }
  }
  else if ( mainbase = GetMainBase(acbptr) )
    wptmode = mainbase->Check_WProtect(acbptr);

RECOVER

ENDSEQ
  return(wptmode);

}

/******************************************************************************/
/**
\brief  ClearEBI - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearEBI"

logical eb_RootBase :: ClearEBI (acb *acbptr )
{
  InstanceDescriptor     *inst_descriptor = NULL;
  eb_MainBase            *mainbase;
  logical                 term = NO;
BEGINSEQ
  if ( shared_rootbase )  
  {
    if ( !(inst_descriptor = object_entries->ProvideEntry(acbptr,YES)) )
                                                     ERROR
    inst_descriptor->get_ebi().Clear();
  }
    
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
  if ( mainbase->ClearEBI(acbptr) )                  ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 


\return rootbase - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

db_RootBase *eb_RootBase :: Close ( )
{

  if ( rb_header && rb_header->stscmod() )
    rb_header->Write();

  delete ws_list;
  ws_list = NULL;
  
  if ( main_bases )
  {
    while ( number_mb-- )
      (main_bases+number_mb)->Close();
    delete[] main_bases;
    main_bases = NULL;
  }
  return(NULL);
}

/******************************************************************************/
/**
\brief  Consolidate - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Consolidate"

logical eb_RootBase :: Consolidate ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Copy - 


\return term - Termination code

\param  srceroot - 
\param  consol_appl - 
\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical eb_RootBase :: Copy (eb_RootBase *srceroot, logical consol_appl, int16 mbnumber )
{
  int16     i;
  logical   term = NO;
BEGINSEQ
  if ( mbnumber != AUTO )
  {
    if ( mbnumber >= number_mb )                      SDBERR(99)
    if ( (main_bases+mbnumber)->Copy(srceroot->get_main_bases()+mbnumber,consol_appl) )
                                                      ERROR
  }
  else 
  {
    for ( i=0; i < number_mb; i++ )
      if ( (main_bases+i)->get_mb_number() != temp_main )
        if ( (main_bases+i)->Copy(srceroot->get_main_bases()+i,consol_appl) )
                                                      ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 


\return entnr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  clnumb - 
\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number eb_RootBase :: Create (EB_Number clnumb, int16 mbnumber, uint16 sbnumber, uint16 version_nr )
{
  eb_MainBase  *mainbase;
  EB_Number     entnr(0);
BEGINSEQ
  if ( !clnumb.IsEmpty(pif) )
  {
    if ( !(mainbase = GetMainBase(clnumb)) )         ERROR
  }
  else
    mainbase = main_bases+mbnumber;

  if ( (entnr = mainbase->Create(sbnumber,mainbase->RBNtoMBN(clnumb),version_nr)).IsEmpty() )
                                                      ERROR
  entnr = mainbase->MBNtoRBN(entnr);
RECOVER

ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

EB_Number eb_RootBase :: Create (acb *acbptr )
{
  eb_MainBase  *mainbase;
  EB_Number     entnr;
  if ( mainbase = GetMainBase(acbptr,NO) )
    entnr = mainbase->Create(acbptr);
  return(entnr);
}

/******************************************************************************/
/**
\brief  CreateNewVersion - 


\return term - Termination code

\param  acbptr - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNewVersion"

logical eb_RootBase :: CreateNewVersion (acb *acbptr, uint16 version_nr )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

BEGINSEQ
  // not currently in use
  
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
    
  if ( mainbase->CreateNewVersion(acbptr,version_nr) )    
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical eb_RootBase :: Delete (acb *acbptr )
{
  ObjectEntry  *ob_entry;
  logical       term = NO;

BEGINSEQ
  if ( shared_rootbase )
  {
    if ( !(ob_entry = object_entries->ReserveEntry(acbptr,YES)) )
                                                     SDBERR(99)
//  Im Moment wird kein SchreibChache unterstützt. 
//  Alle Schreiboperationen werden sofort ausgeführt. 
//  Später erfolgt das Löschen über den InstanceDescriptor!!
    term = DeleteIntern(acbptr);
    
    object_entries->SetupEntry(acbptr,ob_entry);
//Events werden am Objekt gesammelt und bei TA-Ende generiert
//  ob_entry->GenerateEvent(SE_Delete,acbptr);
    object_entries->ReleaseEntry(acbptr);
  }
  else
    term = DeleteIntern(acbptr);


RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteIntern - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteIntern"

logical eb_RootBase :: DeleteIntern (acb *acbptr )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->Delete(acbptr);
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteRB - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteRB"

logical eb_RootBase :: DeleteRB ( )
{
  extern OPAGlobals       opa_globals;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR

  opa_globals.ILockGlobal();
  if ( opa_globals.RootBaseShared() )            // shared rootbase
  {
    if ( use_count == 1 )                        // last user
      opa_globals.UnregisterRootBase(this);
    else
      if ( object_entries->ReleaseLockedEntries(UNDEF) ) // release unlocked entries
      {
        SDBSET(99)
        SDBRESET
      }
  }        
  ReferenceObject::Release();                    // root base destroyed
  opa_globals.IUnlockGlobal();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteVersion - 


\return term - Termination code

\param  acbptr - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteVersion"

logical eb_RootBase :: DeleteVersion (acb *acbptr, uint16 version_nr )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

BEGINSEQ
  // not used so far
  
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
    
  if ( mainbase->DeleteVersion(acbptr,version_nr) )  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteWorkspaces - 


\return term - Termination code

\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteWorkspaces"

logical eb_RootBase :: DeleteWorkspaces (DBHandle *dbhandle )
{
  SDB_Workspace *ws_entry;
  Workspace     *ws;
  char           names[129];
  char           users[81];
  int32           count = 0;
  logical        term  = NO;
BEGINSEQ
  if ( !ws_list )
  {
    if ( rb_header->get_work_spaces().IsEmpty(pif) ) LEAVESEQ
    if ( InitWSList(dbhandle) )                      SDBCERR
  }
  
  if ( ws_list->Lock() )                             ERROR
  if ( (count = ws_list->GetCount()) <= 0 )          LEAVESEQ
    
  while ( count && (ws_entry = ws_list->Get(--count)) )
  {
    SDBEV1(ws_entry->get_name(),UNDEF)
    
//  if ( !(ws = OpenWorkspace(dbhandle,ws_entry->get_name(),ws_entry->get_user(),ws_entry->get_location(),YES)) )    
    gvtxbts(names,ws_entry->get_name(),sizeof(names)-1);
    gvtxbts(users,ws_entry->get_user(),sizeof(users)-1);
    if ( dbhandle->DeleteWorkspace(names,users) )    ERROR
  }

  

RECOVER
  term = YES;
ENDSEQ
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

logical eb_RootBase :: Discard ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ExistEBI - 


\return cond - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistEBI"

logical eb_RootBase :: ExistEBI (acb *acbptr )
{
  InstanceDescriptor  *inst_descriptor = NULL;
  eb_MainBase         *mainbase;
  logical              cond = NO;
BEGINSEQ
  if ( shared_rootbase )
  {
    if ( inst_descriptor = object_entries->ProvideEntry(acbptr,NO) ) 
    {
      switch( inst_descriptor->get_ebi().GetStatus() )
      {
        case  0 :               // undefined
        case  1 : break;        // empty
        case  2 :               // used
        case  3 : cond = YES;   // new entry
                  break;
        default : ;
      }
      LEAVESEQ
    }
  }
  
  if ( !(mainbase = GetMainBase(acbptr,NO)) )      ERROR
  cond = mainbase->ExistEBI(acbptr);

RECOVER

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ExistWorkspace - 


\return cond - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistWorkspace"

logical eb_RootBase :: ExistWorkspace (char *names )
{
  logical            cond = YES;

BEGINSEQ
  if ( !ws_list )                                    ERROR
  
  if ( !ws_list->Get(names) )                        ERROR

   
  

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Flush - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical eb_RootBase :: Flush ( )
{
  int         mbnumber = number_mb;
  logical     term     = NO;
  ILock();
  
  if ( object_entries )
    object_entries->Flush();
  
  if ( main_bases )
    while ( mbnumber-- )
      (main_bases+mbnumber)->Flush();

  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  FlushCluster - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushCluster"

logical eb_RootBase :: FlushCluster (acb *acbptr )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

BEGINSEQ
  if ( acbptr->get_cluster_number().IsEmpty(pif) )      LEAVESEQ
  
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
  if ( mainbase->FlushCluster(acbptr) )              ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  FlushClusterPool - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushClusterPool"

logical eb_RootBase :: FlushClusterPool ( )
{
  int16      nummb = number_mb;
  logical    term = NO;
  while ( nummb-- )
    if ( (main_bases+nummb)->FlushClusterPool() )
      term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateServerEvent - 


\return term - Termination code

\param  ev_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateServerEvent"

logical eb_RootBase :: GenerateServerEvent (EntryEvent *ev_ptr )
{
  ObjectEntry  *ob_entry;
  logical       term = NO;

BEGINSEQ
  if ( !shared_rootbase )                            LEAVESEQ

  if ( !(ob_entry = (ObjectEntry *)object_entries->BinArray::ProvideEntryIntern(ev_ptr->ebsnum.get_ebsnum(),NO)) )
                                                     ERROR
  if ( ob_entry->stscerr() )                         ERROR
  ob_entry->GenerateEvent(ev_ptr);

RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetDataVersion - 


\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataVersion"

int16 eb_RootBase :: GetDataVersion ( )
{

  return(rb_header->get_version());

}

/******************************************************************************/
/**
\brief  GetEBI - 


\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

EBI *eb_RootBase :: GetEBI (acb *acbptr )
{
  logical       old_ent = acbptr->stsctrans();
  eb_MainBase  *mainbase;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  if ( shared_rootbase )  
  {
    if ( !object_entries->ProvideEntry(acbptr,YES) ) ERROR
  }
  else
  {
    if ( !(mainbase = GetMainBase(acbptr)) )         ERROR
    if ( mainbase->ebsprv(acbptr,YES) )              ERROR
    if ( acbptr->stscold() )  //versionierter entry
      acbptr->SetModCount(mainbase->Get_Mod(acbptr));
  }
  if ( old_ent )
    acbptr->stsstrans();

RECOVER
  acbptr = NULL;
ENDSEQ
  return(acbptr);
}

/******************************************************************************/
/**
\brief  GetEntryHeader - 


\return iehptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryHeader"

ieh *eb_RootBase :: GetEntryHeader (acb *acbptr )
{
  ieh             *iehptr  = NULL;
  logical          deleted = NO;
BEGINSEQ
  CheckEBI(acbptr);                                  SDBCERR

  if ( acbptr->stscdel() )
  {
    deleted = YES;
    if ( Undelete(acbptr) )                          ERROR
  }
  
  iehptr = &acbptr->get_acbieh();
  if ( !Locate(acbptr,IEH) )
    iehptr = NULL;

  if ( deleted )
    Delete(acbptr);
  

RECOVER
  iehptr = NULL;
ENDSEQ
  return(iehptr);
}

/******************************************************************************/
/**
\brief  GetFirstEBNumber - 


\return entnr - 

\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFirstEBNumber"

EB_Number eb_RootBase :: GetFirstEBNumber (int16 mbnumber )
{
  EB_Number     entnr = 1;
BEGINSEQ
  if ( mbnumber >= number_mb )                       SDBERR(32)
  
  entnr = (main_bases+mbnumber)->MBNtoRBN(entnr);
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetLastEBNumber - 


\return entnr - 

\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastEBNumber"

EB_Number eb_RootBase :: GetLastEBNumber (int16 mbnumber )
{
  EB_Number     entnr = (main_bases+mbnumber)->get_mb_header()->get_last_EBS_num();
BEGINSEQ
  if ( mbnumber >= number_mb )                       SDBERR(32)
  
  entnr = (main_bases+mbnumber)->MBNtoRBN(entnr);
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetMBCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBCount"

int32 eb_RootBase :: GetMBCount ( )
{

  return(rb_header->get_mb_count());

}

/******************************************************************************/
/**
\brief  GetMBNumber - 


\return mbnumber - MainBase number

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBNumber"

int16 eb_RootBase :: GetMBNumber (EB_Number entnr )
{
  eb_MainBase      *mb;
  return ( (mb = GetMainBase(entnr)) ? mb->get_mb_number() : 0);

}

/******************************************************************************/
/**
\brief  GetMainBase - 


\return mainbase - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

eb_MainBase *eb_RootBase :: GetMainBase (EB_Number entnr )
{
  eb_MainBase   *mainbase = NULL;
  int            mbnumber = entnr.get_ebsnum() >> 48;
  char           string[13];
  int      i;

BEGINSEQ
  if ( entnr.IsEmpty(pif) )                             LEAVESEQ
  mbnumber = entnr.FromPIF(pif).get_ebsnum() >> 48;
  
  for ( i=0; i < number_mb; i++)
    if ( (main_bases+i)->get_mb_number() == mbnumber )
    {
      mainbase = main_bases+i;                  
      if ( mainbase->get_sub_bases() )               LEAVESEQ
                                                     ERROR
//    SDBERR(32)
    }
  
  SDBEV4(gvtxltoa(entnr.get_ebsnum(),string,10),UNDEF)
  SDBERR(32)
RECOVER
  mainbase = NULL;

ENDSEQ
  return(mainbase);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

eb_MainBase *eb_RootBase :: GetMainBase (int32 indx0 )
{
  eb_MainBase   *mainbase = NULL;

BEGINSEQ
  if ( indx0 >= number_mb )                          ERROR
    
  mainbase = main_bases+indx0;                  

RECOVER

ENDSEQ
  return(mainbase);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  acbptr - 
\param  check_acb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

eb_MainBase *eb_RootBase :: GetMainBase (acb *acbptr, logical check_acb )
{
  eb_MainBase            *mainbase = NULL;
BEGINSEQ
  if ( check_acb && acbptr->get_ws_level() != level )
  {
    if ( acbptr->stscmod() )                         SDBERR(99)
    acbptr->set_ebi_position(0);
    acbptr->set_ws_level(level,GetWorkspaceNumber());
    CheckEBI(acbptr);    
    acbptr->stsstrans();
  }

  if ( acbptr->get_ebi_position() )
    mainbase = main_bases+acbptr->get_mb_number();
  else
    if ( mainbase = GetMainBase(acbptr->get_ebsnum()) )
    {
      acbptr->get_mb_ebsnum() = mainbase->RBNtoMBN(acbptr->get_ebsnum());
      acbptr->set_mb_number(mainbase->get_mb_number());
    }
RECOVER

ENDSEQ
  return(mainbase);
}

/******************************************************************************/
/**
\brief  GetNextEBNumber - 


\return entnr - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextEBNumber"

EB_Number eb_RootBase :: GetNextEBNumber (EB_Number entnr )
{
  eb_MainBase  *mainbase;
BEGINSEQ
  if ( entnr.IsEmpty() )
    mainbase = GetMainBase(1);
  else
  {
    if ( !(mainbase = GetMainBase(entnr)) )          ERROR
    entnr = mainbase->RBNtoMBN(entnr);
  }
  
  while ( mainbase && (entnr = mainbase->GetNextEBNumber(entnr)).IsEmpty(NO) )
  {
    mainbase = mainbase->get_mb_number()+1 < number_mb
               ? &main_bases[mainbase->get_mb_number()+1]
               : NULL;
    entnr = 0;
  }
  
  if ( mainbase) 
    entnr = mainbase->MBNtoRBN(entnr);
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetPrevInstance - 


\return term - Termination code

\param  acbptr - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevInstance"

logical eb_RootBase :: GetPrevInstance (acb *acbptr, uint16 version_nr )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

BEGINSEQ
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
    
  if ( mainbase->GetPrevInstance(acbptr,version_nr) )    
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetRootBase - 


\return rootbase - 

\param  wslevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRootBase"

db_RootBase *eb_RootBase :: GetRootBase (uint8 wslevel )
{

  return( this && (!wslevel || wslevel == level) ? this : NULL);

}

/******************************************************************************/
/**
\brief  GetWorkspace - 


\return ws_entry - 

\param  lindx0 - 
\param  user_name - 
\param  refresh - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspace"

SDB_Workspace *eb_RootBase :: GetWorkspace (int32 lindx0, char *user_name, logical refresh )
{
  int32                indx = 0;
  SDB_Workspace      *ws_entry = NULL;
BEGINSEQ
  if ( !ws_list )                                    ERROR
  
  SDB_Workspace       start_entry("","",user_name);
  
  while ( lindx0 >= 0 && (ws_entry = ws_list->Get(indx++)) )
    if ( *ws_entry == start_entry )
      lindx0--;
      

RECOVER

ENDSEQ
  return(ws_entry);
}

/******************************************************************************/
/**
\brief  GetWorkspaceNumber - 


\return wsnumber - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspaceNumber"

int32 eb_RootBase :: GetWorkspaceNumber (char *names )
{
  char             *wsroot;
  SDB_Workspace    *ws_entry;
  int32              wsnumber = 0;
BEGINSEQ
  if ( !ws_list )                                    SDBERR(99)
  
  wsroot = IsWorkspace() ? ((Workspace *)this)->get_ws_name() : "";
    
  SDB_Workspace   ws(wsroot,names,"",UNDEF,NULL);
  if ( !(ws_entry = ws_list->Get(names)) )           ERROR
  
  wsnumber = ws_entry->get_id();

RECOVER
  wsnumber = 0;
ENDSEQ
  return(wsnumber);
}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspaceNumber"

int32 eb_RootBase :: GetWorkspaceNumber ( )
{

  return ( IsWorkspace() ? ((Workspace *)this)->get_ws_number() 
                         : 0                                    );

}

/******************************************************************************/
/**
\brief  Get_Length - 


\return entlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Length"

int32 eb_RootBase :: Get_Length (acb *acbptr )
{
  eb_MainBase           *mainbase;
  InstanceDescriptor    *inst_descriptor = NULL;
  int32               odblen = 0;
BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  if ( shared_rootbase )
    inst_descriptor = object_entries->ProvideEntry(acbptr,YES);
  
  if ( acbptr->get_ebi_position() && acbptr->get_mod_count() )
    odblen = acbptr->get_entry_length();
  else
  {
    if ( shared_rootbase && inst_descriptor )
      odblen = inst_descriptor->GetLength()+IEH;
    if ( !odblen && (mainbase = GetMainBase(acbptr)) )
      odblen = mainbase->Get_Length(acbptr);
  }
RECOVER

ENDSEQ
  return(odblen);

}

/******************************************************************************/
/**
\brief  Get_Mod - 


\return modcnt - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Mod"

uint8 eb_RootBase :: Get_Mod (acb *acbptr )
{
  eb_MainBase  *mainbase;
  logical       trans;
  uint8         modcnt = 0;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  if ( shared_rootbase )
  {
    if ( object_entries->ProvideEntry(acbptr,YES) )
    {
      if ( acbptr->stscdel() )                     SDBERR(3)
      modcnt = acbptr->get_mod_count();
    }
  }
  else if ( mainbase = GetMainBase(acbptr) )
  {
    trans  = acbptr->stsctrans();
    modcnt = mainbase->Get_Mod(acbptr);
    if ( trans )
      acbptr->stsstrans();
  }

RECOVER

ENDSEQ
  return(modcnt);

}

/******************************************************************************/
/**
\brief  IgnoreSharedRB - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IgnoreSharedRB"

void eb_RootBase :: IgnoreSharedRB ( )
{

  shared_rootbase = NO;

}

/******************************************************************************/
/**
\brief  InitDataArea - 


\return term - Termination code

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  danumber - Number for DataArea
\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitDataArea"

logical eb_RootBase :: InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{
  EB_DAHeader  *daheader = NULL;
  logical       term = NO;
BEGINSEQ
  if ( headerpt )
    daheader = (EB_DAHeader  *)headerpt;
  else
  {
    daheader = new EB_DAHeader(sizeof(EB_extDAHeader),NO);
    daheader->set_da_number(danumber);
  }

  daheader->SetSize(dasize);
  if ( InitHeader(mbnumber,sbnumber,daheader,filename,NULL) )
                                                      ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( !headerpt )
    delete daheader;
  return(term);
}

/******************************************************************************/
/**
\brief  InitHeader - 


\return term - Termination code

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  pheader - 
\param  filename - File name for DataArea file
\param  server - Name for MainBase server
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHeader"

logical eb_RootBase :: InitHeader (int16 mbnumber, uint16 sbnumber, EB_Header *pheader, char *filename, char *server )
{
  eb_DataArea     *dataarea = main_bases->GetDataArea0();
  EBMainBase      mbentry(NULL,NULL);
  EBMainBase      mbnew(filename,server);
  int64            position64 = 0;
  int64            newpos64   = 0;
  logical          term       = NO;
BEGINSEQ
  if ( mbnumber != AUTO )
  {
    if ( mbnumber >= number_mb )                      SDBERR(32)                  
    if ( (main_bases+mbnumber)->InitHeader(sbnumber,pheader,filename) )
                                                      ERROR
    LEAVESEQ
  }

  if ( dataarea->Read(rb_header->get_header_length(),sizeof(EBMainBase),&mbentry) )
                                                      SDBERR(30)
  mbentry.FromPIF(pif);
  mbnumber = 1;
  position64 = rb_header->get_header_length();
  while ( mbentry.get_next_mb() )
  {
    position64 = mbentry.get_next_mb();
    mbnumber++;
    if ( dataarea->Read(position64,sizeof(EBMainBase),&mbentry) )
                                                      SDBERR(31)
    mbentry.FromPIF(pif);
  }
  mbnew.ToPIF(pif);
  term = !(newpos64 = dataarea->Append(sizeof(EBMainBase),sizeof(EBMainBase),&mbnew));
  mbnew.FromPIF(pif);
  if ( term )                                         ERROR
    
  if ( *(((int32 *)&newpos64)+1) )                     SDBERR(99)
  mbentry.SetNext(newpos64);
  
  rb_header->Lock();
  rb_header->set_mb_count(rb_header->get_mb_count()+1);
  rb_header->stssmod();
  rb_header->Unlock();
  mbentry.ToPIF(pif);
  term = dataarea->Write(position64,sizeof(EBMainBase),&mbentry);
  mbentry.FromPIF(pif);
  if ( term )                                         ERROR
  
  if ( eb_DataArea::InitFile(pheader,&mbnew,sizeof(EBSubBase)) )
                                                      ERROR

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitKeyCache - 


\return term - Termination code

\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitKeyCache"

logical eb_RootBase :: InitKeyCache (ACObject *obhandle )
{
  logical                 term = NO;
  if ( !obhandle->IsClientObject() )   // runs on a server
    key_cache = new KeyCache();
  else
    key_cache = new KeyCacheFile(obhandle);
  return(term);
}

/******************************************************************************/
/**
\brief  InitMainBase - 


\return term - Termination code

\param  mbnumber - MainBase number
\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
\param  pindep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMainBase"

logical eb_RootBase :: InitMainBase (int16 mbnumber, char *filename, int32 dasize, char *server, EB_Header *headerpt, logical pindep )
{
  EB_MBHeader  *mbheader;
  logical       term = NO;
BEGINSEQ
  if ( headerpt )
    mbheader = (EB_MBHeader  *)headerpt;
  else
  {
    mbheader = new EB_MBHeader(sizeof(EB_extMBHeader),NO);
    mbheader->set_mb_number(mbnumber);
  }
  
  mbheader->set_platform_indep(pindep);
    
  if ( InitSubBase(AUTO,AUTO,filename,dasize,server,mbheader) ) 
                                                         ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( !headerpt )
    delete mbheader;
  return(term);
}

/******************************************************************************/
/**
\brief  InitRootBase - 


\return term - Termination code

\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
\param  pindep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRootBase"

logical __cdecl eb_RootBase :: InitRootBase (char *filename, int32 dasize, logical pindep )
{
  EB_RBHeader     rbheader(sizeof(EB_extRBHeader),NO);
  EBMainBase      mbdef(filename,NULL);
  eb_DataArea     dataarea();
  logical         term             = NO;

  rbheader.SetSize(dasize);
  rbheader.set_platform_indep(pindep);
  
  mbdef.ToPIF(pindep);
  term = eb_DataArea::InitFile(&rbheader,&mbdef,sizeof(EBMainBase));
  mbdef.FromPIF(pindep);

  return(term);
}

/******************************************************************************/
/**
\brief  InitSubBase - 


\return term - Termination code

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  filename - File name for DataArea file
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitSubBase"

logical eb_RootBase :: InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{
  EB_SBHeader   *sbheader;
  logical        term = NO;

  if ( headerpt )
    sbheader = (EB_SBHeader  *)headerpt;
  else
  {
    sbheader = new EB_SBHeader(sizeof(EB_extSBHeader),NO);
    sbheader->set_sb_number(sbnumber);
  }
  
  term = InitDataArea(mbnumber,AUTO,AUTO,filename,dasize,server,sbheader);
  if ( !headerpt )
    delete sbheader;
  return(term);
}

/******************************************************************************/
/**
\brief  InitWSList - 


\return term - Termination code

\param  dbhandle - Database handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitWSList"

logical eb_RootBase :: InitWSList (DBHandle *dbhandle )
{
  acb                    *acbptr;
  logical                 term = NO;
BEGINSEQ
  if ( !ws_list )
  {
    ws_list = new WSList(this,dbhandle);             SDBCERR
    if ( rb_header->get_work_spaces().IsEmpty(pif) )
    {
      if ( rb_header->Lock() )                       ERROR
      rb_header->stssmod();
      ws_list->InitialWrite();
      term = rb_header->Write();
      rb_header->Unlock();
      if ( term )                                    ERROR
    }
    ws_list->ProvideEXD();
    acbptr = ws_list->get_exd_area()->get_exdacb();
    acbptr->set_locate_exact(YES);
    acbptr->set_ws_level(level,GetWorkspaceNumber());
    if ( !ExistEBI(acbptr) )
      eb_RootBase::Create(acbptr);
    ws_list->Refresh();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IntGetEBI - 


\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntGetEBI"

EBI *eb_RootBase :: IntGetEBI (acb *acbptr )
{
  eb_MainBase  *mainbase;

BEGINSEQ
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
    
  acbptr->SetIEH(0,UNDEF,UNDEF,0);
  if ( mainbase->GetEBI(acbptr,YES) )                ERROR 

RECOVER
  acbptr = NULL;
ENDSEQ
  return(acbptr);
}

/******************************************************************************/
/**
\brief  IntPutEBI - 


\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntPutEBI"

EBI *eb_RootBase :: IntPutEBI (acb *acbptr )
{
  eb_MainBase  *mainbase;

BEGINSEQ
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
    
  if ( mainbase->PutEBI(acbptr) )                    ERROR 

RECOVER
  acbptr = NULL;
ENDSEQ
  return(acbptr);
}

/******************************************************************************/
/**
\brief  IsODABARootBase - 


\return eb_rootbase - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsODABARootBase"

eb_RootBase *eb_RootBase :: IsODABARootBase ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  IsPIF - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPIF"

logical eb_RootBase :: IsPIF ( )
{

  return(pif);

}

/******************************************************************************/
/**
\brief  IsWorkspace - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsWorkspace"

logical eb_RootBase :: IsWorkspace ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Locate - 


\return area - 

\param  acbptr - 
\param  entlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *eb_RootBase :: Locate (acb *acbptr, int32 entlen )
{
  eb_MainBase         *mainbase;
  InstanceDescriptor  *inst_descriptor = NULL;
  void                *area = NULL;
BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  if ( shared_rootbase )
  {
    if ( !(inst_descriptor = object_entries->ProvideEntry(acbptr,YES)) ) 
                                                     SDBERR(99)
    if ( area = inst_descriptor->Locate(acbptr,entlen,pif) )
                                                     LEAVESEQ
    area = LocateIntern(acbptr,entlen);
    
    if ( entlen == AUTO || entlen >= acbptr->GetLength() + IEH ) // ganzer entry
      object_entries->SetupEntry(acbptr,inst_descriptor);
  }
  else
    area = LocateIntern(acbptr,entlen);
        

RECOVER

ENDSEQ
  return(area);

}

/******************************************************************************/
/**
\brief  LocateIntern - 


\return area - 

\param  acbptr - 
\param  entlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateIntern"

void *eb_RootBase :: LocateIntern (acb *acbptr, int32 entlen )
{
  eb_MainBase         *mainbase;
  void                *area = NULL;
BEGINSEQ
  if ( mainbase = GetMainBase(acbptr) )
    if ( !(area = mainbase->Locate(acbptr,entlen)) ) ERROR

  acbptr->stsrtrans();

RECOVER

ENDSEQ
  return(area);

}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical eb_RootBase :: Lock (acb *acbptr, logical wait )
{
  eb_MainBase  *mainbase;
  logical       term = YES;
BEGINSEQ
  if ( shared_rootbase )
  {
    if ( term = object_entries->Lock(acbptr,wait) )    SDBERR(6)
    LEAVESEQ
  }
  
  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->Lock(acbptr,wait);

RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  LockInternal - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical eb_RootBase :: LockInternal (acb *acbptr, logical wait )
{
  eb_MainBase  *mainbase;
  logical       term = YES;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  if ( shared_rootbase )
    return (object_entries->LockInternal(acbptr,wait));
  
  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->LockInternal(acbptr,wait);

RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Open - 


\return term - Termination code

\param  path - 
\param  outopt - 
\param  exclusive - 
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical eb_RootBase :: Open (char *path, logical outopt, logical exclusive, char sysenv )
{
  eb_MainBase     mainbase;
  int16           mbnumber = 0;
  EBMainBase     mb_entry(NULL);
  int64          position64;
  int32          len;
  char           *tmppath = NULL;
  logical         term = NO;
BEGINSEQ
  net_option = net_option;
  if ( mainbase.Open(rb_header,path,outopt,net_option,sysenv,NO) ) 
                                                          ERROR
  pif = mainbase.get_pif();
  root_path = strdup(path);
  if ( !rb_header->stscold() )
  {
    EBRootBase    rbentry(NULL);
    gvtxbts(rbentry.get_file_name(),path,512);
    mainbase.WriteInitial(&rbentry,sizeof(EBRootBase));
  }

  number_mb = rb_header->get_mb_count();
//  if ( outopt )  we need temporary mainbases also for read-only applications, 8.2.2006
  number_mb++;
  
  if ( !mainbase.get_sub_bases()->
             Locate(0,rb_header->get_header_length(),sizeof(EBMainBase),&mb_entry) )
                                                          SDBERR(30)
  mb_entry.FromPIF(pif);
  main_bases = new eb_MainBase[number_mb];
  *main_bases = mainbase;

  while ( position64 = mb_entry.get_next_mb() )
  {
    mbnumber++;
    if ( !mainbase.get_sub_bases()->Locate(0,position64,sizeof(EBMainBase),&mb_entry) )
                                                          SDBERR(31)
    mb_entry.FromPIF(pif);
    (main_bases+mbnumber)->Open(NULL,mb_entry.get_file_name(),outopt,net_option,sysenv,pif);
  }
  
  if ( number_mb > rb_header->get_mb_count() )
  {
    temp_main = (main_bases+mbnumber)->get_mb_number()+1;
    mbnumber++;
    (main_bases+mbnumber)->OpenTemp(temp_main,pif);
  }

RECOVER
  int16 errsav = SDBERROR;
  Close();
  term = YES;
  SDBISET(errsav);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenTemp - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenTemp"

logical eb_RootBase :: OpenTemp ( )
{
  eb_MainBase     mainbase;
  logical         term = NO;
BEGINSEQ
  if ( mainbase.OpenTemp(0,pif) )                        ERROR
  if ( !rb_header->stscold() )
  {
    EBRootBase    rbentry(NULL);
    strcpy(rbentry.get_file_name(),"ta_base");
    mainbase.WriteInitial(&rbentry,sizeof(EBRootBase));
  }

  number_mb = 1;
  
  main_bases = new eb_MainBase[number_mb];
  *main_bases = mainbase;
RECOVER
  int16 errsav = SDBERROR;
  Close();
  term = YES;
  SDBISET(errsav);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenWorkspace - 


\return workspace - 

\param  dbhandle - Database handle
\param  names - 
\param  user_name - 
\param  cpath - Complete path
\param  exclusive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenWorkspace"

Workspace *eb_RootBase :: OpenWorkspace (DBHandle *dbhandle, char *names, char *user_name, char *cpath, logical exclusive )
{
  Workspace              *workspace = NULL;
BEGINSEQ
  if ( !ws_list )                                   SDBERR(99)
  
  workspace = new Workspace(dbhandle,names,cpath,exclusive,level+1); 
                                                     SDBCERR
RECOVER
  delete workspace;
  workspace = NULL;
ENDSEQ
  return(workspace);
}

/******************************************************************************/
/**
\brief  Provide - 


\return term - Termination code

\param  cpath - Complete path
\param  accopt - Access mode
\param  exclusive - 
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

logical eb_RootBase :: Provide (char *cpath, PIACC accopt, logical exclusive, char sysenv )
{
  logical       largedb = TestSysVariable("LARGE_DB","YES");
  logical       pindep  = TestSysVariable("PLATFORM_INDEPENDENT","YES");
  logical                 term = NO;
BEGINSEQ
  if ( !Exist(cpath,net_option) )
  {
    if ( SDBERROR || accopt != PI_Write )            SDBERR(5)
    if ( InitRootBase(cpath,0,pindep) )
    {
      SDBEV1(cpath && *cpath > ' ' ? cpath : "[NULL]",UNDEF)
      SDBERR(5)
    }
  }

  if ( Open(cpath,accopt != PI_Read,exclusive,sysenv) ) SDBERR(5)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideWSEntry - 


\return term - Termination code

\param  acbptr - 
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideWSEntry"

logical eb_RootBase :: ProvideWSEntry (acb *acbptr, logical del_opt )
{
  acb           acbenty(*acbptr);
  logical       term = NO;

BEGINSEQ
  acbenty.ResetACB();
  if ( CheckEBI(&acbenty) )                          SDBERR(99)
  
  GetEBI(acbptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ProvideWorkspace - 


\return cpath - Complete path

\param  names - 
\param  user_name - 
\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideWorkspace"

char *eb_RootBase :: ProvideWorkspace (char *names, char *user_name, char *cpath )
{
  char             *wsroot;
  SDB_Workspace    *ws_entry;
BEGINSEQ
  if ( !ws_list )                                    SDBERR(99)
  
  wsroot = IsWorkspace() ? ((Workspace *)this)->get_ws_name() : "";
    
  SDB_Workspace   ws(wsroot,names,user_name,UNDEF,cpath);
  if ( !(ws_entry = ws_list->Get(names)) )
    if ( ws_list->Add(ws) )                          ERROR
  
  if ( !(ws_entry = ws_list->Get(ws)) )              SDBERR(325)

  cpath = ws_entry->get_location();

RECOVER
  cpath = NULL;
ENDSEQ
  return(cpath);
}

/******************************************************************************/
/**
\brief  RBType - 


\return rbtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RBType"

RootBase_Types eb_RootBase :: RBType ( )
{

  return(RBT_ODABA);

}

/******************************************************************************/
/**
\brief  ReleaseEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

logical eb_RootBase :: ReleaseEntry (acb *acbptr )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

BEGINSEQ
  if ( !acbptr )                                     LEAVESEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
    
  if ( shared_rootbase )
    object_entries->ReleaseEntry(acbptr);

//if ( shared_rootbase )                               LEAVESEQ
  
  if ( acbptr->get_cluster_number().IsEmpty(pif) )      LEAVESEQ
  
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
  if ( mainbase->ReleaseCluster(acbptr) )            ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ReleaseWSEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseWSEntry"

logical eb_RootBase :: ReleaseWSEntry (acb *acbptr )
{
  acb           acbenty(*acbptr);
  logical       term = NO;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  acbenty.ResetACB();
  if ( !eb_RootBase::GetEBI(&acbenty) )            SDBERR(99)
  acbenty.ResetWProtect();
  if ( eb_RootBase::Update(&acbenty,0,AUTO) )    SDBERR(242)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  RemoveWorkspace - 


\return term - Termination code

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveWorkspace"

logical eb_RootBase :: RemoveWorkspace (char *names )
{
  SDB_Workspace          *ws_entry;
  logical                 term = NO;
BEGINSEQ
  if ( !ws_list )                                    ERROR
  
  if ( !(ws_entry = ws_list->Get(names)) )           ERROR
  remove(ws_entry->get_location());
  
  if ( ws_list->Delete(names) )                      ERROR
      

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reserve - 


\return term - Termination code

\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical eb_RootBase :: Reserve (acb *acbptr, logical wait )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  if ( shared_rootbase )
    return (object_entries->LockInternal(acbptr,wait));
    
  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->Reserve(acbptr,wait);


RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ReserveEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEntry"

logical eb_RootBase :: ReserveEntry (acb *acbptr )
{
  eb_MainBase  *mainbase;
  logical       term = NO;

BEGINSEQ
  if ( !acbptr )                                     LEAVESEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  if ( shared_rootbase && !acbptr->get_ebsnum().IsEmpty(pif) )
    object_entries->ReserveEntry(acbptr,NO);
  
//if ( shared_rootbase )                               LEAVESEQ
  
  if ( acbptr->get_cluster_number().IsEmpty(pif) )      LEAVESEQ
  
  if ( !(mainbase = GetMainBase(acbptr)) )           ERROR
  if ( mainbase->UseCluster(acbptr) )                ERROR

RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ReserveWSEntry - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveWSEntry"

logical eb_RootBase :: ReserveWSEntry (acb *acbptr )
{
  acb           acbenty(*acbptr);
  logical       term = NO;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  acbenty.ResetACB();
  if ( !GetEBI(&acbenty) )                           SDBERR(99)
    
  if ( acbenty.GetWProtect() )                       LEAVESEQ
    
  acbenty.SetWProtect();
  Update(&acbenty,0,AUTO);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ResetSize - 


\return term - Termination code

\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetSize"

logical eb_RootBase :: ResetSize (int16 mbnumber )
{

  return(main_bases[mbnumber].ResetSize(0));


}

/******************************************************************************/
/**
\brief  SaveBuffer - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveBuffer"

logical eb_RootBase :: SaveBuffer ( )
{
  int      i;
  logical  term = NO;
  for ( i=0; i < number_mb; i++)
    if ( (main_bases+i)->SaveBuffer() )
      term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  Undelete - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Undelete"

logical eb_RootBase :: Undelete (acb *acbptr )
{
  eb_MainBase  *mainbase;
  ObjectEntry  *ob_entry;
  logical       term = YES;

BEGINSEQ
  if ( shared_rootbase )
  {
    if ( !(ob_entry = object_entries->ReserveEntry(acbptr,YES)) )
                                                     SDBERR(99)
//  Im Moment wird kein SchreibChache unterstützt. 
//  Alle Schreiboperationen werden sofort ausgeführt. 
//  Später erfolgt das Löschen über den InstanceDescriptor!!
    term = UndeleteIntern(acbptr);
    
    ob_entry->Initialize(acbptr);
//  object_entries->SetupEntry(acbptr,ob_entry); sonst statt Initialize
//  ob_entry->GenerateEvent(SE_Update,acbptr);
    object_entries->ReleaseEntry(acbptr);
  }
  else
    term = UndeleteIntern(acbptr);


RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  UndeleteIntern - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UndeleteIntern"

logical eb_RootBase :: UndeleteIntern (acb *acbptr )
{
  eb_MainBase  *mainbase;
  ObjectEntry  *ob_entry;
  logical       term = YES;

  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->Undelete(acbptr);



  return(term);

}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical eb_RootBase :: Unlock (acb *acbptr )
{
  eb_MainBase  *mainbase;
  logical       term = YES;

BEGINSEQ
  if ( shared_rootbase )
  {
    if ( term = object_entries->Unlock(acbptr) )    SDBERR(6)
    LEAVESEQ
  }
  
  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->Unlock(acbptr);

RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  UnlockInternal - 


\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical eb_RootBase :: UnlockInternal (acb *acbptr )
{
  eb_MainBase  *mainbase;
  logical       term = YES;

BEGINSEQ
  if ( acbptr->get_locate_exact()  && acbptr->get_ws_level() != level )
                                                     ERROR
  
  if ( shared_rootbase )
    return (object_entries->UnlockInternal(acbptr));
  
  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->UnlockInternal(acbptr);

RECOVER

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Update - 


\return term - Termination code

\param  acbptr - 
\param  entlen - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Update"

logical eb_RootBase :: Update (acb *acbptr, int32 entlen, int32 offset )
{
  eb_MainBase         *mainbase;
  EB_Number            clnumb(0);
  EBI                  temp_ebi;
  ObjectEntry         *inst_descriptor;
  logical              term = YES;

BEGINSEQ
  if ( shared_rootbase )
  {
    if ( acbptr->stscmod() )  // 4.5.2006, sonst werden EBI-Modifikationen beim Schreiben zurückgesetzt
      temp_ebi = *acbptr;
    if ( !(inst_descriptor = (ObjectEntry *)object_entries->ProvideEntry(acbptr,YES)) ) 
                                                     SDBERR(99)
    if ( temp_ebi.stscmod() )  // s.o.
      *(EBI *)acbptr = temp_ebi;
                                                     SDBERR(99)
//  Im Moment wird kein SchreibChache unterstützt. 
//  Alle Schreiboperationen werden sofort ausgeführt. 
//  Später erfolgt das Schreiben über den InstanceDescriptor!!
    term = UpdateIntern(acbptr,entlen,offset);
    object_entries->SetupEntry(acbptr,inst_descriptor);
//Events werden am Objekt gesammelt und bei TA-Ende generiert
//  inst_descriptor->GenerateEvent(SE_Update,acbptr);
  }
  else
    term = UpdateIntern(acbptr,entlen,offset);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  UpdateIntern - 


\return term - Termination code

\param  acbptr - 
\param  entlen - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateIntern"

logical eb_RootBase :: UpdateIntern (acb *acbptr, int32 entlen, int32 offset )
{
  eb_MainBase         *mainbase;
  logical              term = YES;

  acbptr->stsrtrans();
  
  if ( mainbase = GetMainBase(acbptr) )
    term = mainbase->Update(acbptr,entlen,offset);

  acbptr->stsrtrans();

  return(term);

}

/******************************************************************************/
/**
\brief  eb_RootBase - 



\param  netopt - Multi-user access
\param  shared_rb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "eb_RootBase"

     eb_RootBase :: eb_RootBase (logical netopt, logical shared_rb )
                     : db_RootBase (netopt),
  rb_header(new             EB_RBHeader(sizeof(EB_extRBHeader),netopt)),
  main_bases(NULL), number_mb(0), 
  db_handle_list(),
  shared_rootbase(shared_rb),
  object_entries(NULL),
  ws_list(NULL),
  pif(NO)
{

  if ( shared_rootbase )
    object_entries = new ObjectEntryList(this);

}

/******************************************************************************/
/**
\brief  getEBI - 


\return ebiptr - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getEBI"

EBI *eb_RootBase :: getEBI (acb *acbptr )
{
  eb_MainBase  *mainbase;
BEGINSEQ
  if ( !(mainbase = GetMainBase(acbptr)) )         ERROR
  if ( mainbase->ebsprv(acbptr,YES) )              ERROR

RECOVER
  acbptr = NULL;
ENDSEQ
  return(acbptr);
}

/******************************************************************************/
/**
\brief  ~eb_RootBase - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~eb_RootBase"

     eb_RootBase :: ~eb_RootBase ( )
{

  if ( object_entries )
    object_entries->Flush();
  delete object_entries;
  object_entries = NULL;
  
  Close();
  
  delete rb_header; 
  rb_header = NULL;

  if ( root_path )
    free(root_path);
  root_path = NULL;


}


