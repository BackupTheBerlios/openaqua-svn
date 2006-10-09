/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    LDBHandle

\brief    Database Handle
          Database  handle  must  be  created  for  accessing  data in an ODABA2
          database.  An  ODABA2  database  must  be  connected  with  a  {\b {.r
          Dictionary}}, which defines the object model for the database. 
          Each  ODABA database is a Database  Object (RootObject) that may refer
          to  subordinated root Database Objects.  Each Database Object within a
          database  has  its  own  name  space, i.e. identifying keys are unique
          only within a Database Object. 
          When   creating   a   database   handle   the   object handle ({\b {.r
          ACObject}})  for  the  root  Database  Object is created automatically
          (the  database handle is an Database  Object handle), i.e. besides the
          DBHandle  functions all ACObject functions  can be called. In addition
          the database handle is responsible for the log and recovery file.

\date     $Date: 2006/08/26 12:57:14,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "LDBHandle"

#include  <fileacc.h>
#include  <popa7.h>
#include  <coctp.h>
#ifndef   GSRT_WorkspaceEntry_HPP
#define   GSRT_WorkspaceEntry_HPP
#include  <sWorkspaceEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <cExtInstTypes.h>
#include  <cRootBase_Types.h>
#include  <sACObject.hpp>
#include  <sDBHeader.hpp>
#include  <sDBIndex.hpp>
#include  <sDBInfo.hpp>
#include  <sDictionary.hpp>
#include  <sEB_Header.hpp>
#include  <sEB_RBHeader.hpp>
#include  <sEntryEvent.hpp>
#include  <sGlobalObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sLDictionary.hpp>
#include  <sLNode.hpp>
#include  <iNetConversion.h>
#include  <sOPAGlobals.hpp>
#include  <sSDB_Dataset.hpp>
#include  <sSDB_ObjectExt.hpp>
#include  <sSDB_Workspace.hpp>
#include  <sWSList.hpp>
#include  <sWorkspace.hpp>
#include  <sWorkspaceEntry.hpp>
#include  <sacb.hpp>
#include  <sdb_RootBase.hpp>
#include  <sexd.hpp>
#include  <sguid.hpp>
#include  <sieh.hpp>
#include  <sinti.hpp>
#include  <srefTable.hpp>
#include  <srvr.hpp>
#include  <ssrt.hpp>
#include  <stim.hpp>
#include  <sxml_RootBase.hpp>
#include  <sLDBHandle.hpp>


