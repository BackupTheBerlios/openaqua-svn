/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CDBHandle

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

\date     $Date: 2006/03/12 19:12:24,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CDBHandle_HPP
#define   CDBHandle_HPP

class     CDBHandle;

class     CDBHandle;
class     CDictionary;
class     CS_Connection;
class     Dictionary;
class     ODABAClient;
#include  <cPIACC.h>
#include  <cRecoveryType.h>
#include  <cResourceTypes.h>
#include  <sCACObject.hpp>
#include  <sCheckOptions.hpp>
#include  <sClientConnection.hpp>
#include  <sDBHandle.hpp>
#include  <sDBObjectHandle.hpp>
#pragma pack(8)

class  CDBHandle :public CACObject,
public virtual DBHandle
{
protected  :         CDictionary                                 *cdictionary ATTR_ALIGN(4);                                 // Dictionary handle
protected  :         char                                        *server_path;                                               //
protected  :         uint32                                       schema_version;                                            //
protected  :         uint32                                       system_version;                                            //

public     :
                     CDictionary                                 *get_cdictionary() { return(cdictionary); }
                     char                                        *get_server_path() { return(server_path); }
                     uint32                                       get_schema_version() { return(schema_version); }
                     uint32                                       get_system_version() { return(system_version); }
public     : virtual                             logical ActivateShadowBase ( );
public     : virtual                             logical BackupDB (char *target );
public     :                                                             CDBHandle (Dictionary *dict_ptr, char *cpath, PIACC accopt, logical online_version=NO, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     :                                                             CDBHandle (CS_Connection *cs_connection );
public     :                                                             CDBHandle ( );
public     : virtual                             logical ChangeRecovery (RecoveryType rec_type, char *rec_path );
public     : virtual                             logical CheckDB (CheckOptions check_opts, char *resnames );
public     : virtual                             logical CheckLicence (char *applname_w=NULL );
public     : virtual                             logical CheckLicence (char *lic_owner, char *lic_number );
public     : virtual                             logical CloseDBHandle ( );
public     : virtual                             logical CloseRecovery ( );
public     : virtual                             logical CloseWorkspace ( );
public     : virtual                             logical ConsolidateWorkspace ( );
public     : virtual                             logical DeactivateShadowBase ( );
public     : virtual                             logical DeleteWorkspace (char *names, char *user_name );
public     : virtual                             logical DisableWorkspace ( );
public     : virtual                             logical DiscardWorkspace ( );
public     : virtual                             logical EnableWorkspace (char *cpath );
public     : virtual                             logical ExecDBCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual                             logical ExistWorkspace (char *names );
public     : virtual                             logical FlushClusterPool ( );
public     : virtual                             CDBHandle *GetClientDBHandle ( );
public     : virtual                             int32 GetDatabaseID ( );
public     : virtual                             int16 GetNewTypeID ( );
public     : virtual                             char *GetPath ( );
public     : virtual                             char *GetRecoveryFile (uint16 recnum=0 );
public     : virtual                             uint16 GetRecoveryNum ( );
public     : virtual                             char *GetRecoveryPath ( );
public     : virtual                             uint16 GetRecoveryStartNumber ( );
public     : virtual                             RecoveryType GetRecoveryType ( );
public     : virtual                             uint16 GetSchemaVersion ( );
public     : virtual                             uint16 GetSystemVersion ( );
public     :                                     char *GetVersionString ( );
public     : virtual                             char *GetWorkspace (char *ws_root, int32 lindx0, char *user_name, char *names, logical refresh, char *ws_info=NULL );
public     : virtual                             logical InitDataArea (int16 mbnumber, uint16 sbnumber, uint16 danumber, char *filename, int32 dasize=0 );
public     : virtual                             logical InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize=0, logical largedb=NO, logical pindep=NO );
public     : virtual                             logical InitRecovery (char *recpath, uint16 recnum=0 );
public     : virtual                             logical InitSubBase (int16 mbnumber, uint16 sbnumber, char *filename, int32 dasize=0 );
public     : virtual                             logical IsLicenced ( );
public     : virtual                             logical LocateWorkspace (char *names );
public     : virtual                             logical OpenRecovery (char *userinfo=NULL, int16 uilen=0 );
public     : virtual                             logical OpenWorkspace (char *names, char *user_name, logical exclusive, char *cpath_w=NULL );
public     : virtual                             logical ResetLastSchemaVersion (logical reset_opt );
public     : virtual                             logical ResetLastVersion (uint16 version_nr=CUR_VERSION );
public     : virtual                             logical RestoreDB (char *target );
public     : virtual                             logical SetupTypeID (int16 sid );
public     : virtual                                                     ~CDBHandle ( );
};

#pragma pack()
#endif
