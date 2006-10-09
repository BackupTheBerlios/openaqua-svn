/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    EmailReceive



\date     $Date: 2006/05/17 11:09:13,87 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EmailReceive"

#include  <pdefault.h>
#include  <sEmailAnalyze.hpp>
#include  <sSocketException.hpp>
#include  <standard.hpp>
#include  <sEmailReceive.hpp>


/******************************************************************************/
/**
\brief  Connect

\return term - Success

\param  sUsername
\param  sPassword
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

logical EmailReceive :: Connect (std_string sUsername, std_string sPassword )
{
std::ostringstream   usernamerequest, passwordrequest;
std_string           reply;
try{
	if( !Response("+OK")) throw SocketException ( "Could not read initial data" );
	usernamerequest << "USER " << sUsername << "\r\n";
	Send(usernamerequest.str());
	if( !Response("+OK")) throw SocketException ( "Username not found" );
	passwordrequest << "PASS " << sPassword << "\r\n";
	Send(passwordrequest.str());
	if( !Response("+OK")) throw SocketException ( "Password authentication Failed" );
	connected = true;
}
catch ( SocketException& e) {
std::cerr << "login failed failed " << e.description() << std::endl;
connected = false;
}  

  return(connected);
}

/******************************************************************************/
/**
\brief  Disconnect

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

logical EmailReceive :: Disconnect ( )
{
  logical      term = NO;
BEGINSEQ
	Send("QUIT\r\n");
	if(!Response("+OK"))                               ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EmailReceive


\param  shost
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EmailReceive"

     EmailReceive :: EmailReceive (std_string shost )
                     :   SocketClient(shost, 110)
 ,connected(false)
{
}

/******************************************************************************/
/**
\brief  GetMessage

\return cond - Success

\param  indx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMessage"

logical EmailReceive :: GetMessage (int16 indx )
{
  logical            cond = YES;
  std_string         reply;
  std::ostringstream request;

BEGINSEQ
if(!connected)                                      ERROR

try
{
	request << "RETR " << indx << "\r\n";
	Send(request.str());
	if(!Response("+OK"))
	  throw SocketException ( "unexpected message from server:" + reply );
	
	bool receiving = true;
	rawmail = "";
	while(receiving){
		receiving = false;
		if(reply.rfind(".\r",reply.length())!=reply.length()-3){
			Receive(reply);
			rawmail+= reply;
			receiving = true;
		}
	}
}
catch ( SocketException& e) {
  std::cerr << "mail download failed:"<< e.description() << std::endl;
  ERROR
}
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetMessageList

\return cond - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMessageList"

logical EmailReceive :: GetMessageList ( )
{
  logical      cond = YES;
  bool receiving = true, first = true;  
  std_string   reply,serverline,mailentry;
  std_string   scount;
  std_string   ssize;
  std_string   listdata;
  int end = 0, eend = 0;

BEGINSEQ
if(!connected)                                      ERROR

try
{
  Send("LIST\r\n");
  Receive(reply);
  if( reply.find("+OK",0) != 0) throw;
  std::cout<< reply;
  
  serverline = reply.substr(0,reply.find("\n"));
  reply = reply.substr(serverline.length(),reply.length()-serverline.length());
  // can be "+OK...\n1 123\n2 132\n.\n
  // or "+OK..."
  listdata = "";
  maillist.clear();
  first = true;
  while(receiving){
    receiving = false;
    if(reply.find(".\r")!=reply.length()-3){
      Receive(reply);
      receiving = true;
      first = true;
    }
    if(first){
      listdata+= reply;
      first = false;
    }
  }

  while(end==eend){
    eend = 0;
    eend = listdata.find("\r",end);
	if(eend>=0){
	    if(listdata.substr(end,1)=="\n") 
	      end++;
	    mailentry = listdata.substr(end,eend-end);
	    if(mailentry!=".")
  		  maillist.push_back(mailentry);
		eend++;
		end = eend;
	}
  }
  std::cout << maillist.size() << " messages on server " << std::endl;
}
catch ( SocketException& ) {
//  std::cerr << "list failed" << std::endl;
}  

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  RemoveMessage

\return term - Success

\param  indx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveMessage"

logical EmailReceive :: RemoveMessage (int16 indx )
{
  logical      term = NO;
  std_string         reply;
  std::ostringstream request;

BEGINSEQ
if(!connected)                                      ERROR

try
{
	request << "DELE " << indx << "\r\n";
	Send(request.str());
    if( !Response("+OK"))  throw SocketException ( request.str() + reply );
}
catch ( SocketException& e) 
{
  std::cerr << "mail remove failed:"<< e.description() << std::endl;
}
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


