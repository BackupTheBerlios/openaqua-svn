/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    SocketClient

\brief    


\date     $Date: 2006/08/28 14:49:26,74 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SocketClient"

#include  <pdefault.h>
#include  <standard.hpp>
#include  <sSocketClient.hpp>


/******************************************************************************/
/**
\brief  Connect - 



\return term - Success
-------------------------------------------------------------------------------
\brief  i00 - 



\param  shost - 
\param  port_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical SocketClient :: Connect (std_string shost, int32 port_number )
{
  logical   term = NO;
BEGINSEQ
  if( SetHost(shost) || SetPort(port_number) )      ERROR
  term = Connect();


RECOVER
  Disconnect();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical SocketClient :: Connect ( )
{
  logical   term = NO;
  char      atoibuffer[30];
BEGINSEQ

  if ( Socket::Create() )                           SOSERR(61)
  if ( Socket::Connect(host,port) ){
    SOSEV1("Connect failed",14)
    SOSEV2((char*)host.c_str(),host.length())
    std_string sport = gvtxitoa(port,atoibuffer,10);
    SOSEV3((char*)sport.c_str(),sport.length())
	SOSERR(62)
  }
// Add text: "Could not bind socket to port."

RECOVER
  Disconnect();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetResponse - 



\return term - Success

\param  std_str - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResponse"

logical SocketClient :: GetResponse (std::string &std_str )
{
  logical        term = NO;
  std_string     buffer, completebuffer;
  int            nlpos, bspos;
BEGINSEQ
  if ( !Receive(buffer) )                           ERROR
  completebuffer = buffer;
  // extract the first line
  // extract the first word
  nlpos = buffer.find("\n");
  // store everything behind the newline for next request
  if( nlpos != std::string::npos && nlpos>0 ){
    buffer = buffer.substr(0,nlpos-1);
  }
  // extract the code
  if( (bspos = buffer.find(" ",0)) != std::string::npos)
    std_str = buffer.substr(0,bspos);    	

RECOVER
  term = YES;
  std_str = "";
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Receive - 



\return bytecount - 

\param  rSBuffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Receive"

int32 SocketClient :: Receive (std_string &rSBuffer ) const
{
  int32 bytecount = 0;
  int   retry     = 0;
BEGINSEQ
  while ( bytecount == 0 && retry < 30 )
  {
    bytecount = Socket::Receive(rSBuffer);
    if ( !bytecount )
    {
#ifdef __unix__
      sleep(30+retry*10);
#else
      Sleep(30+retry*10);
#endif
      retry++;
    }
  }
  if ( !bytecount )                                 SOSERR(63)
 

RECOVER
  bytecount = 0;
ENDSEQ
  return(bytecount);
}

/******************************************************************************/
/**
\brief  Response - 



\return term - Success
-------------------------------------------------------------------------------
\brief  overload for int codes - 



\param  responsecode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Response"

logical SocketClient :: Response (int32 responsecode )
{
  std_string      code;
  logical         term = NO;
BEGINSEQ
  //return ( GetResponse(code) ||
  //         atoi(code.c_str()) != responsecode );
  // debugable
  term = GetResponse(code);
  if(!term && atoi(code.c_str()) != responsecode){
    SOSEV1("Invalid int Response",20);
    SOSEV2((char*)code.c_str(),code.length())
    char            atoibuffer[30];
    std_string srcode = gvtxitoa(responsecode,atoibuffer,10);
    SOSEV3((char*)srcode.c_str(),srcode.length())
    SOSERR(74)
  }
RECOVER
  term = YES;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  string code - 



\param  sCode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Response"

logical SocketClient :: Response (std_string sCode )
{
  logical         term = NO;
  std_string      code;

BEGINSEQ
  //  return ( GetResponse(code) || code != sCode );
  // debugable
  term = GetResponse(code);
  if(!term && code != sCode){
    SOSEV1("Invalid Response",16)
    SOSEV2((char*)code.c_str(),code.length())
    SOSEV3((char*)sCode.c_str(),sCode.length())
    SOSERR(74)
  }


RECOVER
  term = YES;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  SetHost - 



\return term - Success

\param  shost - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHost"

logical SocketClient :: SetHost (std_string shost )
{
  logical      term = NO;
BEGINSEQ
  if(shost == "")                                   ERROR
  host = shost;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPort - 



\return term - Success

\param  port_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPort"

logical SocketClient :: SetPort (int32 port_number )
{
  logical      term = NO;
BEGINSEQ
  if( port_number <=0 || port_number >= 65535 )                   ERROR
  port = port_number;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SocketClient - 




\param  shost - 
\param  port_number - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SocketClient"

     SocketClient :: SocketClient (std_string shost, int32 port_number )
                     : Socket(),
  host(shost),
  port(port_number)
{



}

/******************************************************************************/
/**
\brief  operator<< - 



\return crSocketClient - Success
-------------------------------------------------------------------------------
\brief  i00 - 



\param  cSBuffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

const SocketClient &SocketClient :: operator<< (const std_string cSBuffer ) const
{

  Send(cSBuffer);
  return *this;

}

/******************************************************************************/
/**
\brief  i01 - 



\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

const SocketClient &SocketClient :: operator<< (int32 intval ) const
{
  char           string[33];
  Send(gvtxitoa(intval,string,10));
  return *this;

}

/******************************************************************************/
/**
\brief  operator>> - 



\return crSocketClient - Success

\param  rSBuffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>>"

const SocketClient &SocketClient :: operator>> (std_string &rSBuffer ) const
{

  Receive(rSBuffer);
  return *this;


}

/******************************************************************************/
/**
\brief  ~SocketClient - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SocketClient"

     SocketClient :: ~SocketClient ( )
{



}


