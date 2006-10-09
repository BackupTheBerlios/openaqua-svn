/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    EmailReceive



\date     $Date: 2006/05/16 20:38:46,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EmailReceive_HPP
#define   EmailReceive_HPP

class     EmailReceive;
#include "csosdll.h"

#include  <sEmailAnalyze.hpp>
#include  <sSocketClient.hpp>
#include  <sStringVector.hpp>
#include  <standard.hpp>
class  EmailReceive :public SocketClient
{
protected  :         logical                                      connected;                                                 
protected  :         std_string                                   rawmail;                                                   
protected  :         StringVector                                 maillist;                                                  

public     :
                     logical                                      get_connected() { return(connected); }
                     std_string                                  &get_rawmail() { return(rawmail); }
                     StringVector                                &get_maillist() { return(maillist); }
public     :                  SOSImpExp             logical Connect (std_string sUsername, std_string sPassword );
public     :                  SOSImpExp             logical Disconnect ( );
public     :                  SOSImpExp                  EmailReceive (std_string shost );
public     :                  SOSImpExp             logical GetMessage (int16 indx );
public     :                  SOSImpExp             logical GetMessageList ( );
public     :                  SOSImpExp             logical RemoveMessage (int16 indx );
};

#endif
