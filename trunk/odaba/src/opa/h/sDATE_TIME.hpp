/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DATE_TIME

\brief    


\date     $Date: 2006/03/12 19:12:47,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DATE_TIME_HPP
#define   DATE_TIME_HPP

class     DATE_TIME;

#include  <sDATE_TIME.hpp>
#pragma pack(8)

class  DATE_TIME
{
protected  :         dbdt                                         date;                                                      
protected  :         dbtm                                         time;                                                      

public     :
                     dbdt                                         get_date() { return(date); }
                     dbtm                                         get_time() { return(time); }
public     :                                                             DATE_TIME (dttm &timestamp_ref );
public     :                                                             DATE_TIME (dbdt date_val, dbtm time_val );
public     :                                                             DATE_TIME ( );
public     :                                     logical IsEmpty ( );
public     :                                     void SetCurrent ( );
};

#pragma pack()
#endif
