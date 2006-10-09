/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    EventLinkList

\brief    


\date     $Date: 2006/07/16 10:59:44,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EventLinkList_HPP
#define   EventLinkList_HPP

class     EventLinkList;

#ifndef   DLL_EventLink_HPP
#define   DLL_EventLink_HPP
#include  <sEventLink.hpp>
#include  <sDLL.h>
#endif
class     EventLink;
#include  <sReferenceObject.hpp>
class  EventLinkList :public ReferenceObject,
public DLL(EventLink)
{

public     :
public     :                                        void AddEventLink (EventLink *event_link );
public     :                                             EventLinkList ( );
public     :                                        void RemoveEventLink (EventLink *event_link );
public     :                                             ~EventLinkList ( );
};

#endif
