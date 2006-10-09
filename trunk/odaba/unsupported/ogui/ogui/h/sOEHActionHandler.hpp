/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OEHActionHandler

\brief    Base Class for Action Handler


\date     $Date: 2006/05/03 13:03:29,67 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHActionHandler_HPP
#define   OEHActionHandler_HPP

class     OEHActionHandler;

class     ODataWidget;
#include  <cADK_DATAEVENT.h>
#include  <cADK_DBEVENT.h>
#include  <cADK_GUIEVENT.h>
#include  <sDKey.hpp>
class  OEHActionHandler :public vcls
{
protected  :         logical                                      gui_call;                                                  

public     :
                     logical                                      get_gui_call() { return(gui_call); }
public     : virtual          OGUIImpExp            int8 ExecuteAction (char *act_names );
public     :                                        int8 ExecuteActionCall (char *act_names );
public     : virtual          OGUIImpExp            int32 ExecuteDBEventAction (ADK_DBEVENT ogui_db_event );
public     : virtual          OGUIImpExp            int32 ExecuteDataEventAction (ADK_DATAEVENT ogui_data_event );
public     : virtual          OGUIImpExp            int32 ExecuteGUIEventAction (ADK_GUIEVENT ogui_event );
public     :                  OGUIImpExp            logical IsGUICall ( );
public     :                  OGUIImpExp                 OEHActionHandler ( );
public     : virtual          OGUIImpExp            int8 ProcessKeyEvent (DKey &dkey );
};

#endif
