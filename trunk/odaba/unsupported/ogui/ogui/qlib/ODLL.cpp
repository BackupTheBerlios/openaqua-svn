/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODLL

\brief    Double linked list
          This  class supports a sort of fast double linked list. Entries in the
          list  are directly linked, which  requires a member dllLink (ODLLItem)
          in  the  linked  entry.  The  linked  entry  must  not be derived from
          ODLLItem. 
          es and outer widgets for certain controls.
          Complex  controls  are  collecting  the  events  from  all  associated
          controls  and sending  the events  to the parent. Subordinated complex
          controls  as labes do not handle  events explicitly but sending events
          to  the  parent,  the  control  owning the label. You may set an event
          handler  for the control,  which receives all  events collected by the
          control (see OEH).

\date     $Date: 2006/03/13 21:35:20,64 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODLL"

#include  <pogui7.h>
#include  <sODLLItem.hpp>
#include  <sODLLIterator.hpp>
#include  <sODLL.hpp>



