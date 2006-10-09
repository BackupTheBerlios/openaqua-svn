/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    dbdt

\brief    


\date     $Date: 2006/07/21 12:34:59,26 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dbdt_HPP
#define   dbdt_HPP

class     dbdt;
#include "csosdll.h"

#include  <sdbdt.hpp>
#pragma pack(4)

class  dbdt
{
protected  :         int32                                        dbdtdate;                                                  // 

public     :
public     :                  SOSImpExp             void FromPIF (logical convert );
public     :                  SOSImpExp             dbdt FromString (char *string, uint16 size, int32 date_format );
public     :                                        logical FromUnix (int64 unixtimestamp );
public     :                  SOSImpExp             uint16 GetDay ( );
public     :                  SOSImpExp             void GetDayMonthYear (uint16 *day_ptr, uint16 *month_ptr, uint16 *year_ptr );
public     :                  SOSImpExp             uint16 GetDecade ( );
public     :                  SOSImpExp             int32 GetLongInt ( );
public     :                  SOSImpExp             uint16 GetMonth ( );
public     :                  SOSImpExp             uint16 GetWeekDay ( );
public     :                  SOSImpExp             uint16 GetYear ( );
public     :                  SOSImpExp             logical IsEmpty ( );
public     :                  SOSImpExp             dbdt &MinusMonth (uint16 month_count );
public     :                  SOSImpExp             dbdt &MinusYear (uint16 year_count );
public     :                  SOSImpExp             dbdt &PlusMonth (uint16 month_count );
public     :                  SOSImpExp             dbdt &PlusYear (uint16 year_count );
public     :                  SOSImpExp             dbdt &SetDate ( );
public     :                  SOSImpExp             void ToPIF (logical convert );
public     :                  SOSImpExp             char *ToString (char *string, uint16 size, int32 date_format );
public     :                                        int64 ToUnix ( );
public     :                  SOSImpExp                  dbdt (int32 datval=0 );
public     :                  SOSImpExp                  dbdt (uint16 day, uint16 month, uint16 year );
protected  :                                        void dbdtlgt (uint16 *day_ptr, uint16 *month_ptr, uint16 *year_ptr );
protected  :                                        int32 dbdtlst (uint16 day, uint16 month, uint16 year );
public     :                  SOSImpExp             logical operator!= (dbdt dbdate );
public     :                  SOSImpExp             dbdt operator+ (int32 days );
public     :                  SOSImpExp             dbdt operator+= (int32 days );
public     :                  SOSImpExp             dbdt operator- (int32 days );
public     :                  SOSImpExp             dbdt operator-= (int32 days );
public     :                  SOSImpExp             logical operator< (dbdt dbdate );
public     :                  SOSImpExp             logical operator<= (dbdt dbdate );
public     :                  SOSImpExp             dbdt operator= (int32 days );
public     :                  SOSImpExp             dbdt operator= (char *string );
public     :                  SOSImpExp             logical operator== (dbdt dbdate );
public     :                  SOSImpExp             logical operator> (dbdt dbdate );
public     :                  SOSImpExp             logical operator>= (dbdt dbdate );
};

#pragma pack()
#endif
