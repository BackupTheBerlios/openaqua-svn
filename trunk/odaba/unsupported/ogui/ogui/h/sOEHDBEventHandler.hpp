/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHDBEventHandler

\brief    


\date     $Date: 2006/03/13 21:34:12,34 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHDBEventHandler_HPP
#define   OEHDBEventHandler_HPP

class     OEHDBEventHandler;

class     ODSItem;
#include  <sEventHandler.hpp>
class  OEHDBEventHandler :public EventHandler
{
protected  :         ODSItem                                     *ods_item;                                                  //
protected  :         logical                                      is_busy;                                                   //

public     :
                     ODSItem                                     *get_ods_item() { return(ods_item); }
                     logical                                      get_is_busy() { return(is_busy); }
public     :                                     void ActivateEventHandler ( );
public     :                                     void ActivateEvents ( );
public     :                                     void DeactivateEventHandler ( );
public     :                                     void DeactivateEvents ( );
public     :                                     logical InstanceEventHandler (CSA_Events csa_event, int32 objid );
public     :                                                             OEHDBEventHandler (ODSItem *odsitem );
public     :                                     logical ProcessInstanceHandler (DB_Event db_event );
public     :                                     logical ProcessPropertyHandler (DB_Event db_event );
public     :                                     logical PropertyEventHandler (CSA_Events csa_event, int32 objid );
public     :                                                             ~OEHDBEventHandler ( );
};

#endif