/******************************************************************************/
/**
\brief  ActivateShadowBase - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateShadowBase"

logical LDBHandle :: ActivateShadowBase ( )
{
  logical              term = NO;
BEGINSEQ
  if ( !shadow_rb )                                  ERROR
    
  current_rb = shadow_rb;

  LACObject::ActivateShadowDB();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  BackupDB - 



\return term - Termination code

\param  target - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BackupDB"

logical LDBHandle :: BackupDB (char *target )
{
  logical   term      = NO;

BEGINSEQ
  if ( FileCopy(GetPath(),target,YES) )                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeRecovery - Enable/disable recovery support



\return term - Termination code

\param  rec_type - Type of recovery support
\param  rec_path - Folder for recovery files
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeRecovery"

logical LDBHandle :: ChangeRecovery (RecoveryType rec_type, char *rec_path )
{
  int                     recnum = 0;
  logical                 lock = NO;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(70)
  if ( access_mode == PI_Read )                      SDBERR(120)
 
  if ( LockHeader() )                                ERROR
  lock = YES;
  if ( ReadHeader() )                                ERROR
  
  if ( db_header->get_recover_pos() > 0 )            SDBERR(117)
    
  if ( strcmp(rec_path,db_header->get_recover_path()) || !db_header->get_recover_write() )
    recnum = 1;                                 // new cycle
  else
    recnum = db_header->get_recover_number()+1; // new generation

  db_header->set_recover_writ(NO);
  db_header->set_save_ta(NO);
  
  switch ( rec_type )
  {
    case RECOVERY_Full        : break;
    case RECOVERY_Transaction : recnum   = 0;
                                break;
    default                   : recnum   = 0;
                                rec_path = NULL;
  }
   
  UnlockHeader();
  lock = NO;
  if ( InitRecovery(rec_path,recnum) )               ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( lock )
    UnlockHeader();
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDB - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical LDBHandle :: CheckDB (CheckOptions check_opts )
{
  logical   term = NO;
  ResetOutputResult();
  if ( check_opts.instances )
  {
    term = CheckDBInstances(check_opts);
      term = YES;
    check_opts.instances = NO;
  }
  
  if ( check_opts.collections )
    term = CheckDBCollections(check_opts);


  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  check_opts - 
\param  resnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDB"

logical LDBHandle :: CheckDB (CheckOptions check_opts, char *resnames )
{
  DatabaseHandle          dbh(this);
  PropertyHandle          ph;
  LNode                  *lnodeptr;
  NString                 nresult;
  logical                 term = NO;
BEGINSEQ
  ResetOutputResult();
  if ( resnames && *resnames )
  {
    ph.Open(dbh,resnames,PI_Write);                SDBCERR
    lnodeptr = (LNode *)ph.get_nodeptr();
    lnodeptr->CheckDB(check_opts);
  }
  else
    CheckDB(check_opts);
RECOVER
  OutputResult("\n  Could not open data source ");
  OutputResult(resnames);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBCollections - 



\return term - Termination code

\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBCollections"

logical LDBHandle :: CheckDBCollections (CheckOptions check_opts )
{
  PropertyHandle   ph;
  char            *extname;
  DBExtend        *extdef;
  Dictionary      *dictionary = GetDictionary();
  DatabaseHandle   dbh(this);
  int32            indx0      = 0; 
  logical          term       = YES;
  while ( extname = GetExtent(indx0++) )
    if ( strcmp(extname,"VOID") )
      if ( extdef = dictionary->ProvideExtendDef(extname) )
        if ( !extdef->IsEnumeration() )
          if ( !ph.Open(dbh,extname,PI_Write) )
            ((LNode *)ph.get_nodeptr())->CheckDB(check_opts);

  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBEntry - 



\return sid - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBEntry"

int16 LDBHandle :: CheckDBEntry (EB_Number entnr )
{
  int16            sid = AUTO;
  acb              acbenty(entnr,0);
BEGINSEQ
  if ( !this )                                       ERROR
  if ( current_rb->CheckEBI(&acbenty) )              ERROR
  if ( acbenty.NewEntry() )                          LEAVESEQ
  if ( GetUsedLength(&acbenty) < 0 )                 ERROR
  
  sid = acbenty.GetSID();

RECOVER
  sid = UNDEF;
ENDSEQ
  return(sid);
}

/******************************************************************************/
/**
\brief  CheckDBGUID - 



\return term - Termination code

\param  acbptr - 
\param  rstring - 
\param  repair - 
\param  warnings - 
\param  maxlen - Size of the output buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBGUID"

logical LDBHandle :: CheckDBGUID (acb *acbptr, NString &rstring, logical repair, logical warnings, int32 maxlen )
{
  DBStructDef      *strdef;
  char             *guid_inst;
  char              guid_string[ID_SIZE+1];
  int32             pos;
  int16             sid;
  NString           mstring;
  char             *string;
  logical           term = NO;

BEGINSEQ
  *guid_string = 0; 
  
  if ( (sid = acbptr->get_acbieh().get_iehsid())<0 ) LEAVESEQ
  
  if ( !(strdef = dictionary->ProvideStructDef(sid,GetSchemaVersion())) )
                                                     LEAVESEQ
  if ( (pos = strdef->GetExtGUIDPosition(dictionary)) == AUTO )   
                                                     LEAVESEQ
  if ( !strdef->get_global_identity() )              LEAVESEQ
                                                     
  if ( maxlen > 0 )  // for 0 the instance is already located
  {
    if ( sizeof(ieh)+pos+16 > maxlen )                 SDBERR(999)
    if ( !root_base->Locate(acbptr,sizeof(ieh)+pos+16) )  ERROR
  }
  
  guid_inst = ((char *)&acbptr->get_acbieh())+sizeof(ieh)+pos;
  ((guid *)guid_inst)->GetString(guid_string);
  
  if ( sid != ((guid *)guid_inst)->GetSID() )
  {
    ((guid *)guid_inst)->AutoCorrection();
    mstring.Append(strdef->smcbname,ID_SIZE);
    mstring += ':';
    mstring += (int32)acbptr->get_mb_ebsnum().get_ebsnum();
    
    if ( !((guid *)guid_inst)->GetSID() )
    {
      mstring += " - missing GUID";
      if ( repair )
      {
        DatabaseHandle    dbh(this);
        PropertyHandle    void_pi(dbh,"VOID",PI_Write);
        if ( void_pi.Get((int32)acbptr->get_mb_ebsnum().get_ebsnum()) )
        {
          void_pi.Modify();
          void_pi.Save();
          ((guid *)guid_inst)->Initialize(void_pi.GetGUID());
          mstring += ' ';
          mstring += (char*) (((guid *)guid_inst)->GetSID() ? "(corrected)" : "(not corrected)");
          rstring += "\n  GUID error for";
          rstring += ' ';
          rstring += mstring;
          term = YES;
        }
      }
    }
    else if ( warnings )
    {
      mstring += " - SID differs in";
      mstring += ' ';
      mstring += guid_string;
    }
  }
  
  if ( !guid_pi.GetID(guid_inst) )
  {
    if ( repair )
      term = ((LNode *)guid_pi.GetNode())->AddID(guid_inst,acbptr->get_ebsnum(),AUTO);
  
    mstring = "";
    mstring.Append(strdef->smcbname,ID_SIZE);
    mstring += ':';
    mstring += (int32)acbptr->get_mb_ebsnum().get_ebsnum();
    mstring += " - not registered";
    mstring += ' ';
    if ( repair )
      mstring += (char*)(term ? "(not corrected)" : "(corrected)");
 
    rstring += "\n  GUID error for";
    rstring += ' ';
    rstring += mstring;
    term = YES;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBInstances - 



\return term - Termination code

\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBInstances"

logical LDBHandle :: CheckDBInstances (CheckOptions check_opts )
{
  PropertyHandle   vpi(*GetVoidPI());
  EB_Number        last_EB;
  EB_Number        first_EB;
  EBI             *ebiptr;
  int32            maxlen    = 16 * 1024;
  acb             *acbptr    = acb::Create(maxlen);
  int16            mbnumber  = 0;
  uint64           current;
  uint64           lastent;
  NString          rstring;
  CheckOptions     copt      = check_opts;
  int32            ent_count = 0;
  int32            err_count = 0;
  int32            guid_count= 0;
  logical          pif;
  logical          err       = NO;
  logical          term      = NO;
  if ( check_opts.repair_all ) 
  {
    vpi.ChangeMode(PI_Write);
    guid_pi.ChangeMode(PI_Write);
  }
  
  copt.guids = NO;
  pif = root_base->IsPIF();
  
  while ( !(first_EB = root_base->GetFirstEBNumber(mbnumber)).IsEmpty() )
  {
    last_EB = root_base->GetLastEBNumber(mbnumber++);
    current = first_EB.FromPIF(pif).get_ebsnum();
    lastent = last_EB.FromPIF(pif).get_ebsnum();
    while ( current <= lastent )
    {
      acbptr->set_ebsnum(BigToPIF(current,pif));
      if ( (ebiptr = root_base->IntGetEBI(acbptr)) &&
           !ebiptr->stscusr1()                     &&       // not a cluster entry
           !ebiptr->stscdel()                      &&       // not deleted entry
           ebiptr->GetPosition()                   &&       // not a new entry
           root_base->Locate(acbptr,sizeof(ieh))   &&       // can be read  
           acbptr->GetSID() > 2                    &&       // not a system object  
           acbptr->get_acbieh().get_iehtyp() == IDB_INS)    // an instance entry
      {
        ent_count++;
        err = NO;
        if ( check_opts.guids )
        {
          if ( CheckDBGUID(acbptr,rstring,check_opts.repair_all,check_opts.show_warnings,maxlen) )
            OutputResult(rstring);
          rstring = "";
        }
        if ( check_opts.deleted_references || check_opts.inverse_references ||
             check_opts.ref_indexes                                            )
        {
          if ( !vpi.Get(current) )
          {
            CheckDeleteDBInstance(copt,current);
            err = YES;
          }
          else if ( ((LNode *)vpi.get_nodeptr())->CheckDBInstance(copt) )
              err = YES;
        }
        if ( err )
        { 
          err_count++;
          term = YES;
        }
      }
      current++;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDeleteDBInstance - 



\return term - Termination code

\param  check_opts - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDeleteDBInstance"

logical LDBHandle :: CheckDeleteDBInstance (CheckOptions check_opts, EB_Number entnr )
{
  NString     nstring;
  logical     term = NO;
  nstring += "\n  Instance";
  nstring += ' ';
  nstring += (int32)entnr.get_ebsnum();   
  nstring += ' ';
  nstring += "not accessible";

  if ( !check_opts.repair_all )
    nstring += " (not corrected)";
  {
    Delete(entnr);
    nstring += " (deleted)";
  }

  OutputResult(nstring);

  return(term);
}

/******************************************************************************/
/**
\brief  CheckEBI - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical LDBHandle :: CheckEBI (exd *exdptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return ( GetRootBase(exdptr)->CheckEBI(exdptr->get_exdacb()) );

RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical LDBHandle :: CheckEBI (EB_Number entnr )
{
  acb              acbenty(entnr,0);
  return ( this
           ? current_rb->CheckEBI(&acbenty)
           : YES );


}

/******************************************************************************/
/**
\brief  CheckLicence - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  lic_owner - 
\param  lic_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical LDBHandle :: CheckLicence (char *lic_owner, char *lic_number )
{

  return( database_info->CheckLicence(this,lic_owner,lic_number) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  applname_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckLicence"

logical LDBHandle :: CheckLicence (char *applname_w )
{
  DBInfo        *dbinfo = NULL;
  logical        term = NO;
BEGINSEQ
  if ( !applname_w )
    return(CheckLicence(NULL,NULL));
  else
  {
    SetSysVariable("__APPLICATION_NAME",applname_w);
    dbinfo = new DBInfo(this,applname_w);
    if ( dbinfo->IsExpired() )                   SDBERR(314)
    if ( !dbinfo->get_licenced() )               SDBERR(317)
  }

RECOVER
  term = YES;
ENDSEQ
  delete dbinfo;
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 



\return wpmode - 

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

uint8 LDBHandle :: CheckWProtect (exd *exdptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( current_rb->Check_WProtect(exdptr->get_exdacb()) );

RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  CloseDBHandle - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseDBHandle"

logical LDBHandle :: CloseDBHandle ( )
{


BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  if ( context )
  {
    context->ExecuteAction(DBO_Close);
    context->SetProcessState(PRC_Closed);
  }
  
  if ( db_handle )
    LACObject::CloseObject();

  delete recovery_handle;
  recovery_handle = NULL;

  if ( current_rb && access_mode != PI_Read && !net_option )
    WriteHeader();

  if ( root_base )
    root_base->DeleteRB();
  root_base = NULL;
    
  if ( shadow_rb )
    shadow_rb->DeleteRB();
  shadow_rb = NULL;
  
  current_rb = NULL;
  
  DBHandle::CloseDBHandle();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  CloseRecovery - Close recovery file



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseRecovery"

logical LDBHandle :: CloseRecovery ( )
{
  logical  term = NO;
BEGINSEQ
  if ( !this )                                      SDBERR(70)

  delete recovery_handle;
  recovery_handle = NULL;


RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  CloseWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseWorkspace"

logical LDBHandle :: CloseWorkspace ( )
{
  db_RootBase            *rootbase;
  logical                 term = NO;
BEGINSEQ
  if ( !root_base->IsWorkspace() )                  ERROR
// so einfach geht das nicht. Wir müssen den Use-Count herunterzählen!!  
  if ( !(rootbase = root_base->Close()) )            ERROR

  if ( root_base->get_use_count() <= 0 )
    delete root_base;
    
  root_base = rootbase;
  if ( current_rb != shadow_rb )
    current_rb = root_base;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ConsolidateWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConsolidateWorkspace"

logical LDBHandle :: ConsolidateWorkspace ( )
{

  return(root_base->Consolidate());

}

/******************************************************************************/
/**
\brief  CreateACObject - 



\return obhandle - Database Object handle
-------------------------------------------------------------------------------
\brief  i0 - 



\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *LDBHandle :: CreateACObject (PIACC accopt, uint16 version_nr )
{
  ACObject     *acobject = NULL;
BEGINSEQ
  if ( !(acobject = new LACObject(this,accopt,version_nr)) )
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER
  delete acobject;
  acobject = NULL;
ENDSEQ
  return(acobject);
}

/******************************************************************************/
/**
\brief  i3 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *LDBHandle :: CreateACObject ( )
{

  return(new LACObject());

}

/******************************************************************************/
/**
\brief  CreateEntry - 



\return entnr - 

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  clnumb - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEntry"

EB_Number LDBHandle :: CreateEntry (int16 mbnumber, uint16 sbnumber, EB_Number clnumb, uint16 version_nr )
{
  EB_Number     entnr;

BEGINSEQ
  if ( (entnr = root_base->Create(clnumb,mbnumber,sbnumber,version_nr)).IsEmpty() )
                                                     ERROR
  if ( shadow_rb )
  {
    acb    acbenty(entnr,clnumb,version_nr);
    if ( entnr != shadow_rb->Create(&acbenty) )      SDBERR(99)
  }

RECOVER

ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  CreateRootBase - 



\return rootbase - 

\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRootBase"

db_RootBase *LDBHandle :: CreateRootBase (char *cpath, PIACC accopt, logical netopt, char sysenv )
{
  db_RootBase      *rootbase = NULL;
BEGINSEQ
  switch ( db_RootBase::GetRBType(cpath) )
  {
    case RBT_ORACLE: //rootbase = new ob_RootBase(netopt,NO);
                     break;
    case RBT_MS_SQL: //rootbase = new ms_RootBase(netopt,NO);
                     break;
    case RBT_ODBC  : //rootbase = new odbc_RootBase(netopt,NO);
                     break;
    case RBT_OXML  : rootbase = new xml_RootBase(netopt,NO);
                     break;
    case RBT_ODABA :
    default        : rootbase = new eb_RootBase(netopt,NO);
                     break;
  }

  if ( rootbase )
    if ( rootbase->Provide(cpath,accopt,NO,sysenv) )   ERROR
RECOVER
  rootbase = NULL;
ENDSEQ
  return(rootbase);
}

/******************************************************************************/
/**
\brief  CreateShadowRB - 



\return term - Termination code

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateShadowRB"

logical LDBHandle :: CreateShadowRB (char *cpath )
{
  char                   *path;
  logical                 term = NO;
BEGINSEQ
  if ( shadow_rb )
  {
//    SDBEV1(shadow_rb->get_root_path(),UNDEF);
    SDBError().DisplayMessage(339,shadow_rb->get_root_path());
    LEAVESEQ
  }

  if ( !(path = ProvideShadowRBPath(NO)) )          ERROR
  
  if ( cpath && *cpath > ' ' )
    strncpy(path,cpath,255);
  else
  {
    strncpy(path,root_base->get_root_path(),255);
    filextr(path,"sdw");
  } 

  // CopySingleFile geht noch nicht für große Datenbanken.
  remove(path);
  if ( CopySingleFile(root_base->get_root_path(),path) )
  {
    remove(path);
    SDBERR(332)
  }
  
  if ( shadow_rb_acb->get_ebsnum().IsEmpty() )
    if ( (db_header->get_shadow_db() = root_base->Create(0,0,0)).IsEmpty() )
                                                     ERROR
  shadow_rb_acb->set_ebsnum(db_header->get_shadow_db());
  shadow_rb_acb->SetPIF();  // SDB_Dataset ist z.Z. noch PIF (keine int Felder)
  
  if ( root_base->GetRootBase(0)->Update(shadow_rb_acb,sizeof(SDB_Dataset)+IEH,AUTO) )  
                                                     ERROR
  db_header->set_next_ws_number(1);
  WriteHeader();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeactivateShadowBase - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateShadowBase"

logical LDBHandle :: DeactivateShadowBase ( )
{
  logical              term = NO;
BEGINSEQ
  if ( !shadow_rb || current_rb == root_base )       ERROR
    
  current_rb = root_base;

  LACObject::DeactivateShadowDB();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  EBSNum - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical LDBHandle :: Delete (EB_Number entnr )
{
  acb            acbenty(entnr,0,0);
  logical        term   = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( !entnr.IsEmpty(pif) )
    if ( root_base->Delete(&acbenty) )               SDBERR(1)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  i0 - 



\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical LDBHandle :: Delete (exd *exdptr )
{
  EB_Number      entnr  = exdptr->get_exdebsn();
  logical        term   = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  exdptr->ResetACB(0);
  if ( !entnr.IsEmpty(pif) )
  {
    if ( GetRootBase(exdptr)->Delete(exdptr->get_exdacb()) )
                                                     SDBERR(1)
    if ( !exdptr->get_shadow_base() )
      if ( DeleteShadow(exdptr) )                    ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteShadow - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteShadow"

logical LDBHandle :: DeleteShadow (exd *exdptr )
{
  acb            temp_acb(0,0);
  logical        term    = NO;
BEGINSEQ
  if ( !shadow_rb || !exdptr->get_write_shadow() )   LEAVESEQ
  
  temp_acb = *exdptr->get_exdacb();
  exdptr->ResetACB(0);
  shadow_rb->GetEBI(exdptr->get_exdacb());
  term = shadow_rb->Delete(exdptr->get_exdacb());

  *exdptr->get_exdacb() = temp_acb;
  if ( term )                                        SDBERR(1)
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteWorkspace - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  names - 
\param  user_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteWorkspace"

logical LDBHandle :: DeleteWorkspace (char *names, char *user_name )
{
  logical                 term = NO;
BEGINSEQ
  SDBEV1(names,UNDEF)
  
  if ( OpenWorkspace(names,user_name,YES) )          ERROR
  if ( DeleteWorkspace() )                           ERROR


RECOVER
  CloseWorkspace();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteWorkspace"

logical LDBHandle :: DeleteWorkspace ( )
{
  char                   *names = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !root_base->IsWorkspace() )                   ERROR
  SDBEV1(((Workspace *)root_base)->get_ws_name(),UNDEF)
    
  if ( root_base->DeleteWorkspaces(this) )           ERROR
  
  // fragt nicht, ob sub-space da sind, das klärt DeleteWorkspaces()
  if ( !((Workspace *)root_base)->IsEmpty() )        SDBERR(326)
    
  names = strdup(((Workspace *)root_base)->get_ws_name());
  CloseWorkspace();
  root_base->RemoveWorkspace(names);
  free(names);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DisableWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableWorkspace"

logical LDBHandle :: DisableWorkspace ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( net_option )                                  SDBERR(334)
  
  if ( !this || !root_base )                         ERROR
    
  switch ( root_base->get_level() )
  {
    case 1  : if ( DeleteWorkspace() )               ERROR
              break;
    case 0  : if ( DeleteWorkspace("WS0","SysAdmin") )
                                                     ERROR
              break;
    default : SDBERR(333)
  }
   
  if ( RemoveShadowRB() )                            ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DiscardWorkspace - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiscardWorkspace"

logical LDBHandle :: DiscardWorkspace ( )
{

  return( InitWSList(YES) || root_base->Discard());

}

/******************************************************************************/
/**
\brief  EnableWorkspace - Worspace ativieren

        Die  Funktion  aktiviert  das  Workbase-Feature und die Shadow-Database.
        Als Pfad kann der Name für die Shadow-Database angegeben werden.

\return term - Termination code

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableWorkspace"

logical LDBHandle :: EnableWorkspace (char *cpath )
{
  logical                 term = NO;
BEGINSEQ
  if ( net_option )                                  SDBERR(334)
  
  if ( pif )
    SetSysVariable("PLATFORM_INDEPENDENT","YES");
    
  if ( CreateShadowRB(cpath) )                       ERROR

  // z.Z. wird WS0 im gleichen Verzeichnis, wie die Database angelegt. 
  // WS0 ohne database macht genausowenig Sinn, wie database ohne WS0
  
  if ( !HasWorkspace() )
    if ( OpenWorkspace("WS0","SysAdmin",YES) )       ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Exist - Check whether a database exists



\return term - Termination code

\param  cpath - Complete path
\param  chkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Exist"

logical __cdecl LDBHandle :: Exist (char *cpath, char chkopt )
{
  eb_RootBase  ebr(YES,NO);
  return(ebr.Exist(cpath,YES,chkopt) );


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

logical LDBHandle :: ExistWorkspace (char *names )
{

  return(root_base->ExistWorkspace(names));

}

/******************************************************************************/
/**
\brief  Flush - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical LDBHandle :: Flush ( )
{

  return ( current_rb->Flush() );

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

logical LDBHandle :: FlushCluster (acb *acbptr )
{


BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( current_rb->FlushCluster(acbptr) );
RECOVER
  return(YES);
ENDSEQ


}

/******************************************************************************/
/**
\brief  FlushClusterPool - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushClusterPool"

logical LDBHandle :: FlushClusterPool ( )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( current_rb )
    return(current_rb->FlushClusterPool());
RECOVER
  return(YES);
ENDSEQ
  return(NO);
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

logical LDBHandle :: GenerateServerEvent (EntryEvent *ev_ptr )
{

  return( root_base->GenerateServerEvent(ev_ptr) );

}

/******************************************************************************/
/**
\brief  GetDatabaseID - 



\return db_id - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDatabaseID"

int32 LDBHandle :: GetDatabaseID ( )
{

  return ( database_info->get_db_number() );

}

/******************************************************************************/
/**
\brief  GetEBI - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

logical LDBHandle :: GetEBI (acb *acbptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return ( current_rb->GetEBI(acbptr) ? NO : YES );

RECOVER
  return(YES);
ENDSEQ
 

}

/******************************************************************************/
/**
\brief  GetInstInfo - 



\return cond - 

\param  entnr - 
\param  sid_ref - 
\param  otype_ref - 
\param  delind_ref - 
\param  modcount_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstInfo"

logical LDBHandle :: GetInstInfo (EB_Number entnr, int16 &sid_ref, char &otype_ref, logical &delind_ref, int16 &modcount_ref )
{
  EBI        *ebiptr;
  acb         acbenty(entnr,0);
  logical     cond = YES;
BEGINSEQ
  sid_ref      = 0;
  otype_ref    = UNDEF;
  delind_ref   = NO;
  modcount_ref = UNDEF;
  
  if ( !(ebiptr = current_rb->IntGetEBI(&acbenty)) )  ERROR
  if ( ebiptr->stscusr1() )                          ERROR
  
  if ( acbenty.stscdel() )
  {
    acbenty.stsrdel();
    delind_ref = YES;
  }
  
  if ( acbenty.GetPosition() ) 
    if ( !current_rb->Locate(&acbenty,sizeof(ieh)) )  ERROR
  
  if ( delind_ref )
    acbenty.stssdel();

  sid_ref      = abs(acbenty.get_acbieh().get_iehsid());
  otype_ref    = acbenty.get_acbieh().get_iehtyp();
  modcount_ref = acbenty.get_mod_count();
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetInstStat - 



\return instlen - 

\param  entnr - 
\param  iehptr - 
\param  delind_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstStat"

int32 LDBHandle :: GetInstStat (EB_Number entnr, ieh *iehptr, logical &delind_ref )
{
  ieh      *iehpt   = NULL;
  int32  instlen  = 0;
  logical   deleted = NO; 
  logical   lockind;
  ieh       iehentry(UNDEF,UNDEF);
  ieh       tempieh(UNDEF,UNDEF);
BEGINSEQ

//  if ( ebsnum <= idbebs->ebshlnrg() )
  {
    SDBRESET 

    lockind = NO;
    delind_ref = NO;
/*
    if ( !(iehpt = (ieh *)current_rb->Locate(acbptr,&instlen,NO)) )
    {
      iehpt  = &iehentry;
      if ( SDBERROR == 3 )
      {
        delind_ref = YES;
        if ( !current_rb->Undelete(acbptr) )
        {
	  iehpt   = (ieh *)current_rb->Locate(acbptr,&instlen,NO);
          tempieh = *iehpt;
          iehpt   = &tempieh;
          current_rb->Delete(acbptr,YES);
        }
      }  
      if ( SDBERROR == 6 )
        lockind = YES;
    }
  *iehptr = *iehpt;
*/
  }


