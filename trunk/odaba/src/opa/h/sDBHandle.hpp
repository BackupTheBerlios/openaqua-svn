/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    DBHandle

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

\date     $Date: 2006/06/04 13:16:43,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBHandle_HPP
#define   DBHandle_HPP

class     DBHandle;

#include  <sDLL.h>
class     ACObject;
class     CDBHandle;
class     CTX_DataBase;
class     DBHandle;
class     DBResource;
class     Dictionary;
class     EB_Header;
class     LDBHandle;
class     RessourceLock;
class     exd;
#include  <cPIACC.h>
#include  <cRecoveryType.h>
#include  <sACObject.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  DBHandle :public virtual ACObject
{
protected  :         Dictionary                                  *dictionary;                                                // 
protected  :         DLL(ACObject)                               *root_object_list;                                          // 
protected  :         logical                                      net_option;                                                // 
protected  :         int8                                         system_env;                                                // 
protected  :         DBResource                                  *resource;                                                  // 
protected  :         RessourceLock                               *db_lock;                                                   // 
protected  :         CTX_DataBase                                *context;                                                   // 

public     :
                     Dictionary                                  *get_dictionary() { return(dictionary); }
                     DLL(ACObject)                               *get_root_object_list() { return(root_object_list); }
                     logical                                      get_net_option() { return(net_option); }
                     int8                                         get_system_env() { return(system_env); }
                     DBResource                                  *get_resource() { return(resource); }
                     RessourceLock                               *get_db_lock() { return(db_lock); }
                     CTX_DataBase                                *get_context() { return(context); }
public     : virtual          OPAImpExp             logical ActivateShadowBase ( );
public     : virtual          OPAImpExp             logical BackupDB (char *target );
public     : virtual          OPAImpExp             logical ChangeRecovery (RecoveryType rec_type, char *rec_path );
public     : virtual          OPAImpExp             logical CheckDB (CheckOptions check_opts, char *resnames );
public     : virtual          OPAImpExp             logical CheckLicence (char *lic_owner, char *lic_number );
public     : virtual          OPAImpExp             logical CheckLicence (char *applname_w=NULL );
public     : virtual          OPAImpExp             logical CloseDBHandle ( );
public     : virtual          OPAImpExp             logical CloseRecovery ( );
public     : virtual          OPAImpExp             logical CloseWorkspace ( );
public     : virtual          OPAImpExp             logical ConsolidateWorkspace ( );
public     : virtual          OPAImpExp             ACObject *CreateACObject (PIACC accopt, uint16 version_nr=CUR_VERSION );
public     : virtual          OPAImpExp             ACObject *CreateACObject ( );
public     :                                        logical CreateContext ( );
public     : virtual          OPAImpExp             EB_Number CreateEntry (int16 mbnumber, uint16 sbnumber, EB_Number clnumb, uint16 version_nr=CUR_VERSION );
public     :                  OPAImpExp                  DBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     :                  OPAImpExp                  DBHandle (Dictionary *dictptr, PIACC accopt );
public     :                  OPAImpExp                  DBHandle ( );
public     :                  OPAImpExp                  DBHandle (char *cpath, int16 lowEBN, int16 highEBN, int32 dasize=0, logical largedb=NO );
public     : virtual          OPAImpExp             logical DeactivateShadowBase ( );
public     : virtual          OPAImpExp             logical DeleteWorkspace (char *names, char *user_name );
public     :                                        logical DiffersFrom (DBHandle *dbhandle );
public     : virtual          OPAImpExp             logical DisableWorkspace ( );
public     : virtual          OPAImpExp             logical DiscardWorkspace ( );
public     : virtual          OPAImpExp             logical EnableWorkspace (char *cpath );
public     : virtual          OPAImpExp             logical ExecDBCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual          OPAImpExp             logical ExistWorkspace (char *names );
public     : virtual          OPAImpExp             logical FlushClusterPool ( );
public     : virtual          OPAImpExp             CDBHandle *GetClientDBHandle ( );
public     :                                        DatabaseHandle *GetDatabaseHandle ( );
public     : virtual          OPAImpExp             int32 GetDatabaseID ( );
public     : virtual          OPAImpExp             LDBHandle *GetLocalDBHandle ( );
public     : virtual          OPAImpExp             int16 GetNewTypeID ( );
public     : virtual          OPAImpExp             char *GetRecoveryFile (uint16 recnum=0 );
public     : virtual          OPAImpExp             uint16 GetRecoveryNum ( );
public     : virtual          OPAImpExp             char *GetRecoveryPath ( );
public     : virtual          OPAImpExp             uint16 GetRecoveryStartNumber ( );
public     : virtual          OPAImpExp             RecoveryType GetRecoveryType ( );
public     : virtual          OPAImpExp             uint16 GetSchemaVersion ( );
public     : virtual          OPAImpExp             uint16 GetSystemVersion ( );
public     : virtual          OPAImpExp             int16 GetTempMain ( );
public     : virtual          OPAImpExp             DBHandle *GetThisDBHandle ( );
public     : virtual          OPAImpExp             char *GetVersionString ( );
public     : virtual          OPAImpExp             char *GetWorkspace (char *ws_root, int32 lindx0, char *user_name, char *names, logical refresh, char *ws_info=NULL );
public     :                  OPAImpExp             logical IgnoreWriteProtect ( );
public     : virtual          OPAImpExp             logical InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     : virtual          OPAImpExp             logical InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL, logical largedb=NO, logical pindep=NO );
public     : virtual          OPAImpExp             logical InitRecovery (char *recpath, uint16 recnum=0 );
public     : virtual          OPAImpExp             logical InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize=0, char *server=NULL, EB_Header *headerpt=NULL );
public     :                                        void Initialize (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical netopt, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     :                                        void Initialize (Dictionary *dict_ptr, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     : virtual          OPAImpExp             logical IsLicenced ( );
public     : virtual          OPAImpExp             logical LocateWorkspace (char *names );
public     : virtual          OPAImpExp             logical OpenRecovery (char *userinfo=NULL, int16 uilen=0 );
public     : virtual          OPAImpExp             logical OpenWorkspace (char *names, char *user_name, logical exclusive, char *cpath_w=NULL );
public     : virtual          OPAImpExp             logical RecreateExtent (char *extnames );
public     : virtual          OPAImpExp             logical ResetLastSchemaVersion (logical reset_opt );
public     : virtual          OPAImpExp             logical ResetLastVersion (uint16 version_nr=CUR_VERSION );
public     : virtual          OPAImpExp             logical RestoreDB (char *source );
public     : virtual          OPAImpExp             logical SetupTypeID (int16 sid );
public     : virtual          OPAImpExp             logical Write (exd *exdptr );
public     : virtual          OPAImpExp                  ~DBHandle ( );
public     : virtual          OPAImpExp             char *GetPath ( ){

  return(NULL);

}

};

#pragma pack()
#endif
