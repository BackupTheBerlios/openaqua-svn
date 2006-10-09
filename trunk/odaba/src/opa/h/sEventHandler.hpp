/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/03/12 19:13:20,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EventHandler_HPP
#define   EventHandler_HPP

class     EventHandler;

class     EventLink;
#include  <cDB_Event.h>
#include  <sPropertyHandle.hpp>
#include  <svcls.hpp>
#pragma pack(8)

class  EventHandler :public vcls
{
protected  :         PropertyHandle                               property_handle ATTR_ALIGN(4);                             
protected  :         EventLink                                   *instance_link;                                             
protected  :         EventLink                                   *property_link;                                             
protected  :         EventLink                                   *proc_inst_link;                                            
protected  :         EventLink                                   *proc_prop_link;                                            

public     :
                     PropertyHandle                              &get_property_handle() { return(property_handle); }
                     EventLink                                   *get_proc_inst_link() { return(proc_inst_link); }
                     EventLink                                   *get_proc_prop_link() { return(proc_prop_link); }
public     :                                     void Acitvate ( );
public     :         opa7ImpExp                  void ActivateProcessEventHandler ( );
public     :         opa7ImpExp                  void ActivateServerEventHandler ( );
public     :                                     void Deactivate ( );
public     :         opa7ImpExp                  void DeactivateProcessEventHandler ( );
public     :         opa7ImpExp                  void DeactivateServerEventHandler ( );
public     :         opa7ImpExp                                          EventHandler (PropertyHandle &prop_hdl );
public     :                                     logical InstHandler (CSA_Events event_id, int32 objid, PropertyHandle &prop_hdl );
public     :                                     logical InstProcHandler (DB_Event intevent );
public     : virtual opa7ImpExp                  logical InstanceEventHandler (CSA_Events event_id, int32 objid );
public     : virtual opa7ImpExp                  logical ProcessInstanceHandler (DB_Event intevent );
public     : virtual opa7ImpExp                  logical ProcessPropertyHandler (DB_Event intevent );
public     :                                     logical PropHandler (CSA_Events event_id, int32 objid, PropertyHandle &prop_hdl );
public     :                                     logical PropProcHandler (DB_Event intevent );
public     : virtual opa7ImpExp                  logical PropertyEventHandler (CSA_Events event_id, int32 objid );
public     :         opa7ImpExp                   virtual                       ~EventHandler ( );
};

#pragma pack()
#endif
