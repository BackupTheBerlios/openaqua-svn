/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    EmailSend



\date     $Date: 2006/05/17 13:01:25,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EmailSend_HPP
#define   EmailSend_HPP

class     EmailSend;
#include "csosdll.h"

#include  <sSocketClient.hpp>
#include  <standard.hpp>
class  EmailSend :public SocketClient
{
protected  :         logical                                      connected;                                                 
protected  :         std_string                                   servername;                                                
protected  :         std_string                                   sender;                                                    
protected  :         std_string                                   receiver;                                                  
protected  :         std_string                                   mailbody;                                                  

public     :
                     logical                                      get_connected() { return(connected); }
                     std_string                                  &get_servername() { return(servername); }
                     std_string                                  &get_sender() { return(sender); }
                     std_string                                  &get_receiver() { return(receiver); }
                     std_string                                  &get_mailbody() { return(mailbody); }
public     :                  SOSImpExp             logical Deliver ( );
public     :                  SOSImpExp                  EmailSend (std_string shost );
protected  :                                        logical EnsureCRLF (std_string &rSData );
public     :                  SOSImpExp             logical SetMessage (const std_string cSReceiver, const std_string cSSubject, const std_string cSMessage );
public     :                  SOSImpExp             logical SetSender (std_string sUsername );
};

#endif
