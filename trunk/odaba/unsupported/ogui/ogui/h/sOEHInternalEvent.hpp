/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHInternalEvent

\brief    


\date     $Date: 2006/03/13 21:34:14,95 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHInternalEvent_HPP
#define   OEHInternalEvent_HPP

class     OEHInternalEvent;

#include  <cADK_DATAEVENT.h>
#include  <cADK_DBEVENT.h>
#include  <cADK_GUIEVENT.h>
#include  <sOEHInternalEvent.hpp>
class  OEHInternalEvent
{
protected  :         ADK_GUIEVENT                                 gui_event;                                                 //
protected  :         ADK_DATAEVENT                                data_event;                                                //
protected  :         ADK_DBEVENT                                  db_event;                                                  //

public     :
                     ADK_GUIEVENT                                 get_gui_event() { return(gui_event); }
                     ADK_DATAEVENT                                get_data_event() { return(data_event); }
                     ADK_DBEVENT                                  get_db_event() { return(db_event); }
public     :                                     int GetIntEvent ( );
public     :         OGUI7ImpExp                                         OEHInternalEvent (int int_event );
public     :         OGUI7ImpExp                                         OEHInternalEvent (ADK_DATAEVENT ogui_data_event );
public     :         OGUI7ImpExp                                         OEHInternalEvent (ADK_DBEVENT ogui_db_event );
public     :         OGUI7ImpExp                                         OEHInternalEvent (ADK_GUIEVENT ogui_event );
public     :         OGUI7ImpExp                                         OEHInternalEvent ( );
public     :                                     logical operator== (OEHInternalEvent &rOEHInternalEvent );
};

#endif