RECOVER

ENDSEQ
  return(instlen);

}

/******************************************************************************/
/**
\brief  GetLength - 



\return instlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 LDBHandle :: GetLength (acb *acbptr )
{
//  int32           size;

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
//  if ( !(size = current_rb->Get_Length(acbptr)) )   ERROR
  return ( current_rb->Get_Length(acbptr) );

RECOVER
  return(AUTO);
ENDSEQ
//  return(size-IEH);

}

/******************************************************************************/
/**
\brief  GetLocalDBHandle - 



\return ldbhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalDBHandle"

LDBHandle *LDBHandle :: GetLocalDBHandle ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  GetMainBase - 



\return mbnumber - MainBase number

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMainBase"

int16 LDBHandle :: GetMainBase (acb *acbptr )
{

  return(acbptr->get_ebsnum().IsEmpty(pif) ? 0 : current_rb->GetMBNumber(acbptr->get_ebsnum()));

}

/******************************************************************************/
/**
\brief  GetNewTypeID - 



\return sid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNewTypeID"

int16 LDBHandle :: GetNewTypeID ( )
{
  int16                   sid = UNDEF;
BEGINSEQ
  if ( LockHeader() )                                SDBERR(6)
  if ( ReadHeader() )                                ERROR

  db_header->set_last_str_num(sid=db_header->get_last_str_number()+1);
  if ( WriteHeader() )                               ERROR
RECOVER
  sid = UNDEF;
ENDSEQ
  UnlockHeader();
  return(sid);
}

/******************************************************************************/
/**
\brief  GetNextWSNumber - 



\return wsnumber - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextWSNumber"

int32 LDBHandle :: GetNextWSNumber ( )
{
  int32            wsnumber = 0;
BEGINSEQ
  if ( LockHeader() )                                SDBERR(6)
  if ( ReadHeader() )                                ERROR

  wsnumber = db_header->get_next_ws_number();
  db_header->inc_next_ws_number();
  
  if ( WriteHeader() )                               ERROR
RECOVER
  wsnumber = 0;
ENDSEQ
  UnlockHeader();
  return(wsnumber);
}

/******************************************************************************/
/**
\brief  GetRecoveryFile - Provide name of recovery file



\return rfilname - 

\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryFile"

char *LDBHandle :: GetRecoveryFile (uint16 recnum )
{
  static   char  rfilname[13];
  char          *filname = NULL;
BEGINSEQ
  if ( !this )                                     SDBERR(70)
  memset(rfilname,0,13);

  if ( !recnum )
    recnum = db_header->get_recover_number();

  if ( recnum < db_header->get_recover_first() || 
       recnum > db_header->get_recover_number()      )
    recnum = 0;
  filname = recnum ? rvr::rvrfngt(rfilname,recnum) : NULL;
RECOVER

ENDSEQ
  return (filname);
}

/******************************************************************************/
/**
\brief  GetRecoveryHdl - 



\return rec_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryHdl"

rvr *LDBHandle :: GetRecoveryHdl ( )
{
  int        rec_number;
  rvr       *rec_handle = recovery_handle;
BEGINSEQ
  if ( !recovery_handle )                            LEAVESEQ

  if ( LockHeader() )                                ERROR
  if ( ReadHeader() )                                ERROR

  if ( db_header->get_save_transaction() )  // temp. recovery
  {
    db_header->set_write_ta(db_header->get_write_transact()+1);
    rec_number = db_header->get_write_transact();
    if ( recovery_handle->Open(rec_number) )         ERROR
  }
  recovery_handle->StartTA();  

  if ( WriteHeader() )                               ERROR

RECOVER
  rec_handle = NULL;
ENDSEQ
  if ( recovery_handle )
    UnlockHeader();
  return(rec_handle);
}

/******************************************************************************/
/**
\brief  GetRecoveryNum - Provide number for current recovery file



\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryNum"

uint16 LDBHandle :: GetRecoveryNum ( )
{
  uint16    recnum = 0;
BEGINSEQ
  if ( !this )                                    SDBERR(70)
  recnum = db_header->get_recover_number();
RECOVER

ENDSEQ
  return(recnum);
}

/******************************************************************************/
/**
\brief  GetRecoveryPath - Provide path for recovery folder



\return recpath - Recovery path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryPath"

char *LDBHandle :: GetRecoveryPath ( )
{
  char     *path = NULL;
BEGINSEQ
  if ( !this )                                    SDBERR(70)
  path = db_header->get_recover_path();
RECOVER

ENDSEQ
  return(path);
}

/******************************************************************************/
/**
\brief  GetRecoveryStartNumber - Get number for first recovery file



\return recnum - Numer of recovery file

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryStartNumber"

uint16 LDBHandle :: GetRecoveryStartNumber ( )
{
  uint16    recnum = 0;
BEGINSEQ
  if ( !this )                                    SDBERR(70)
  recnum = db_header->get_recover_first();
RECOVER

ENDSEQ
  return(recnum);
}

/******************************************************************************/
/**
\brief  GetRecoveryType - 



\return rec_type - Type of recovery support

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecoveryType"

RecoveryType LDBHandle :: GetRecoveryType ( )
{
  RecoveryType    rec_type = RECOVERY_none;
BEGINSEQ
  if ( !this )                                    SDBERR(70)
 
   if ( db_header->get_recover_write() )
     rec_type = RECOVERY_Full;
   else if ( db_header->get_save_transaction() )  
     rec_type = RECOVERY_Transaction;

RECOVER

ENDSEQ
  return(rec_type);
}

/******************************************************************************/
/**
\brief  GetRootBase - 



\return rootbase - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRootBase"

db_RootBase *LDBHandle :: GetRootBase (exd *exdptr )
{
  db_RootBase  *rb = current_rb;
BEGINSEQ
//  return( exdptr && exdptr->get_shadow_base() ? shadow_rb : current_rb);

  if ( !exdptr )                                     LEAVESEQ
  
  if ( exdptr->get_shadow_base() )
    rb = shadow_rb;
  else if ( exdptr->get_exdacb()->get_locate_exact() )
    rb = GetRootBase(exdptr->get_exdacb()->get_ws_level());

ENDSEQ
  return(rb);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  wslevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRootBase"

db_RootBase *LDBHandle :: GetRootBase (uint8 wslevel )
{

  return( wslevel == 255 ? root_base : root_base->GetRootBase(wslevel) );

}

/******************************************************************************/
/**
\brief  GetSchemaVersion - 



\return schemaversion - Scheme version

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSchemaVersion"

uint16 LDBHandle :: GetSchemaVersion ( )
{

  return( (Dictionary *)this == dictionary 
          ? GetCurrentSystemVersion() 
          : db_header->get_schema_version() );

}

/******************************************************************************/
/**
\brief  GetShadowRB - 



\return cpath - Complete path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetShadowRB"

char *LDBHandle :: GetShadowRB ( )
{
  char                 *cpath = NULL;
BEGINSEQ
  if ( !(cpath = ProvideShadowRBPath(YES)) )         ERROR
  
  if ( *cpath <= ' ' )                               SDBERR(331)
RECOVER
  cpath = NULL;
ENDSEQ
  return(cpath);
}

/******************************************************************************/
/**
\brief  GetStats - Provide entry statistics



\return term - Termination code

\param  rootbase - 
\param  typeinfo - 
\param  acbptr - 
\param  pif - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStats"

logical __cdecl LDBHandle :: GetStats (db_RootBase *rootbase, DPA(StatEntry) &typeinfo, acb *acbptr, logical pif )
{
  logical                 deleted = NO;
  uint16                  sid;
  uint32                  hcount  = 0;
  uint32                  hsize   = 0;
  uint64                  vpos;
  logical                 term    = NO;
BEGINSEQ
  if ( acbptr->stscdel() )
  {
    acbptr->stsrdel();
    deleted = YES;
  }
  
  if ( acbptr->GetPosition() ) 
    if ( !rootbase->Locate(acbptr,sizeof(ieh)) )    ERROR
  
  acb   vacb(*acbptr);
  *(EBI *)&vacb = *(EBI *)acbptr;
  while ( vpos = vacb.get_version_list() )
  {
    vacb.set_ebi_position(vpos);
    if ( !rootbase->GetEBI(&vacb) )         
      vacb.SetVersionList(0);
    else
    {
      hcount++;
      hsize += vacb.get_entry_length();
    }
  }

  
  if ( deleted )
    acbptr->stssdel();

  if ( sid = abs(acbptr->get_acbieh().get_iehsid()) )
  {
    if ( typeinfo.GetSize() <= sid || !typeinfo[sid] )
      typeinfo.SetAtGrow(sid,new StatEntry);
    typeinfo[sid]->Update(acbptr,hcount,hsize);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetSystemVersion - 



\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemVersion"

uint16 LDBHandle :: GetSystemVersion ( )
{

  return(this && db_header ? db_header->get_system_version() 
                           : GetCurrentSystemVersion()       );

}

/******************************************************************************/
/**
\brief  GetTempMain - 



\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTempMain"

int16 LDBHandle :: GetTempMain ( )
{

  return ( current_rb->get_temp_main() );

}

/******************************************************************************/
/**
\brief  GetUsedLength - 



\return instlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedLength"

int32 LDBHandle :: GetUsedLength (acb *acbptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return ( !current_rb->Locate(acbptr,IEH) 
           ? AUTO 
           : acbptr->get_acbieh().get_iehlen() );

RECOVER
  return(AUTO);
ENDSEQ

}

/******************************************************************************/
/**
\brief  GetVersionString - 



\return version_string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersionString"

char *LDBHandle :: GetVersionString ( )
{

  return( database_info->GetVersionString() );

}

/******************************************************************************/
/**
\brief  GetWorkspace - Get Workspace

        The  fuction  checks  the  workspace  for the name passed. When an empty
        user-name  is passed the function returns the user name in the user-name
        field, which must contain at least 81 bytes.

\return names - 

\param  ws_root - 
\param  lindx0 - 
\param  user_name - 
\param  names - 
\param  refresh - 
\param  ws_info - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspace"

char *LDBHandle :: GetWorkspace (char *ws_root, int32 lindx0, char *user_name, char *names, logical refresh, char *ws_info )
{
  int32                indx    = 0;
  int32                rblevel = 0;
  eb_RootBase         *eb_rootbase = NULL;
  char               *wsnames = NULL;
  SDB_Workspace     *ws_entry;
BEGINSEQ
  if ( !(eb_rootbase = root_base->IsODABARootBase()) )
                                                     ERROR
  if ( db_header->get_next_ws_number() <= 0 )        ERROR

  if ( refresh || !eb_rootbase->get_ws_list() )
    if ( InitWSList(refresh) )                       ERROR
  
  rblevel = root_base->get_level();
  
  if ( ws_root && *ws_root > ' ' )
    if ( !OpenWorkspace(ws_root,user_name,NO) )      ERROR
  
  if ( !(ws_entry = eb_rootbase->GetWorkspace(lindx0,user_name,refresh)) )
                                                     ERROR
  if ( names )
    gvtxbts(names,ws_entry->get_name(),128);
  
  nstring.SetString(ws_entry->get_name(),128);
  wsnames = nstring;
  if ( user_name && !*user_name )
    gvtxbts(user_name,ws_entry->get_user(),80);

  if ( ws_info )
    ws_entry->Fill(ws_info);
RECOVER
  wsnames = NULL;
ENDSEQ
  while ( rblevel && rblevel < root_base->get_level() )
    CloseWorkspace();
  return(wsnames);
}

/******************************************************************************/
/**
\brief  GetWorkspaceLevel - 



\return wslevel - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspaceLevel"

uint8 LDBHandle :: GetWorkspaceLevel ( )
{

  return ( root_base ? root_base->get_level() : AUTO );

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

int32 LDBHandle :: GetWorkspaceNumber (char *names )
{

  return( root_base->GetWorkspaceNumber(names) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  wslevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspaceNumber"

int32 LDBHandle :: GetWorkspaceNumber (uint8 wslevel )
{
  db_RootBase        *rb;
  int32                wsnumber = 0;
BEGINSEQ
  if ( !wslevel )                                    LEAVESEQ

  if ( wslevel == AUTO )
    wsnumber = root_base->GetWorkspaceNumber();
  else
  {
    if ( !(rb = root_base->GetRootBase(wslevel)) )   ERROR
    wsnumber = ((Workspace *)rb)->get_ws_number();
  }
RECOVER
  wsnumber = AUTO;
ENDSEQ
  return(wsnumber);
}

/******************************************************************************/
/**
\brief  Get_Mod - 



\return modcnt - 

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get_Mod"

uint8 LDBHandle :: Get_Mod (exd *exdptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  exdptr->ResetACB(0);
  return ( current_rb->Get_Mod(exdptr->get_exdacb()) );
RECOVER
  return(UNDEF);
ENDSEQ
 

}

/******************************************************************************/
/**
\brief  HasWorkspace - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasWorkspace"

logical LDBHandle :: HasWorkspace ( )
{

  return(root_base ? root_base->IsWorkspace() : NO);

}

/******************************************************************************/
/**
\brief  IgnoreSharedRB - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IgnoreSharedRB"

void LDBHandle :: IgnoreSharedRB ( )
{

  if ( this && root_base )
    root_base->IgnoreSharedRB();

}

/******************************************************************************/
/**
\brief  InitDataArea - Initialise DataArea



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

logical LDBHandle :: InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{
  logical                 term = NO;
BEGINSEQ
  current_rb->Open(db_path,YES,NO,YES);               SDBCERR
          
  if ( current_rb->InitDataArea(mbnumber,sbnumber,danumber,
                               filename,dasize,server) )
                                                     SDBCERR
  current_rb->Close();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitMainBase - Initialize MainBase



\return term - Termination code

\param  mbnumber - MainBase number
\param  filename - File name for DataArea file
\param  lowEBN - First entry number in database
\param  highEBN - Last entry number in database
\param  dasize - Size of data area in byte
\param  server - Name for MainBase server
\param  headerpt - Header-Pointer
\param  largedb - Indicates a large database
\param  pindep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitMainBase"

logical LDBHandle :: InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize, char *server, EB_Header *headerpt, logical largedb, logical pindep )
{
  logical     term = NO;
BEGINSEQ
  current_rb->Open(db_path,YES,NO,YES);               SDBCERR
      
  if ( current_rb->InitMainBase(mbnumber,filename,
                                dasize,server,headerpt,pindep) )
                                                     SDBCERR
  current_rb->Close();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitRecovery - Initialise recovery file



\return term - Termination code

\param  recpath - Recovery path
\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRecovery"

logical LDBHandle :: InitRecovery (char *recpath, uint16 recnum )
{
  logical   rnew = recovery_handle ? NO : YES;
  logical   term = NO;

BEGINSEQ
  if ( !this )                                     SDBERR(70)

  if ( access_mode == PI_Read )                    SDBERR(120)
  if ( LockHeader() || ReadHeader() )              ERROR
  
  if ( !recovery_handle )
    if ( !(recovery_handle = new rvr(db_header->get_recover_path(),
                                     db_header->get_recover_number(),
                                     NULL,UNDEF,net_option,WT)) )
                                                   SDBERR(95)
                                                   SDBCERR
  db_header->set_recover_writ(NO);
  db_header->set_save_ta(NO);
  if ( recnum )
    db_header->set_recover_writ(YES);
  else if ( recpath )
    db_header->set_save_ta(YES);

  db_header->set_recover_numb(recnum);

  db_header->set_recover_path(recpath);

  if ( recnum )   // mit LOG datei
  {
    if ( !db_header->set_recover_numb(recovery_handle->rvrcrt(
             db_header->get_recover_path(),db_header->get_recover_number())) )
                                                   SDBERR(115)
    db_header->set_recover_fst();
  }

  if ( WriteHeader() || UnlockHeader()  )          SDBERR(115)

RECOVER
  rnew = YES;
  term = YES;
ENDSEQ
  if ( rnew )
    CloseRecovery();
  return(term);

}

/******************************************************************************/
/**
\brief  InitSubBase - Initialise SubBase



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

logical LDBHandle :: InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize, char *server, EB_Header *headerpt )
{
  logical                 term = NO;
BEGINSEQ
  current_rb->Open(db_path,YES,NO,YES);               SDBCERR
        
  if ( current_rb->InitSubBase(mbnumber,sbnumber,filename,
                              dasize,server) )       SDBCERR
  
  current_rb->Close();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitWSList - 



\return term - Termination code

\param  refresh - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitWSList"

logical LDBHandle :: InitWSList (logical refresh )
{
  eb_RootBase            *eb_rootbase = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(eb_rootbase = root_base->IsODABARootBase()) )
                                                     ERROR
  if ( db_header->get_next_ws_number() <= 0 )        SDBERR(329)
    
  if ( eb_rootbase->InitWSList(this) )               ERROR
  
  if ( !refresh )                                    LEAVESEQ

  eb_rootbase->get_ws_list()->Refresh();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dict_ptr - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  online_version - 
\param  version_nr - Internal version number
\param  sysenv - System application
\param  is_server - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void LDBHandle :: Initialize (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, logical online_version, uint16 version_nr, char sysenv, logical is_server )
{
  extern OPAGlobals  opa_globals;
  UtilityHandle     *utility_cb = UtilityControlBlock();
  eb_RootBase       *rootbase = NULL;
  logical            lic_req  = YES;
  char               applnames[41];
  int                saverr;
BEGINSEQ
  SDBCERR

  DBHandle::Initialize(dict_ptr,cpath,accopt,netopt,version_nr,sysenv);
  LACObject::Initialize(this,accopt,version_nr,is_server);

  local_dbhandle = this;
  
  if ( dict_ptr )
    local_dictionary = dict_ptr->GetLocalDictionary();

  SDBEV1("",UNDEF)
  if ( !cpath || !*cpath )                           SDBERR(5)
    
  strncpy((char *)memset(db_path,0,sizeof(db_path)),cpath,sizeof(db_path)-1);
  SDBEV1(db_path,UNDEF)
  
  if ( !(header_acb = (acb *)msmgs(sizeof(acb)+sizeof(DBHeader)-IEH)) )
                                                     SDBERR(95)
  db_header = (DBHeader *)&header_acb->get_acbieh();
  
  if ( utility_cb && *utility_cb->sdbuname > ' ' )
    gvtxbts(applnames,utility_cb->sdbuname,sizeof(utility_cb->sdbuname));
  else
    *applnames = 0;
  
  database_info = new DBInfo(this,*applnames ? applnames : NULL);
  if ( Open(dict_ptr,NULL,cpath,accopt,netopt,online_version,sysenv) ) ERROR
      
  if ( TestSysVariable("NO_LICENCE_REQ","YES") )
    lic_req = NO;
  
  CreateContext();
  if ( global_object )
    global_object->SetupContext(context);
  if ( context && context->ExecuteAction(DBP_Open) )
  {
    SDBCERR
    SDBCTXCERR
    SDBERR(99)
  }
  if ( lic_req && database_info->IsExpired() )       SDBERR(314)
  if ( lic_req && !database_info->get_licenced() )   SDBERR(317)
  if ( database_info->GetMaxUsers() == 1 && netopt )
  {
    CloseDBHandle();
    netopt = NO;
  }
  
  if ( !root_base )
    if ( Open(dict_ptr,NULL,cpath,accopt,netopt,online_version,sysenv) ) ERROR

  strncpy(db_path,root_base->GetRootBase(0)->get_root_path(),sizeof(db_path)-1);
  if ( db_header->get_recover_write() || db_header->get_save_transaction() )
    if ( OpenRecovery(0,0) )                         ERROR
 
  if ( db_header->get_recover_pos() > 0 )
  {
    if ( net_option )
    {
      access_mode = PI_Read;
      ACObject::access_mode = PI_Read;
      SDBSET(224)
      SDBError().DisplayMessage();
    }
    if ( access_mode != PI_Read )
      if ( StoreRecovery() )                           ERROR
  }
// die ressource muß noch angelegt werden!
  if ( context )
  {
    context->ExecuteAction(DBO_Opened);
    context->SetProcessState(PRC_Opened);
  }
RECOVER
  saverr = SDBERROR;
  CloseDBHandle();
  SDBISET(saverr);
ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 



\param  dictptr - Dictionary handle
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void LDBHandle :: Initialize (Dictionary *dictptr, PIACC accopt )
{
  logical         pif = NO;
BEGINSEQ
// 
  DBHandle::Initialize(dictptr,accopt);
  LACObject::Initialize(this,accopt);
  
  SDBCERR
 
  local_dbhandle = this;
  
  if ( dictptr )
  {
    dictionary = dictptr;
    local_dictionary = dictptr->GetLocalDictionary();
  }
  if ( !(header_acb = (acb *)msmgs(sizeof(acb)+sizeof(DBHeader)-IEH)) )
                                                     SDBERR(95)
  if ( local_dictionary )
    pif = local_dictionary->get_current_rb()->IsPIF();
    
  header_acb->set_ebsnum(BigToPIF(1,pif));
  db_header = (DBHeader *)&header_acb->get_acbieh();
  
// sonst müsen wir dictionary eintragen, damit das freigegeben wird
//  if ( dictptr )
//    dictptr->AddHandle(this);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  IsLicenced - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsLicenced"

logical LDBHandle :: IsLicenced ( )
{

  return( database_info->get_licenced() );

}

/******************************************************************************/
/**
\brief  IsPIF - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPIF"

logical LDBHandle :: IsPIF ( )
{

  return(root_base ? root_base->IsPIF() : NO);

}

/******************************************************************************/
/**
\brief  IsRBLocked - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRBLocked"

logical LDBHandle :: IsRBLocked ( )
{

  return ( this && current_rb ? current_rb->IsLocked() : NO );

}

/******************************************************************************/
/**
\brief  IsSaveTransact - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSaveTransact"

logical LDBHandle :: IsSaveTransact ( )
{

  return(db_header->get_save_transaction());

}

/******************************************************************************/
/**
\brief  LDBHandle - Create a database handle



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dict_ptr - Dictionary handle
\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  online_version - 
\param  version_nr - Internal version number
\param  sysenv - System application
\param  is_server - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDBHandle"

     LDBHandle :: LDBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, logical online_version, uint16 version_nr, char sysenv, logical is_server )
                     : DBHandle (),
LACObject (),
ACObject(), 
  header_acb(NULL),
  db_header(NULL), 
  ms_pool(NULL), 
  root_base(NULL),
  recovery_handle(NULL), 
  database_info(NULL),
  local_dictionary(NULL),
  shadow_rb_acb(NULL),
  shadow_rb(NULL),
  current_rb(NULL)
{

BEGINSEQ
  SDBCERR
  
  Initialize(dict_ptr,cpath,accopt,netopt,online_version,version_nr,sysenv,is_server);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i03 - 



\param  dict_ptr - Dictionary handle
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDBHandle"

     LDBHandle :: LDBHandle (Dictionary *dict_ptr, PIACC accopt )
                     : LACObject (),
ACObject(), 
  header_acb(NULL),
  db_header(NULL), 
  ms_pool(NULL), 
  root_base(NULL),
  recovery_handle(NULL), 
  database_info(NULL),
  local_dictionary(NULL),
  shadow_rb_acb(NULL),
  shadow_rb(NULL),
  current_rb(NULL)

{

  Initialize(dict_ptr,accopt);

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDBHandle"

     LDBHandle :: LDBHandle ( )
                     : LACObject (),
ACObject (), 
  header_acb(NULL),
  db_header(NULL),
  ms_pool(NULL),
  root_base(NULL),
  recovery_handle(NULL),
  database_info(NULL),
  local_dictionary(NULL),
  shadow_rb_acb(NULL),
  shadow_rb(NULL),
  current_rb(NULL)

{

  local_dbhandle = this;
  memset(db_path,0,sizeof(db_path)); 


}

/******************************************************************************/
/**
\brief  i2 - 



\param  cpath - Complete path
\param  dasize - Size of data area in byte
\param  pindep - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LDBHandle"

     LDBHandle :: LDBHandle (char *cpath, int32 dasize, logical pindep )
                     : LACObject (),
ACObject (), 
  header_acb(NULL),
  db_header(NULL),
  ms_pool(NULL),
  root_base(NULL),
  recovery_handle(NULL),
  database_info(NULL),
  local_dictionary(NULL),
  shadow_rb_acb(NULL),
  shadow_rb(NULL),
  current_rb(NULL)
{

BEGINSEQ
  local_dbhandle = this;
  
  if ( eb_RootBase::InitRootBase(cpath,dasize,pindep) )
                                                     SDBCERR
  strncpy(db_path,cpath,64);
  if ( !(root_base = new eb_RootBase(NO,NO)) )       SDBERR(95)
  current_rb = root_base;
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  LocateWorkspace - 



\return term - Termination code

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateWorkspace"

logical LDBHandle :: LocateWorkspace (char *names )
{
  eb_RootBase            *eb_rootbase = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(eb_rootbase = root_base->IsODABARootBase()) )
                                                     ERROR
  if ( !eb_rootbase->get_ws_list() )
    if ( InitWSList(YES) )                           ERROR
  
  if ( !eb_rootbase->ExistWorkspace(names) )         ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical LDBHandle :: Lock (acb *acbptr )
{


BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( !net_option ? NO : current_rb->Lock(acbptr,YES) );
RECOVER
  return(YES);
ENDSEQ


}

/******************************************************************************/
/**
\brief  LockHeader - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockHeader"

logical LDBHandle :: LockHeader ( )
{

  return( current_rb->GetRootBase(0)->Lock(header_acb,YES) );

}

/******************************************************************************/
/**
\brief  LockInternal - 



\return term - Termination code

\param  exdptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical LDBHandle :: LockInternal (exd *exdptr, logical wait )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( !net_option ? NO : GetRootBase(exdptr)->LockInternal(exdptr->get_exdacb(),wait));
RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  LockKey - 



\return term - Termination code

\param  entnr - 
\param  db_index - 
\param  keyptr - 
\param  owner_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockKey"

logical LDBHandle :: LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{
  logical           term = NO;
BEGINSEQ
  if ( !root_base )                                  LEAVESEQ
    
  if ( !root_base->get_key_cache() )
    root_base->InitKeyCache(this);
    
  term =  root_base->LockKey(entnr,db_index,keyptr,owner_id);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LockRB - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockRB"

logical LDBHandle :: LockRB ( )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( !net_option ? NO : current_rb->ILock());
RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  Open - 



\return new_db - 

\param  dict_ptr - Dictionary handle
\param  rootbase - 
\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  online_version - 
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical LDBHandle :: Open (Dictionary *dict_ptr, db_RootBase *rootbase, char *cpath, PIACC accopt, logical netopt, logical online_version, char sysenv )
{
  extern OPAGlobals opa_globals;
  logical       new_db  = NO;
  logical       shared_rb = opa_globals.RootBaseShared();
  uint16        schema_version;
  char          msg[512];
  char          str1[16];
  char          str2[16];
  logical       ws;
  logical       term    = NO;
BEGINSEQ
  db_handle = this;
  db_hdl    = this;
  
  if ( shared_rb )
  {
    accopt = PI_Write;
    netopt = 2;     
  }

  if ( !(root_base = OpenRootBase(cpath,accopt,netopt,sysenv)) )
                                                     ERROR
  current_rb = root_base;
  pif = current_rb->IsPIF();
  header_acb->set_ebsnum(BigToPIF(1,pif));
  if ( !root_base->Locate(header_acb,sizeof(DBHeader)) )    
  {
    if ( SDBERROR == 6 )                             SDBERR(4)
    SDBSET(98)
    SDBError().DisplayMessage();
    SDBError().TraceMessage(cpath);
    SDBRESET
    
    header_acb->set_ebsnum(0);
    *db_header = DBHeader();
    db_header->set_system_version(GetCurrentSystemVersion());
    if ( WriteHeader() )                             ERROR
    new_db = YES;
  }
  else
    if ( ReadHeader() )                              ERROR

  if ( ws = (db_header->get_next_ws_number() > 0) ) // running with workspaces
    if ( OpenWorkspace("WS0","SysAdmin",NO,NULL) )   ERROR
  
  if ( !db_header->get_shadow_db().IsEmpty() ) // running with shadow
  {
    if ( !(shadow_rb = OpenRootBase(GetShadowRB(),accopt,netopt,sysenv)) )
                                                     ERROR
  }
  else
    if ( ws )                                        SDBERR(99)
  
  if ( VersionCheck() )                              ERROR
  if ( dict_ptr )
  {
    if ( (schema_version = dict_ptr->GetVersion()) != CUR_VERSION ) // kein internes Dictionary
    {
      if ( !new_db && (!TestSysVariable("ONLINE_VERSION","YES") && !online_version ) )
      {
        if ( dict_ptr->GetVersion() != db_header->get_schema_version() )
        { 
          SDBError().TraceMessage("!!! running old dictionary version for: ");
          SDBError().TraceMessage(dict_ptr->GetPath());
          SDBError().TraceMessage(db_path);
          strcat(strcat(strcat(strcpy(msg," Schema Version: "),gvtxitoa(db_header->get_schema_version(),str1,10)),", Dictionary Version: "),gvtxitoa(dict_ptr->GetVersion(),str2,10));
          SDBError().TraceMessage(msg);
        }
        if ( dict_ptr->SetVersion(db_header->get_schema_version()) )
                                                     ERROR
        dict_ptr->UpdateVersionList();
      }
      schema_version = dict_ptr->GetVersion();
    }
    else
      schema_version = db_header->get_schema_version();
      
    if ( schema_version < db_header->get_schema_version() )
                                                     SDBERR(231)
    if ( schema_version > db_header->get_schema_version() )
    {
      if ( !new_db )
      {
        SDBSET(accopt == PI_Write ? 232 : 233)
        SDBError().DisplayMessage();
      }
      db_header->set_schema_vers(schema_version);
      if ( accopt == PI_Write )
        if ( WriteHeader() )                         ERROR
    }
    if ( OpenRootObject() )                          ERROR
    dict_ptr->AddHandle(this);
    if ( access_mode > PI_Read )
      SetupTypeID(dict_ptr->GetLastStructureID());
    db_header->set_schema_vers(schema_version);  // wurde gerade wieder zurückgesetzt (durch Lesen)
  }
  else
    if ( new_db || db_header->get_schema_version() < GetCurrentSystemVersion() )
    {
      db_header->set_schema_vers(GetCurrentSystemVersion());
      if ( accopt == PI_Write )
        if ( WriteHeader() )                         ERROR
    }

  SDBRESET
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenRecovery - Open recovery file



\return term - Termination code

\param  userinfo - Area for application recovery information
\param  uilen - Length of application data area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenRecovery"

logical LDBHandle :: OpenRecovery (char *userinfo, int16 uilen )
{
  logical      term = NO;

BEGINSEQ
  if ( !this )                                       SDBERR(70)

  if ( access_mode == PI_Read )                      LEAVESEQ
  
  if ( recovery_handle )
    recovery_handle->rvrsup(userinfo,uilen);
  else
    if ( !(recovery_handle = new rvr(db_header->get_recover_path(),
                                     db_header->get_recover_number(),
                                     userinfo,uilen,net_option,YES,
                                     db_header->get_recover_write())) )
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER
  CloseRecovery();
  term   = YES;
ENDSEQ
  SOSRESET
  return(term);

}

/******************************************************************************/
/**
\brief  OpenRootBase - 



\return rootbase - 

\param  cpath - Complete path
\param  accopt - Access mode
\param  netopt - Multi-user access
\param  sysenv - System application
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenRootBase"

db_RootBase *LDBHandle :: OpenRootBase (char *cpath, PIACC accopt, logical netopt, char sysenv )
{
  extern OPAGlobals  opa_globals;
  db_RootBase       *rootbase = NULL;
  logical            term = NO;
  db_RootBase       *rb = NULL;
BEGINSEQ
  if ( opa_globals.RootBaseShared() )
  {
    opa_globals.ILockGlobal();
    if ( !(rootbase = opa_globals.ProvideRootBase(database_info->GetDBIdent(),cpath)) )
    {
      rb = new eb_RootBase(netopt,YES);
      if ( !(term = rb->Provide(cpath,accopt,YES,sysenv)) )
      {
        rootbase = rb;
        opa_globals.RegisterRootBase(rootbase,database_info->GetDBIdent(),cpath);
      }
    }
    else
      rootbase->ReferenceObject::Reserve();
    opa_globals.IUnlockGlobal();
    if ( term )                                      ERROR
  }
  else
    rb = CreateRootBase(cpath,accopt,netopt,sysenv);
  
  if ( rb )
  {
    rootbase = rb;
    data_version = rootbase->GetDataVersion();
  }
RECOVER
  delete rootbase;
  rootbase = NULL;
ENDSEQ
  return(rootbase);
}

/******************************************************************************/
/**
\brief  OpenRootObject - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenRootObject"

logical LDBHandle :: OpenRootObject ( )
{
  logical   locked = NO;
  logical   term   = NO;

BEGINSEQ
  if ( db_header->get_root_objekt().IsEmpty() )
  {
    if ( access_mode != PI_Write )                    SDBERR(61)
    if ( LockHeader() )                               SDBERR(4)
    locked = YES;
    if ( db_header->set_root_objekt(CreateObjInst()).IsEmpty() )   
                                                      ERROR
    if ( WriteHeader() )                              ERROR
    UnlockHeader();
    locked = NO;
  }
  if ( LACObject::Open(db_header->get_root_objekt(),NULL) ) 
                                                      ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( locked )
    UnlockHeader();
  return(term);
}

/******************************************************************************/
/**
\brief  OpenWorkspace - 



\return term - Termination code

\param  names - 
\param  user_name - 
\param  exclusive - 
\param  cpath_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenWorkspace"

logical LDBHandle :: OpenWorkspace (char *names, char *user_name, logical exclusive, char *cpath_w )
{
  extern OPAGlobals       opa_globals;
  Workspace              *workspace;
  db_RootBase            *rootbase = NULL;
  char                   *pos;
  char                    cpath[256];
  logical                 term = NO;
BEGINSEQ
  if ( ta_buffer )                                   SDBERR(328)
// muss eigentlich fuer alle LACObjects geprueft werden

  if ( pos = STRSearchChar(names,'.',YES) )
  {
    *pos = 0;
    if ( OpenWorkspace(names,user_name,NO,cpath_w) ) ERROR
    *pos = '.';
    names = pos+1;
  }
  if ( !root_base )                                  ERROR
    
  if ( InitWSList(YES) )                             ERROR
    
  if ( !cpath_w || !*cpath_w )
  {
    strcpy(cpath,root_base->GetRootBase(0)->get_root_path());
    gvtsexc(cpath,"\\","/",UNDEF);
    cpath_w = cpath;
  }
  if ( !(cpath_w = root_base->ProvideWorkspace(names,user_name,cpath_w)) )
                                                     SDBERR(325)
  
  if ( opa_globals.RootBaseShared() )
  {
    if ( !(rootbase = opa_globals.ProvideRootBase("_WORKSPACE",cpath_w)) )
    { 
      if ( !(rootbase = (eb_RootBase *)root_base->OpenWorkspace(this,names,user_name,cpath_w,exclusive)) )
                                                     ERROR
      opa_globals.RegisterRootBase(rootbase,"_WORKSPACE",cpath_w);
    }
  }
  else
    if ( !(rootbase = (eb_RootBase *)root_base->OpenWorkspace(this,names,user_name,cpath_w,exclusive)) )
                                                     ERROR

  root_base = rootbase;
  if ( current_rb != shadow_rb )
    current_rb = root_base;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideShadowRBPath - 



\return cpath - Complete path

\param  read_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideShadowRBPath"

char *LDBHandle :: ProvideShadowRBPath (logical read_opt )
{
  char                   *cpath = NULL;
BEGINSEQ
  if ( !shadow_rb_acb )
  { 
    if ( !(shadow_rb_acb = (acb *)msmgs(sizeof(acb)+sizeof(SDB_Dataset))) )
                                                     SDBERR(95)
    shadow_rb_acb->set_ebsnum(db_header->get_shadow_db());
    shadow_rb_acb->SetIEH(sizeof(SDB_Dataset),386,UNDEF,0);
  }
  
  if ( read_opt )
    if ( !root_base->GetRootBase(0)->Locate(shadow_rb_acb,sizeof(SDB_Dataset)+IEH) ) 
                                                     SDBERR(330)
  
  cpath = ((SDB_Dataset *)shadow_rb_acb->GetInstance())->get_path();

RECOVER
  cpath = NULL;
ENDSEQ
  return(cpath);
}

/******************************************************************************/
/**
\brief  Read - 



\return term - Termination code

\param  exdptr - 
\param  instlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical LDBHandle :: Read (exd *exdptr, int32 instlen )
{
  logical    term = NO;

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  exdptr->ResetACB(0);
  if ( !GetRootBase(exdptr)->Locate(exdptr->get_exdacb(),instlen+IEH) )
  {
//    exdptr->SetLength(0);  müssen wir vielleicht wegen workspace machen, wird aber in ACObject überschrieben
    term = YES;
  }
  
  if ( GetErrorCode() == 88 )
  {
    char           string[129];
    SDBRESET
    strcpy(string,"Recovery SID: ");
    gvtxitoa(exdptr->GetIEH()->get_iehsid(),&string[strlen(string)],10);
    strcat(string,"; KEY: ");
    memset(&string[strlen(string)],0,33);
    memcpy(&string[strlen(string)],exdptr->GetInstance(),32);
    SDBError().TraceMessage(string);
  }
RECOVER
  term = YES;
  switch ( SDBERROR )
  {
    case  0 : 
    case  3 : 
    case  6 : break;
    default : SDBSET(1)
  }

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ReadHeader - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadHeader"

logical LDBHandle :: ReadHeader ( )
{
  logical    term = NO;
BEGINSEQ
  if ( !current_rb->GetRootBase(0)->Locate(header_acb,sizeof(DBHeader)) ||
       (memcmp(db_header->get_ident(),"DBH2",4)	&&
        memcmp(db_header->get_ident(),"SDB ",4)) )   SDBERR(60)
        
  if ( header_acb->IsPIF() )
  {
    db_header->FromPIF(pif);
    header_acb->ResetPIF();
  }


RECOVER
  *db_header->get_ident() = 0;
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  RecreateExtent - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RecreateExtent"

logical LDBHandle :: RecreateExtent (char *extnames )
{
  DBExtend   *dbext_def;
  EB_Number   last_EB;
  EB_Number   first_EB;
  EB_Number   pebs;
  uint64      ebsnum;
  uint64      last_ebs;
  int16       extsid;
  int16       sid;
  int16       modcount;
  char        orgtype;
  logical     delind;
  char        string[13];
  int32        count  = 0;
  int32        rderr  = 0;
  int32        iderr  = 0;
  int32        adderr = 0;
  logical     term   = NO;
BEGINSEQ
  if ( !(dbext_def = dictionary->ProvideExtendDef(extnames)) )
                                                     ERROR
  first_EB = current_rb->GetFirstEBNumber(dbext_def->get_mb_number());
  last_EB  = current_rb->GetLastEBNumber(dbext_def->get_mb_number());
  extsid   = dbext_def->fmcbityp;
    
  if ( first_EB.IsEmpty() )                          SDBERR(99)
  if ( extsid <= 0 )                                 SDBERR(99)
    
  if ( DeleteExtendRef(extnames) )                   SDBCERR

  PropertyHandle extent_pi(*GetDatabaseHandle(),extnames,PI_Write);
                                                     SDBCERR
  PropertyHandle void_pi(*GetDatabaseHandle(),"VOID",PI_Read);
                                                     SDBCERR
  SDBError().InsertStatField();
  ebsnum   = first_EB.FromPIF(pif).get_ebsnum();
  last_ebs = last_EB.FromPIF(pif).get_ebsnum();
  while ( ebsnum <= last_ebs )
  {
    pebs = ebsnum;
    pebs.ToPIF(pif);
    if ( GetInstInfo(pebs,sid,orgtype,delind,modcount) &&
         sid == extsid && orgtype == IDB_INS && !delind )
    {
      count++;
      SDBError().SetStatField(gvtxltoa(count,string,10));
      if ( void_pi(ebsnum) )
      {  
        if ( ((LNode *)extent_pi.get_nodeptr())->get_noderefl()->CheckNewID(void_pi.get_nodeptr()->get_nodeinst()->get_iselarea(),pebs) ) 
          iderr++;
        else  
          if ( ((LNode *)extent_pi.get_nodeptr())->get_noderefl()->AddID(void_pi.get_nodeptr()->get_nodeinst(),pebs,AUTO) )
            adderr++;
      }  
      else
        rderr++;  
    }
    ebsnum++;
  }
  SDBError().RemoveStatField();
  SaveExtentList();

  if ( rderr )
    SDBError().TraceMessage("Number of read errors: ",gvtxltoa(rderr,string,10));
  if ( iderr )
    SDBError().TraceMessage("Number of key errors : ",gvtxltoa(iderr,string,10));
  if ( adderr )
    SDBError().TraceMessage("Number of add errors : ",gvtxltoa(adderr,string,10));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseInstance - 




\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseInstance"

void LDBHandle :: ReleaseInstance (acb *acbptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  if ( current_rb )
    current_rb->ReleaseEntry(acbptr);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  RemoveResources - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveResources"

void LDBHandle :: RemoveResources ( )
{

  delete database_info;
  database_info = NULL;
  
  msmfs((void **)&header_acb);
  header_acb = NULL;
  
  msmfs((void **)&shadow_rb_acb);
  shadow_rb_acb = NULL;
  
  msmcl(&ms_pool);  
  dictionary = NULL;

}

/******************************************************************************/
/**
\brief  RemoveShadowRB - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveShadowRB"

logical LDBHandle :: RemoveShadowRB ( )
{
  char         *path;
  logical       term = NO;
  DeactivateShadowBase();
  delete shadow_rb;
  shadow_rb = NULL;
  
  if ( (path = ProvideShadowRBPath(YES)) && *path > ' ' )
    remove(path);
  
  if ( !shadow_rb_acb->get_ebsnum().IsEmpty() )
  {
    root_base->GetRootBase(0)->Delete(shadow_rb_acb);
    shadow_rb_acb->set_ebsnum(0);
  }
  
  db_header->get_shadow_db()    = 0;
  db_header->set_next_ws_number(0);
  WriteHeader();

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

logical LDBHandle :: Reserve (acb *acbptr, logical wait )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return ( current_rb->Reserve(acbptr,wait) );
RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  ReserveInstance - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveInstance"

logical LDBHandle :: ReserveInstance (acb *acbptr )
{

BEGINSEQ
//  if ( !this )                                       SDBERR(99)   wegen XDBHandle
  
  return ( this ? current_rb->ReserveEntry(acbptr) : NO );
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetLastSchemaVersion - 



\return term - Termination code

\param  reset_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastSchemaVersion"

logical LDBHandle :: ResetLastSchemaVersion (logical reset_opt )
{
  EB_Number        last_EB;
  EB_Number        first_EB;
  EBI             *ebiptr;
  int32            schema_version = db_header->get_schema_version();
  acb             *acbptr    = acb::Create(256);
  int16            mbnumber  = 0;
  uint64           current;
  uint64           lastent;
  logical          term = NO;
BEGINSEQ
  if ( schema_version <= 0 )                         LEAVESEQ
  if ( access_mode == PI_Read )                      SDBERR(28)
  pif = root_base->IsPIF();
  
  while ( !(first_EB = root_base->GetFirstEBNumber(mbnumber)).IsEmpty() )
  {
    last_EB = root_base->GetLastEBNumber(mbnumber++);
    current = first_EB.FromPIF(pif).get_ebsnum();
    lastent = last_EB.FromPIF(pif).get_ebsnum();
    while ( current <= lastent )
    {
      acbptr->set_ebsnum(BigToPIF(current,pif));
      if ( (ebiptr = root_base->IntGetEBI(acbptr)) &&
           !ebiptr->stscdel()                      &&       // not deleted entry
           ebiptr->GetPosition()                   &&       // not a new entry
           root_base->Locate(acbptr,sizeof(ieh))   &&       // can be read  
           acbptr->get_acbieh().get_iehtyp() == IDB_INS)    // an instance entry
      {
        if ( acbptr->get_acbieh().get_iehver() >= schema_version )
        {
          printf("\n  Instance %i is refers to new schema version %i",(int32)current,schema_version);
          if ( reset_opt )
          {
            acbptr->get_acbieh().set_iehver(schema_version-1); 
            if ( root_base->Update(acbptr,sizeof(ieh),0) )
              term = YES;
          }
          else
            term = YES;
        }
      }
      current++;
    }
  }

  if ( term ) 
    printf("\nNew schema version is referenced . schema version not reset.");
  else
  {
    db_header->set_schema_vers(schema_version-1);
    if ( WriteHeader() )                         ERROR
    printf("\nSchema version reset to %i.",schema_version-1);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetLastVersion - 



\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastVersion"

logical LDBHandle :: ResetLastVersion (uint16 version_nr )
{
  EB_Number        last_EB;
  EB_Number        first_EB;
  EBI             *ebiptr;
  acb             *acbptr    = acb::Create(256);
  int16            mbnumber  = 0;
  uint64           current;
  uint64           lastent;
  int32            ecount    = 0;
  logical          term      = NO;
BEGINSEQ
  if ( access_mode == PI_Read )                      SDBERR(28)
  pif = root_base->IsPIF();
  
  if ( version_nr == CUR_VERSION )
    version_nr = version;
  if ( version_nr > version )                        SDBERR(99)
  
  while ( !(first_EB = root_base->GetFirstEBNumber(mbnumber)).IsEmpty() )
  {
    last_EB = root_base->GetLastEBNumber(mbnumber++);
    current = first_EB.FromPIF(pif).get_ebsnum();
    lastent = last_EB.FromPIF(pif).get_ebsnum();
    while ( current <= lastent )
    {
      acbptr->set_ebsnum(BigToPIF(current,pif));
      if ( root_base->IntGetEBI(acbptr) )
      {
        if ( acbptr->get_version() >= version_nr )
        {
          acbptr->FromPIF(pif);
          if ( acbptr->GetPrevEBI(root_base,version_nr-1,pif) )
          { // old EBI version does not exist
            *(EBI *)acbptr = EBI();
            acbptr->stsswpt(2);
          }
          acbptr->ToPIF(pif);
          root_base->IntPutEBI(acbptr);
          ecount++;
        }
      }
      current++;
    }
  }

  RemoveVersionEntries(version_nr);
  db_header->set_version(version_nr-1);
  WriteHeader();
  printf("\nDatabase version reset to %i.",version-1);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetWSNumber - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWSNumber"

logical LDBHandle :: ResetWSNumber ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( LockHeader() )                                SDBERR(6)
  if ( ReadHeader() )                                ERROR

  db_header->set_next_ws_number(0);
  
  if ( WriteHeader() )                               ERROR
RECOVER
  term = YES;
ENDSEQ
  UnlockHeader();
  return(term);
}

/******************************************************************************/
/**
\brief  ResetWorkspace - 



\return rootbase - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWorkspace"

db_RootBase *LDBHandle :: ResetWorkspace ( )
{
  db_RootBase            *rootbase = root_base;
  root_base = root_base->GetRootBase(0);

  if ( current_rb != shadow_rb )
    current_rb = root_base;

  return(rootbase);
}

/******************************************************************************/
/**
\brief  RestoreDB - 



\return term - Termination code

\param  source - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RestoreDB"

logical LDBHandle :: RestoreDB (char *source )
{
  char         target[1024];
  Dictionary  *dict_ptr = dictionary;
  PIACC        accopt = access_mode;
  logical      netopt = net_option;
  logical      term = NO;

BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  strcpy(target,GetPath());
  
  CloseDBHandle();
  if ( FileCopy(source,target,AUTO) )                ERROR
  Open(dict_ptr,NULL,target,accopt,netopt);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RlsRecoveryHdl - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RlsRecoveryHdl"

logical LDBHandle :: RlsRecoveryHdl ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !recovery_handle )                            LEAVESEQ

  if ( LockHeader() )                                ERROR
  if ( ReadHeader() )                                ERROR
    
  WriteHeader();
  
  SaveBuffer();
  root_base->Flush();

  db_header->set_recover_pos(AUTO);

  term = WriteHeader();
  UnlockHeader();

  if ( db_header->get_save_transaction() )  // temp. recovery
    recovery_handle->DeleteFile();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SavRecoveryHdl - 



\return term - Termination code

\param  error - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SavRecoveryHdl"

logical LDBHandle :: SavRecoveryHdl (logical error )
{
  int                     wait = 10;
  logical                 term = NO;
BEGINSEQ
  if ( !recovery_handle )                            LEAVESEQ
  if ( error )                                       ERROR

  while ( --wait ) 
  {
    if ( LockHeader() )                              ERROR
    if ( ReadHeader() )                              ERROR
    if ( db_header->get_recover_pos() <= 0 )
      break;
    UnlockHeader();
    tim::timestp(2);
  }
  if ( !wait )                                       SDBERR(99)
    
  db_header->set_recover_pos(recovery_handle->StopTA(NO));
  db_header->set_recover_numb(recovery_handle->get_rvrnum());

  if ( db_header->get_save_transaction() )  // temp. recovery
    recovery_handle->Close();

  term = WriteHeader();
  UnlockHeader();
  current_rb->Flush();
RECOVER
  recovery_handle->StopTA(YES);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SaveBuffer - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveBuffer"

logical LDBHandle :: SaveBuffer ( )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return ( current_rb->SaveBuffer() );
RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetCurrentRB - 




\param  rootbase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentRB"

void LDBHandle :: SetCurrentRB (db_RootBase *rootbase )
{

  current_rb = rootbase;

}

/******************************************************************************/
/**
\brief  SetWorkspace - 




\param  rootbase - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWorkspace"

void LDBHandle :: SetWorkspace (db_RootBase *rootbase )
{

  root_base = rootbase;

  if ( current_rb != shadow_rb )
    current_rb = root_base;


}

/******************************************************************************/
/**
\brief  SetupTypeID - 



\return term - Termination code

\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupTypeID"

logical LDBHandle :: SetupTypeID (int16 sid )
{
  logical     term = NO;
BEGINSEQ
  if ( LockHeader() )                                SDBERR(6)
  if ( ReadHeader() )                                ERROR

  if ( db_header->get_last_str_number() < (uint16)sid )
  {
    db_header->set_last_str_num((uint16)sid);
    if ( WriteHeader() )                             ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  UnlockHeader();
  return(term);
}

/******************************************************************************/
/**
\brief  StatDisplay - 



\return term - Termination code

\param  dbpath - Complete database path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StatDisplay"

logical __cdecl LDBHandle :: StatDisplay (char *dbpath, char *ppath )
{
  eb_RootBase entbase(YES,NO);
  EB_Number   last_EB;
  EB_Number   first_EB;
  FILE       *filptr = NULL;
  EBI        *ebiptr;
  acb         acbenty(0,0);
  EBI         oldebi;
  char        area[512];     
  int16       dbfile;
  int32       emptcnt   = 0;
  int32       clustdcnt = 0;
  int32       clustdsum = 0;
  int32       clustecnt = 0;
  int32       clustesum = 0;
  int32       clustcnt  = 0;
  int32       clustsum  = 0;
  int32       usedcnt   = 0;
  int32       usedsum   = 0;
  int32       delcnt    = 0;
  int32       delsum    = 0;
  int16       mbnumber  = 0;
  uint64      current;
  uint64      lastent;
  uint64      indx0;
  logical     pif;
  logical     term = YES;
  DPA(StatEntry) typeinfo;
  StatEntry  *elmt_ptr;
BEGINSEQ
  entbase.Open(dbpath,NO,YES,YES);                   SDBCERR
  dbfile = entbase.get_rb_header()->get_file_handle();
  if ( !(filptr = fopen(ppath,"wt")) )               SDBERR(187)
  pif = entbase.IsPIF();
  
  while ( !(first_EB = entbase.GetFirstEBNumber(mbnumber)).IsEmpty() )
  {
    last_EB = entbase.GetLastEBNumber(mbnumber++);
    current = first_EB.FromPIF(pif).get_ebsnum();
    lastent = last_EB.FromPIF(pif).get_ebsnum();
    if ( filptr )
    {
      fprintf(filptr,"\n\nDatabase Statistics for MainBase %d",mbnumber-1);
      fprintf(filptr,"\n\nLast Entry Number in Entry Base %ld",lastent);
    }
    while ( current <= lastent )
    {
      acbenty.set_ebsnum(BigToPIF(current++,pif));
      if ( ebiptr = entbase.IntGetEBI(&acbenty) )
      {  
        if ( ebiptr->stscusr1() )
        {
          if ( ebiptr->stscdel() )
          {
            clustdcnt++;
            if ( !ebiptr->stscusr2() )
              clustdsum += ebiptr->get_entry_length();
          }
          else
          {
            if ( ebiptr->GetPosition() )
            {
              clustcnt++;
              clustsum += ebiptr->get_entry_length();
            }
            else
              emptcnt++;
          }
        }
        else
        {
          GetStats(&entbase,typeinfo,&acbenty,pif);
          if ( ebiptr->stscdel() )
          {
            delcnt++;
            delsum += ebiptr->get_entry_length();
          }
          else
          {
            if ( ebiptr->GetPosition() )
            {
              usedcnt++;
              usedsum += ebiptr->get_entry_length();
              if ( ebiptr->stscusr2() )
              {
                clustecnt++;
                clustesum += ebiptr->get_entry_length();
              }
            }
            else
              emptcnt++;
          }
        }
      }
    }
       
    if ( filptr )
    {
      StatEntry   tot_elm;
      
      fprintf(filptr,"\n\n   Entry Statistics");
      fprintf(filptr,"\n\n           Number of lost Entries         %ld",emptcnt);
      fprintf(filptr,"\n\n           Number of deleted Entries      %ld",delcnt);
      fprintf(filptr,"\n           Size for deleted Entries       %ld",delsum);
      fprintf(filptr,"\n\n           Number of used Entries         %ld",usedcnt);
      fprintf(filptr,"\n           Size for used Entries          %ld",usedsum);
      fprintf(filptr,"\n\n   Cluster Statistics");
      fprintf(filptr,"\n           Number of clustered Entries    %ld",clustecnt);
      fprintf(filptr,"\n           Size for clustered Entries     %ld",clustesum);
      fprintf(filptr,"\n           Number of used Clusters        %ld",clustcnt);
      fprintf(filptr,"\n           Size for used Clusters         %ld",clustsum);
      fprintf(filptr,"\n           Number of deleted Clusters     %ld",clustdcnt);
      fprintf(filptr,"\n           Size for deleted Clusters      %ld",clustdsum);
      
      fprintf(filptr,"\n");
      fprintf(filptr,"\n             instances      deleted instances      Index Entries   del. index entries     history entries");
      fprintf(filptr,"\n SID      count      size     count      size     count      size     count      size     count      size");
      fprintf(filptr,"\n --------------------------------------------------------------------------------------------------------");
      indx0 = 0;
      while ( indx0 < typeinfo.GetSize() )
      {
        if ( elmt_ptr = typeinfo[indx0] )
        {
          memset(area,' ',sizeof(area));
          memcpy(area+1,"\n9999",5);
          gvtxltp(area+2,indx0,4);
          elmt_ptr->Print(filptr,area+7);
          area[120] = 0;
          fprintf(filptr,area);
          tot_elm += *elmt_ptr;
          delete elmt_ptr;
        }
        indx0++;
      }
      fprintf(filptr,"\n --------------------------------------------------------------------------------------------------------");
      memset(area,' ',sizeof(area));
      memcpy(area+1,"\ntotal",6);
      tot_elm.Print(filptr,area+7);
      area[120] = 0;
      fprintf(filptr,area);
      fprintf(filptr,"\n\n");
    }
    typeinfo.Clear();
  }    
  

RECOVER
  term = YES;
ENDSEQ
  if ( filptr )
    fclose(filptr);
  return(term);
}

/******************************************************************************/
/**
\brief  StoreRecovery - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreRecovery"

logical LDBHandle :: StoreRecovery ( )
{
  logical     close = NO;
  acb        *acbptr;
  logical     rec_close = NO;
  logical     term = NO;
BEGINSEQ
  if ( access_mode == PI_Read )                      SDBERR(117)

  if ( net_option )                                  LEAVESEQ

  if ( !recovery_handle ) 
  { 
    if ( OpenRecovery(0,0) )                         ERROR
    close = YES;
  }

  if ( !recovery_handle->IsOpened() )
  {
    if ( recovery_handle->Open(0) )                  ERROR
    rec_close = YES;
  }
  
  if ( recovery_handle->TA_Top(db_header->get_recover_pos()) )
                                                     ERROR
  
  while ( acbptr = recovery_handle->TA_Next() )
  {
    acb      loc_acb(*acbptr);
    if ( GetEBI(&loc_acb) )
      root_base->Create(&loc_acb);
      
    if ( acbptr->stscdel() )
    {
      if ( root_base->Delete(acbptr)  )              ERROR
    }
    else
      if ( root_base->Update(acbptr,
                             acbptr->get_acbieh().get_iehlen()+IEH,
                             AUTO) )                 ERROR
  }
  
//  SDBCERR
  
  RlsRecoveryHdl();
RECOVER
  term = YES;
ENDSEQ
  if ( rec_close )
    recovery_handle->Close();
  if ( close )
    CloseRecovery();
  return(term);
}

/******************************************************************************/
/**
\brief  SysInfoDisplay - 



\return term - Termination code

\param  dbpath - Complete database path
\param  ppath - Protocol path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SysInfoDisplay"

logical __cdecl LDBHandle :: SysInfoDisplay (char *dbpath, char *ppath )
{
  extern OPAGlobals opa_globals;
  logical           pif;
  db_RootBase      *rbase     = NULL;
  logical           del_rb    = YES;
  logical           shared_rb = opa_globals.RootBaseShared();
  logical           netopt    = YES+shared_rb;
  FILE             *filptr    = NULL;
  acb              *hd_acb    = (acb *)msmgs(sizeof(acb)+sizeof(DBHeader)-IEH);
  DBHeader         *dbheader  = (DBHeader *)&hd_acb->get_acbieh();
  acb              *ob_acb    = (acb *)msmgs(sizeof(acb)+sizeof(SDB_ObjectExt));
  SDB_ObjectExt    *extobj    = (SDB_ObjectExt *)ob_acb->GetInstance();
  EB_Number         last_EB;
  void             *void_ptr;
  char              string[129];
  logical           term      = NO;
BEGINSEQ
  if ( !(filptr = fopen(ppath,"wt")) )               SDBERR(187)
    
  fprintf(filptr,"\n\nDatabase System Information for: %s",dbpath);
  fprintf(filptr,  "\n  ODABA version                : %s",ODABA2Version());
  
  {
    if ( !shared_rb || !(rbase = opa_globals.ProvideRootBase("",dbpath)) )
    {
      rbase  = new eb_RootBase(netopt,shared_rb);
      if ( !rbase->Exist(dbpath,YES) )
        fprintf(filptr,"\n\n  Database does not exist");
      else
      {      
        rbase->Open(dbpath,shared_rb,netopt,YES);
        if ( SOSERROR )
          fprintf(filptr,"\n\n  Database could not be opened");
        else
        {
          del_rb = NO;
          if ( shared_rb )    
            opa_globals.RegisterRootBase(rbase,"",dbpath);
        }
      }
      if ( del_rb )
      {
        delete rbase;
        rbase = NULL;
      }
    }
    
    if ( rbase )
    {
      pif = rbase->IsPIF();
      last_EB = rbase->GetLastEBNumber(0);
      fprintf(filptr,"\n\n  Platform independent format (PIF): %s",pif ? "yes" : "no");
      fprintf(filptr,  "\n  Number of Mainbases              : %d",rbase->GetMBCount());
      fprintf(filptr,  "\n  Last Entry Number in Mainbase 0  : %ld",last_EB.FromPIF(pif).get_ebsnum());

      hd_acb->set_ebsnum(BigToPIF(1,pif));
      if ( !rbase->Locate(hd_acb,sizeof(DBHeader)) )
        fprintf(filptr,"\n\n  DBHeader could not be read");
      else
      {
        fprintf(filptr,"\n\n  DBHeader information");
        fprintf(filptr,"\n    Ident:                 %s",gvtxbts(string,dbheader->get_ident(),4));
        fprintf(filptr,"\n    Progam Version:        %d",PIFToShort(dbheader->get_version(),pif));
        fprintf(filptr,"\n    Schema Version:        %d",PIFToShort(dbheader->get_schema_version(),pif));
        fprintf(filptr,"\n    System Version:        %d",PIFToShort(dbheader->get_system_version(),pif));
        fprintf(filptr,"\n    Last Structure ID:     %d",PIFToShort(dbheader->get_last_str_number(),pif));
        fprintf(filptr,"\n    Root Object Identity:  %ld",dbheader->get_root_objekt().FromPIF(pif).get_ebsnum());
      
        ob_acb->set_ebsnum(dbheader->get_root_objekt().get_ebsnum());
        if ( !rbase->Locate(ob_acb,sizeof(SDB_ObjectExt)) )
          fprintf(filptr,"\n\n  Root Object Instance could not be read");
        else
        {
          fprintf(filptr,"\n\n  Root Object information");
          fprintf(filptr,"\n    Id:                    %ld",(int32)PIFToBig(extobj->get_object_id(),pif));
          fprintf(filptr,"\n    Version:               %d",PIFToShort(extobj->get_version(),pif));
          fprintf(filptr,"\n    Version List Identity: %ld",extobj->get_version_list().FromPIF(pif).get_ebsnum());
          fprintf(filptr,"\n    Extend List Identity:  %ld",extobj->get_extends().FromPIF(pif).get_ebsnum());
        }
      }
    }
  }

  fprintf(filptr,"\n\nDatabase System Information completed");

RECOVER
  term = YES;
ENDSEQ
  void_ptr = (void *)hd_acb;
  msmfs(&void_ptr);
  void_ptr = (void *)ob_acb;
  msmfs(&void_ptr);
  if ( filptr )
    fclose(filptr);
  if ( !shared_rb )
    delete rbase;
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

logical LDBHandle :: Unlock (acb *acbptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( !net_option ? NO : current_rb->Unlock(acbptr) );
RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  UnlockHeader - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockHeader"

logical LDBHandle :: UnlockHeader ( )
{

  return( current_rb->GetRootBase(0)->Unlock(header_acb) );

}

/******************************************************************************/
/**
\brief  UnlockInternal - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical LDBHandle :: UnlockInternal (exd *exdptr )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( !net_option ? NO : GetRootBase(exdptr)->UnlockInternal(exdptr->get_exdacb()));

RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  UnlockKey - 



\return term - Termination code

\param  entnr - 
\param  db_index - 
\param  keyptr - 
\param  owner_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockKey"

logical LDBHandle :: UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{

  return( root_base->UnlockKey(entnr,db_index,keyptr,owner_id) );

}

/******************************************************************************/
/**
\brief  UnlockRB - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockRB"

logical LDBHandle :: UnlockRB ( )
{

BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  return( !net_option ? NO : current_rb->IUnlock());

RECOVER
  return(YES);
ENDSEQ

}

/******************************************************************************/
/**
\brief  VersionCheck - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionCheck"

logical LDBHandle :: VersionCheck ( )
{
  logical         locked = NO;
  logical         term = NO;
BEGINSEQ
  if ( db_header->get_version() == CUR_DBVERSION )   LEAVESEQ
  if ( LockHeader() )                                ERROR
  locked = YES;
  if ( db_header->get_version() > CUR_DBVERSION )    SDBERR(176)
  
//  if ( Version?() )                                  ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( locked )
  {
//    WriteHeader();
    UnlockHeader();
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

logical LDBHandle :: Write (exd *exdptr )
{
  int32  	 len = exdptr->get_write_end();
  int32  	 pos = exdptr->get_write_start();
  EB_Number      entnr   = exdptr->get_exdebsn();
  char           opera   = entnr.IsEmpty(pif) ? 'A' : 'U';
  db_RootBase   *rb;
  logical        tempmain = NO;
  logical        term    = NO;
BEGINSEQ
  if ( !this )                                       SDBERR(99)

//if ( len == AUTO && !exdptr->stscmod() && exdptr->get_exdacb()->stscmod() )  // nur EBI geändert
  if ( len == AUTO && !exdptr->stscmod() )  // nur EBI geändert oder top-ref
    len = 0;
  else
  {
    if ( len == AUTO )
      len = exdptr->GetLength();

    if ( pos == AUTO )
      len += IEH;
    else
    {
      len -= pos;
      pos += IEH;
    }
  }
  
  exdptr->ResetACB(0);
  
  rb = exdptr->get_write_shadow() == WRITE_EXTEND_LIST ? GetRootBase((uint8)0) : GetRootBase(exdptr);
  if ( exdptr->get_exdacb()->get_mb_number() == root_base->get_temp_main() )
  {
    rb = GetRootBase((uint8)0);
    tempmain = YES;
  }
  if ( rb->Update(exdptr->get_exdacb(),len,pos) )    ERROR
  
  if ( !exdptr->get_shadow_base() && !tempmain )
    if ( WriteShadow(exdptr,len,pos) )                       ERROR
      
  exdptr->ResetWriteLen();

RECOVER
  term = YES;
  switch ( SDBERROR )
  {
    case  0 : 
    case  6 : break;
    default : if ( SDBERROR != 116 )
                SDBSET(1)
  }
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  WriteHeader - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteHeader"

logical LDBHandle :: WriteHeader ( )
{
  logical        term = NO;

BEGINSEQ
  if ( access_mode == PI_Read )                      LEAVESEQ
  
  if ( pif && !header_acb->IsPIF() )
  {
    db_header->ToPIF(pif);
    header_acb->SetPIF();
  }
    
  if ( header_acb->get_ebsnum().IsEmpty() )
    if ( (header_acb->get_ebsnum() = current_rb->GetRootBase(0)->Create(0,0,0)).IsEmpty() )
                                                     ERROR
  
  if ( current_rb->GetRootBase(0)->Update(header_acb,sizeof(DBHeader),AUTO) )  
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( header_acb->IsPIF() )
  {
    db_header->FromPIF(pif);
    header_acb->ResetPIF();
  }
  return(term);

}

/******************************************************************************/
/**
\brief  WriteShadow - 



\return term - Termination code

\param  exdptr - 
\param  instlen - 
\param  writepos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteShadow"

logical LDBHandle :: WriteShadow (exd *exdptr, int32 instlen, int32 writepos )
{
  acb            temp_acb(0,0);
  logical        term    = NO;
BEGINSEQ
  if ( !shadow_rb || !exdptr->get_write_shadow() )   LEAVESEQ
  
  temp_acb = *exdptr->get_exdacb();
  exdptr->ResetACB(0);
  shadow_rb->GetEBI(exdptr->get_exdacb());
  term = shadow_rb->Update(exdptr->get_exdacb(),instlen,writepos);

  *exdptr->get_exdacb() = temp_acb;
  if ( term )                                        SDBERR(1)
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ~LDBHandle - Destructur




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~LDBHandle"

     LDBHandle :: ~LDBHandle ( )
{

  if ( dictionary )
    CloseDBHandle();
    
  RemoveResources();



}


