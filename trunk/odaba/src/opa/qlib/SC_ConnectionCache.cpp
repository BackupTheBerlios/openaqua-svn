/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_ConnectionCache

\brief    Connection cache
          The  connection cache  store connections  for a given timeout interval
          defined  in  the  server  ini-file.  A  connection  cached may cache a
          number   of   dictionaries,   databases   and   database   objects.  
          PropertyHandles are closed and not cached.

\date     $Date: 2006/03/12 19:18:06,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SC_ConnectionCache"

#include  <popa7.h>
#include  <sSC_CacheInfo.hpp>
#include  <sSC_Connection.hpp>
#include  <sSC_ConnectionCache.hpp>


/******************************************************************************/
/**
\brief  Add - Add connection to cache


\return term - Termination code

\param  sc_connection -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical SC_ConnectionCache :: Add (SC_Connection *sc_connection )
{
  SC_CacheInfo    *cinfo;
  logical          term = NO;
BEGINSEQ
  ILock();
  
  if ( !sc_connection )                              ERROR
  if ( !(cinfo = sc_connection->GetCacheInfo()) )    LEAVESEQ
  
  cinfo->SetLastUsed();
  sc_connection->ReleaseConnection();
  
  if ( Find(cinfo) )                                 LEAVESEQ
  AddTail(cinfo);
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Check - Check cache for timeout connections


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical SC_ConnectionCache :: Check ( )
{
  SC_CacheInfo           *cinfo;
  dbtm                    ctime;
  int32                   itime;
  logical                 term = NO;
  ILock();
  ctime.SetTime(); 
  itime = ctime.GetLongInt();
  
  GoTop();
  while ( cinfo = GetNext() )
    if ( itime - cinfo->get_last_used().GetLongInt() > timeout )
    {
      RemoveAt();
      GoTop();
      Remove(cinfo);
    }

  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void SC_ConnectionCache :: Close ( )
{
  SC_CacheInfo          *cinfo;
  GoTop();
  while ( cinfo = RemoveTail() )
    Remove(cinfo);


}

/******************************************************************************/
/**
\brief  Create - 


\return cinfo -

\param  sc_connection -
\param  connection_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

SC_CacheInfo *SC_ConnectionCache :: Create (SC_Connection *sc_connection, char *connection_string )
{
  SC_CacheInfo           *cinfo = NULL;
  logical                 term = NO;
  cinfo = new SC_CacheInfo(sc_connection,connection_string,++last_id);
  cinfo->SetLastUsed();

  return(cinfo);
}

/******************************************************************************/
/**
\brief  Provide - Provide connection from cache


\return sc_connection -
-------------------------------------------------------------------------------
\brief i00


\param  connection_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

SC_Connection *SC_ConnectionCache :: Provide (char *connection_string )
{
  SC_CacheInfo           *cinfo;
  SC_Connection          *sc_connection = NULL;
BEGINSEQ
  ILock();
  
  GoTop();
  while ( !sc_connection && (cinfo = GetNext()) )
    if ( !strcmp(cinfo->get_name(),connection_string) )
      sc_connection = cinfo->get_connection();

  if ( !sc_connection )                                ERROR
  RemoveAt();
RECOVER
  sc_connection = NULL;
ENDSEQ
  IUnlock();
  return(sc_connection);
}

/******************************************************************************/
/**
\brief i01


\param  connection_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

SC_Connection *SC_ConnectionCache :: Provide (int32 connection_id )
{
  SC_CacheInfo           *cinfo;
  SC_Connection          *sc_connection = NULL;
BEGINSEQ
  ILock();
  
  GoTop();
  while ( !sc_connection && (cinfo = GetNext()) )
    if ( cinfo->get_id() == connection_id )
      sc_connection = cinfo->get_connection();

  if ( !sc_connection )                                ERROR
  RemoveAt();
RECOVER
  sc_connection = NULL;
ENDSEQ
  IUnlock();
  return(sc_connection);
}

/******************************************************************************/
/**
\brief  Remove - Remove connection from cache


\return term - Termination code

\param  cacheinfo -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

logical SC_ConnectionCache :: Remove (SC_CacheInfo *cacheinfo )
{
  SC_Connection          *sconnection = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !cacheinfo )                                  ERROR
  sconnection = cacheinfo->get_connection();
  delete cacheinfo;

  if ( !sconnection )                                ERROR
  sconnection->SetCacheInfo(NULL);
  
  sconnection->ForceClose(); 
  delete sconnection;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SC_ConnectionCache - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SC_ConnectionCache"

                        SC_ConnectionCache :: SC_ConnectionCache ( )
                     : RessourceLock(NO),
DLL(SC_CacheInfo) (),
  timeout(15*60*100),
  last_id(0)
{
  char             *stime;
  int32             time;
  if ( stime = GetSysVariable("CC_TIMEOUT") )
    if ( (time = atoi(stime)) > 0 )
      timeout = time*60*100;  // timeout in 1/100 seconds

}

/******************************************************************************/
/**
\brief  ~SC_ConnectionCache - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SC_ConnectionCache"

                        SC_ConnectionCache :: ~SC_ConnectionCache ( )
{
  SC_CacheInfo          *cinfo;
  Close();

}


