/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHTimeEvent

\brief    


\date     $Date: 2006/03/13 21:34:16,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHTimeEvent_HPP
#define   OEHTimeEvent_HPP

class     OEHTimeEvent;

#include  <sOEHTimeEvent.hpp>
class  OEHTimeEvent
{
protected  :         dbdt                                         date;                                                      //
protected  :         dbtm                                         time;                                                      //
protected  :         int8                                         date_distance;                                             //
protected  :         dbtm                                         time_distance;                                             //

public     :
                     dbdt                                         get_date() { return(date); }
                     dbtm                                         get_time() { return(time); }
                     int8                                         get_date_distance() { return(date_distance); }
                     dbtm                                         get_time_distance() { return(time_distance); }
public     :                                     char *GetDefaultAction ( );
public     :         OGUI7ImpExp                                         OEHTimeEvent (dbdt start_date, dbtm start_time, int32 dist_date, dbtm dist_time );
public     :         OGUI7ImpExp                                         OEHTimeEvent ( );
public     :                                     logical operator== (OEHTimeEvent rOEHTimeEvent );
};

#endif
