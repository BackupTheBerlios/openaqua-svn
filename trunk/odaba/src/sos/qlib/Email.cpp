/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    Email

\brief    


\date     $Date: 2006/08/30 21:52:13,65 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Email"

#include  <pdefault.h>
#include  <sNString.hpp>
#include  <standard.hpp>
#include  <sEmail.hpp>


/******************************************************************************/
/**
\brief  Analyze - 



\return term - Success

\param  crSMessage - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Analyze"

logical Email :: Analyze (const std_string &crSMessage )
{
  logical      term = NO;
  message = crSMessage;
  Partition(header,body);
  attachments.clear();
  parts.clear();
  
  sender        = HeaderValue(header,"From");
  subject       = HeaderValue(header,"Subject");
  content_type  = HeaderValue(header,"Content-Type");
  file_name     = FieldAttribute(HeaderValue(header,"Content-Disposition"),"filename");
    
  FindParts(content_type,body);
  if ( !MailBody() && !MailBodyAlternative() && !MailBodyMixed() )
    display_body = body;
  

  return(term);
}

/******************************************************************************/
/**
\brief  Attachments - 



\return string_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Attachments"

const StringVector &Email :: Attachments ( ) const
{

  return(attachments);

}

/******************************************************************************/
/**
\brief  Deliver - 



\return term - Success

\param  cSReceiver - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deliver"

logical Email :: Deliver (const std_string cSReceiver )
{
  logical              term  = NO;
  std_string           receiver;

BEGINSEQ
  receiver = cSReceiver;
  if(receiver.find(" ")!=std::string::npos){
    SOSError().TraceMessage("Email Delivery: Trim Blanks");
    int pos;
    while((pos = receiver.find(" "))!=std::string::npos)
	    receiver.erase(pos,1);
  }
  //SOSError().TraceMessage("Email Delivery: Connect");
  if ( SocketClient::Connect() )                     ERROR
  //SOSError().TraceMessage("Email Delivery: Handshake");

  if ( Response(220) )                               SOSERR(64)

  *this << "helo " << host << "\r\n";
  if ( Response(250) )                               SOSERR(65)

  //SOSError().TraceMessage("Email Delivery: From ", (char*)sender.c_str());
  *this << "mail from: <" << sender << ">\r\n";
  if ( Response(250) )                               SOSERR(66)

  //SOSError().TraceMessage("Email Delivery: To ", (char*)receiver.c_str());
  *this << "rcpt to: <" << receiver << ">\r\n";
  if ( Response(250) )                                 SOSERR(67)

  //SOSError().TraceMessage("Email Delivery: Data");
  *this << "data\r\n";
  if ( Response(354) )                                 SOSERR(68)

  EnsureCRLF(message);
  *this << message;
  *this << "\r\n.\r\n";
  if ( Response(250) )                                 SOSERR(69)

  //SOSError().TraceMessage("Email Delivery: Quit");
  *this << "quit\r\n";
  if ( Response(221) )                                 SOSERR(70)
//	Add error text 70: "Quit Failed" );


RECOVER
  term = YES;
ENDSEQ
  SocketClient::Disconnect();
  return(term);
}

/******************************************************************************/
/**
\brief  DisplayBody - 



\return std_str - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayBody"

const std::string &Email :: DisplayBody ( ) const
{

  return(display_body);

}

/******************************************************************************/
/**
\brief  Email - 



-------------------------------------------------------------------------------
\brief  empty - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Email"

     Email :: Email ( )
                     : SocketClient("",0),
  sender(),
  subject(),
  message(),
  header(),
  body(),
  alternative_body(),
  display_body(),
  content_type(),
  file_name(),
  parts(),
  attachments()
{

// thats not exactly what i intended
// use this constructor to analyze a message

}

/******************************************************************************/
/**
\brief  i00 - 



\param  shost - 
\param  sCSender - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Email"

     Email :: Email (std_string shost, const std_string &sCSender )
                     : SocketClient(shost,-1)
{

  sender = sCSender;

}

/******************************************************************************/
/**
\brief  EnsureCRLF - 



\return term - Success

\param  rSData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnsureCRLF"

logical Email :: EnsureCRLF (std_string &rSData )
{
  logical      term = NO;
  int          posn = 0;
  int          posr = 0;
  do
  {
    posn = rSData.find("\n",posn+1);
    if ( posn != -1 )
    {
      posr = rSData.find("\r",posn-1);
      if ( posn-posr != 1 || posr == -1 )
      {
        rSData.replace(posn,1,"\r\n");
        posn++;
      }
    }
  } while ( posn != -1 );
  return(term);
}

/******************************************************************************/
/**
\brief  FieldAttribute - 



\return sAttribute - Success

\param  crSHeader - 
\param  sField - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldAttribute"

std_string Email :: FieldAttribute (const std_string &crSHeader, std_string sField )
{
  std_string          sAttribute,begin,end;
  int                 pbegin,pend;
BEGINSEQ
  begin  = sField + "=\"";
  end    = "\"";
  pbegin = crSHeader.find(begin,0);
  pend   = crSHeader.rfind(end,crSHeader.length());
  if(pbegin==-1 || pend == -1 || pend<pbegin)       ERROR

  sAttribute =  crSHeader.substr(pbegin+begin.length(), pend - (pbegin+begin.length()));

RECOVER
  sAttribute = "";
ENDSEQ
  return(sAttribute);
}

/******************************************************************************/
/**
\brief  FileName - 



\return std_str - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FileName"

std::string &Email :: FileName ( )
{

  return(file_name);

}

/******************************************************************************/
/**
\brief  FindParts - 



\return term - Success

\param  crSContentType - 
\param  crSBody - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindParts"

logical Email :: FindParts (const std_string &crSContentType, const std_string &crSBody )
{
  logical      term = NO;
  std_string   separator, part;
  int          start,end;
BEGINSEQ
  separator = FieldAttribute(crSContentType,"boundary");
  if ( separator == "" )                            ERROR

  start = end = 0;
  parts.clear();
  while ( start == end )
  {
    if (end >=0 ) 
      start = crSBody.find(separator,end);
    if ( start>= 0 ) 
      end   = crSBody.find(separator,start+separator.length());
    if (start >= 0 && end>=0 )
    {
      start += separator.length() + 1;
      end   -= 2;
      part   = crSBody.substr(start, end - start);
      start  = end;
      parts.push_back(part);
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetMessage - 



\return term - Success

\param  indx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMessage"

logical Email :: GetMessage (int16 indx )
{
  logical            cond = YES;
  std_string         reply;
  std_string         buffer;
  int                nlpos;
  bool               receiving = true;

BEGINSEQ
  if ( !IsConnected() )                               ERROR

  *this << "RETR " << indx << "\r\n";
 
  if ( !Receive(reply) )                            ERROR
  if ( reply.find("+OK",0) != 0){
    SOSEV1("Invalid Response",16)
    SOSEV2((char*)reply.c_str(),reply.length())
    SOSEV3("+OK",3)
    SOSERR(74)
  }
  if ( (nlpos = reply.find("\n")) != std::string::npos )
    message = reply.substr(nlpos,reply.length()-nlpos);
  else
    message = "";
    
  while ( receiving )
  {
	receiving = false;
	if ( reply.rfind(".\r",reply.length()) != reply.length()-3)
	{
	  if ( !Receive(reply) )                           ERROR
	  message += reply;
	  receiving = true;
	}
  }
  // reset message
  Analyze(message);

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetMessageList - 



\return sList - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMessageList"

StringVector Email :: GetMessageList ( )
{
  bool         receiving = true;
  bool         first = true;  
  std_string   reply;
  StringVector maillist;
  std_string   serverline;
  std_string   mailentry;
  std_string   listdata;
  int          end = 0, eend = 0;

BEGINSEQ
  if ( !IsConnected() )                             ERROR

  Send("LIST\r\n");
  if ( !Receive(reply) )                            ERROR
  if ( reply.find("+OK",0) != 0)                    SOSERR(75)
// Add error text 75: no message list available
  
  serverline = reply.substr(0,reply.find("\n"));
  reply = reply.substr(serverline.length(),reply.length()-serverline.length());
  // can be "+OK...\n1 123\n2 132\n.\n
  // or "+OK..."

  listdata = "";
  first = true;
  while(receiving)
  {
    receiving = false;
    if(reply.find(".\r")!=reply.length()-3)
    {
      if ( !Receive(reply) )                        ERROR
      receiving = true;
      first = true;
    }
    if ( first )
    {
      listdata+= reply;
      first = false;
    }
  }

  while( end == eend )
  {
	if ( (eend = listdata.find("\r",end)) > 0 )
	{
	  if ( listdata.substr(end,1) == "\n" ) 
	    end++;
	  mailentry = listdata.substr(end,eend-end);
	  if(mailentry!=".")
  		maillist.push_back(mailentry);
	  eend++;
	  end = eend;
	}
  }

RECOVER
  maillist.clear();
ENDSEQ
  return(maillist);
}

/******************************************************************************/
/**
\brief  HeaderField - 



\return sField - Success

\param  crSHeader - 
\param  cSName - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HeaderField"

std_string Email :: HeaderField (const std_string &crSHeader, std_string cSName ) const
{
  int                 start, end, rend;
  std_string          stitle;
  std_string          sField;
BEGINSEQ
	stitle = std_string("\n") + cSName + ":";	
	start = crSHeader.find(stitle,0);
    if ( start == -1 )                               ERROR

	start++; // without the newline at the beginning
  	end = start;
	do
	{
  	  end   = crSHeader.find(":",end+stitle .length()); 
	  rend  = crSHeader.rfind("\r",end); // to the beginning
	  if ( rend < start )   // on the same line
	  { 
	    end++;
	    rend = end;
	  }
	  else if ( rend != -1 && crSHeader.find(" ",rend) < end ) // is there a space between : and beginning of line
	    end = rend;
	} while ( end == rend && end != -1 );

	end = rend;
	sField = crSHeader.substr(start,end-start);
RECOVER
  sField = "";
ENDSEQ
  return( sField );
}

/******************************************************************************/
/**
\brief  HeaderValue - 



\return sValue - Success

\param  crSHeader - 
\param  cSName - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HeaderValue"

std_string Email :: HeaderValue (const std_string &crSHeader, std_string cSName )
{
  std_string   field;
  int          valuestart;
BEGINSEQ
  field = HeaderField(crSHeader,cSName);
  if ( field == "" )                                 ERROR
  
  valuestart = field.find(cSName)+cSName.length()+2;  //[: ]
  field = field.substr(valuestart,field.length()-valuestart);
RECOVER
  field = "";
ENDSEQ
  return(field);
}

/******************************************************************************/
/**
\brief  MailBody - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MailBody"

logical Email :: MailBody ( )
{
  logical      cond = YES;
BEGINSEQ
  if ( content_type.find("text/plain") == -1 )    ERROR

  if ( HeaderValue(header,"Content-Disposition") != "" )
                                                    ERROR
  display_body = body;

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  MailBodyAlternative - 



\return cond - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MailBodyAlternative"

logical Email :: MailBodyAlternative ( )
{
  logical      cond = YES;
  StringVector::iterator pit;

BEGINSEQ
  if ( content_type.find("multipart/alternative") == -1 )
                                                    ERROR
  for ( pit = parts.begin(); pit != parts.end(); pit++)
  {
	Email part;
	part.Analyze(*pit);
	if ( !part.MailBody() )
	  alternative_body = part.get_body();
	else
	  display_body = part.get_display_body();
  }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  MailBodyMixed - 



\return cond - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MailBodyMixed"

logical Email :: MailBodyMixed ( )
{
  logical      cond = YES;
  StringVector::iterator pit;

BEGINSEQ
  if ( content_type.find("multipart/mixed") == -1 ) ERROR

  for ( pit = parts.begin(); pit != parts.end(); pit++ )
  {
	Email part;
	part.Analyze(*pit);
	if( !part.MailBody() && !part.MailBodyAlternative() )
      attachments.push_back(*pit);
    else
      display_body = part.get_display_body();
  }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  NL2BR - 



\return shtml - Success

\param  cSMessage - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NL2BR"

std_string Email :: NL2BR (const std_string cSMessage )
{
  std_string shtml = cSMessage;
  int pos;
  pos = shtml.find("\n");
  while(pos!=std::string::npos){
    shtml.replace(pos,1,"<br/>\n");
    pos = shtml.find("\n",pos + 6); //<br/>\n
  }
  return(shtml);
}

/******************************************************************************/
/**
\brief  POPDisconnect - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "POPDisconnect"

void Email :: POPDisconnect ( )
{
  logical      term = NO;
  if( IsConnected() ){
	  Send("QUIT\r\n");
	  term = Response("+OK");
  }
  Disconnect();


}

/******************************************************************************/
/**
\brief  POPLogin - 



\return term - Success

\param  sUsername - 
\param  sPassword - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "POPLogin"

logical Email :: POPLogin (std_string sUsername, std_string sPassword )
{
  logical           term = NO;
BEGINSEQ
  SOSError().TraceMessage("Email POP: Handshake");
  if ( IsConnected() )                              LEAVESEQ
  if ( SocketClient::Connect() )                    ERROR

  if ( Response("+OK") )                            SOSERR(71)
// Add Error text 71: "Could not read initial data"

  SOSError().TraceMessage("Email POP: Authentication");
  *this << "USER " << sUsername << "\r\n";
  if( Response("+OK") )
  {
    POPDisconnect();
    SOSERR(72)
  }
// Add Error text 72: "Username not found"
  
  *this << "PASS " << sPassword << "\r\n";
  if( Response("+OK"))
  {
     POPDisconnect();
     SOSERR(73)
  }
// Add Error text 73: "Password authentication Failed"
  SOSError().TraceMessage("Email POP: Connected");

RECOVER
  term = YES;
ENDSEQ
  return(!IsConnected());
}

/******************************************************************************/
/**
\brief  Partition - 



\return term - Success

\param  rSHeader - 
\param  rSBody - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Partition"

logical Email :: Partition (std_string &rSHeader, std_string &rSBody )
{
  logical      term = NO;
  int          pos_border;
BEGINSEQ
  pos_border = message.find("\n\r");
  if ( pos_border == -1 )                              ERROR

  rSHeader    = message.substr(0,pos_border);
  pos_border += 3;
  rSBody      = message.substr(pos_border,message.length()-pos_border);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveMessage - 



\return term - Success

\param  indx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveMessage"

logical Email :: RemoveMessage (int16 indx )
{
  logical      term = NO;
  std_string         reply;

BEGINSEQ
  if ( !IsConnected() )                               ERROR

  *this << "DELE " << indx << "\r\n";
  if ( Response("+OK") )                            SOSERR(76)
// Add error text 76: Remove message failed

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Sender - 



\return std_str - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Sender"

const std::string &Email :: Sender ( ) const
{

  return(sender);

}

/******************************************************************************/
/**
\brief  SetMessage - 



\return term - Success
-------------------------------------------------------------------------------
\brief  HTML - 



\param  cSSubject - 
\param  cSMessage - 
\param  cSHTMLMessage - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMessage"

logical Email :: SetMessage (const std_string cSSubject, const std_string cSMessage, const std_string cSHTMLMessage )
{
  logical   term = NO;
  std_string uboundary = "0xcf00efdda4255479";
message = "From: " + sender + "\n";
message+= "MIME-Version: 1.0\n";
message+= "Content-Type: multipart/alternative";
message+= "; boundary = " + uboundary + "\n";
message+= "Subject: " + cSSubject + "\n\n";
message+= cSMessage;
message+= "\n\n";

// plaintext
message+= "--" + uboundary + "\n";
message+="Content-Type: text/plain; charset=ISO-8859-1\n";
message+="Content-Transfer-Encoding: base64\n\n";
message+="\n";
message+= ToMIME(cSMessage);

// html
message+= "\n\n";
message+= "--" + uboundary + "\n";
message+="Content-Type: text/html; charset=ISO-8859-1\n";
message+="Content-Transfer-Encoding: base64\n"; 
message+="\n";
message+=ToMIME(cSHTMLMessage);


  return(term);
}

/******************************************************************************/
/**
\brief  HTML_char_string - 



\param  subject - 
\param  text - Error text
\param  html_text - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMessage"

logical Email :: SetMessage (char *subject, char *text, char *html_text )
{

  return ( SetMessage(std_string(subject),
                      std_string(text),
                      std_string(html_text)) );

}

/******************************************************************************/
/**
\brief  i00 - 



\param  cSSubject - 
\param  cSMessage - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMessage"

logical Email :: SetMessage (const std_string cSSubject, const std_string cSMessage )
{
  logical      term = NO;
 // replace \r\n.\r\n in cSMessage
 // replace \n with \r\n
  // simple plain text
  message  = "";
  message += "From: " + sender +"\n";
  message += "Subject: " + cSSubject +"\n";
  message += "\n" + cSMessage;

  return(term);
}

/******************************************************************************/
/**
\brief  SetSender - 



\return term - Success

\param  sUsername - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetSender"

logical Email :: SetSender (std_string sUsername )
{
  logical      term = NO;
  sender = sUsername;
  return(term);
}

/******************************************************************************/
/**
\brief  Subject - 



\return std_str - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Subject"

const std::string &Email :: Subject ( ) const
{

  return(subject);

}

/******************************************************************************/
/**
\brief  ToBase64 - 



\return base64 - Success

\param  cSMessage - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToBase64"

std_string Email :: ToBase64 (const std_string cSMessage )
{
  std_string base64;
  NString    ns,ns64;
  int        indx0;
//encode base64
ns = (char*) cSMessage.c_str();
ns64 = ns.ToBase64();
base64= (char*)ns;
  return(base64);
}

/******************************************************************************/
/**
\brief  ToMIME - 



\return mimedata - Success

\param  cSMessage - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToMIME"

std_string Email :: ToMIME (const std_string cSMessage )
{
  std_string base64;
  std_string mimedata;
  int        indx0;
//encode base64
//\n every 76 characters
base64 = ToBase64(cSMessage);
if(base64 == cSMessage )
  return base64;
for(indx0 = 0; indx0<base64.length(); indx0++)
{
  mimedata+=base64[indx0];
  if(indx0>0&&indx0%76==0)
    mimedata+="\n";
}
  return(mimedata);
}


