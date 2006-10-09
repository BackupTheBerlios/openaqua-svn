/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    EmailAnalyze



\date     $Date: 2006/05/16 20:19:54,53 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EmailAnalyze_HPP
#define   EmailAnalyze_HPP

class     EmailAnalyze;
#include "csosdll.h"

#include  <sStringVector.hpp>
#include  <standard.hpp>
class  EmailAnalyze
{
protected  :         std_string                                   message;                                                   
protected  :         std_string                                   header;                                                    
protected  :         std_string                                   body;                                                      
protected  :         std_string                                   alternativebody;                                           
protected  :         std_string                                   displaybody;                                               
protected  :         std_string                                   sender;                                                    
protected  :         std_string                                   subject;                                                   
protected  :         std_string                                   contenttype;                                               
protected  :         StringVector                                 parts;                                                     
protected  :         StringVector                                 attachments;                                               
protected  :         std_string                                   filename;                                                  

public     :
                     std_string                                  &get_message() { return(message); }
                     std_string                                  &get_header() { return(header); }
                     std_string                                  &get_body() { return(body); }
                     std_string                                  &get_alternativebody() { return(alternativebody); }
                     std_string                                  &get_displaybody() { return(displaybody); }
                     std_string                                  &get_sender() { return(sender); }
                     std_string                                  &get_subject() { return(subject); }
                     std_string                                  &get_contenttype() { return(contenttype); }
                     StringVector                                &get_parts() { return(parts); }
                     StringVector                                &get_attachments() { return(attachments); }
                     std_string                                  &get_filename() { return(filename); }
public     :                  SOSImpExp                  EmailAnalyze (const std_string &crSMessage );
public     :                                        std_string FieldAttribute (const std_string &crSHeader, std_string sField );
public     :                                        logical FindParts (const std_string &crSContentType, const std_string &crSBody );
public     :                                        std_string HeaderField (const std_string &crSHeader, std_string cSName ) const;
public     :                                        std_string HeaderValue (const std_string &crSHeader, std_string cSName );
public     :                                        logical Initialize ( );
public     :                                        logical MailBody (EmailAnalyze &rEmailAnalyze );
public     :                                        logical MailBodyAlternative (EmailAnalyze &rEmailAnalyze );
public     :                                        logical MailBodyMixed (EmailAnalyze &rEmailAnalyze );
public     :                                        logical Partition (const std_string &crSMessage, std_string &rSHeader, std_string &rSBody );
};

#endif
