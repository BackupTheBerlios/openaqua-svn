/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    CS_Connection

\brief    


\date     $Date: 2006/08/27 20:18:15,23 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_Connection"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <ctfctp.h>
#include  <igvtc.h>
#include  <sCS_Buffer.hpp>
#include  <sCS_Handle.hpp>
#include  <sCS_Message.hpp>
#include  <sEvent.hpp>
#include  <sRessourceLock.hpp>
#include  <sThreadEntry.hpp>
#include  <sThreadLink.hpp>
#include  <stim.hpp>
#include  <swinsock.hpp>
#include  <sCS_Connection.hpp>


/******************************************************************************/
/**
\brief  CS_Connection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_Connection"

     CS_Connection :: CS_Connection ( )
                     : vcls (),
  threadExecID(),
  threadSpoolID(),
  m_in_sock_lock(NO),
  m_out_sock_lock(NO),
  m_in_in(64000),
  m_in_out(64000),
  m_in_lock(NO),
  m_out_in(64000),
  m_out_out(64000),
  m_out_lock(NO),
  m_in_in_oob(),
  compressThreshold(0),
  compressLevel(1),
  m_send_lock(NO),
  m_in_work(new CS_Buffer(64000)),
  m_out_work(new CS_Buffer(64000))
{

// QueryPerformanceFrequency( (LARGE_INTEGER*) &perf_frq );

Initialize();



}

/******************************************************************************/
/**
\brief  DoConnect - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoConnect"

logical CS_Connection :: DoConnect ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ExecThread - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecThread"

logical CS_Connection :: ExecThread ( )
{
  logical                 term = NO;
threadExecID= ThreadEntry::GetThreadID();

InitConnection();

while( !threadTerm )
{
    m_in_sock_lock.ILock();
    sock_waitfor( m_in_sock, CS_CYCLE_TIME, NULL, stopSockets );
    m_in_sock_lock.IUnlock();
    recvInIn(0);
    checkInInOOB();
    execute(-1);
    sendInOut();
}


  shutdown( m_in_sock, 2 );
  closesocket( m_in_sock );
  threadExec= NO;
  OnExecTerm();
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 



\return term - Success

\param  dwServiceClass - 
\param  dwServiceFunc - 
\param  pParams - 
\param  pResult - 
\param  pError - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical CS_Connection :: Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult, logical *pError )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Flush - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical CS_Connection :: Flush ( )
{
  logical                 term = NO;
BEGINSEQ
  m_send_lock.ILock();

  if( sendOutOut() )                                 ERROR
RECOVER
  term = YES;
ENDSEQ
  m_send_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  GetConnectionName - 



\return server_name - 

\param  server_name - 
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionName"

char *CS_Connection :: GetConnectionName (char *server_name, int32 maxlen )
{
  struct sockaddr_in   name;
  int                  len = sizeof(name);
  int                 *namelen = &len;
  struct hostent      *host_entry;
  char                *sname = NULL;


BEGINSEQ
  if ( m_in_sock == 0 )                              ERROR
  if ( getsockname(m_in_sock,(sockaddr *)&name,namelen) )       ERROR
#ifndef __unix__ 
  if ( !(host_entry = gethostbyaddr((char *)&name.sin_addr,maxlen-1,AF_INET)) )
                                                     ERROR
  sname = gvtxbts(server_name,host_entry->h_name,maxlen-1);
#else
  if ( !getnameinfo((sockaddr *)&name,len,server_name,maxlen-1,
                     NULL,0,0) )                   ERROR
  sname = gvtxbts(server_name,server_name,maxlen-1);
#endif
RECOVER
  sname = NULL;
ENDSEQ
  return(sname);
}

/******************************************************************************/
/**
\brief  HandshakeC - 



\return term - Success

\param  socket - 
\param  socket2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandshakeC"

logical CS_Connection :: HandshakeC (SOCKET socket, SOCKET socket2 )
{
  logical                 term = NO;
BEGINSEQ
// warte auf toten status (ist hier -glaubich- nicht nötig)
stopSockets= YES;
while( m_in_conn || m_out_conn ) tim::timestp(10);
stopSockets= NO;

// socket  : m_in_sock
// socket2 : m_out_sock

CS_Buffer temp;

// wir senden, bis wo wir daten erhalten haben
temp.Clear();
temp.AddINT64( m_in_in_pos + m_in_in.GetSize() ); 
temp.AddINT64( m_out_in_pos + m_out_in.GetSize() );
if( sock_send( socket, temp.GetRPtr(), 2*8, stopSockets ) ) ERROR

temp.Clear();
temp.AddReserve(2*8);
if( sock_recv( socket2, temp.GetWPtr(), 2*8, stopSockets ) ) ERROR

// wir werten aus, bis wo der peer daten erhalten hat
m_out_out.SetRPos( temp.GetINT64() - m_out_out_pos );
m_in_out.SetRPos( temp.GetINT64() - m_in_out_pos );

m_in_sock= socket;
m_out_sock= socket2;

m_in_conn= YES;
m_out_conn= YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  HandshakeS - 



\return term - Success

\param  socket - 
\param  socket2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HandshakeS"

logical CS_Connection :: HandshakeS (SOCKET socket, SOCKET socket2 )
{
  logical                 term = NO;
BEGINSEQ
// warte auf toten status
stopSockets= YES;
while( m_in_conn || m_out_conn ) tim::timestp(10);
stopSockets= NO;

// socket  : m_in_sock
// socket2 : m_out_sock

CS_Buffer temp;

temp.Clear();
temp.AddReserve(2*8);
if( sock_recv( socket2, temp.GetWPtr(), 2*8, stopSockets ) ) ERROR

// wir werten aus, bis wo der peer daten erhalten hat
m_out_out.SetRPos( temp.GetINT64() - m_out_out_pos );
m_in_out.SetRPos( temp.GetINT64() - m_in_out_pos );


// wir senden, bis wo wir daten erhalten haben
temp.Clear();
temp.AddINT64( m_in_in_pos + m_in_in.GetSize() ); 
temp.AddINT64( m_out_in_pos + m_out_in.GetSize() );
if( sock_send( socket, temp.GetRPtr(), 2*8, stopSockets ) ) ERROR

m_in_sock= socket;
m_out_sock= socket2;

m_in_conn= YES;
m_out_conn= YES;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitConnection - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitConnection"

logical CS_Connection :: InitConnection ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CS_Connection :: Initialize ( )
{

  connect_id     = 0;
  pointer_size   = sizeof(void *);
  machine_type   = MT_undefined;
  conversion     = NO;
  threadTerm     = NO;
  threadExec     = NO;
  shutting_down  = NO;
  perf_frq       = 0;
  perf_total     = 0;
  perf_send      = 0;
  perf_wait      = 0;
  perf_build     = 0;
  perf_recv      = 0;
  perf_exec      = 0;
  perf_rwait     = 0;
  threadSpool    = NO;
  m_in_sock      = NULL;
  m_out_sock     = NULL;
  m_out_in_pos   = 0; m_out_in.Clear();
  m_out_out_pos  = 0; m_out_out.Clear();
  m_in_in_pos    = 0; m_in_in.Clear();
  m_in_in_oob_pos= 0; m_in_in_oob.Clear();
  m_in_out_pos   = 0; m_in_out.Clear();
  m_in_conn      = NO;
  m_out_conn     = NO;
  closedbypeer   = NO;
  closing        = NO;
  socketError    = NO;

}

/******************************************************************************/
/**
\brief  IsAlive - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAlive"

logical CS_Connection :: IsAlive ( )
{
  logical     error;
  logical     rfStopSocket = NO;
  logical     cond = YES;
BEGINSEQ
  sock_select(m_in_sock,-1,&error,YES,rfStopSocket);
  if ( error )                                       ERROR
    
  sock_select(m_out_sock,-1,&error,YES,rfStopSocket);
  if ( error )                                       ERROR
    

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  LockExecute - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockExecute"

void CS_Connection :: LockExecute ( )
{

m_in_lock.ILock();

}

/******************************************************************************/
/**
\brief  LockSend - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockSend"

void CS_Connection :: LockSend ( )
{

  m_send_lock.ILock();

}

/******************************************************************************/
/**
\brief  OnExecTerm - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OnExecTerm"

logical CS_Connection :: OnExecTerm ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Output - 



\return term - Success

\param  fstring - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
\param  parm4 - 
\param  parm5 - 
\param  parm6 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CS_Connection :: Output (char *fstring, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5, char *parm6 )
{
  char                    string[4096];
  logical                 term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  sprintf(fstring,string,parm1,parm2,parm3,parm4,parm5);
  SystemOutput(string,NO,YES);


  return(term);
}

/******************************************************************************/
/**
\brief  ReceiveCSMessage - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReceiveCSMessage"

logical CS_Connection :: ReceiveCSMessage ( )
{
  logical                 term = NO;
// obsolete
  return(term);
}

/******************************************************************************/
/**
\brief  SendCSBye - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendCSBye"

logical CS_Connection :: SendCSBye ( )
{
  logical                 term = NO;
m_send_lock.ILock();

closing= YES;

m_out_out.AddULONG( CS_MSG_BYE );
sendOutOut();

m_send_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  SendCSMessage - 



\return term - Success

\param  dwServiceClass - 
\param  dwServiceFunc - 
\param  pParams - 
\param  pResult - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SendCSMessage"

logical CS_Connection :: SendCSMessage (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult )
{
  logical                 term = NO;
BEGINSEQ
  m_send_lock.ILock();

  perf_build++;

  int32 type;

  if( pResult != NULL )
    type= CS_MSG_REQUEST;
  else
    type= CS_MSG_MESSAGE;
  
  m_out_out.AddULONG( type );
  m_out_out.AddULONG( dwServiceClass );
  m_out_out.AddULONG( dwServiceFunc );
  m_out_out.AddBuf( pParams->GetHandle(), sizeof(CS_Handle) );
  m_out_out.AddULONG( pParams->GetLength() );
  m_out_out.AddBuf( pParams->GetData(), pParams->GetLength() );

  if( type == CS_MSG_REQUEST || pParams->flush )
    if( sendOutOut() ) ERROR
  
  if( type == CS_MSG_REQUEST )
  {
    while(1)
    {
      if( recvOutIn(1000) ) ERROR
      if( m_out_in.HasRData() ) break;
      sendOutOut(); //maybe disconnected
    }
    int64 p= m_out_in.GetINT64();
    m_in_lock.ILock();
    while( m_in_in_pos + m_in_in.GetSize() < p )
    {
      // da muss oob vorliegen!
      m_in_lock.IUnlock();
      tim::timestp(1); // warte bis execthread daten empfangen hat
      m_in_lock.ILock();
    }
    execute( p );
    m_in_lock.IUnlock();  
    term = (logical)m_out_in.GetULONG();
    m_out_in.GetBuf( pResult->GetHandle(), sizeof(CS_Handle) );
    uint32 mlen= m_out_in.GetULONG();
    pResult->SetLength( mlen );
    m_out_in.GetBuf( pResult->GetData(), mlen );
  }
RECOVER
  term = YES;
ENDSEQ
m_send_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  SetCompress - 




\param  threshold - 
\param  level_AUTO - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCompress"

void CS_Connection :: SetCompress (size_t threshold, int level_AUTO )
{

compressThreshold= threshold;
compressLevel= level_AUTO;

}

/******************************************************************************/
/**
\brief  SocketError - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SocketError"

logical CS_Connection :: SocketError ( )
{
  int       time_out = 20; // seconds befor closing the socket
  logical   term = NO;
BEGINSEQ
  if ( closing )                                     ERROR

  if( socketError )
  {
    while( !threadTerm && !m_in_conn && !m_out_conn ) tim::timestp(10); 
    if ( threadTerm )                                ERROR
    LEAVESEQ
  }

  socketError= YES;

  m_in_lock.ILock(); // reihenfolge ist wichtig! (wg. deadlocks)
  m_out_lock.ILock();
  m_in_sock_lock.ILock();        
  m_out_sock_lock.ILock();

  shutdown( m_in_sock, 2 ); 
  shutdown( m_out_sock, 2 );

  m_in_conn= NO;
  m_out_conn= NO;

  SOCKET ins= m_in_sock;
  SOCKET ous= m_out_sock;
  
  DoConnect();

//while( !threadTerm && !m_in_conn && !m_out_conn ) tim::timestp(10);
  while( !threadTerm && !m_in_conn && !m_out_conn )
  { 
    if ( time_out-- == 0 || shutting_down )
    {
      threadTerm   = YES;
      closedbypeer = YES;
      break;
    }
    tim::timestp(10); 
  }
  
  closesocket( ins );
  closesocket( ous );  

  m_in_lock.IUnlock();
  m_out_lock.IUnlock();
  m_in_sock_lock.IUnlock();
  m_out_sock_lock.IUnlock();

  if ( threadTerm )                                  ERROR
  
  socketError= NO;

RECOVER
  term = YES;
ENDSEQ
return(term);
}

/******************************************************************************/
/**
\brief  SpoolThread - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SpoolThread"

logical CS_Connection :: SpoolThread ( )
{
  logical                 term = NO;
BEGINSEQ
  threadSpoolID = ThreadEntry::GetThreadID();

  retry:

  while ( !threadTerm )
  {
    tim::WaitMilliseconds(CS_CYCLE_TIME);
    if ( threadTerm )                                 LEAVESEQ
      
    if( m_out_out.GetSize() > 0 ) Flush();
    else
    {
      // mglw. haben wir noch viel im puffer, was der server mal freigeben kann
      m_in_lock.ILock();
      m_out_lock.ILock();    
      logical havedata= m_in_in.GetSize() > 10240 || m_out_in.GetSize() > 10240;
      m_in_lock.IUnlock();
      m_out_lock.IUnlock();
      if( havedata ) sendCSAlive(); // ab und zu mal ein alive
    }
    // schauen wir mal, ob die sockets noch gehen
    logical error;
  
    m_out_sock_lock.ILock();
    sock_waitfor( m_out_sock, 0, &error, stopSockets );
    m_out_sock_lock.IUnlock();    
    if ( threadTerm )                                 LEAVESEQ
    if( error ) goto sock_fail;   
       
    m_in_sock_lock.ILock();
    sock_waitfor( m_in_sock, 0, &error, stopSockets );
    m_in_sock_lock.IUnlock();    
    if ( threadTerm )                                 LEAVESEQ
    if( error ) goto sock_fail;      
  }

LEAVESEQ

sock_fail:
{
  if( SocketError() ) ERROR
  goto retry;
}
RECOVER
  term = YES;
ENDSEQ
  shutdown( m_out_sock, 2 );
  closesocket( m_out_sock );
  threadSpool= NO;
  return(term);
}

/******************************************************************************/
/**
\brief  StartThreads - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartThreads"

logical CS_Connection :: StartThreads ( )
{
  logical                 term = NO;
  threadTerm  = NO;
  threadExec  = YES;
  threadSpool = YES;

  ulong fl = 1;

// set non-blocking mode
  ioctlsocket(m_in_sock, FIONBIO,&fl);
  ioctlsocket(m_out_sock,FIONBIO,&fl);

  TLINK(this,CS_Connection,ExecThread).ThreadCall();
  TLINK(this,CS_Connection,SpoolThread).ThreadCall();

  return(term);
}

/******************************************************************************/
/**
\brief  StopThreads - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopThreads"

logical CS_Connection :: StopThreads ( )
{
  DWORD           exit_code;
  logical         term = NO;
  threadTerm  = YES;
  stopSockets = YES;
#ifdef __unix__
  if ( !pthread_equal(ThreadEntry::GetThreadID(),threadExecID) )
#else
  if ( ThreadEntry::GetThreadID() != threadExecID )
//    && GetExitCodeThread(&threadExecID,&exit_code) && exit_code == STILL_ACTIVE )
#endif
  {
    while( threadExec && !socketError ) 
      tim::WaitMilliseconds(CS_CYCLE_TIME);
  }
  
#ifdef __unix__
  if ( !pthread_equal(ThreadEntry::GetThreadID(),threadSpoolID) )
#else
  if ( ThreadEntry::GetThreadID() != threadSpoolID )
//    && GetExitCodeThread(&threadSpoolID,&exit_code) && exit_code == STILL_ACTIVE )
#endif
  {
    while( threadSpool && !socketError ) 
      tim::timestp(10);
  }
  

  return(term);
}

/******************************************************************************/
/**
\brief  UnlockExecute - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockExecute"

void CS_Connection :: UnlockExecute ( )
{

  m_in_lock.IUnlock();

}

/******************************************************************************/
/**
\brief  UnlockSend - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockSend"

void CS_Connection :: UnlockSend ( )
{

  m_send_lock.IUnlock();

}

/******************************************************************************/
/**
\brief  checkInInOOB - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "checkInInOOB"

logical CS_Connection :: checkInInOOB ( )
{
logical cond;
m_in_lock.ILock();

if( m_in_in.GetSize() + m_in_in_pos == m_in_in_oob_pos )
{
  m_in_in.SetWPos( m_in_in.GetSize() );
  m_in_in.AddReserve( m_in_in_oob.GetSize() );
  m_in_in.AddBuf( m_in_in_oob.GetBPtr(), m_in_in_oob.GetSize() );
  m_in_in_oob.Clear();
  cond= YES;
}
else cond= NO;

m_in_lock.IUnlock();

return cond;

}

/******************************************************************************/
/**
\brief  execute - 



\return term - Success

\param  stopat_int64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "execute"

logical CS_Connection :: execute (int64 stopat_int64 )
{
  logical                 term = NO;
  m_in_lock.ILock();
BEGINSEQ
CS_Message parms, result;    

    size_t end= stopat_int64 < 0 ? m_in_in.GetSize() :
                                   stopat_int64 - m_in_in_pos;
    
    while( m_in_in.HasRData() && m_in_in.GetRPos() < end )
    {
      uint32 type= m_in_in.GetULONG();
      switch( type )
      {
        case CS_MSG_BYE:
          closing= YES;
          closedbypeer= YES;
          m_in_lock.IUnlock();
          StopThreads();
          m_in_lock.ILock();
          ERROR
        case CS_MSG_REQUEST:
        case CS_MSG_MESSAGE:
        {
          uint32 cid, fid, mlen;
          cid= m_in_in.GetULONG();
          fid= m_in_in.GetULONG();
          m_in_in.GetBuf( parms.GetHandle(), sizeof(CS_Handle) );          
          mlen= m_in_in.GetULONG();
          parms.SetLength( mlen );
          m_in_in.GetBuf( parms.GetData(), mlen );
          if( type == CS_MSG_MESSAGE )
          {
            Execute( cid, fid, &parms, NULL, NULL );
          }
          else
          {
            logical error;
            Execute( cid, fid, &parms, &result, &error );
            m_out_lock.ILock();
            m_in_out.AddINT64( m_out_out_pos + m_out_out.GetSize() );
            m_out_lock.IUnlock();            
            m_in_out.AddULONG( (uint32)error );
            m_in_out.AddBuf( result.GetHandle(), sizeof(CS_Handle) );
            m_in_out.AddULONG( result.GetLength() );
            m_in_out.AddBuf( result.GetData(), result.GetLength() );
          }
          break;
        }
        case CS_MSG_ALIVE:
        {
          break;
        }
        default: SOSSET(99)
                 SOSRESET
      }
    }
RECOVER
  term = YES;
ENDSEQ
  m_in_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  getInIn - 



\return term - Success

\param  fIn - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getInIn"

logical CS_Connection :: getInIn (logical fIn )
{
  SOCKET         sock= fIn ? m_in_sock : m_out_sock;
  int            csize;
  size_t         usize;
  int64          ack;
  int64          bpos;
  logical        iscomp;
  logical        term = NO;


BEGINSEQ
  SOCKET sock= fIn ? m_in_sock : m_out_sock;

  m_in_lock.ILock();  
  if ( fIn ) 
    m_in_sock_lock.ILock();
  else 
    m_out_sock_lock.ILock();

  // get size
  if( sock_recv( sock, &csize, 4, stopSockets ) )    ERROR
  csize = ntohl( csize );

  m_in_work->AddReserve( csize + 20 );

  if( sock_recv( sock, m_in_work->GetWPtr(), csize + 20, stopSockets ) ) ERROR

  usize = m_in_work->GetULONG(); // uncompressed size
  ack   = m_in_work->GetINT64();  // ack
  bpos  = m_in_work->GetINT64(); // position of recvd. block
  iscomp = usize > 0;
  
  if ( !iscomp ) usize = csize;

  // if all acked, clear out buf
  if( ack == m_in_out.GetSize() + m_in_out_pos )
  {
    m_in_out_pos= ack;
    m_in_out.Clear();
  }

  if( m_in_in.GetWPos() < bpos - m_in_in_pos )
  {
    // Out-of-bound detected:
    // dies kann passieren, wenn der Courier-Dienst ein Paket mitgebracht hat,
    // jedoch schon ein älteres Paket unterwegs aber noch nicht angekommen ist
    // oder auch anderesrum, also generell, da die pakte auf zwei sockets unterwegs 
    // sind
    if ( m_in_in_oob.GetSize() == 0 )
      m_in_in_oob_pos= bpos;
    else
      if ( m_in_in_oob.GetWPos() < bpos - m_in_in_oob_pos ) SOSERR(202)
    m_in_in_oob.AddReserve( usize );
    if( iscomp )
      Unpack( m_in_in_oob.GetWPtr(), &usize, m_in_work->GetRPtr(), csize );
    else
      memcpy( m_in_in_oob.GetWPtr(), m_in_work->GetRPtr(), usize );
    m_in_in_oob.AddBuf( NULL, usize );
  }
  else
  {
    if( !m_in_in.HasRData() )
    {
      m_in_in_pos+= m_in_in.GetSize();
      m_in_in.Clear();  
    }

    if ( bpos < m_in_in_pos ) SOSERR(202)
    m_in_in.SetWPos( bpos - m_in_in_pos );
    m_in_in.AddReserve( usize );
    if ( iscomp )
      Unpack( m_in_in.GetWPtr(), &usize, m_in_work->GetRPtr(), csize );
    else
      memcpy( m_in_in.GetWPtr(), m_in_work->GetRPtr(), usize );
    m_in_in.AddBuf( NULL, usize );
  }
RECOVER
term=YES;

ENDSEQ
  m_in_work->Clear();
  m_in_lock.IUnlock();  
  if ( fIn ) 
    m_in_sock_lock.IUnlock();
  else 
    m_out_sock_lock.IUnlock();
  return term;
}

/******************************************************************************/
/**
\brief  getOutIn - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getOutIn"

logical CS_Connection :: getOutIn ( )
{
  int            csize;
  size_t         usize;
  int64          ack;
  int64          bpos;
  logical        iscomp;
  logical        term = NO;

BEGINSEQ
  m_out_lock.ILock();  
  m_out_sock_lock.ILock();

  // get size
  if ( sock_recv(m_out_sock,&csize,4,stopSockets) )  ERROR
  csize = ntohl( csize );

  m_out_work->AddReserve( csize + 20 );

  if( sock_recv(m_out_sock,m_out_work->GetWPtr(),csize+20,stopSockets) ) 
                                                     ERROR

  usize  = m_out_work->GetULONG(); // uncompressed size
  ack    = m_out_work->GetINT64(); // ack
  bpos   = m_out_work->GetINT64(); // position of recvd. block
  iscomp = usize > 0;
 
  if ( !iscomp ) 
    usize = csize;

  // if all acked, clear out buf
  if( ack == m_out_out.GetSize() + m_out_out_pos )
  {
    m_out_out_pos= ack;
    m_out_out.Clear(); 
  }

  if( !m_out_in.HasRData() )
  {
    m_out_in_pos+= m_out_in.GetSize();
    m_out_in.Clear();  
  }
  
  if ( bpos < m_out_in_pos )                         SOSERR(202)
  m_out_in.SetWPos( bpos - m_out_in_pos );
  m_out_in.AddReserve( usize );
  
  if( iscomp )
    Unpack( m_out_in.GetWPtr(), &usize, m_out_work->GetRPtr(), csize );
  else
    memcpy( m_out_in.GetWPtr(), m_out_work->GetRPtr(), usize );

  m_out_in.AddBuf( NULL, usize );

RECOVER
  term= YES;
ENDSEQ
  m_out_work->Clear();
  m_out_lock.IUnlock();  
  m_out_sock_lock.IUnlock();
return term;
}

/******************************************************************************/
/**
\brief  putInOut - 




\param  pCS_Buffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "putInOut"

void CS_Connection :: putInOut (CS_Buffer *pCS_Buffer )
{

size_t usize= m_in_out.GetRLeft();
size_t csize= usize * 2 + 24 + 12; // must at least be 12 bytes (see zlib)

pCS_Buffer->AddReserve( csize );

if( !compressThreshold || usize < compressThreshold )
{
  memcpy( pCS_Buffer->GetWPtr() + 24, m_in_out.GetRPtr(), usize );
  csize= usize;  
  usize= 0;
}
else
  Pack( pCS_Buffer->GetWPtr() + 24, &csize, m_in_out.GetRPtr(), usize, compressLevel );

int64 bpos= m_in_out_pos + m_in_out.GetRPos();

m_in_out.SetRPos( m_in_out.GetSize() );

pCS_Buffer->AddULONG( csize ); // compressed size
pCS_Buffer->AddULONG( usize ); // uncompressed size
pCS_Buffer->AddINT64( m_in_in_pos + m_in_in.GetSize() );  // ack in-in block-position
pCS_Buffer->AddINT64( bpos );  // block-position
pCS_Buffer->AddBuf( NULL, csize);

}

/******************************************************************************/
/**
\brief  putOutOut - 




\param  pCS_Buffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "putOutOut"

void CS_Connection :: putOutOut (CS_Buffer *pCS_Buffer )
{

size_t usize= m_out_out.GetRLeft();
size_t csize= usize * 2 + 24 + 12; // must at least be 12 bytes (see zlib)

pCS_Buffer->AddReserve( csize );

if( !compressThreshold || usize < compressThreshold )
{
  memcpy( pCS_Buffer->GetWPtr() + 24, m_out_out.GetRPtr(), usize );
  csize= usize;
  usize= 0;
}
else
  Pack( pCS_Buffer->GetWPtr() + 24, &csize, m_out_out.GetRPtr(), usize, compressLevel );

int64 bpos= m_out_out_pos + m_out_out.GetRPos();

m_out_out.SetRPos( m_out_out.GetSize() );

pCS_Buffer->AddULONG( csize ); // compressed size
pCS_Buffer->AddULONG( usize ); // uncompressed size
pCS_Buffer->AddINT64( m_out_in_pos + m_out_in.GetSize() );  // ack out-in block-position
pCS_Buffer->AddINT64( bpos );  // block-position
pCS_Buffer->AddBuf( NULL, csize );

}

/******************************************************************************/
/**
\brief  recvInIn - 



\return term - Success

\param  timeout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "recvInIn"

logical CS_Connection :: recvInIn (int32 timeout )
{

repeat:
{

logical data;
if( timeout >= 0 )
{
  logical error;
  m_in_sock_lock.ILock();
  data= !sock_waitfor( m_in_sock, timeout, &error, stopSockets );
  m_in_sock_lock.IUnlock();  
  if( error ) goto socket_error;
}
else data= YES;

if( data && getInIn(YES) ) goto socket_error;

return NO;
}

socket_error:
  if( SocketError() ) return YES;

  goto repeat;


}

/******************************************************************************/
/**
\brief  recvOutIn - 



\return term - Success

\param  timeout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "recvOutIn"

logical CS_Connection :: recvOutIn (int32 timeout )
{

repeat:
{

logical data;
if( timeout >= 0 )
{
  logical error;
  m_out_sock_lock.ILock();
  data= !sock_waitfor( m_out_sock, timeout, &error, stopSockets );
  m_out_sock_lock.IUnlock();  
  if( error ) goto socket_error;
}
else data= YES;

if( data && ( getInIn(NO)   // courier
              || getOutIn() ) ) goto socket_error;
              
return NO;            
}

socket_error:
  if( SocketError() ) return YES;

  goto repeat;


}

/******************************************************************************/
/**
\brief  sendCSAlive - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sendCSAlive"

logical CS_Connection :: sendCSAlive ( )
{
  logical                 term = NO;
m_send_lock.ILock();

m_out_out.AddULONG( CS_MSG_ALIVE );
sendOutOut();

m_send_lock.IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  sendInOut - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sendInOut"

logical CS_Connection :: sendInOut ( )
{
  logical     cont = YES;
  logical     term = NO;
  while ( cont )
  {
    cont = NO;
    m_in_lock.ILock();
    m_out_lock.ILock();
    m_in_sock_lock.ILock();

    // ACHTUNG: sendInOut darf nur Courier spielen, wenn auch
    // wirklich ein Datenpakt in der inout-queue liegt, 
    // sonst wartet der peer gar nicht auf ein Resultat und würde
    // niemals das courierte Paket annehmen

    if( m_in_out.GetRLeft() != 0 )
    {
      putOutOut(m_in_work); // courier    
      putInOut(m_in_work); 
  
      cont = sock_send(m_in_sock, m_in_work->GetBPtr(),m_in_work->GetSize(),stopSockets);
      m_in_work->Clear();
    }

    m_in_lock.IUnlock();
    m_out_lock.IUnlock();
    m_in_sock_lock.IUnlock();
    
    if ( cont && SocketError() )
    {
      term = YES;
      cont = NO;
    }
  }

/*
  repeat:

  m_in_lock.ILock();
  m_out_lock.ILock();
  m_in_sock_lock.ILock();

  if( m_in_out.GetRLeft() != 0 )
  {
    putOutOut(m_in_work); // courier    
    putInOut(m_in_work); 
  
    if ( sock_send(m_in_sock, m_in_work->GetBPtr(),m_in_work->GetSize(),stopSockets) ) 
      goto socket_error;
  }

  m_in_lock.IUnlock();
  m_out_lock.IUnlock();
  m_in_sock_lock.IUnlock();

  return NO;

socket_error:
  
  m_in_lock.IUnlock();
  m_out_lock.IUnlock();
  m_in_sock_lock.IUnlock();

  if ( SocketError() ) 
    return YES;
  
  goto repeat;
*/
  return(term);
}

