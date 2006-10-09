/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEventHandler

\brief    


\date     $Date: 2006/03/13 21:34:16,39 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEventHandler_HPP
#define   OEventHandler_HPP

class     OEventHandler;

class     ODSItem;
#include  <sEventHandler.hpp>
class  OEventHandler :public EventHandler
{
protected  :         ODSItem                                     *o;                                                         //

public     :
public     :                                     logical InstanceEventHandler (CSA_Events csa_event_id, int32 objid );
public     :                                                             OEventHandler (ODSItem *pODSItem );
public     :                                     logical PropertyEventHandler (CSA_Events csa_event_id, int32 objid );
};

#endif
