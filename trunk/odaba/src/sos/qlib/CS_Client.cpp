/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    CS_Client

\brief    


\date     $Date: 2006/08/27 18:23:28,51 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CS_Client"

#include  <pdefault.h>
#include  <cactp.h>
#include  <cfctp.h>
#include  <sCS_Message.hpp>
#include  <sflnk.hpp>
#include  <stim.hpp>
#include  <sCS_Client.hpp>


/******************************************************************************/
/**
\brief  CS_Client - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CS_Client"

     CS_Client :: CS_Client ( )
                     : CS_Connection (),
  server_id()
{

  Initialize();
  
#ifndef __unix__
  WSAData d;
  WSAStartup( MAKEWORD( 1, 1 ), &d );
#endif

}

/******************************************************************************/
/**
\brief  ConnectServer - 



\return term - Success

\param  host_name - 
\param  host_port - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConnectServer"

logical CS_Client :: ConnectServer (char *host_name, uint32 host_port )
{
  int     saverr;
  logical term=NO;
BEGINSEQ
  host= strdup( host_name );
  port= host_port;

  if ( DoConnect() )                                SOSERR(last_error)

  if( connect_error ) ERROR

  StartThreads();

RECOVER
  saverr = last_error;
  CS_Connection::Initialize();
  Initialize();
  if ( saverr )
    SOSISET(saverr);
  term=YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DisconnectServer - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisconnectServer"

logical CS_Client :: DisconnectServer ( )
{
  logical                 term = NO;
  shutting_down = YES;
  
  if ( IsAlive() )
    SendCSBye();
  else
    socketError = YES;

  StopThreads();
  free( host );
  CS_Connection::Initialize();
  Initialize();
  return(term);
}

/******************************************************************************/
/**
\brief  DoConnect - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoConnect"

logical CS_Client :: DoConnect ( )
{
  logical                 term  = NO;
  int                     tries = 20;
DEFLOCALERR
SOCKET sock= NULL;
BEGINSEQ
connect_error= NO;

retry:
  SOCKET sock= NULL;
  
  while( 1 )
  {
    sock= InternalConnect();
    if( sock ) break;
    if( --tries == 0 ) ERROR
    tim::timestp( tries % 10 ); // a lil noise ! (for server queue overrun!)
  }
    
  SOCKET s2= NULL;
  
  while( 1 )
  {
    s2= InternalConnect();
    if( s2 ) break;
    if( --tries == 0 ) ERROR
    tim::timestp( tries % 10 ); // a lil noise ! (for server queue overrun!)
  }
  
{
  if( connect_id == 0 )
  {
    uint32 cid = 0;
    if( sock_send( sock, &cid, 4, term ) ) 
      goto sock_fail;
    if( sock_recv( sock, &cid, 4, term ) ) 
      goto sock_fail;
    if( cid == 0 ) 
      goto sock_fail;
    connect_id = cid;
    if( sock_recv( sock, &server_id, 8, term ) ) 
      goto sock_fail;
  }
  else
  {
    if( sock_send( sock, &connect_id, 4, term ) ) 
      goto sock_fail;
    if( sock_send( sock, &server_id, 8, term ) ) 
      goto sock_fail;
    uint32 cid;
    if( sock_recv( sock, &cid, 4, term ) ) 
      goto sock_fail;
    if( cid == 0 ) LOCALERR(303)
  }  
  int32 l = htonl( -1 );
    
  if( sock_send( s2, &l, 4, term ) ) 
    goto sock_fail;
    
  int64 i;
  if( sock_recv( s2, &i, 8, term ) ) 
    goto sock_fail;
  if( sock_send( sock, &i, 8, term ) ) 
    goto sock_fail;
    
  HandshakeC( s2, sock );
}

LEAVESEQ

sock_fail:
{
  closesocket( sock );
  closesocket( s2 );
  if( --tries == 0 ) ERROR
  tim::timestp(10);
  goto retry;
}
RECOVER
  term = YES;
  if ( LOCALERROR )
    last_error= LOCALERROR;
  connect_error= YES;
ENDSEQ
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

logical CS_Client :: Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult, logical *pError )
{
  logical                 term = NO;
  // nur zum Test;
  
  if ( dwServiceClass == 1 && dwServiceFunc == 1 )
  {
    Output("Daten: %s",pParams->GetData());
  }

  return(term);
}

/******************************************************************************/
/**
\brief  GetHost - 



\return host_name - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHost"

char *CS_Client :: GetHost ( )
{

  return ( host );

}

/******************************************************************************/
/**
\brief  GetLastError - 



\return err_code - Error code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastError"

int16 CS_Client :: GetLastError ( )
{


  return(last_error);
}

/******************************************************************************/
/**
\brief  GetPort - 



\return host_port - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPort"

uint32 CS_Client :: GetPort ( )
{

  return ( port );

}

/******************************************************************************/
/**
\brief  Initialize - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CS_Client :: Initialize ( )
{

  server_ptr_size = 0;
  server_mtype    = MT_undefined;
  host            = NULL;
  port            = 0;
  last_error      = 0;
  connect_error   = NO;


}

/******************************************************************************/
/**
\brief  InternalConnect - 



\return sock - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InternalConnect"

SOCKET CS_Client :: InternalConnect ( )
{
DEFLOCALERR
SOCKET sock= NULL;
logical term= NO;
BEGINSEQ
  sockaddr_in  sa;
  memset(&sa,0,sizeof(sa));
	
  sa.sin_family = PF_INET;
  sa.sin_port   = htons((WORD)port);
	
  uint32 ulAddress;
  ulAddress = inet_addr( host ); 
  if( INADDR_NONE == ulAddress )
  { 
    hostent *pHost;
    pHost = gethostbyname( host );
    if ( NULL == pHost )                             LOCALERR(300)
    memcpy(&ulAddress,pHost->h_addr,pHost->h_length); 
  }  

  sa.sin_addr.s_addr = ulAddress; 
        
  sock = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);

  if ( connect(sock,(LPSOCKADDR)&sa,sizeof(sa)) )    LOCALERR(305)

  BOOL b= YES;
  setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(char *)&b,sizeof(b));

// now identify c/s
  char buf[1024];
  strcpy(buf+4,"HALLO-ODABA2-SERVER");
  int32  sl = strlen(buf+4) + 1;
  *((int32 *) buf) = htonl(sl);
  if( sock_send( sock, buf, sl + 4, term ) ) LOCALERR(302)
  if( sock_recv( sock, &sl, 4, term ) ) LOCALERR(302)
  sl = ntohl( sl );
  if( sl > 256 ) LOCALERR(302)
  if( sock_recv( sock, buf, sl, term ) ) LOCALERR(302)
  if( strcmp( buf, "HALLO-ODABA2-CLIENT" ) != 0 ) LOCALERR(302)

RECOVER
  if( sock != NULL ) closesocket( sock );
  sock= NULL;
  last_error= LOCALERROR;
ENDSEQ
  return(sock);
}

/******************************************************************************/
/**
\brief  ~CS_Client - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CS_Client"

     CS_Client :: ~CS_Client ( )
{

#ifndef __unix__
  WSACleanup();
#endif


}


