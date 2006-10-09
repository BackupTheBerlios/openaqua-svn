/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHDataEvent

\brief    


\date     $Date: 2006/03/13 21:35:47,62 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHDataEvent"

#include  <pogui7.h>
#include  <sOEHDataEvent.hpp>


/******************************************************************************/
/**
\brief  OEHDataEvent - 


-------------------------------------------------------------------------------
\brief  i0


\param  data_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHDataEvent"

                        OEHDataEvent :: OEHDataEvent (DB_Event data_event )
                     :   type(data_event)
{



}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHDataEvent"

                        OEHDataEvent :: OEHDataEvent ( )
                     : type(DB_undefined)
{



}

/******************************************************************************/
/**
\brief  operator== - 


\return cond -

\param  rOEHDataEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical OEHDataEvent :: operator== (OEHDataEvent &rOEHDataEvent )
{

  return ( type == rOEHDataEvent.type );

}


