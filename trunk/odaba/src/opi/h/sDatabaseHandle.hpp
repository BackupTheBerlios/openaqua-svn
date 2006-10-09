/********************************* Class Declaration ***************************/
/**
\package  OPI - 
\class    DatabaseHandle

\brief    Database Handle
          Database  handle  must  be  created  for  accessing  data  in an ODABA
          database.  An  ODABA  database  must  be  connected with a dictionary,
          which defines the object model for the database. 
          Each  ODABA database  consists of  at least  one Database Object (Root
          Object) that is the owner od extents and other data collections. 
          When  creating a database handle the object  handle this is based on a
          database  object handle (-> DBObjectHandle)  for the root object, i.e.
          the  database handle inherits all  the functionality from the database
          object handle. 
          A  database may consists of a  number of physical separated mainbases,
          sub-bases  and data areas. This  is, however, handles internally after
          creating  the database. For creating  a multiple resource database the
          database  handle provides several functions  for initializing main and
          sub bases and data areas. 
          Moreover,  the  database  handle  provides  log and recovery features,
          that  allow logging all changes made on the database or recovering the
          database in case of errors. 
          The  workspace feature supported  by the database  handle is a sort of
          persistent  transactions.  It  allows  storing  changes  for  a longer
          period  outside the  database and  consolidating or discarding changes
          when requested by the user.

\date     $Date: 2006/06/25 17:07:36,54 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DatabaseHandle_HPP
#define   DatabaseHandle_HPP

#include "copadll.h"
class     DatabaseHandle;

class     ACObject;
class     DBHandle;
class     ODABAClient;
#include  <cPIACC.h>
#include  <cRecoveryType.h>
#include  <cResourceTypes.h>
#include  <sCheckOptions.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#pragma pack(8)

class  DatabaseHandle :public DBObjectHandle
{

public     :
public     :                  OPIImpExp             logical ActivateShadowBase ( );
public     :                  OPIImpExp             logical BackupDB (char *target );
public     :                  OPIImpExp             logical ChangeRecovery (RecoveryType rec_type, char *rec_path );
public     :                  OPIImpExp             logical CheckDB (CheckOptions check_opts, char *source );
public     :                  OPIImpExp             logical CheckLicence (char *lic_owner, char *lic_number );
public     :                  OPIImpExp             logical CheckLicence (char *applname_w=NULL );
public     :                  OPIImpExp             logical Close ( );
public     :                  OPIImpExp             logical CloseRecovery ( );
public     :                  OPIImpExp             logical CloseWorkspace ( );
public     :                  OPIImpExp             logical ConsolidateWorkspace ( );
public     :                  OPIImpExp                  DatabaseHandle (DictionaryHandle &dict_handle, char *cpath, PIACC accopt, logical w_netopt, logical online_version=NO, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic, logical sysenv=NO );
public     :                  OPIImpExp                  DatabaseHandle (const DatabaseHandle &dbhandle_refc );
public     :                  OPIImpExp                  DatabaseHandle (DBHandle *_dbhandle );
public     :                  OPIImpExp                  DatabaseHandle (char *cpath, int32 dasize=0, logical pindep=NO );
public     :                  OPIImpExp                  DatabaseHandle (DictionaryHandle &dict_handle, PIACC accopt );
public     :                  OPIImpExp                  DatabaseHandle ( );
public     :                  OPIImpExp             logical DeactivateShadowBase ( );
public     :                  OPIImpExp             logical DeleteWorkspace (char *ws_names, char *user_name=NULL );
public     :                  OPIImpExp             logical DisableWorkspace ( );
public     :                  OPIImpExp             logical DiscardWorkspace ( );
public     :                  OPIImpExp             logical EnableWorkspace (char *sdw_path=NULL );
public     :                  OPIImpExp             logical ExecuteDatabaseAction (char *action_name, char *parm_string );
public     :                  OPIImpExp             logical ExistWorkspace (char *ws_names );
public     :                  OPIImpExp             logical FlushClusterPool ( );
public     :                  OPIImpExp             int32 GetDatabaseID ( );
public     :                  OPIImpExp             int16 GetNewTypeID ( );
public     :                  OPIImpExp             char *GetPath ( );
public     :                  OPIImpExp             char *GetRecoveryFile (uint16 recnum );
public     :                  OPIImpExp             uint16 GetRecoveryNum ( );
public     :                  OPIImpExp             char *GetRecoveryPath ( );
public     :                  OPIImpExp             uint16 GetRecoveryStartNumber ( );
public     :                  OPIImpExp             RecoveryType GetRecoveryType ( );
public     :                  OPIImpExp             uint16 GetSchemaVersion ( );
public     :                  OPIImpExp             uint16 GetSystemVersion ( );
public     :                  OPIImpExp             char *GetVersionString ( );
public     :                  OPIImpExp             char *GetWorkspace (char *ws_root, int32 ws_index, char *user_name=NULL, char *ws_name=NULL, logical refresh_opt=NO, char *ws_info=NULL );
public     :                  OPIImpExp             logical IgnoreWriteProtect ( );
public     :                  OPIImpExp             logical InitDataArea (int16 mbnumber, int16 sbnumber, uint16 danumber, char *filename, int32 dasize=0 );
public     :                  OPIImpExp             logical InitMainBase (int16 mbnumber, char *filename, int16 lowEBN, int16 highEBN, int32 dasize=0, logical largedb=NO, logical pindep=NO );
public     :                  OPIImpExp             logical InitRecovery (char *recpath, uint16 recnum );
public     :                  OPIImpExp             logical InitSubBase (int16 mbnumber, int16 sbnumber, char *filename, int32 dasize=0 );
public     :                  OPIImpExp             logical IsLicenced ( );
public     :                  OPIImpExp             logical IsShared ( );
public     :                  OPIImpExp             logical LocateWorkspace (char *ws_names );
public     :                  OPIImpExp             logical Open (DictionaryHandle &dict_handle, char *cpath, PIACC accopt, logical w_netopt, logical online_version=NO, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic, logical sysenv=NO );
public     :                  OPIImpExp             logical Open (char *cpath, int32 dasize=0, logical pindep=NO );
public     :                  OPIImpExp             logical Open (DictionaryHandle &dict_handle, PIACC accopt );
public     :                  OPIImpExp             logical OpenDatabase (DictionaryHandle &dict_handle, char *cpath, PIACC accopt, logical w_netopt, logical online_version=NO, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic, logical sysenv=NO );
public     :                  OPIImpExp             logical OpenRecovery (char *userinfo, int16 uilen );
public     :                  OPIImpExp             logical OpenWorkspace (char *ws_names, char *user_name=NULL, logical exclusive=NO, char *ws_path=NULL );
public     :                  OPIImpExp             logical RecreateExtent (char *extnames );
public     :                  OPIImpExp             logical ResetLastSchemaVersion (logical reset_opt );
public     :                  OPIImpExp             logical ResetLastVersion (uint16 version_nr=CUR_VERSION );
public     :                  OPIImpExp             logical RestoreDB (char *source );
public     :                  OPIImpExp             logical SetupTypeID (int16 sid );
public     :                                        DBHandle *get_dbhandle ( );
public     :                  OPIImpExp             NOTYPE operator bool ( ) const;
public     :                  OPIImpExp             logical operator!= (DatabaseHandle &dbhandle_ref );
public     :                  OPIImpExp             logical operator!= (DBObjectHandle &obhandle_ref );
public     :                                        DBHandle *operator-> ( );
public     :                  OPIImpExp             DatabaseHandle &operator= (const DatabaseHandle &dbhandle_refc );
public     :                  OPIImpExp             DatabaseHandle &operator= (ACObject *acobject );
public     :                  OPIImpExp                  ~DatabaseHandle ( );
};

#pragma pack()
#endif
