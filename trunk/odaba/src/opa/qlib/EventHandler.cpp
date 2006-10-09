/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EventHandler

\brief    Event Handler Class
          The  Event Handler Class is a  base class for supporting writing event
          handlers.  It  provides  some  basic  functionality  for  setting  and
          calling event handlers for handling server events. 
          You  may derive your own handler  classes from EventHandler to provide
          handler  functions  for  server  events.  You may overload the handler
          functions   InstanceEventHandler()   and   PropertyEventHandler()  for
          providing your application specific event handling.
          The  event handler allows handling  instance, property (collection) or
          local  events. Instance  and property  events are client server events
          that  are  generated,  when  an  instance or collection changes. Local
          events  are those events, which are usually handled in the instance or
          property  context.  You  may,  however,  set  event  handler for local
          events  for  a  specific  property handle, which allows overwriting or
          expanding context functions.

\date     $Date: 2006/03/12 19:17:32,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EventHandler"

#include  <popa7.h>
#include  <cevtp.h>
#include  <sACObject.hpp>
#include  <sEventLink.hpp>
#include  <sEventHandler.hpp>


/******************************************************************************/
/**
\brief  Acitvate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Acitvate"

void EventHandler :: Acitvate ( )
{

  instance_link->Activate();
  property_link->Activate();
  proc_inst_link->Activate();
  proc_prop_link->Activate();

}

/******************************************************************************/
/**
\brief  ActivateProcessEventHandler - Activate process event handlers
        The  function activates the event handlers  for process events. When not
        activating  process event handling process events will not passed to the
        application.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateProcessEventHandler"

void EventHandler :: ActivateProcessEventHandler ( )
{
  ACObject    *obh = property_handle.StartRTA();

  if ( !proc_prop_link )
    proc_prop_link = new ELINKL(this,EventHandler,PropProcHandler);
  property_handle.SetPropertyProcessHandler(proc_prop_link);

  if ( !proc_inst_link )
    proc_inst_link = new ELINKL(this,EventHandler,InstProcHandler);
  property_handle.SetInstanceProcessHandler(proc_inst_link);
  obh->StopReadTA(NO);

}

/******************************************************************************/
/**
\brief  ActivateServerEventHandler - Activate server event handlers
        The  function activates the  event handlers for  server events. When not
        activating  server event handling process events  will not passed to the
        application.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateServerEventHandler"

void EventHandler :: ActivateServerEventHandler ( )
{
  ACObject    *obh = property_handle.StartRTA();
  if ( !instance_link )
    instance_link = new ELINK(this,EventHandler,InstHandler);
  property_handle.SetInstanceEventHandler(instance_link);
  
  if ( !property_link )
    property_link = new ELINK(this,EventHandler,PropHandler);
  property_handle.SetPropertyEventHandler(property_link);
  
  property_handle.RegisterHandle();
  obh->StopReadTA(NO);
}

/******************************************************************************/
/**
\brief  Deactivate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

void EventHandler :: Deactivate ( )
{

  instance_link->Deactivate();
  property_link->Deactivate();
  proc_inst_link->Deactivate();
  proc_prop_link->Deactivate();

}

/******************************************************************************/
/**
\brief  DeactivateProcessEventHandler


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateProcessEventHandler"

void EventHandler :: DeactivateProcessEventHandler ( )
{

  if ( proc_prop_link )
    property_handle.ResetPropertyProcessHandler(proc_prop_link);

  if ( proc_inst_link )
    property_handle.ResetInstanceProcessHandler(proc_inst_link);

}

/******************************************************************************/
/**
\brief  DeactivateServerEventHandler


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateServerEventHandler"

void EventHandler :: DeactivateServerEventHandler ( )
{

  if ( instance_link )
    property_handle.ResetInstanceEventHandler(instance_link);
  
  if ( property_link )
    property_handle.ResetPropertyEventHandler(property_link);
  
  property_handle.UnregisterHandle();

}

/******************************************************************************/
/**
\brief  EventHandler - Konstruktor
        Constructing  an  event  handler  class instance for the property handle
        passed  to the function. The constructor sets the property event handler
        as  well  as  the  instance  event  handler.  The  property  handle  is 
        registered for receiving server events (-> RegisterHandle()).


\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventHandler"

                        EventHandler :: EventHandler (PropertyHandle &prop_hdl )
                     : vcls (),
  property_handle(&property_handle),
  instance_link(NULL),
  property_link(NULL),
  proc_inst_link(NULL),
  proc_prop_link(NULL)
{

  property_handle.CopyHandle(&prop_hdl);
  

  


}

/******************************************************************************/
/**
\brief  InstHandler - Internal Handler implementation


\return cont - Continuation

\param  event_id - Ivend type
\param  objid - Instance or index identity
\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstHandler"

logical EventHandler :: InstHandler (CSA_Events event_id, int32 objid, PropertyHandle &prop_hdl )
{

  return( InstanceEventHandler(event_id,objid) );

}

/******************************************************************************/
/**
\brief  InstProcHandler - Internal process handler implementation


\return cont - Continuation

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstProcHandler"

logical EventHandler :: InstProcHandler (DB_Event intevent )
{

  return( ProcessInstanceHandler(intevent) );

}

/******************************************************************************/
/**
\brief  InstanceEventHandler - Instance event handler
        The  instance event handler has to  be overloaded when specific handling
        for  instance events as updated or deleted  has to be provided. The type
        of  event is passed  via the event_id.  The objid refers to the instance
        identity of the updated instance.
        When  a  notification  handler  is  implemented in the context class, it
        will  be  called  after  calling  the event handler set for the ptoperty
        handle.

\return cont - Continuation

\param  event_id - Ivend type
\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceEventHandler"

logical EventHandler :: InstanceEventHandler (CSA_Events event_id, int32 objid )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ProcessInstanceHandler - Process Instance Event Handler
        The  process event handler  has to be  overloaded when specific handling
        for  process events (as  update or delete  instance) has to be provided.
        The type of event is passed via the intevent parameter. 
        The  function should return true (YES)  to pre-process handlers to abort
        the process.

\return cont - Continuation

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessInstanceHandler"

logical EventHandler :: ProcessInstanceHandler (DB_Event intevent )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ProcessPropertyHandler - Process Property Event Handler
        The  process event handler  has to be  overloaded when specific handling
        for  process events  (as read  or change  selection) has to be provided.
        The type of event is passed via the intevent parameter. 
        The  function should return true (YES)  to pre-process handlers to abort
        the process.

\return cont - Continuation

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessPropertyHandler"

logical EventHandler :: ProcessPropertyHandler (DB_Event intevent )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  PropHandler - Internal Handler implementation


\return cont - Continuation

\param  event_id - Ivend type
\param  objid - Instance or index identity
\param  prop_hdl - Property Handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropHandler"

logical EventHandler :: PropHandler (CSA_Events event_id, int32 objid, PropertyHandle &prop_hdl )
{

  return( PropertyEventHandler(event_id,objid) );

}

/******************************************************************************/
/**
\brief  PropProcHandler - Internal process handler implementation


\return cont - Continuation

\param  intevent - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropProcHandler"

logical EventHandler :: PropProcHandler (DB_Event intevent )
{

  return( ProcessPropertyHandler(intevent) );

}

/******************************************************************************/
/**
\brief  PropertyEventHandler - Property event handler
        The  property event handler has to  be overloaded when specific handling
        for  property  (collection)  events  as  updated  or  deleted  has to be
        provided.  The  type  of  event  is  passed  via the event_id. The objid
        refers to the index identity of the updated collection.
        When  a  notification  handler  is  implemented in the context class, it
        will  be  called  after  calling  the event handler set for the ptoperty
        handle.

\return cont - Continuation

\param  event_id - Ivend type
\param  objid - Instance or index identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PropertyEventHandler"

logical EventHandler :: PropertyEventHandler (CSA_Events event_id, int32 objid )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ~EventHandler - Destructor
        Destructing  the class  will reset  the handler  in the property handle.
        The  property  handle  is  unregistered from receiving server events (->
        UnregisterHandle()).


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EventHandler"

                        EventHandler :: ~EventHandler ( )
{

  property_handle.UnregisterHandle();
    
  if ( instance_link )
  {
    property_handle.ResetInstanceEventHandler(instance_link);  
    delete instance_link;
    instance_link = NULL;
  }
  if ( property_link )
  {
    property_handle.ResetPropertyEventHandler(property_link);
    delete property_link;
    property_link = NULL;
  }
  if ( proc_inst_link )
  {
    property_handle.ResetInstanceProcessHandler(proc_inst_link);  
    delete proc_inst_link;
    proc_inst_link = NULL;
  }
  if ( proc_prop_link )
  {
    property_handle.ResetPropertyProcessHandler(proc_prop_link);  
    delete proc_prop_link;
    proc_prop_link = NULL;
  }


}


