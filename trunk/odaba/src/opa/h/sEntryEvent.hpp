/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EntryEvent

\brief    


\date     $Date: 2006/03/12 19:13:20,03 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EntryEvent_HPP
#define   EntryEvent_HPP

class     EntryEvent;

#include  <sEB_Number.hpp>
class  EntryEvent
{
public     :         EB_Number                                    ebsnum;                                                    //
protected  :         CSA_Events                                   event;                                                     
protected  :         int16                                        sid;                                                       
protected  :         logical                                      is_instance;                                               

public     :
                     CSA_Events                                  &get_event() { return(event); }
                     int16                                        get_sid() { return(sid); }
                     logical                                      get_is_instance() { return(is_instance); }
public     :                                     void Copy (EntryEvent &entry_event );
public     :                                                             EntryEvent (EB_Number entnr, CSA_Events event_id, int16 sid, logical is_inst );
public     :                                     void set_event (CSA_Events event_id );
};

#endif
