/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    EventLinkList

\brief    


\date     $Date: 2006/07/16 10:59:45,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EventLinkList"

#include  <popa7.h>
#include  <sEventLink.hpp>
#include  <sEventLinkList.hpp>


/******************************************************************************/
/**
\brief  AddEventLink - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEventLink"

void EventLinkList :: AddEventLink (EventLink *event_link )
{

  if ( !Find(event_link) )
    AddTail(event_link);

}

/******************************************************************************/
/**
\brief  EventLinkList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EventLinkList"

     EventLinkList :: EventLinkList ( )
                     : ReferenceObject(NO),
DLL(EventLink)()
{



}

/******************************************************************************/
/**
\brief  RemoveEventLink - 



\param  event_link - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEventLink"

void EventLinkList :: RemoveEventLink (EventLink *event_link )
{

  Remove(event_link);

}

/******************************************************************************/
/**
\brief  ~EventLinkList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EventLinkList"

     EventLinkList :: ~EventLinkList ( )
{



}


