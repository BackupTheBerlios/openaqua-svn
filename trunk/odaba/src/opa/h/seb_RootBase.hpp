/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    eb_RootBase

\brief    


\date     $Date: 2006/06/25 16:20:20,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   eb_RootBase_HPP
#define   eb_RootBase_HPP

class     eb_RootBase;

#ifndef   DLL_DBHandle_HPP
#define   DLL_DBHandle_HPP
#include  <sDBHandle.hpp>
#include  <sDLL.h>
#endif
class     DBHandle;
class     EBI;
class     EB_Header;
class     EB_RBHeader;
class     EntryEvent;
class     ObjectEntryList;
class     SDB_Workspace;
class     WSList;
class     Workspace;
class     acb;
class     eb_MainBase;
class     eb_RootBase;
class     ieh;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <sdb_RootBase.hpp>
#pragma pack(8)

class  eb_RootBase :public db_RootBase
{
protected  :         EB_RBHeader                                 *rb_header;                                                 // 
protected  :         eb_MainBase                                 *main_bases;                                                // 
protected  :         int16                                        number_mb;                                                 // 
protected  :         DLL(DBHandle)                                db_handle_list;                                            // 
protected  :         logical                                      shared_rootbase;                                           // 
protected  :         logical                                      pif;                                                       // 
protected  :         ObjectEntryList                             *object_entries;                                            // 
protected  :         WSList                                      *ws_list;                                                   // 

public     :
                     EB_RBHeader                                 *get_rb_header() { return(rb_header); }
                     eb_MainBase                                 *get_main_bases() { return(main_bases); }
                     int16                                        get_number_mb() { return(number_mb); }
                     DLL(DBHandle)                               &get_db_handle_list() { return(db_handle_list); }
                     logical                                      get_shared_rootbase() { return(shared_rootbase); }
                     logical                                      get_pif() { return(pif); }
                     ObjectEntryList                             *get_object_entries() { return(object_entries); }
                     WSList                                      *get_ws_list() { return(ws_list); }
public     : virtual                                logical CheckEBI (acb *acbptr );
public     : virtual                                uint8 Check_WProtect (acb *acbptr );
public     :                                        logical ClearEBI (acb *acbptr );
public     : virtual          OPAImpExp             db_RootBase *Close ( );
public     : virtual                                logical Consolidate ( );
public     :                                        logical Copy (eb_RootBase *srceroot, logical consol_appl, int16 mbnumber );
public     : virtual                                EB_Number Create (EB_Number clnumb, int16 mbnumber, uint16 sbnumber, uint16 version_nr=CUR_VERSION );
public     : virtual                                EB_Number Create (acb *acbptr );
public     :                                        logical CreateNewVersion (acb *acbptr, uint16 version_nr=CUR_VERSION );
public     : virtual                                logical Delete (acb *acbptr );
public     :                                        logical DeleteIntern (acb *acbptr );
public     :                                        logical DeleteRB ( );
public     :                                        logical DeleteVersion (acb *acbptr, uint16 version_nr=CUR_VERSION );
public     :                                        logical DeleteWorkspaces (DBHandle *dbhandle );
public     : virtual                                logical Discard ( );
public     : virtual                                logical ExistEBI (acb *acbptr );
public     :                  OPAImpExp             logical ExistWorkspace (char *names );
public     : virtual                                logical Flush ( );
public     :                                        logical FlushCluster (acb *acbptr );
public     :                                        logical FlushClusterPool ( );
public     : virtual                                logical GenerateServerEvent (EntryEvent *ev_ptr );
public     :                                        int16 GetDataVersion ( );
public     : virtual                                EBI *GetEBI (acb *acbptr );
public     :                                        ieh *GetEntryHeader (acb *acbptr );
public     :                  OPAImpExp             EB_Number GetFirstEBNumber (int16 mbnumber );
public     :                  OPAImpExp             EB_Number GetLastEBNumber (int16 mbnumber );
public     :                                        int32 GetMBCount ( );
public     : virtual                                int16 GetMBNumber (EB_Number entnr );
public     :                                        eb_MainBase *GetMainBase (EB_Number entnr );
public     :                                        eb_MainBase *GetMainBase (int32 indx0 );
public     :                                        eb_MainBase *GetMainBase (acb *acbptr, logical check_acb=YES );
public     :                                        EB_Number GetNextEBNumber (EB_Number entnr );
public     :                                        logical GetPrevInstance (acb *acbptr, uint16 version_nr=CUR_VERSION );
public     : virtual                                db_RootBase *GetRootBase (uint8 wslevel );
public     : virtual                                SDB_Workspace *GetWorkspace (int32 lindx0, char *user_name, logical refresh );
public     :                                        int32 GetWorkspaceNumber (char *names );
public     :                                        int32 GetWorkspaceNumber ( );
public     : virtual                                int32 Get_Length (acb *acbptr );
public     : virtual                                uint8 Get_Mod (acb *acbptr );
public     : virtual                                void IgnoreSharedRB ( );
public     :                  OPAImpExp             logical InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     :                                        logical InitHeader (int16 mbnumber, uint16 sbnumber, EB_Header *pheader, char *filename, char *server=NULL );
public     : virtual          OPAImpExp             logical InitKeyCache (ACObject *obhandle );
public     :                  OPAImpExp             logical InitMainBase (int16 mbnumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL, logical pindep=NO );
public     : static           OPAImpExp             logical __cdecl InitRootBase (char *filename, int32 dasize=0, logical pindep=NO );
public     :                  OPAImpExp             logical InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     :                                        logical InitWSList (DBHandle *dbhandle );
public     :                                        EBI *IntGetEBI (acb *acbptr );
public     :                                        EBI *IntPutEBI (acb *acbptr );
public     :                                        eb_RootBase *IsODABARootBase ( );
public     :                                        logical IsPIF ( );
public     : virtual                                logical IsWorkspace ( );
public     : virtual                                void *Locate (acb *acbptr, int32 entlen );
public     :                                        void *LocateIntern (acb *acbptr, int32 entlen );
public     : virtual                                logical Lock (acb *acbptr, logical wait );
public     : virtual                                logical LockInternal (acb *acbptr, logical wait );
public     :                  OPAImpExp             logical Open (char *path, logical outopt, logical exclusive, char sysenv=NO );
public     :                                        logical OpenTemp ( );
public     :                                        Workspace *OpenWorkspace (DBHandle *dbhandle, char *names, char *user_name, char *cpath, logical exclusive );
public     :                                        logical Provide (char *cpath, PIACC accopt, logical exclusive, char sysenv=NO );
public     : virtual                                logical ProvideWSEntry (acb *acbptr, logical del_opt );
public     :                                        char *ProvideWorkspace (char *names, char *user_name, char *cpath );
public     : virtual                                RootBase_Types RBType ( );
public     : virtual                                logical ReleaseEntry (acb *acbptr );
public     : virtual                                logical ReleaseWSEntry (acb *acbptr );
public     :                                        logical RemoveWorkspace (char *names );
public     : virtual                                logical Reserve (acb *acbptr, logical wait );
public     : virtual                                logical ReserveEntry (acb *acbptr );
public     : virtual                                logical ReserveWSEntry (acb *acbptr );
public     :                                        logical ResetSize (int16 mbnumber );
public     : virtual                                logical SaveBuffer ( );
public     : virtual                                logical Undelete (acb *acbptr );
public     :                                        logical UndeleteIntern (acb *acbptr );
public     : virtual                                logical Unlock (acb *acbptr );
public     : virtual                                logical UnlockInternal (acb *acbptr );
public     : virtual                                logical Update (acb *acbptr, int32 entlen, int32 offset );
public     :                                        logical UpdateIntern (acb *acbptr, int32 entlen, int32 offset );
public     :                  OPAImpExp                  eb_RootBase (logical netopt, logical shared_rb );
public     :                                        EBI *getEBI (acb *acbptr );
public     : virtual          OPAImpExp                  ~eb_RootBase ( );
};

#pragma pack()
#endif
