/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/07/17 22:07:34,31 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   LDBHandle_HPP
#define   LDBHandle_HPP

class     LDBHandle;

#define  WRITE_EXTEND_LIST                         2
#include  <sGSRT.h>
class     WorkspaceEntry;
#ifndef   DPA_StatEntry_HPP
#define   DPA_StatEntry_HPP
#include  <sStatEntry.hpp>
#include  <sDPA.h>
#endif
class     ACObject;
class     DBHeader;
class     DBIndex;
class     DBInfo;
class     Dictionary;
class     EB_Header;
class     EntryEvent;
class     LDBHandle;
class     LDictionary;
class     WorkspaceEntry;
class     acb;
class     db_RootBase;
class     exd;
class     ieh;
class     rvr;
class     srt;
#include  <cPIACC.h>
#include  <cRecoveryType.h>
#include  <sCheckOptions.hpp>
#include  <sDBHandle.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sNString.hpp>
#pragma pack(8)

class  LDBHandle :public virtual DBHandle,
public LACObject
{
protected  :         acb                                         *header_acb;                                                // 
protected  :         DBHeader                                    *db_header;                                                 // 
protected  :         void                                        *ms_pool;                                                   // 
protected  :         char                                         db_path[256];                                              // 
protected  :         db_RootBase                                 *root_base;                                                 // 
protected  :         rvr                                         *recovery_handle;                                           // 
protected  :         DBInfo                                      *database_info;                                             // 
protected  :         LDictionary                                 *local_dictionary;                                          // 
protected  :         acb                                         *shadow_rb_acb;                                             // 
protected  :         db_RootBase                                 *shadow_rb;                                                 // 
protected  :         db_RootBase                                 *current_rb;                                                // 

public     :
                     acb                                         *get_header_acb() { return(header_acb); }
                     DBHeader                                    *get_db_header() { return(db_header); }
                     void                                        *get_ms_pool() { return(ms_pool); }
                     char                                        *get_db_path() { return(db_path); }
                     db_RootBase                                 *get_root_base() { return(root_base); }
                     rvr                                         *get_recovery_handle() { return(recovery_handle); }
                     DBInfo                                      *get_database_info() { return(database_info); }
                     LDictionary                                 *get_local_dictionary() { return(local_dictionary); }
                     acb                                         *get_shadow_rb_acb() { return(shadow_rb_acb); }
                     db_RootBase                                 *get_shadow_rb() { return(shadow_rb); }
                     db_RootBase                                 *get_current_rb() { return(current_rb); }
public     : virtual                                logical ActivateShadowBase ( );
public     : virtual          OPAImpExp             logical BackupDB (char *target );
public     : virtual                                logical ChangeRecovery (RecoveryType rec_type, char *rec_path );
public     : virtual          OPAImpExp             logical CheckDB (CheckOptions check_opts );
public     : virtual          OPAImpExp             logical CheckDB (CheckOptions check_opts, char *resnames );
public     :                                        logical CheckDBCollections (CheckOptions check_opts );
public     :                                        int16 CheckDBEntry (EB_Number entnr );
public     :                                        logical CheckDBGUID (acb *acbptr, NString &rstring, logical repair, logical warnings, int32 maxlen );
public     :                                        logical CheckDBInstances (CheckOptions check_opts );
public     :                                        logical CheckDeleteDBInstance (CheckOptions check_opts, EB_Number entnr );
public     :                                        logical CheckEBI (exd *exdptr );
public     :                                        logical CheckEBI (EB_Number entnr );
public     : virtual                                logical CheckLicence (char *lic_owner, char *lic_number );
public     : virtual                                logical CheckLicence (char *applname_w=NULL );
public     :                                        uint8 CheckWProtect (exd *exdptr );
public     : virtual                                logical CloseDBHandle ( );
public     : virtual                                logical CloseRecovery ( );
public     : virtual                                logical CloseWorkspace ( );
public     : virtual                                logical ConsolidateWorkspace ( );
public     : virtual                                ACObject *CreateACObject (PIACC accopt, uint16 version_nr=CUR_VERSION );
public     : virtual                                ACObject *CreateACObject ( );
public     : virtual                                EB_Number CreateEntry (int16 mbnumber, uint16 sbnumber, EB_Number clnumb, uint16 version_nr=CUR_VERSION );
public     :                                        db_RootBase *CreateRootBase (char *cpath, PIACC accopt, logical netopt, char sysenv=NO );
public     :                                        logical CreateShadowRB (char *cpath );
public     : virtual                                logical DeactivateShadowBase ( );
public     :                                        logical Delete (EB_Number entnr );
public     :                                        logical Delete (exd *exdptr );
public     : virtual                                logical DeleteShadow (exd *exdptr );
public     :                                        logical DeleteWorkspace (char *names, char *user_name );
public     :                                        logical DeleteWorkspace ( );
public     : virtual                                logical DisableWorkspace ( );
public     : virtual                                logical DiscardWorkspace ( );
public     : virtual                                logical EnableWorkspace (char *cpath );
public     : static                                 logical __cdecl Exist (char *cpath, char chkopt=AUTO );
public     : virtual                                logical ExistWorkspace (char *names );
public     :                                        logical Flush ( );
public     :                                        logical FlushCluster (acb *acbptr );
public     : virtual                                logical FlushClusterPool ( );
public     :                                        logical GenerateServerEvent (EntryEvent *ev_ptr );
public     : virtual                                int32 GetDatabaseID ( );
public     :                                        logical GetEBI (acb *acbptr );
public     :                                        logical GetInstInfo (EB_Number entnr, int16 &sid_ref, char &otype_ref, logical &delind_ref, int16 &modcount_ref );
public     :                                        int32 GetInstStat (EB_Number entnr, ieh *iehptr, logical &delind_ref );
public     :                                        int32 GetLength (acb *acbptr );
public     : virtual                                LDBHandle *GetLocalDBHandle ( );
public     :                                        int16 GetMainBase (acb *acbptr );
public     : virtual                                int16 GetNewTypeID ( );
public     :                                        int32 GetNextWSNumber ( );
public     : virtual                                char *GetRecoveryFile (uint16 recnum=0 );
public     :                                        rvr *GetRecoveryHdl ( );
public     : virtual                                uint16 GetRecoveryNum ( );
public     : virtual                                char *GetRecoveryPath ( );
public     : virtual                                uint16 GetRecoveryStartNumber ( );
public     : virtual                                RecoveryType GetRecoveryType ( );
public     :                                        db_RootBase *GetRootBase (exd *exdptr );
public     :                                        db_RootBase *GetRootBase (uint8 wslevel );
public     : virtual                                uint16 GetSchemaVersion ( );
public     :                                        char *GetShadowRB ( );
public     : static                                 logical __cdecl GetStats (db_RootBase *rootbase, DPA(StatEntry) &typeinfo, acb *acbptr, logical pif );
public     : virtual                                uint16 GetSystemVersion ( );
public     : virtual                                int16 GetTempMain ( );
public     :                                        int32 GetUsedLength (acb *acbptr );
public     : virtual                                char *GetVersionString ( );
public     : virtual                                char *GetWorkspace (char *ws_root, int32 lindx0, char *user_name, char *names, logical refresh, char *ws_info=NULL );
public     :                                        uint8 GetWorkspaceLevel ( );
public     :                                        int32 GetWorkspaceNumber (char *names );
public     :                                        int32 GetWorkspaceNumber (uint8 wslevel );
public     :                                        uint8 Get_Mod (exd *exdptr );
public     :                                        logical HasWorkspace ( );
public     :                                        void IgnoreSharedRB ( );
public     : virtual                                logical InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     : virtual                                logical InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL, logical largedb=NO, logical pindep=NO );
public     : virtual                                logical InitRecovery (char *recpath, uint16 recnum=0 );
public     : virtual                                logical InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     :                                        logical InitWSList (logical refresh );
public     :                                        void Initialize (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, logical online_version=NO, uint16 version_nr=CUR_VERSION, char sysenv=NO, logical is_server=NO );
public     :                                        void Initialize (Dictionary *dictptr, PIACC accopt );
public     : virtual                                logical IsLicenced ( );
public     :                                        logical IsPIF ( );
public     :                                        logical IsRBLocked ( );
public     :                                        logical IsSaveTransact ( );
public     :                                             LDBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, logical online_version=NO, uint16 version_nr=CUR_VERSION, char sysenv=NO, logical is_server=NO );
public     :                                             LDBHandle (Dictionary *dict_ptr, PIACC accopt );
public     :                                             LDBHandle ( );
public     :                                             LDBHandle (char *cpath, int32 dasize=0, logical pindep=NO );
public     : virtual                                logical LocateWorkspace (char *names );
public     :                                        logical Lock (acb *acbptr );
public     :                                        logical LockHeader ( );
public     :                                        logical LockInternal (exd *exdptr, logical wait );
public     :                                        logical LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     :                                        logical LockRB ( );
public     :                                        logical Open (Dictionary *dict_ptr, db_RootBase *rootbase, char *cpath, PIACC accopt, logical netopt, logical online_version=NO, char sysenv=NO );
public     : virtual                                logical OpenRecovery (char *userinfo=NULL, int16 uilen=0 );
public     :                                        db_RootBase *OpenRootBase (char *cpath, PIACC accopt, logical netopt, char sysenv=NO );
public     :                                        logical OpenRootObject ( );
public     : virtual                                logical OpenWorkspace (char *names, char *user_name, logical exclusive, char *cpath_w=NULL );
public     :                                        char *ProvideShadowRBPath (logical read_opt=YES );
public     :                                        logical Read (exd *exdptr, int32 instlen );
public     :                                        logical ReadHeader ( );
public     : virtual                                logical RecreateExtent (char *extnames );
public     :                                        void ReleaseInstance (acb *acbptr );
public     :                                        void RemoveResources ( );
public     :                                        logical RemoveShadowRB ( );
public     :                                        logical Reserve (acb *acbptr, logical wait );
public     :                                        logical ReserveInstance (acb *acbptr );
public     : virtual                                logical ResetLastSchemaVersion (logical reset_opt );
public     : virtual                                logical ResetLastVersion (uint16 version_nr=CUR_VERSION );
public     :                                        logical ResetWSNumber ( );
public     :                                        db_RootBase *ResetWorkspace ( );
public     : virtual          OPAImpExp             logical RestoreDB (char *source );
public     :                                        logical RlsRecoveryHdl ( );
public     :                                        logical SavRecoveryHdl (logical error );
public     :                                        logical SaveBuffer ( );
public     :                                        void SetCurrentRB (db_RootBase *rootbase );
public     :                                        void SetWorkspace (db_RootBase *rootbase );
public     : virtual                                logical SetupTypeID (int16 sid );
public     : static           OPAImpExp             logical __cdecl StatDisplay (char *dbpath, char *ppath );
public     :                                        logical StoreRecovery ( );
public     : static           OPAImpExp             logical __cdecl SysInfoDisplay (char *dbpath, char *ppath );
public     :                                        logical Unlock (acb *acbptr );
public     :                                        logical UnlockHeader ( );
public     :                                        logical UnlockInternal (exd *exdptr );
public     :                                        logical UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     :                                        logical UnlockRB ( );
public     :                                        logical VersionCheck ( );
public     : virtual                                logical Write (exd *exdptr );
public     :                                        logical WriteHeader ( );
public     : virtual                                logical WriteShadow (exd *exdptr, int32 instlen, int32 writepos );
public     : virtual                                     ~LDBHandle ( );
public     : virtual                                char *GetPath ( ){

  return(db_path);

}

};

#pragma pack()
#endif
