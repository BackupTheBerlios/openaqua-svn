/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_CacheInfo

\brief    Connection cache data
          Connection  cache data  provides information  for reusing connections.
          For  re-using a connection,  the connection is  stored in a connection
          cache  instead  of  closing  the  connection  when  the  client  has 
          terminated.  A connection from the  connection cache can be identified
          by  a connection ID, or by the  connection name, which has passed when
          creating  the connection the first time. Cached connections are closed
          after a timeout interval defined in the server ini-file.

\date     $Date: 2006/03/12 19:13:47,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_CacheInfo_HPP
#define   SC_CacheInfo_HPP

class     SC_CacheInfo;

#include  <sSC_Connection.hpp>
class  SC_CacheInfo
{
protected  :         SC_Connection                               *connection;                                                //
protected  :         char                                        *name;                                                      //
protected  :         int32                                        id;                                                        //
protected  :         dbtm                                         last_used;                                                 //

public     :
                     SC_Connection                               *get_connection() { return(connection); }
                     char                                        *get_name() { return(name); }
                     int32                                        get_id() { return(id); }
                     dbtm                                         get_last_used() { return(last_used); }
public     :                                                             SC_CacheInfo (SC_Connection *sc_connection, char *connection_string, int32 connection_id );
public     :                                     void SetConnectionString (char *connection_string );
public     :                                     void SetLastUsed ( );
public     :                                                             ~SC_CacheInfo ( );
};

#endif
