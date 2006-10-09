/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_Connection

\brief    


\date     $Date: 2006/03/12 19:13:47,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_Connection_HPP
#define   SC_Connection_HPP

class     SC_Connection;

#ifndef   DLL_SC_Dictionary_HPP
#define   DLL_SC_Dictionary_HPP
#include  <sSC_Dictionary.hpp>
#include  <sDLL.h>
#endif
class     CS_Handle;
class     CServer;
class     SC_CacheInfo;
class     SC_Dictionary;
class     SC_Handle;
class     ServerConnection;
#include  <cPIACC.h>
#include  <sCheckOptions.hpp>
#include  <sNString.hpp>
#pragma pack(8)

class  SC_Connection :public SC_Handle
{
protected  :         CServer                                     *odaba_server ATTR_ALIGN(4);                                //
protected  :         DLL(SC_Dictionary)                           dict_clients;                                              //
protected  :         DatabaseHandle                               resource_db;                                               //
protected  :         SC_CacheInfo                                *cache_info;                                                //

public     :
                     CServer                                     *get_odaba_server() { return(odaba_server); }
                     DLL(SC_Dictionary)                          &get_dict_clients() { return(dict_clients); }
                     SC_CacheInfo                                *get_cache_info() { return(cache_info); }
public     :                                     logical BackupDB (char *cpath, char *target );
public     :                                     logical CacheConnection ( );
public     :                                     logical CheckDB (DictionaryHandle &dict_hdl, char *cpath, CheckOptions check_opts, char *source, NString &nstring );
public     :                                     void ForceClose ( );
public     :                                     SC_CacheInfo *GetCacheInfo ( );
public     :                                     logical IsCached ( );
public     :                                     SC_Handle *IsUsingDB (char *cpath, int8 database_opt );
public     :                                     SC_Dictionary *LocateDict (CS_Handle *handle );
public     :                                     SC_Dictionary *ProvideDict (int64 client_handle, char *cpath, uint16 version, PIACC accopt );
public     :                                     void ReleaseConnection ( );
public     :                                     logical ReleaseDict (CS_Handle *handle );
public     :                                     logical RestoreDB (char *cpath, char *source );
public     :                                                             SC_Connection (ServerConnection *sconnection );
public     :                                     void SetCacheInfo (SC_CacheInfo *cacheinfo );
public     :                                     void Setup (ServerConnection *sconnection );
public     : virtual                                                     ~SC_Connection ( );
};

#pragma pack()
#endif
