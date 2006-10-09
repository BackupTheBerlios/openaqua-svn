/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    db_RootBase

\brief    


\date     $Date: 2006/06/25 16:19:24,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   db_RootBase_HPP
#define   db_RootBase_HPP

class     db_RootBase;

class     ACObject;
class     DBHandle;
class     DBIndex;
class     EBI;
class     EB_Header;
class     EntryEvent;
class     KeyCacheBase;
class     SDB_Workspace;
class     Workspace;
class     acb;
class     db_RootBase;
class     eb_RootBase;
class     ieh;
#include  <cPIACC.h>
#include  <cRootBase_Types.h>
#include  <sEB_Number.hpp>
#include  <sReferenceObject.hpp>
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  db_RootBase :public ReferenceObject
{
protected  :         KeyCacheBase                                *key_cache;                                                 // 
protected  :         char                                        *root_path;                                                 // 
protected  :         logical                                      net_option;                                                // 
protected  :         uint8                                        level;                                                     // 
protected  :         int16                                        temp_main;                                                 // 

public     :
                     KeyCacheBase                                *get_key_cache() { return(key_cache); }
                     char                                        *get_root_path() { return(root_path); }
                     logical                                      get_net_option() { return(net_option); }
                     uint8                                        get_level() { return(level); }
                     int16                                        get_temp_main() { return(temp_main); }
public     : virtual                                logical CheckEBI (acb *acbptr );
public     : virtual                                uint8 Check_WProtect (acb *acbptr );
public     : virtual          OPAImpExp             db_RootBase *Close ( );
public     : virtual                                logical Consolidate ( );
public     : virtual                                EB_Number Create (EB_Number clnumb, int16 mbnumber, uint16 sbnumber, uint16 version_nr=CUR_VERSION );
public     : virtual                                EB_Number Create (acb *acbptr );
public     : virtual                                logical Delete (acb *acbptr );
public     : virtual                                logical DeleteRB ( );
public     : virtual                                logical DeleteWorkspaces (DBHandle *dbhandle );
public     : virtual                                logical Discard ( );
public     : static           OPAImpExp             logical __cdecl Exist (char *path, logical netopt, char chkopt=AUTO );
public     : virtual                                logical ExistEBI (acb *acbptr );
public     : virtual          OPAImpExp             logical ExistWorkspace (char *names );
public     : virtual                                logical Flush ( );
public     : virtual                                logical FlushCluster (acb *acbptr );
public     : virtual                                logical FlushClusterPool ( );
public     : virtual                                logical GenerateServerEvent (EntryEvent *ev_ptr );
public     : virtual                                int16 GetDataVersion ( );
public     : virtual                                EBI *GetEBI (acb *acbptr );
public     : virtual                                ieh *GetEntryHeader (acb *acbptr );
public     : virtual          OPAImpExp             EB_Number GetFirstEBNumber (int16 mbnumber );
public     : virtual          OPAImpExp             EB_Number GetLastEBNumber (int16 mbnumber );
public     : virtual                                int32 GetMBCount ( );
public     : virtual                                int16 GetMBNumber (EB_Number entnr );
public     : static                                 RootBase_Types __cdecl GetRBType (char *cpath );
public     : virtual                                db_RootBase *GetRootBase (uint8 wslevel );
public     : virtual                                SDB_Workspace *GetWorkspace (int32 lindx0, char *user_name, logical refresh );
public     : virtual                                int32 GetWorkspaceNumber (char *names );
public     : virtual                                int32 GetWorkspaceNumber ( );
public     : virtual                                int32 Get_Length (acb *acbptr );
public     : virtual                                uint8 Get_Mod (acb *acbptr );
public     : virtual                                void IgnoreSharedRB ( );
public     : virtual          OPAImpExp             logical InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     : virtual          OPAImpExp             logical InitKeyCache (ACObject *obhandle );
public     : virtual          OPAImpExp             logical InitMainBase (int16 mbnumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL, logical pindep=NO );
public     : virtual          OPAImpExp             logical InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     : virtual                                logical InitWSList (DBHandle *dbhandle );
public     : virtual                                EBI *IntGetEBI (acb *acbptr );
public     : virtual                                EBI *IntPutEBI (acb *acbptr );
public     : virtual                                eb_RootBase *IsODABARootBase ( );
public     : virtual                                logical IsPIF ( );
public     : virtual                                logical IsWorkspace ( );
public     : virtual                                logical IsXMLBase ( );
public     : virtual                                void *Locate (acb *acbptr, int32 entlen );
public     : virtual                                logical Lock (acb *acbptr, logical wait );
public     : virtual                                logical LockInternal (acb *acbptr, logical wait );
public     :                                        logical LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     : virtual          OPAImpExp             logical Open (char *path, logical outopt, logical exclusive, char sysenv=NO );
public     : virtual                                Workspace *OpenWorkspace (DBHandle *dbhandle, char *names, char *user_name, char *cpath, logical exclusive );
public     : virtual                                logical Provide (char *cpath, PIACC accopt, logical exclusive, char sysenv=NO );
public     : virtual                                logical ProvideWSEntry (acb *acbptr, logical del_dep=YES );
public     : virtual                                char *ProvideWorkspace (char *names, char *user_name, char *cpath );
public     : virtual                                RootBase_Types RBType ( );
public     : virtual                                logical ReleaseEntry (acb *acbptr );
public     : virtual                                logical ReleaseWSEntry (acb *acbptr );
public     : virtual                                logical RemoveWorkspace (char *names );
public     : virtual                                logical Reserve (acb *acbptr, logical wait );
public     : virtual                                logical ReserveEntry (acb *acbptr );
public     : virtual                                logical ReserveWSEntry (acb *acbptr );
public     : virtual                                logical SaveBuffer ( );
public     : virtual                                logical Undelete (acb *acbptr );
public     : virtual                                logical Unlock (acb *acbptr );
public     : virtual                                logical UnlockInternal (acb *acbptr );
public     :                                        logical UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     : virtual                                logical Update (acb *acbptr, int32 entlen, int32 offset );
public     :                  OPAImpExp                  db_RootBase (logical netopt );
public     : virtual          OPAImpExp                  ~db_RootBase ( );
};

#pragma pack()
#endif
