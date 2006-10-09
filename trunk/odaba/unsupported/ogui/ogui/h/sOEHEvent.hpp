/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OEHEvent

\brief    Event Definition


\date     $Date: 2006/05/04 10:54:50,15 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHEvent_HPP
#define   OEHEvent_HPP

class     OEHEvent;

#include  <cOEH_Type.h>
#include  <sOEHDataEvent.hpp>
#include  <sOEHEvent.hpp>
#include  <sOEHInternalEvent.hpp>
#include  <sOEHKeyEvent.hpp>
#include  <sOEHMouseEvent.hpp>
#include  <sOEHShortcut.hpp>
#include  <sOEHTimeEvent.hpp>
class  OEHEvent
{
protected  :         OEH_Type                                     type;                                                      
protected  :         OEHShortcut                                  shortcut;                                                  
protected  :         OEHKeyEvent                                  key;                                                       
protected  :         OEHMouseEvent                                mouse;                                                     
protected  :         OEHTimeEvent                                 time;                                                      
protected  :         OEHInternalEvent                             system;                                                    
protected  :         OEHDataEvent                                 data;                                                      
protected  :         int32                                        id;                                                        

public     :
                     OEH_Type                                    &get_type() { return(type); }
                     OEHShortcut                                 &get_shortcut() { return(shortcut); }
                     OEHKeyEvent                                 &get_key() { return(key); }
                     OEHMouseEvent                               &get_mouse() { return(mouse); }
                     OEHTimeEvent                                &get_time() { return(time); }
                     OEHDataEvent                                &get_data() { return(data); }
                     int32                                        get_id() { return(id); }
public     :                                        logical IsSystemType ( );
public     :                  OGUIImpExp                 OEHEvent (OEHKeyEvent key_event );
public     :                  OGUIImpExp                 OEHEvent (OEHMouseEvent mouse_event );
public     :                  OGUIImpExp                 OEHEvent (OEHInternalEvent system_event, int32 lID_w=0 );
public     :                  OGUIImpExp                 OEHEvent (DB_Event data_event );
public     :                  OGUIImpExp                 OEHEvent (OEHTimeEvent time_event );
public     :                  OGUIImpExp                 OEHEvent (OEHShortcut short_cut );
public     :                  OGUIImpExp                 OEHEvent (int int_event );
public     :                  OGUIImpExp                 OEHEvent ( );
public     :                                        logical operator== (OEHEvent &rOEHEvent );
};

#endif