/******************************************************************************/
/**
\brief  sendOutOut - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sendOutOut"

logical CS_Connection :: sendOutOut ( )
{
  logical     cont = YES;
  logical     term = NO;
  while ( cont )
  {
    cont = NO;

    m_out_lock.ILock();
    m_out_sock_lock.ILock();

    if( m_out_out.GetRLeft() != 0 )
    {
      putOutOut(m_out_work);
      cont = sock_send(m_out_sock,m_out_work->GetBPtr(),m_out_work->GetSize(),stopSockets);
      m_out_work->Clear();
    }

    m_out_lock.IUnlock();
    m_out_sock_lock.IUnlock();
    
    if ( cont && SocketError() )
    {
      term = YES;
      cont = NO;
    }
  }

/*
  repeat:

  m_out_lock.ILock();
  m_out_sock_lock.ILock();

  if( m_out_out.GetRLeft() != 0 )
  {
    putOutOut(m_out_work);
    if( sock_send(m_out_sock, temp.GetBPtr(),temp.GetSize(),stopSockets) ) 
      goto socket_error;
  }

  m_out_lock.IUnlock();
  m_out_sock_lock.IUnlock();
  
  return NO;

socket_error:
  m_out_lock.IUnlock();
  m_out_sock_lock.IUnlock();

  if( SocketError() ) 
    return YES;
  
  goto repeat;
*/
  return(term);
}

