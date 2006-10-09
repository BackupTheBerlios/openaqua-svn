/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    dttm

\brief    


\date     $Date: 2006/06/12 12:49:03,60 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dttm_HPP
#define   dttm_HPP

class     dttm;
#include "csosdll.h"

#include  <sdbdt.hpp>
#include  <sdbtm.hpp>
#include  <sdttm.hpp>
#pragma pack(4)

class  dttm
{
protected  :         dbdt                                         date;                                                      // 
protected  :         dbtm                                         time;                                                      // 

public     :
                     dbdt                                        &get_date() { return(date); }
                     dbtm                                        &get_time() { return(time); }
public     :                  SOSImpExp             dttm &Clear ( );
public     :                  SOSImpExp             void FromPIF (logical convert );
public     :                                        dbtm FromString ( );
public     :                                        logical FromUnix (int64 unixtimestamp );
public     :                  SOSImpExp             dbdt &GetDate ( );
public     :                  SOSImpExp             dbtm &GetTime ( );
public     :                  SOSImpExp             logical IsEmpty ( );
public     :                  SOSImpExp             dttm &Normalize ( );
public     :                  SOSImpExp             dttm &SetCurDate ( );
public     :                  SOSImpExp             dttm &SetCurTime ( );
public     :                  SOSImpExp             dttm &SetCurrent ( );
public     :                  SOSImpExp             dttm &SetDate (dbdt dbdate );
public     :                  SOSImpExp             dttm &SetTime (dbtm dbtime );
public     :                  SOSImpExp             void ToPIF (logical convert );
public     :                                        int64 ToUnix ( );
public     :                  SOSImpExp                  dttm ( );
public     :                  SOSImpExp                  dttm (dbdt dbdate, dbtm dbtime );
public     :                  SOSImpExp             logical operator!= (dttm dbdatetime );
public     :                  SOSImpExp             dttm operator+ (uint32 duration );
public     :                  SOSImpExp             dttm &operator+= (uint32 duration );
public     :                  SOSImpExp             uint32 operator- (dttm dbdatetime );
public     :                  SOSImpExp             dttm &operator-= (uint32 duration );
public     :                  SOSImpExp             logical operator< (dttm dbdatetime );
public     :                  SOSImpExp             logical operator<= (dttm dbdatetime );
public     :                  SOSImpExp             dttm operator= (dttm dbdatetime );
public     :                  SOSImpExp             logical operator== (dttm dbdatetime );
public     :                  SOSImpExp             logical operator> (dttm dbdatetime );
public     :                  SOSImpExp             logical operator>= (dttm dbdatetime );
public     :                  SOSImpExp                  ~dttm ( );
};

#pragma pack()
#endif
