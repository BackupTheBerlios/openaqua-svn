/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHDataEvent

\brief    


\date     $Date: 2006/03/13 21:34:12,56 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHDataEvent_HPP
#define   OEHDataEvent_HPP

class     OEHDataEvent;

#include  <sOEHDataEvent.hpp>
class  OEHDataEvent
{
protected  :         DB_Event                                     type;                                                      //

public     :
                     DB_Event                                    &get_type() { return(type); }
public     :                                                             OEHDataEvent (DB_Event data_event );
public     :                                                             OEHDataEvent ( );
public     :                                     logical operator== (OEHDataEvent &rOEHDataEvent );
};

#endif
