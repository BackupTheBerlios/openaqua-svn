/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    Services

\brief    System Services


\date     $Date: 2006/07/27 12:28:29,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Services_HPP
#define   Services_HPP

class     Services;

class     DBErrorHandle;
class     DBObjectHandle;
class     DataSourceHandle;
class     Error;
class     ODABAClient;
#include  <ssvel.hpp>
#pragma pack(8)

class  Services
{
protected  :         DataSourceHandle                            *data_catalogue;                                            // 
protected  :         svel                                         file_definitions;                                          // 
protected  :         DataSourceHandle                            *system_database;                                           // 
protected  :         DBErrorHandle                               *error_handle;                                              // 
protected  :         char                                         ini_file[257];                                             // 
protected  :         PropertyHandle                               ds_pi;                                                     // 

public     :
                     DataSourceHandle                            *get_data_catalogue() { return(data_catalogue); }
                     svel                                        &get_file_definitions() { return(file_definitions); }
                     DataSourceHandle                            *get_system_database() { return(system_database); }
                     DBErrorHandle                               *get_error_handle() { return(error_handle); }
                     char                                        *get_ini_file() { return(ini_file); }
public     :                                        logical DeInitialize ( );
public     :                  OPAImpExp             DBObjectHandle &GetDataCatalogue ( );
public     :                                        char *GetDataSource (int32 indx0 );
public     :                  OPAImpExp             DBErrorHandle *GetErrorHandle ( );
public     :                  OPAImpExp             char *GetFileName (char *sym_nams, char *cpath, int32 maxlen );
public     :                  OPAImpExp             char *GetIniFile ( );
public     :                  OPAImpExp             DictionaryHandle &GetSystemDictionary ( );
public     :                  OPAImpExp             DBObjectHandle &GetSystemObject ( );
public     :                                        void Initialize (CClient *odaba_client, char *inipath, char *progdir );
public     :                  OPAImpExp             void RegisterError (Error *error_instance, DBObjectHandle *object_handle );
public     :                                        logical RegisterThread ( );
public     :                                             Services ( );
public     :                  OPAImpExp             void SetErrorHandle (DBErrorHandle *err_hdl );
public     :                                        void SetProgPath (char *progdir );
public     :                                        logical SetSymVariables ( );
public     :                                        logical SetupDataSource (DataSourceHandle *datasource );
public     :                  OPAImpExp             void UnregisterError (Error *error_instance );
public     :                                             ~Services ( );
};

#pragma pack()
#endif
