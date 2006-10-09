/********************************* Class Declaration ***************************/
/**
\package  OPI - 
\class    DBObjectHandle

\brief    Database Object handle
          Database  object  handles  are  necessary  for  accessing  data  in an
          database  object. A  database object  can be  considered as a database
          within  a database. Each  database has a  root database object on top.
          Below  each  database  object  any  number  of  subordinated  database
          objects can be created. 
          Database  objects  in  a  database  are  logically  separated  but not
          physically.  Thus,  it  becomes  possible  to  establish links between
          structure  instances  in  different  database  objects.  Each database
          object  has, however, its own  extents containing the global instances
          of the database object. 
          The  database object  handle for  the root  database object is part of
          the  database  handle  (->  DatabaseHandle)  and need not to be opened
          explicitly. 
          A  database  object  handle  is  required  for opening extent property
          handles for accessing structure instances stored in extents.
          The  database  object  handle administrates transactions. Transactions
          can  be  started  and  stopped  for  each  object handle. The database
          object  handle is not thread save,  i.e. a database object handle must
          not be used simultaneously in different threads. 
          The  database  object  supports  version  slices,  i.e.  each database
          object may have its own current version.

\date     $Date: 2006/08/27 20:20:36,71 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBObjectHandle_HPP
#define   DBObjectHandle_HPP
#include "copadll.h"

class     DBObjectHandle;

#include  <sGSRT.h>
class     ExtentListEntry;
#ifndef   INTERVAL_dttm_HPP
#define   INTERVAL_dttm_HPP
#include  <sINTERVAL.h>
#endif
class     ACObject;
class     DBFieldDef;
class     DBStructDef;
class     DataSourceHandle;
#include  <cPIACC.h>
#include  <cResourceTypes.h>
#include  <sDBObjectHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODABAClient.hpp>
#include  <sObjectReferenceHandle.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  DBObjectHandle :public ObjectReferenceHandle
{

public     :
public     :                  OPIImpExp             int16 BeginTransaction (logical ext_TA=NO, int16 w_maxnum=AUTO );
public     :                  OPIImpExp             logical ChangeTimeStamp (uint16 version_nr=CUR_VERSION, dttm timestamp=dttm() );
public     :                  OPIImpExp             logical Close ( );
public     :                  OPIImpExp             logical CommitTransaction (int16 talevel=AUTO );
public     :                  OPIImpExp             PropertyHandle CreateTempPropertyHandle (DBFieldDef *dbfielddef );
public     :                  OPIImpExp             PropertyHandle CreateTempPropertyHandle (PropertyHandle &prophdl_ref );
public     :                  OPIImpExp             PropertyHandle CreateTempPropertyHandle (PropertyHandle &prophdl_ref, char *grouping_rule );
public     :                  OPIImpExp                  DBObjectHandle (DatabaseHandle &dbhandle, PIACC accopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp                  DBObjectHandle (DBObjectHandle &dbobject, int32 objid, PIACC accopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp                  DBObjectHandle (DBObjectHandle &dbobject, char *objname, PIACC accopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp                  DBObjectHandle (ODABAClient &odaba_client, char *data_source_name, PIACC access_mode=PI_Read, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp                  DBObjectHandle (const DBObjectHandle &obhandle_refc );
public     :                  OPIImpExp                  DBObjectHandle (ACObject *acobject );
public     :                  OPIImpExp                  DBObjectHandle ( );
public     :                  OPIImpExp             logical DeleteExtent (char *extnames );
public     :                  OPIImpExp             logical DeleteExtentRef (char *extnames );
public     :                  OPIImpExp             void DisableEventHandling ( );
public     :                  OPIImpExp             void EnableEventHandling ( );
public     :                  OPIImpExp             logical EventHandling ( );
public     :                  OPIImpExp             logical ExecuteDBObjectAction (char *action_name, char *parm_string );
public     :                  OPIImpExp             PropertyHandle ExecuteExpression (DBObjectHandle &res_obhandle, char *expression );
public     :                  OPIImpExp             logical ExtentExist (char *extnames );
public     :                  OPIImpExp             PIACC GetAccess ( );
public     :                  OPIImpExp             char *GetActionResult ( );
public     :                  OPIImpExp             DatabaseHandle &GetDBHandle ( );
public     :                  OPIImpExp             DataSourceHandle *GetDataSource ( );
public     :                  OPIImpExp             DictionaryHandle &GetDictionary ( ) const;
public     :                  OPIImpExp             int16 GetExtInstModCount (int32 objid );
public     :                  OPIImpExp             char *GetExtent (int32 indx0 );
public     :                  OPIImpExp             GSRT(ExtentListEntry) *GetExtentList ( );
public     :                  OPIImpExp             DBObjectHandle &GetHighObject ( );
public     :                  OPIImpExp             char *GetObject (int32 indx0 );
public     :                  OPIImpExp             char *GetServerVariable (char *var_name );
public     :                  OPIImpExp             DBStructDef *GetStructDef (char *scoped_name );
public     :                  OPIImpExp             uint16 GetSystemVersion ( );
public     :                  OPIImpExp             dttm GetTimeStamp (uint16 version_nr=CUR_VERSION );
public     :                  OPIImpExp             int16 GetTransactionLevel ( );
public     :                  OPIImpExp             uint16 GetVersion (dttm timestamp=dttm() );
public     :                  OPIImpExp             logical IsClient ( );
public     :                  OPIImpExp             logical IsEmpty ( );
public     :                                        void IsEventHandlingEnabled ( );
public     :                  OPIImpExp             logical IsOpened ( );
public     :                  OPIImpExp             logical IsServer ( );
public     :                  OPIImpExp             logical IsValid ( ) const;
public     :                  OPIImpExp             logical NewVersion (dttm timestamp=dttm(), uint16 version_nr=CUR_VERSION );
public     :                  OPIImpExp             logical Open (DatabaseHandle &dbhandle, PIACC accopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp             logical Open (DBObjectHandle &dbobject, int32 objid, PIACC accopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp             logical Open (DBObjectHandle &dbobject, char *objname, PIACC accopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp             logical Open (ODABAClient &odaba_client, char *data_source_name, PIACC access_mode=PI_Read, ResourceTypes local_ressources=RES_automatic );
public     :                  OPIImpExp             logical OpenObject (DBObjectHandle &dbobject, char *objname, PIACC accopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic );
public     :                                        void Reset ( );
public     :                  OPIImpExp             void ResetError ( );
public     :                                        void ResetErrorObject ( );
public     :                  OPIImpExp             logical RollBack (int16 talevel=AUTO );
public     :                  OPIImpExp             logical SaveExtentList ( );
public     :                  OPIImpExp             void SetActionResult (char *result_string );
public     :                  OPIImpExp             int8 SetOverload (logical overload_opt );
public     :                  OPIImpExp             logical SetServerVariable (char *var_name, char *var_string );
public     :                  OPIImpExp             logical SetUserDefinedIdentity (logical identity_opt );
public     :                  OPIImpExp             logical SetVersion (uint16 version_nr=CUR_VERSION );
public     :                  OPIImpExp             logical SetVersion (dbdt date );
public     :                  OPIImpExp             logical SetVersion (dttm timestamp=dttm() );
public     :                  OPIImpExp             logical UpdateTimestamp (logical time_stamp_enable=YES );
public     :                  OPIImpExp             int32 VersionCount ( );
public     :                  OPIImpExp             INTERVAL(dttm) VersionIntervall (uint16 version_nr=CUR_VERSION );
public     :                                        ACObject *get_obhandle ( ) const;
public     :                  OPIImpExp             NOTYPE operator bool ( ) const;
public     :                                        ACObject *operator-> ( ) const;
public     :                  OPIImpExp             DBObjectHandle &operator= (const DBObjectHandle &obhandle_refc );
public     :                  OPIImpExp             logical operator== (const DBObjectHandle &obhandle_refc );
public     :                  OPIImpExp             logical operator== (const DatabaseHandle &dbhandle_refc );
public     :                  OPIImpExp             logical operator== (const DictionaryHandle &dictionary_refc );
public     :                  OPIImpExp                  ~DBObjectHandle ( );
};

#pragma pack()
#endif
