/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    Email

\brief    


\date     $Date: 2006/08/28 14:43:27,36 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Email_HPP
#define   Email_HPP

class     Email;
#include "csosdll.h"

#include  <sSocketClient.hpp>
#include  <sStringVector.hpp>
#include  <standard.hpp>
class  Email :public SocketClient
{
protected  :         std_string                                   sender;                                                    // 
protected  :         std_string                                   subject;                                                   // 
protected  :         std_string                                   message;                                                   // 
protected  :         std_string                                   header;                                                    // 
protected  :         std_string                                   body;                                                      // 
protected  :         std_string                                   alternative_body;                                          // 
protected  :         std_string                                   display_body;                                              // 
protected  :         std_string                                   content_type;                                              // 
protected  :         std_string                                   file_name;                                                 // 
protected  :         StringVector                                 parts;                                                     // 
protected  :         StringVector                                 attachments;                                               // 

public     :
                     std_string                                  &get_sender() { return(sender); }
                     std_string                                  &get_subject() { return(subject); }
                     std_string                                  &get_message() { return(message); }
                     std_string                                  &get_header() { return(header); }
                     std_string                                  &get_body() { return(body); }
                     std_string                                  &get_alternative_body() { return(alternative_body); }
                     std_string                                  &get_display_body() { return(display_body); }
                     std_string                                  &get_content_type() { return(content_type); }
                     std_string                                  &get_file_name() { return(file_name); }
                     StringVector                                &get_parts() { return(parts); }
                     StringVector                                &get_attachments() { return(attachments); }
public     :                  SOSImpExp             logical Analyze (const std_string &crSMessage );
public     :                  SOSImpExp             const StringVector &Attachments ( ) const;
public     :                  SOSImpExp             logical Deliver (const std_string cSReceiver );
public     :                  SOSImpExp             const std::string &DisplayBody ( ) const;
public     :                  SOSImpExp                  Email ( );
public     :                  SOSImpExp                  Email (std_string shost, const std_string &sCSender );
public     :                                        logical EnsureCRLF (std_string &rSData );
public     :                                        std_string FieldAttribute (const std_string &crSHeader, std_string sField );
public     :                  SOSImpExp             std::string &FileName ( );
public     :                                        logical FindParts (const std_string &crSContentType, const std_string &crSBody );
public     :                  SOSImpExp             logical GetMessage (int16 indx );
public     :                  SOSImpExp             StringVector GetMessageList ( );
public     :                                        std_string HeaderField (const std_string &crSHeader, std_string cSName ) const;
public     :                  SOSImpExp             std_string HeaderValue (const std_string &crSHeader, std_string cSName );
public     :                                        logical MailBody ( );
public     :                                        logical MailBodyAlternative ( );
public     :                                        logical MailBodyMixed ( );
public     :                                        std_string NL2BR (const std_string cSMessage );
public     :                  SOSImpExp             void POPDisconnect ( );
public     :                  SOSImpExp             logical POPLogin (std_string sUsername, std_string sPassword );
public     :                  SOSImpExp             logical Partition (std_string &rSHeader, std_string &rSBody );
public     :                  SOSImpExp             logical RemoveMessage (int16 indx );
public     :                  SOSImpExp             const std::string &Sender ( ) const;
public     :                  SOSImpExp             logical SetMessage (const std_string cSSubject, const std_string cSMessage, const std_string cSHTMLMessage );
public     :                  SOSImpExp             logical SetMessage (char *subject, char *text, char *html_text );
public     :                  SOSImpExp             logical SetMessage (const std_string cSSubject, const std_string cSMessage );
public     :                  SOSImpExp             logical SetSender (std_string sUsername );
public     :                  SOSImpExp             const std::string &Subject ( ) const;
public     :                                        std_string ToBase64 (const std_string cSMessage );
public     :                                        std_string ToMIME (const std_string cSMessage );
};

#endif