/******************************************************************************/
/**
\brief  set_shutting_down - 




\param  shut_down_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_shutting_down"

void CS_Connection :: set_shutting_down (char shut_down_opt )
{

  shutting_down = shut_down_opt;

}

/******************************************************************************/
/**
\brief  sock_recv - 



\return term - Success

\param  sock - 
\param  buf - 
\param  len - 
\param  rfStopSocket - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sock_recv"

logical __cdecl CS_Connection :: sock_recv (SOCKET sock, void *buf, size_t len, logical &rfStopSocket )
{
  char       *p    = (char *)buf;
  logical     term = NO;
BEGINSEQ
  const int frame= 65535;

  while( len > 0 )
  {
    int32   slen = len < frame ? len : frame;
    logical error;
    
    sock_select(sock,-1,&error,NO,rfStopSocket);
    if ( error )                                     ERROR
    
    slen = recv(sock,p,slen,0);
    if ( slen <= 0 )                                 ERROR
    
    len -= slen;
    p   += slen;
  }
RECOVER
#ifndef __unix__
  static DWORD lasterror= ::GetLastError();
#endif
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sock_select - 



\return term - Success

\param  sock - 
\param  timeout - 
\param  pfError - 
\param  fForWrite - 
\param  rfStopSocket - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sock_select"

logical __cdecl CS_Connection :: sock_select (SOCKET sock, int32 timeout, logical *pfError, logical fForWrite, logical &rfStopSocket )
{
  logical                 term = NO;
fd_set fd;
#ifdef __unix__
FD_ZERO(&fd);
FD_SET(sock, &fd);
#else
fd.fd_count= 1;
fd.fd_array[0]= sock;
#endif

while( 1 )
{
  int32 tu;
    
  timeval tv;
  logical usetv;
  
  if( timeout >= 0 )
  {  
    usetv= YES;
    tu= MIN( timeout, 1000 );
    timeout-= tu;
  
    tv.tv_sec= tu / 1000;
    tv.tv_usec= ( tu % 1000 ) * 1000;
  }
  else usetv= NO;

#ifdef __unix__
int res= select( 255, 
   !fForWrite ? &fd : NULL, 
   fForWrite ? &fd : NULL,
   NULL, usetv ? &tv : NULL );
#else
int res= select( 1, 
   !fForWrite ? &fd : NULL, 
   fForWrite ? &fd : NULL,
   NULL, usetv ? &tv : NULL );
#endif

  if( pfError != NULL ) *pfError= res < 0;
  term= res == 0;
  
  if( rfStopSocket )
  {
    if( pfError ) *pfError= YES;
    term= NO;
    break;
  }

  if( timeout <= 0 || res != 0 ) break;
}
  return(term);
}

/******************************************************************************/
/**
\brief  sock_send - 



\return term - Success

\param  sock - 
\param  buf - 
\param  len - 
\param  rfStopSocket - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sock_send"

logical __cdecl CS_Connection :: sock_send (SOCKET sock, void *buf, size_t len, logical &rfStopSocket )
{
  char       *p    = (char *)buf;
  logical     term = NO;
BEGINSEQ
  const int frame = 65535;

  while( len > 0 )
  {
    int32   slen = len < frame ? len : frame;
    logical error;
    
    sock_select(sock,-1,&error,YES,rfStopSocket);
    if ( error )                                     ERROR
    
    slen = send(sock,p,slen,0);
    if ( slen <= 0 )                                 ERROR
    
    len -= slen;
    p   += slen;
  }
RECOVER
#ifndef __unix__
  static DWORD lasterror= ::GetLastError();
#endif
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sock_waitfor - 



\return term - Success

\param  sock - 
\param  timeout - 
\param  pfError - 
\param  rfStopSocket - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sock_waitfor"

logical __cdecl CS_Connection :: sock_waitfor (SOCKET sock, int32 timeout, logical *pfError, logical &rfStopSocket )
{

return sock_select( sock, timeout, pfError, NO, rfStopSocket );

}

/******************************************************************************/
/**
\brief  ~CS_Connection - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CS_Connection"

     CS_Connection :: ~CS_Connection ( )
{

  delete m_in_work;
  m_in_work = NULL;

  delete m_out_work;
  m_out_work = NULL;


}


