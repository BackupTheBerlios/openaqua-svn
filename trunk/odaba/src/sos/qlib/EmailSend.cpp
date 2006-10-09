/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    EmailSend



\date     $Date: 2006/05/18 19:02:46,82 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EmailSend"

#include  <pdefault.h>
#include  <standard.hpp>
#include  <sEmailSend.hpp>


/******************************************************************************/
/**
\brief  Deliver

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deliver"

logical EmailSend :: Deliver ( )
{
logical              cond  = YES;
std::ostringstream   request;
std_string           reply;

try{
	if(!Response(220)) throw SocketException ( "Could not read initial data" + reply );

*this<<"helo";
    request << "helo " << servername << "\r\n";
	Send(request.str());
	if(!Response(250)) throw SocketException ( "Helo not Accepted" + reply );

	request.clear();request << "mail from: <" << sender << ">\r\n";
	Send(request.str());
	if(!Response(250)) throw SocketException ( "Sender not Accepted" );

	request.clear();request << "rcpt to: <" << receiver << ">\r\n";
	Send(request.str());
	if(!Response(250)) throw SocketException ( "Receiver not Accepted" );

	request.clear();request << "data\r\n";
	Send(request.str());
	if(!Response(354)) throw SocketException ( "data command not Accepted" );
	
	Send(mailbody);
	if(!Response(250)) throw SocketException ( "Data not accepted - mail not send" );

	Send("quit\n");
	if(!Response(221)) throw SocketException ( "Quit Failed" );
	connected = true;

}
catch ( SocketException& e) {
  std::cerr << "send failed failed " << e.description() << std::endl;
  cond = false;
}  

  return(cond);
}

/******************************************************************************/
/**
\brief  EmailSend


\param  shost
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EmailSend"

     EmailSend :: EmailSend (std_string shost )
                     :  SocketClient(shost,25)
,connected(false)
{
}

/******************************************************************************/
/**
\brief  EnsureCRLF

\return term - Success

\param  rSData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnsureCRLF"

logical EmailSend :: EnsureCRLF (std_string &rSData )
{
  logical      term = NO;
  int          posn = 0;
  int          posr = 0;
do{
  posn = rSData.find("\n",posn+1);
  if(posn!=-1)
    posr = rSData.find("\r",posn-1);
  if(posn!=-1 && (posr-posn!=1 || posr == -1)){
    rSData.replace(posn,1,"\r\n");
    posn++;
  }
}while(posn!=-1);
  return(term);
}

/******************************************************************************/
/**
\brief  SetMessage

\return term - Success

\param  cSReceiver
\param  cSSubject
\param  cSMessage
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMessage"

logical EmailSend :: SetMessage (const std_string cSReceiver, const std_string cSSubject, const std_string cSMessage )
{
  logical      term = NO;
 receiver = cSReceiver;
 servername = "helena";
 if(sender=="")
   sender = "bigbrother@run-software.com";

 // replace \r\n.\r\n in cSMessage
 // replace \n with \r\n
 
 mailbody = "";
 mailbody+= "From: " + sender +"\n";
 mailbody+= "Subject: " + cSSubject +"\n";
 mailbody+= "\n" + cSMessage;
 EnsureCRLF(mailbody);
 mailbody+= "\r\n.\r\n";
  return(term);
}

/******************************************************************************/
/**
\brief  SetSender

\return term - Success

\param  sUsername
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSender"

logical EmailSend :: SetSender (std_string sUsername )
{
  logical      term = NO;
  sender = sUsername;
  return(term);
}


