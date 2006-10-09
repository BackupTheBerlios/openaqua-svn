/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    Services

\brief    System Services


\date     $Date: 2006/08/27 20:30:06,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Services"

#include  <popa7.h>
#include  <sDBErrorHandle.hpp>
#include  <sDBObjectHandle.hpp>
#include  <sDataSourceHandle.hpp>
#include  <sError.hpp>
#include  <sODABAClient.hpp>
#include  <sProcessInfo.hpp>
#include  <sThreadEntry.hpp>
#include  <ssvel.hpp>
#include  <sServices.hpp>


/******************************************************************************/
/**
\brief  DeInitialize - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeInitialize"

logical Services :: DeInitialize ( )
{

  CTXError().SetHandle(NULL);
  SDBError().SetHandle(NULL);
  OQLError().SetHandle(NULL);
  SOSError().SetHandle(NULL);
  
  delete error_handle;
  error_handle = NULL;
  
  ds_pi.Close();
  delete data_catalogue;
  data_catalogue = NULL;

  delete system_database;
  system_database = NULL;

  memset(ini_file,0,sizeof(ini_file));
  return(NO);
}

/******************************************************************************/
/**
\brief  GetDataCatalogue - 



\return object_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataCatalogue"

DBObjectHandle &Services :: GetDataCatalogue ( )
{
  static DBObjectHandle  statobj;
  return ( this && data_catalogue 
           ?  data_catalogue->get_object_handle()
           :  statobj                        );

}

/******************************************************************************/
/**
\brief  GetDataSource - 



\return data_source_name - Data source name

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDataSource"

char *Services :: GetDataSource (int32 indx0 )
{
  char         *ds_name = NULL;
  if ( ds_pi(indx0) )
    ds_name = ds_pi.GetString("name");
  return(ds_name);
}

/******************************************************************************/
/**
\brief  GetErrorHandle - 



\return error_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetErrorHandle"

DBErrorHandle *Services :: GetErrorHandle ( )
{

  return ( this ? error_handle : NULL );

}

/******************************************************************************/
/**
\brief  GetFileName - 



\return filenames - 

\param  sym_nams - 
\param  cpath - Complete path
\param  maxlen - Size of the output buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFileName"

char *Services :: GetFileName (char *sym_nams, char *cpath, int32 maxlen )
{

BEGINSEQ
  if ( cpath && sym_nams )
    strcpy(cpath,sym_nams);
  
  if ( !this || !cpath || !sym_nams )                 ERROR
  
  file_definitions.svelexc(cpath,maxlen);
RECOVER

ENDSEQ
  return(cpath);
}

/******************************************************************************/
/**
\brief  GetIniFile - 



\return filenames - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIniFile"

char *Services :: GetIniFile ( )
{

  return ( this ? ini_file : NULL );


}

/******************************************************************************/
/**
\brief  GetSystemDictionary - GetSystemDictionary



\return dictionary - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemDictionary"

DictionaryHandle &Services :: GetSystemDictionary ( )
{
  static DictionaryHandle  statdict;
  return ( this && system_database 
           ? system_database->get_dictionary() 
           : statdict );

}

/******************************************************************************/
/**
\brief  GetSystemObject - 



\return object_handle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemObject"

DBObjectHandle &Services :: GetSystemObject ( )
{
  static DBObjectHandle  statobj;
  return ( this && system_database 
           ?  system_database->get_object_handle()
           :  statobj                        );

}

/******************************************************************************/
/**
\brief  Initialize - Initialize Services




\param  odaba_client - 
\param  inipath - 
\param  progdir - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void Services :: Initialize (CClient *odaba_client, char *inipath, char *progdir )
{
  DBObjectHdl     object_handle;
  ODABAClient     oc(odaba_client ? odaba_client : GetMainClient().GetClientPtr());
  char            newini[256];

BEGINSEQ
  SetProgPath(progdir);
  progdir = file_definitions.svelget("__PROGPATH");  SOSRESET
  if ( inipath )
    strcpy(newini,inipath);
  else
  {
    *newini = 0;
    if ( progdir && *progdir )
    {
      strcpy(newini,progdir);
      if ( newini[strlen(newini)-1] == '\\' )
        newini[strlen(newini)-1] = '/';
      if ( newini[strlen(newini)-1] != '/' )
        strcat(newini,"/");
    }
    strcat(newini,"ODABA2.ini");
  }
  
  if ( !strcmp(ini_file,newini) && *ini_file &&
       (!system_database || system_database->dictionary.IsOpened()) )    
                                                     LEAVESEQ
  DeInitialize();
  if ( !odaba_client || odaba_client == GetMainClient().GetClientPtr() )
    oc.Disconnect();
  
  strcpy(ini_file,newini);
  file_definitions.svelfini(ini_file,"FILE-CATALOGUE");

  SetErrorHandle(new DBErrorHandle(object_handle));
  
  if ( data_catalogue )
  {
    data_catalogue->Close();
    delete data_catalogue;
    data_catalogue = NULL;
  }
  if ( !file_definitions.CheckSection("DATA-CATALOGUE") )
  {       
    data_catalogue = new DataSourceHandle();
    if ( data_catalogue->Open(oc,ini_file,"DATA-CATALOGUE") )
    {
      delete data_catalogue;
      data_catalogue = NULL;
    }
    else
    {
      ds_pi.Open(data_catalogue->dbhandle,"DataSource",PI_Read);   
      SetSymVariables();
    }
  }
  
  if ( system_database )
  {
    system_database->Close();
    delete system_database;
    system_database = NULL;
  }
  if ( !file_definitions.CheckSection("SYSTEM") )
  {
    system_database = new DataSourceHandle();
    if ( system_database->Open(oc,ini_file,"SYSTEM") )
    {
      delete system_database;
      system_database = NULL;
    }
    else
    {
      GetSysVariable("ODABA_PATH");
      GetSysVariable("PROGPATH");
    }
  }
    
  if ( GetSystemObject() )
    object_handle = GetSystemObject();
  if ( error_handle )
    error_handle->SetObjectHandle(object_handle);  

ENDSEQ

}

/******************************************************************************/
/**
\brief  RegisterError - 




\param  error_instance - 
\param  object_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterError"

void Services :: RegisterError (Error *error_instance, DBObjectHandle *object_handle )
{

  if ( this && error_instance )
  {
    if ( error_handle )
      error_instance->SetHandle(error_handle);
    if ( object_handle || (object_handle = &GetSystemObject()) )
      error_instance->SetSource((void *)object_handle);
  }

}

/******************************************************************************/
/**
\brief  RegisterThread - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterThread"

logical Services :: RegisterThread ( )
{
  ErrorHandle   *error_handle = GetErrorHandle();
  ProcessInfo   *procinfo;
  char          *prot_file;
  logical        term = NO;
  procinfo = ThreadEntry::GetCurProcInfo();
  
  CTXError().SetHandle(error_handle);
  SDBError().SetHandle(error_handle);
  OQLError().SetHandle(error_handle);
  SOSError().SetHandle(error_handle);

  if ( (prot_file = GetSysVariable("TRACE")) ||
       (prot_file = GetSysVariable("TEMP"))     )
  {
    SetSysVariable("TRACE",prot_file);
    procinfo->SetProtocolFile(prot_file);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Services - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Services"

     Services :: Services ( )
                     : data_catalogue(NULL),
  file_definitions(50),
  system_database(NULL),
  error_handle(NULL)

{

  *ini_file = 0;

}

/******************************************************************************/
/**
\brief  SetErrorHandle - 




\param  err_hdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetErrorHandle"

void Services :: SetErrorHandle (DBErrorHandle *err_hdl )
{
  CTX_Base          *ctxptr = NULL;
BEGINSEQ
  if ( error_handle )
  {
    if ( error_handle == err_hdl )                  LEAVESEQ
    ctxptr = GetApplicationContext();
    delete error_handle;
  }
  error_handle = err_hdl;
  if ( !GetApplicationContext() && ctxptr )
    SetApplicationContext(ctxptr);
  
  CTXError().SetHandle(error_handle);
  SDBError().SetHandle(error_handle);
  OQLError().SetHandle(error_handle);
  SOSError().SetHandle(error_handle);

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetProgPath - 




\param  progdir - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProgPath"

void Services :: SetProgPath (char *progdir )
{

  if ( progdir && *progdir )
    file_definitions.svelupd("__PROGPATH",progdir);


}

/******************************************************************************/
/**
\brief  SetSymVariables - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSymVariables"

logical Services :: SetSymVariables ( )
{
  int32                    indx0 = 0;
  logical                 term = NO;
  PropertyHandle   file_names(data_catalogue->dbhandle,"File",PI_Read);
  PH(file_names,name)
  PH(file_names,path)

  while ( file_names.Get(indx0++) )
    file_definitions.svelset(name.GetString(),path.GetString());
  return(term);
}

/******************************************************************************/
/**
\brief  SetupDataSource - 



\return term - Termination code

\param  datasource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDataSource"

logical Services :: SetupDataSource (DataSourceHandle *datasource )
{
  PropertyHandle          dshl;
  ODABAClient            *odaba_client = NULL;
  char                    string[256];
  logical                 term = NO;
BEGINSEQ
  if ( !this || !datasource )                        LEAVESEQ
  
  if ( data_catalogue )
  {
    if ( dshl.Open(data_catalogue->object_handle,"DataSource",PI_Read) ) 
                                                     ERROR
    term = dshl.Get(gvtxstb(string,datasource->data_source,ID_SIZE)).GetData() ? NO : YES;
  }
  if ( term || !data_catalogue )     
  {
    if ( *datasource->data_source <= ' ' )           ERROR
    if ( datasource->SetVariables(datasource->data_source) )
                                                     ERROR
    if ( !*datasource->dict_path )                   ERROR
    term = NO;
    LEAVESEQ
  }
                                                     
  strcpy(datasource->server_name,dshl.GetString("server"));
  datasource->server_port = dshl.GetInt("server_port");
  
  strcpy(datasource->dict_path,dshl.GetString("dict_path"));
  strcpy(datasource->res_path,dshl.GetString("res_path"));
  strcpy(datasource->db_path,dshl.GetString("db_path"));
  strcpy(datasource->object_name,dshl.GetString("object_path"));
  strcpy(datasource->extent_name,dshl.GetString("extent"));

  datasource->sys_appl = dshl.GetPropertyHandle("sys_appl")->IsTrue();
  datasource->netopt   = dshl.GetPropertyHandle("net_opt")->IsTrue();

  datasource->version = dshl.GetInt("version");
  datasource->schema_version = dshl.GetPropertyHandle("schema_version")->GetInt();
  datasource->online_version = NO;
  if ( dshl.GetPropertyHandle("online_versioning")->IsTrue() )
    datasource->online_version = YES;

  datasource->accmode = (PIACC)dshl.GetInt("acc_opt");


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UnregisterError - 




\param  error_instance - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregisterError"

void Services :: UnregisterError (Error *error_instance )
{

  if ( this && error_instance )
    error_instance->SetHandle(NULL);

}

/******************************************************************************/
/**
\brief  ~Services - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Services"

     Services :: ~Services ( )
{

  DeInitialize();


}


