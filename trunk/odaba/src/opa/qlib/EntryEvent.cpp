/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EntryEvent

\brief    


\date     $Date: 2006/03/12 19:17:31,42 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EntryEvent"

#include  <popa7.h>
#include  <sEntryEvent.hpp>


/******************************************************************************/
/**
\brief  Copy


\param  entry_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

void EntryEvent :: Copy (EntryEvent &entry_event )
{

  event       = entry_event.event;
  sid         = entry_event.sid;
  is_instance = entry_event.is_instance;

}

/******************************************************************************/
/**
\brief  EntryEvent - 



\param  entnr -
\param  event_id - Ivend type
\param  sid -
\param  is_inst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryEvent"

                        EntryEvent :: EntryEvent (EB_Number entnr, CSA_Events event_id, int16 sid, logical is_inst )
                     : ebsnum(entnr),
  event(event_id),
  sid(sid),
  is_instance(is_inst)
{



}

/******************************************************************************/
/**
\brief  set_event


\param  event_id - Ivend type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_event"

void EntryEvent :: set_event (CSA_Events event_id )
{

  event = event_id;

}


