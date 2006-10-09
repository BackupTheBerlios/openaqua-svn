/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHInternalEvent

\brief    


\date     $Date: 2006/03/13 21:35:50,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHInternalEvent"

#include  <pogui7.h>
#include  <sOEHInternalEvent.hpp>


/******************************************************************************/
/**
\brief  GetIntEvent - 


\return int_event -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIntEvent"

int OEHInternalEvent :: GetIntEvent ( )
{
  int                     int_event;
BEGINSEQ
  int_event = gui_event + data_event + db_event;
  if ( int_event <= 100 || int_event >= 400 )        OGUIERR(99)

RECOVER
  int_event = 0;
ENDSEQ
  return(int_event);
}

/******************************************************************************/
/**
\brief  OEHInternalEvent - Constructor


-------------------------------------------------------------------------------
\brief  i0


\param  int_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHInternalEvent"

                        OEHInternalEvent :: OEHInternalEvent (int int_event )
                     :   gui_event(GEV_undefined),
  data_event(DEV_undefined),
  db_event(DBEV_undefined)
{

BEGINSEQ
  if ( int_event <= 100 || int_event >= 400 )        OGUIERR(99)
    
  if ( int_event > 300 )
    gui_event  = (ADK_GUIEVENT)int_event;
  else if ( int_event > 200 )
    db_event   = (ADK_DBEVENT)int_event;
  else  
    data_event = (ADK_DATAEVENT)int_event;


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01


\param  ogui_data_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHInternalEvent"

                        OEHInternalEvent :: OEHInternalEvent (ADK_DATAEVENT ogui_data_event )
                     :   gui_event(GEV_undefined),
  data_event(ogui_data_event),
  db_event(DBEV_undefined)
{



}

/******************************************************************************/
/**
\brief  i02


\param  ogui_db_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHInternalEvent"

                        OEHInternalEvent :: OEHInternalEvent (ADK_DBEVENT ogui_db_event )
                     :   gui_event(GEV_undefined),
  data_event(DEV_undefined),
  db_event(ogui_db_event)
{



}

/******************************************************************************/
/**
\brief  i03


\param  ogui_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHInternalEvent"

                        OEHInternalEvent :: OEHInternalEvent (ADK_GUIEVENT ogui_event )
                     :   gui_event(ogui_event),
  data_event(DEV_undefined),
  db_event(DBEV_undefined)
{



}

/******************************************************************************/
/**
\brief  i04


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHInternalEvent"

                        OEHInternalEvent :: OEHInternalEvent ( )
                     :   gui_event(GEV_undefined),
  data_event(DEV_undefined),
  db_event(DBEV_undefined)
{



}

/******************************************************************************/
/**
\brief  operator== - Compare operator


\return cond -

\param  rOEHInternalEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical OEHInternalEvent :: operator== (OEHInternalEvent &rOEHInternalEvent )
{

  return ( data_event == rOEHInternalEvent.data_event &&
           db_event   == rOEHInternalEvent.db_event   && 
           gui_event  == rOEHInternalEvent.gui_event     );

}


