/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHTimeEvent

\brief    


\date     $Date: 2006/03/13 21:35:52,65 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHTimeEvent"

#include  <pogui7.h>
#include  <sOEHTimeEvent.hpp>


/******************************************************************************/
/**
\brief  GetDefaultAction - 


\return act_names - Action name

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDefaultAction"

char *OEHTimeEvent :: GetDefaultAction ( )
{
  char                   *act_names;

  return(act_names);
}

/******************************************************************************/
/**
\brief  OEHTimeEvent - 


-------------------------------------------------------------------------------
\brief  i0


\param  start_date -
\param  start_time -
\param  dist_date -
\param  dist_time -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHTimeEvent"

                        OEHTimeEvent :: OEHTimeEvent (dbdt start_date, dbtm start_time, int32 dist_date, dbtm dist_time )
                     : date(start_date),
  time(start_time),
  date_distance(dist_date),
  time_distance(dist_time)
{



}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHTimeEvent"

                        OEHTimeEvent :: OEHTimeEvent ( )
                     : date(),
  time(),
  date_distance(),
  time_distance()
{



}

/******************************************************************************/
/**
\brief  operator== - 


\return cond -

\param  rOEHTimeEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical OEHTimeEvent :: operator== (OEHTimeEvent rOEHTimeEvent )
{

  return ( date == rOEHTimeEvent.date                   && 
           time == rOEHTimeEvent.time                   &&
           date_distance == rOEHTimeEvent.date_distance &&
           time_distance == rOEHTimeEvent.time_distance    );
  


}


