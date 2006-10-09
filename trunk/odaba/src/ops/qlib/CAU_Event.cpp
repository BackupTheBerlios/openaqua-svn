/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_Event

\brief    Event
          An  event  is  defined  through  the  state  transition of one or more
          object  instances.  The  event  defines potential state transitions by
          means  of pre  and post  condition, i.e.  pre- and post-states. Events
          can  be defined on the  structure or property level  as well as on the
          extent level.
          An  event is fired when the instance state before modification returns
          a  true  pre-condition  and  when  the state of the instance after the
          modification  returns a true  post-condition. Pre- and post-conditions
          can  be defined as functions, expressions or any other type of action.
          When  not  defining  pre-  and  post condition any modification on the
          instance is considered as event. 
          Special  events are  system events  that are  signaled by the database
          system  and usually indicate a change in  the process or life state of
          the  instance,  which  cannot  be  expressed  in  terms  of  pre-  and
          post-conditions. 
          Event  definitions  are  stored  globally  with  a unique name that is
          constructed  from the structure name, the  extent or property name and
          the  event name. This  allows referring to  an event from a far linked
          instance or registering instances for event observation. 
          When  an event is fired it can  be handled by an event handler defined
          in  the  causality  rule,  which  is  a  function, expression or other
          action again.

\date     $Date: 2006/03/13 21:30:17,84 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CAU_Event"

#include  <pops7.h>
#include  <sCAU_Event.hpp>



