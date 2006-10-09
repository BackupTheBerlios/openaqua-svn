/********************************* Class Declaration ***************************/
/**
\package  OPI - 
\class    DataSourceHandle

\brief    Data source
          A  data  source  describes  an  ODABA  data  source on a certain level
          (Dictionary,  Database, DBObject, Extent, Instance). A data source can
          be  parametrized by  means of  an INI-file.  The INI file contains the
          names  for the  objects on  the different  levels. Not specified lower
          levels  are not opened and have to  be opened in the application (e.g.
          when  defining only dictionary  and database the  extent is not opened
          and  no instance is selected), The datasource is defined as section in
          the INI-file starting with the [datasource name]. 
          A  data  source  can  be  directed  to  a  server.  In  this  case the
          datasource  has  to  be  opened  with  a connected ODABA client or the
          INI-file  must contain  a server  specification. In  the last case the
          data  source  connects  to  the  server automatically when opening the
          data source. The connection is owned by the datasource in this case.
          A  data source cane be opened and  closed as a whole (Open(), Close())
          or  separately on each  definition level (Connect(), OpenDictionary(),
          ...).
          A  data source may have a connection  name, which is used to cache the
          connection  when running in client/server mode. The connection name is
          used  to reconnect to  the server using  a cached connection, which is
          faster than re-establishing the connection from scratch.

\date     $Date: 2006/06/14 12:47:03,78 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DataSourceHandle_HPP
#define   DataSourceHandle_HPP
#include "copadll.h"

class     DataSourceHandle;

class     DataSourceHandle;
class     PropertyHandle;
class     svel;
#include  <cPIACC.h>
#include  <sDBObjectHandle.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODABAClient.hpp>
#pragma pack(8)

class  DataSourceHandle
{
public     :         ODABAClient                                  client;                                                    // 
public     :         DictionaryHandle                             dictionary;                                                // 
public     :         DatabaseHandle                               reshandle;                                                 // 
public     :         DatabaseHandle                               dbhandle;                                                  // 
public     :         DBObjectHandle                               object_handle;                                             // 
public     :         PropertyHandle                              *extent_pi;                                                 // 
public     :         char                                         data_source[41];                                           // 
public     :         char                                         server_name[64];                                           // 
public     :         int32                                        server_port;                                               // 
public     :         char                                         connection_name[256];                                      // 
public     :         char                                         dict_path[256];                                            // 
public     :         char                                         res_path[256];                                             // 
public     :         char                                         db_path[256];                                              // 
public     :         char                                         workspace[256];                                            // 
public     :         char                                         object_name[41];                                           // 
public     :         char                                         struct_name[41];                                           // 
public     :         char                                         extent_name[41];                                           // 
public     :         char                                         inst_key[256];                                             // 
public     :         uint16                                       system_version;                                            // 
public     :         logical                                      online_version;                                            // 
public     :         char                                         sys_appl;                                                  // 
public     :         logical                                      collopt;                                                   // 
protected  :         int16                                        transaction;                                               // 
public     :         uint16                                       version;                                                   // 
public     :         uint16                                       schema_version;                                            // 
public     :         PIACC                                        accmode;                                                   // 
public     :         logical                                      netopt;                                                    // 
protected  :         logical                                      client_connected;                                          // 
protected  :         logical                                      client_created;                                            // 
protected  :         logical                                      dict_opened;                                               // 
protected  :         logical                                      res_opened;                                                // 
protected  :         logical                                      base_opened;                                               // 
protected  :         logical                                      object_opened;                                             // 
protected  :         logical                                      extent_opened;                                             // 

public     :
                     int16                                        get_transaction() { return(transaction); }
                     logical                                      get_client_connected() { return(client_connected); }
                     logical                                      get_client_created() { return(client_created); }
                     logical                                      get_dict_opened() { return(dict_opened); }
                     logical                                      get_res_opened() { return(res_opened); }
                     logical                                      get_base_opened() { return(base_opened); }
                     logical                                      get_object_opened() { return(object_opened); }
                     logical                                      get_extent_opened() { return(extent_opened); }
public     :                  OPIImpExp             logical BeginTransaction (logical ext_ta=NO );
public     :                  OPIImpExp             logical Close ( );
public     :                  OPIImpExp             logical CloseDBObject ( );
public     :                  OPIImpExp             logical CloseDatabase ( );
public     :                  OPIImpExp             logical CloseDictionary ( );
public     :                  OPIImpExp             logical CloseProperty ( );
public     :                  OPIImpExp             logical CloseResourceDB ( );
public     :                  OPIImpExp             logical CommitTransaction ( );
public     :                  OPIImpExp             logical Connect (ODABAClient &odaba_client );
public     :                  OPIImpExp                  DataSourceHandle ( );
public     :                  OPIImpExp             logical Disconnect ( );
public     :                  OPIImpExp             ODABAClient &GetClient ( );
public     :                                        void Initialize ( );
public     :                  OPIImpExp             logical Open (ODABAClient &odaba_client, PIACC acc_mod=PI_Read );
public     :                  OPIImpExp             logical Open (ODABAClient &odaba_client, char *ini_file, char *datasource_name );
public     :                  OPIImpExp             logical Open (ODABAClient &odaba_client, char *datasource_name );
public     :                  OPIImpExp             DBObjectHandle &OpenDBObject ( );
public     :                  OPIImpExp             DatabaseHandle &OpenDatabase ( );
public     :                  OPIImpExp             DictionaryHandle &OpenDictionary (PIACC accopt );
public     :                  OPIImpExp             PropertyHandle *OpenProperty (char *extname );
public     :                  OPIImpExp             DatabaseHandle &OpenResourceDB ( );
public     :                                        void ResetObjectHandle ( );
public     :                  OPIImpExp             logical RollBack ( );
public     :                  OPIImpExp             logical SetConnectionName (char *cache_string=NULL );
public     :                  OPIImpExp             logical SetDBObject (DBObjectHandle &ohandle, char *w_objname=NULL );
public     :                  OPIImpExp             logical SetDataSource (DataSourceHandle *dbdefptr );
public     :                  OPIImpExp             logical SetDatabase (DatabaseHandle &db_handle, char *w_basepath=NULL );
public     :                  OPIImpExp             logical SetDictionary (DictionaryHandle &dictptr, char *w_dictpath=NULL );
public     :                  OPIImpExp             logical SetResourceDB (DatabaseHandle &db_handle, char *w_basepath=NULL );
public     :                  OPIImpExp             logical SetVariables (char *datasource_name );
public     :                  OPIImpExp             logical Setup (char *ini_file, char *datasource_name );
public     :                  OPIImpExp             logical SetupVariables (char *datasource_name );
public     :                                        DictionaryHandle &get_dictionary ( );
public     :                                        DBObjectHandle &get_object_handle ( );
public     :                                        DatabaseHandle &get_res_handle ( );
public     :                  OPIImpExp             DataSourceHandle &operator= (DataSourceHandle &datasource_ref );
public     :                  OPIImpExp                  ~DataSourceHandle ( );
};

#pragma pack()
#endif
