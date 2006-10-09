/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    EmailAnalyze



\date     $Date: 2006/05/17 13:12:13,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EmailAnalyze"

#include  <pdefault.h>
#include  <standard.hpp>
#include  <sEmailAnalyze.hpp>


/******************************************************************************/
/**
\brief  EmailAnalyze


\param  crSMessage
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EmailAnalyze"

     EmailAnalyze :: EmailAnalyze (const std_string &crSMessage )
                     :  message(crSMessage)
,header()
,body()
,sender()
,subject()
,contenttype()
,parts()
{
Initialize();
}

/******************************************************************************/
/**
\brief  FieldAttribute

\return sAttribute - Success

\param  crSHeader
\param  sField
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldAttribute"

std_string EmailAnalyze :: FieldAttribute (const std_string &crSHeader, std_string sField )
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
\brief  FindParts

\return term - Success

\param  crSContentType
\param  crSBody
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindParts"

logical EmailAnalyze :: FindParts (const std_string &crSContentType, const std_string &crSBody )
{
  logical      term = NO;
  std_string   separator, part;
  int          start,end;
BEGINSEQ
  separator = FieldAttribute(crSContentType,"boundary");
  if(separator == "")                               ERROR
  start = end = 0;
  parts.clear();
  while(start == end){
    if(end  >=0) start = crSBody.find(separator,end);
    if(start>=0) end   = crSBody.find(separator,start+separator.length());
    if(start>=0 && end>=0){
      start+= separator.length() + 1;
      end  -= 2;
      part  = crSBody.substr(start, end - start);
      start = end;
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
\brief  HeaderField

\return sField - Success

\param  crSHeader
\param  cSName
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HeaderField"

std_string EmailAnalyze :: HeaderField (const std_string &crSHeader, std_string cSName ) const
{
  logical             term = NO;
  int                 start, end, rend,nend;
  std::ostringstream  stitle;
  std_string          sField;
BEGINSEQ
	stitle << "\n" << cSName << ":";	
	start = crSHeader.find(stitle.str(),0);
    if(start==-1)                                   ERROR
	start++; // without the newline at the beginning
  	end = start;
	do{
  	  end   = crSHeader.find(":"  ,end+stitle.str().length()); 
	  rend  = crSHeader.rfind("\r",end); // to the beginning
	  if(rend<start){ // on the same line
	    end++;
	    rend = end;
	  }else if(rend!=-1 && crSHeader.find(" ",rend)<end){
	    // is there a space between : and beginning of line
	    end = rend;
	  }
	}while(end == rend && end != -1);
	end = rend;
	sField = crSHeader.substr(start,end-start);
RECOVER
  sField = "";
ENDSEQ
  return( sField );
}

/******************************************************************************/
/**
\brief  HeaderValue

\return sValue - Success

\param  crSHeader
\param  cSName
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HeaderValue"

std_string EmailAnalyze :: HeaderValue (const std_string &crSHeader, std_string cSName )
{
  logical      term = NO;
  std_string   field;
  int          valuestart;
BEGINSEQ
  field = HeaderField(crSHeader,cSName);
  if(field=="")                                     ERROR
  valuestart = field.find(cSName)+cSName.length()+2;  //[: ]
  field = field.substr(valuestart,field.length()-valuestart);
RECOVER
  field = "";
ENDSEQ
  return(field);
}

/******************************************************************************/
/**
\brief  Initialize

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical EmailAnalyze :: Initialize ( )
{
  logical      term = NO;
 	Partition(message,header,body);

	sender        = HeaderValue(header,"From");
	subject       = HeaderValue(header,"Subject");
	contenttype   = HeaderValue(header,"Content-Type");
    filename      = FieldAttribute(HeaderValue(header,"Content-Disposition"),"filename");
    
    FindParts(contenttype,body);
    if(!MailBody(*this) && !MailBodyAlternative(*this) && !MailBodyMixed(*this))
      displaybody = body;
  return(term);
}

/******************************************************************************/
/**
\brief  MailBody

\return cond - Success

\param  rEmailAnalyze
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MailBody"

logical EmailAnalyze :: MailBody (EmailAnalyze &rEmailAnalyze )
{
  logical      cond = YES;
BEGINSEQ
  if(rEmailAnalyze.get_contenttype().find("text/plain")!=-1){
     if(rEmailAnalyze.HeaderValue(rEmailAnalyze.get_header(),"Content-Disposition")!="")
       ERROR
     displaybody = rEmailAnalyze.get_body();
     LEAVESEQ
  }
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  MailBodyAlternative

\return cond - Success

\param  rEmailAnalyze
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MailBodyAlternative"

logical EmailAnalyze :: MailBodyAlternative (EmailAnalyze &rEmailAnalyze )
{
  logical      cond = YES;
  StringVector::iterator pit;

BEGINSEQ
  if(rEmailAnalyze.get_contenttype().find("multipart/alternative")!=-1){
		for(pit = rEmailAnalyze.get_parts().begin(); pit!=rEmailAnalyze.get_parts().end();pit++){
			EmailAnalyze part((*pit));
			if(!MailBody(part))
				alternativebody = part.get_body();
		}
     LEAVESEQ
  }
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  MailBodyMixed

\return cond - Success

\param  rEmailAnalyze
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MailBodyMixed"

logical EmailAnalyze :: MailBodyMixed (EmailAnalyze &rEmailAnalyze )
{
  logical      cond = YES;
  StringVector::iterator pit;

BEGINSEQ
  if(rEmailAnalyze.get_contenttype().find("multipart/mixed")!=-1){
		for(pit = rEmailAnalyze.get_parts().begin(); pit!=rEmailAnalyze.get_parts().end();pit++){
			EmailAnalyze part((*pit));
			if(!MailBody(part) && !MailBodyAlternative(part))
			attachments.push_back(*pit);
		}
     LEAVESEQ
  }
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Partition

\return term - Success

\param  crSMessage
\param  rSHeader
\param  rSBody
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Partition"

logical EmailAnalyze :: Partition (const std_string &crSMessage, std_string &rSHeader, std_string &rSBody )
{
  logical      term = NO;
  int          pos_border;
  std_string   message;
BEGINSEQ
	message = crSMessage;
	pos_border = message.find("\n\r");
	if(pos_border==-1)                                  ERROR
	rSHeader = message.substr(0,pos_border);
	pos_border+=3;
	rSBody   = message.substr(pos_border,message.length()-pos_border);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


