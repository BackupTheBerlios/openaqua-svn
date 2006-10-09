/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    Socket

\brief    Socket


\date     $Date: 2006/08/28 13:42:34,36 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Socket"

#include  <pdefault.h>
#include  <standard.hpp>
#include  <swinsock.hpp>
#include  <sSocket.hpp>


/******************************************************************************/
/**
\brief  Accept - Accept a connection

        </p>

\return cond - Success

\param  rSocket - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Accept"

logical Socket :: Accept (Socket &rSocket )
{
  logical      cond = YES;
BEGINSEQ
  int addr_length = sizeof ( addresshandle );
#ifdef __unix__
  rSocket.sockethandle = accept ( sockethandle, ( sockaddr * ) &addresshandle, ( socklen_t * ) &addr_length );
#endif
  if ( rSocket.sockethandle <= 0 )                  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Bind - 



\return cond - Success

\param  bindport - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Bind"

logical Socket :: Bind (const int16 bindport )
{
  int          bind_return;
  logical      term = NO;
BEGINSEQ
  if ( !IsConnected() )                            ERROR

  addresshandle.sin_family      = AF_INET;
  addresshandle.sin_addr.s_addr = INADDR_ANY;
  addresshandle.sin_port        = htons(bindport);

  bind_return = bind(sockethandle,(struct sockaddr *)&addresshandle, 
                     sizeof(addresshandle) );

  if ( bind_return == -1 )                          ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Connect - Basic Network Socket Class



\return cond - Success

\param  cSHost - 
\param  bindport - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical Socket :: Connect (const std_string cSHost, const int16 bindport )
{
  logical      term = NO;
  int          status = 0;
BEGINSEQ
  if ( !IsConnected() )                             ERROR
  memset(&addresshandle,0,sizeof(addresshandle));

  addresshandle.sin_family = AF_INET;
  addresshandle.sin_port = htons ( bindport );
  
#ifdef __unix__
  status = inet_pton ( AF_INET, cSHost.c_str(), &addresshandle.sin_addr );

  if ( errno == EAFNOSUPPORT )                       ERROR
#else
  uint32 ulAddress;
  ulAddress = inet_addr( cSHost.c_str() ); 
  if( INADDR_NONE == ulAddress )
  { 
    hostent *pHost;
    pHost = gethostbyname( cSHost.c_str() );
    if ( NULL == pHost )                             ERROR
    memcpy(&ulAddress,pHost->h_addr,pHost->h_length); 
  }  
  addresshandle.sin_addr.s_addr = ulAddress;
#endif
  status = connect ( sockethandle, ( sockaddr * ) &addresshandle, sizeof ( addresshandle ) );

  if ( status )                                      ERROR

RECOVER
  Disconnect();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 1



\return cond - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical Socket :: Create ( )
{
  logical      term = NO;
BEGINSEQ

  sockethandle = socket ( AF_INET,  SOCK_STREAM,  0 );

  if ( !IsConnected() )                              ERROR

  int on = 1;
  if ( setsockopt ( sockethandle, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Disconnect - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

void Socket :: Disconnect ( )
{

  if( IsConnected() )
#ifdef __unix__
    close( sockethandle);
#else
        closesocket(sockethandle);
#endif
  sockethandle = AUTO;


}

/******************************************************************************/
/**
\brief  IsConnected - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsConnected"

logical Socket :: IsConnected ( ) const
{


  return( sockethandle != -1 );
}

/******************************************************************************/
/**
\brief  Listen - 



\return cond - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Listen"

logical Socket :: Listen ( ) const
{

BEGINSEQ
  if ( !IsConnected() )                              ERROR

  return( listen(sockethandle,MAXCONNECTIONS) == -1 ? YES : NO);


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Receive - 



\return bytecount - Success

\param  rSBuffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Receive"

int32 Socket :: Receive (std_string &rSBuffer ) const
{
  int         nStatus = 0;
  std_string  buffer;
  int bytecount = 0;

  

BEGINSEQ
  rSBuffer = "";
  if ( !Status() )                                   ERROR
  do
  { 
    nStatus = ReceiveBlock(buffer);
    rSBuffer+=buffer;
    bytecount+=nStatus;
    if ( nStatus == 0 && Status() ) // no bytes read - connection closed by peer
                                                     ERROR
        else if ( nStatus == MAXRECV )  // more bytes that buffer handled red
          nStatus = Status();
        else 
          nStatus = 0;
  } while ( nStatus != 0 );

RECOVER
  bytecount = 0;
ENDSEQ
  return(bytecount);
}

/******************************************************************************/
/**
\brief  ReceiveBlock - 



\return status - Success

\param  rSBuffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReceiveBlock"

int32 Socket :: ReceiveBlock (std_string &rSBuffer ) const
{
  char        buf [MAXRECV + 1];
  int32       status = 0;
  

BEGINSEQ
  rSBuffer = "";
  memset(buf,0,MAXRECV + 1);
  
  status = recv ( sockethandle, buf, MAXRECV, 0 );

  if ( status == -1 )                               ERROR
  if ( status > 0 )
      rSBuffer = buf;


RECOVER
  status = 0;
ENDSEQ
  return(status);
}

/******************************************************************************/
/**
\brief  Send - 



\return cond - Success

\param  cSBuffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Send"

logical Socket :: Send (const std_string cSBuffer ) const
{
  logical      term = NO;
  int32        status = 0;
BEGINSEQ
#ifdef   __linux__
  status = send ( sockethandle, cSBuffer.c_str(), cSBuffer.size(), MSG_NOSIGNAL );
#else
  status = send ( sockethandle, cSBuffer.c_str(), cSBuffer.size(), 0);
#endif
  if ( status == -1 ){
    SOSEV1((char*)cSBuffer.c_str(),cSBuffer.length())
        SOSERR(60)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Socket - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Socket"

     Socket :: Socket ( )
                     :   sockethandle(-1)
{

  memset(&addresshandle,0,sizeof(addresshandle));

}

/******************************************************************************/
/**
\brief  Status - 



\return cond - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Status"

logical Socket :: Status ( ) const
{
  logical      cond = YES;
  int          nStatus = 0;
  timeval      timeout = {0, 0};
  fd_set       fds;

BEGINSEQ
  FD_ZERO(&fds);
  FD_SET(sockethandle, &fds);
  nStatus = select(0, &fds, NULL, NULL, &timeout);
  if (nStatus == SOCKET_ERROR)                     ERROR
  if (nStatus == 0)                                ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ~Socket - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~Socket"

     Socket :: ~Socket ( )
{

  Disconnect();

}


