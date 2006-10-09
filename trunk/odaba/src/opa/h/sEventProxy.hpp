/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EventProxy

\brief    Event proxy
          Event  proxies can be used to transfer events from one property handle
          to  another  one.  Events  signaled  in the sender property handle are
          passed  to  the  receiver  property  handle.  Whether  the  events are
          handled or not, depends on the receiver property handle. 
          Event  proxies  can  be  installed  in addition to any number of event
          handlers for a property handle.
          Eventhandlers     must     be     activated     explicitly     using  
          ActivateProcessEventHandler() and ActivateServerEventHandler().

\date     $Date: 2006/03/12 19:13:22,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EventProxy_HPP
#define   EventProxy_HPP

class     EventProxy;

#include  <cDB_Event.h>
#include  <sEventHandler.hpp>
#include  <sPropertyHandle.hpp>
class  EventProxy :public EventHandler
{
protected  :         PropertyHandle                              *receiver ATTR_ALIGN(4);                                    

public     :
public     :                                                             EventProxy (PropertyHandle &sender_ph, PropertyHandle &receiver_ph );
public     :                                     logical ProcessInstanceHandler (DB_Event intevent );
public     :                                     logical ProcessPropertyHandler (DB_Event intevent );
public     :                                                             ~EventProxy ( );
};

#endif
