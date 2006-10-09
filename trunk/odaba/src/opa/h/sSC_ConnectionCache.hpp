/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_ConnectionCache

\brief    Connection cache
          The  connection cache  store connections  for a given timeout interval
          defined  in  the  server  ini-file.  A  connection  cached may cache a
          number   of   dictionaries,   databases   and   database   objects.  
          PropertyHandles are closed and not cached.

\date     $Date: 2006/03/12 19:13:48,45 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_ConnectionCache_HPP
#define   SC_ConnectionCache_HPP

class     SC_ConnectionCache;

#ifndef   DLL_SC_CacheInfo_HPP
#define   DLL_SC_CacheInfo_HPP
#include  <sSC_CacheInfo.hpp>
#include  <sDLL.h>
#endif
class     SC_CacheInfo;
class     SC_Connection;
class  SC_ConnectionCache :public RessourceLock,
public DLL(SC_CacheInfo)
{
protected  :         int32                                        timeout;                                                   //
protected  :         int32                                        last_id;                                                   //

public     :
                     int32                                        get_timeout() { return(timeout); }
                     int32                                        get_last_id() { return(last_id); }
public     :                                     logical Add (SC_Connection *sc_connection );
public     :                                     logical Check ( );
public     :                                     void Close ( );
public     :                                     SC_CacheInfo *Create (SC_Connection *sc_connection, char *connection_string );
public     :                                     SC_Connection *Provide (char *connection_string );
public     :                                     SC_Connection *Provide (int32 connection_id );
public     :                                     logical Remove (SC_CacheInfo *cacheinfo );
public     :                                                             SC_ConnectionCache ( );
public     :                                                             ~SC_ConnectionCache ( );
};

#endif
