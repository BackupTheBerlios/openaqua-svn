/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    dbtm

\brief    


\date     $Date: 2006/06/12 12:45:25,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dbtm_HPP
#define   dbtm_HPP

class     dbtm;
#include "csosdll.h"

#include  <sdbtm.hpp>
#pragma pack(4)

class  dbtm
{
protected  :         int32                                        dbtmtime;                                                  // 

public     :
public     :                  SOSImpExp             void Clear ( );
public     :                  SOSImpExp             void FromPIF (logical convert );
public     :                  SOSImpExp             dbtm FromString (char *string, uint16 size, int32 time_format );
public     :                                        logical FromUnix (int64 unixtimestamp );
public     :                  SOSImpExp             int16 GetHSecond ( );
public     :                  SOSImpExp             int16 GetHour ( );
public     :                  SOSImpExp             void GetHourMinSec (uint16 *hours_ptr, uint16 *minutes_ptr, uint16 *seconds_ptr, uint16 *hseconds_ptr );
public     :                  SOSImpExp             int32 GetLongInt ( );
public     :                  SOSImpExp             int16 GetMinute ( );
public     :                  SOSImpExp             int16 GetSecond ( );
public     :                  SOSImpExp             int32 GetTime ( );
public     :                  SOSImpExp             logical IsEmpty ( );
public     :                  SOSImpExp             dbtm &SetTime ( );
public     :                  SOSImpExp             void ToPIF (logical convert );
public     :                  SOSImpExp             char *ToString (char *string, uint16 size, int32 time_format );
public     :                                        int64 ToUnix ( );
public     :                  SOSImpExp                  dbtm (int32 timval=AUTO );
public     :                  SOSImpExp                  dbtm (uint16 hours, uint16 minutes, uint16 seconds=UNDEF, uint16 hseconds=UNDF );
public     :                  SOSImpExp             logical operator!= (dbtm dbtime );
public     :                  SOSImpExp             dbtm operator+ (int32 hsec );
public     :                  SOSImpExp             dbtm operator+ (dbtm dbtime );
public     :                  SOSImpExp             dbtm operator+= (int32 hsec );
public     :                  SOSImpExp             dbtm operator+= (dbtm dbtime );
public     :                  SOSImpExp             dbtm operator- (int32 hsec );
public     :                  SOSImpExp             dbtm operator- (dbtm dbtime );
public     :                  SOSImpExp             dbtm operator-= (int32 hsec );
public     :                  SOSImpExp             dbtm operator-= (dbtm dbtime );
public     :                  SOSImpExp             logical operator< (dbtm dbtime );
public     :                  SOSImpExp             logical operator<= (dbtm dbtime );
public     :                  SOSImpExp             dbtm operator= (int32 hsec );
public     :                  SOSImpExp             logical operator== (dbtm dbtime );
public     :                  SOSImpExp             logical operator> (dbtm dbtime );
public     :                  SOSImpExp             logical operator>= (dbtm dbtime );
};

#pragma pack()
#endif
