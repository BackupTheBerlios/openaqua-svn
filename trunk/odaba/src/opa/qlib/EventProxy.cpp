/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/03/12 19:17:33,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EventProxy"

#include  <popa7.h>
#include  <sPropertyHandle.hpp>
#include  <sbinti.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sEventProxy.hpp>


/******************************************************************************/
/**
\brief  EventProxy - Constructor
        The  constructor bulds the  link between the  sender property handle and
        the receiver property handle.


\param  sender_ph -
\param  receiver_ph -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventProxy"

                        EventProxy :: EventProxy (PropertyHandle &sender_ph, PropertyHandle &receiver_ph )
                     :   EventHandler(sender_ph)
{

  if ( receiver_ph.IsValid() )
    receiver = &receiver_ph;

}

/******************************************************************************/
/**
\brief  ProcessInstanceHandler - 


\return cont - Continuation

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessInstanceHandler"

logical EventProxy :: ProcessInstanceHandler (DB_Event intevent )
{
  node      *nodeptr = receiver ? receiver->get_nodeptr() : NULL;
  inti      *intiptr;
  logical    cont = NO;
BEGINSEQ
  if ( !nodeptr || !(nodeptr = nodeptr->GetNode()) || 
       !(intiptr = nodeptr->get_nodeinst())           ) ERROR
       
  if ( intiptr != property_handle.get_nodeptr()->get_nodeinst() )
    cont = ((binti *)intiptr)->GenerateEvent(intevent);
RECOVER

ENDSEQ
  return(cont);
}

/******************************************************************************/
/**
\brief  ProcessPropertyHandler - 


\return cont - Continuation

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessPropertyHandler"

logical EventProxy :: ProcessPropertyHandler (DB_Event intevent )
{
  node      *nodeptr = receiver ? receiver->get_nodeptr() : NULL;
  logical    cont = NO;
BEGINSEQ
  if ( !nodeptr || !(nodeptr = nodeptr->GetNode()) ) ERROR
  
  if ( nodeptr != property_handle.get_nodeptr() )
    cont = nodeptr->GenerateEvent(intevent);
RECOVER

ENDSEQ
  return(cont);
}

/******************************************************************************/
/**
\brief  ~EventProxy - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EventProxy"

                        EventProxy :: ~EventProxy ( )
{

  DeactivateProcessEventHandler();
  DeactivateServerEventHandler();

}


