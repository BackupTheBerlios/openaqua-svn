/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OEventAction_intern



\date     $Date: 2006/04/27 14:29:28,56 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEventAction_intern_HPP
#define   OEventAction_intern_HPP

class     OEventAction_intern;

class     OEventActionControl;
class     PropertyHandle;
#include  <cActionBubbleType.h>
#include  <cMOUSKEY.h>
#include  <sOCAU_Action.hpp>
#include  <sOElementStyle.hpp>
#include  <sOStyleElement.hpp>
class  OEventAction_intern :public OElementStyle
{
protected  :         OCAU_Action                                  default_action;                                            
protected  :         ActionBubbleType                             bubble_type;                                               
protected  :         char                                        *bubble_path;                                               
protected  :         int32                                        system_event_id;                                           
protected  :         int8                                         mouse_clicks;                                              
protected  :         logical                                      mouse_alt;                                                 
protected  :         logical                                      mouse_shift;                                               
protected  :         logical                                      mouse_ctrl;                                                
protected  :         MOUSKEY                                      mouse_button;                                              
protected  :         char                                        *key_string;                                                
protected  :         dbdt                                         start_date;                                                
protected  :         dbtm                                         start_time;                                                
protected  :         dbtm                                         time_cyclus;                                               
protected  :         int8                                         day_cyclus;                                                
protected  :         OEventActionControl                         *action_control;                                            

public     :
                     OCAU_Action                                 &get_default_action() { return(default_action); }
                     ActionBubbleType                             get_bubble_type() { return(bubble_type); }
                     char                                        *get_bubble_path() { return(bubble_path); }
                     int32                                        get_system_event_id() { return(system_event_id); }
                     int8                                         get_mouse_clicks() { return(mouse_clicks); }
                     logical                                      get_mouse_alt() { return(mouse_alt); }
                     logical                                      get_mouse_shift() { return(mouse_shift); }
                     logical                                      get_mouse_ctrl() { return(mouse_ctrl); }
                     MOUSKEY                                      get_mouse_button() { return(mouse_button); }
                     char                                        *get_key_string() { return(key_string); }
                     dbdt                                         get_start_date() { return(start_date); }
                     dbtm                                         get_start_time() { return(start_time); }
                     dbtm                                         get_time_cyclus() { return(time_cyclus); }
                     int8                                         get_day_cyclus() { return(day_cyclus); }
                     OEventActionControl                         *get_action_control() { return(action_control); }
public     :                                        char *ActionID ( );
public     :                                        char *ActionItemID ( );
public     : virtual                                void *CastPointer (char *typenames );
public     :                                             OEventAction_intern ( );
public     :                                             OEventAction_intern (OElementStyle bcOElementStyle, OCAU_Action default_action, ActionBubbleType bubble_type, char *bubble_path, int32 system_event_id, int8 mouse_clicks, logical mouse_alt, logical mouse_shift, logical mouse_ctrl, MOUSKEY mouse_button, char *key_string, dbdt start_date, dbtm start_time, dbtm time_cyclus, int8 day_cyclus, OEventActionControl *action_control );
public     :                                        logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void SetContextMenuProperty ( );
public     : virtual                                     ~OEventAction_intern ( );
};

#endif
