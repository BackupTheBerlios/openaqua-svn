/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DATE_TIME

\brief    


\date     $Date: 2006/03/12 19:16:52,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DATE_TIME"

#include  <popa7.h>
#include  <sDATE_TIME.hpp>


/******************************************************************************/
/**
\brief  DATE_TIME - 


-------------------------------------------------------------------------------
\brief i0


\param  timestamp_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DATE_TIME"

                        DATE_TIME :: DATE_TIME (dttm &timestamp_ref )
                     : date(timestamp_ref.get_date()),
  time(timestamp_ref.get_time())
{



}

/******************************************************************************/
/**
\brief i1


\param  date_val -
\param  time_val -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DATE_TIME"

                        DATE_TIME :: DATE_TIME (dbdt date_val, dbtm time_val )
                     : date(date_val),
  time(time_val)
{



}

/******************************************************************************/
/**
\brief i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DATE_TIME"

                        DATE_TIME :: DATE_TIME ( )
                     : date(0),
  time(0)
{



}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical DATE_TIME :: IsEmpty ( )
{

  return ( date.IsEmpty() );

}

/******************************************************************************/
/**
\brief  SetCurrent - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrent"

void DATE_TIME :: SetCurrent ( )
{

  date = dbdt().SetDate();
  time = dbtm().SetTime();


}


