/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OEHEvent

\brief    Event Definition


\date     $Date: 2006/05/04 10:54:53,07 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHEvent"

#include  <pogui7.h>
#include  <sOEHEvent.hpp>


/******************************************************************************/
/**
\brief  IsSystemType

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSystemType"

logical OEHEvent :: IsSystemType ( )
{

  return ( this && type == ET_System ? YES : NO );

}

/******************************************************************************/
/**
\brief  OEHEvent - 


-------------------------------------------------------------------------------
\brief  i0


\param  key_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent (OEHKeyEvent key_event )
                     :   type(ET_Key),
  shortcut(),
  key(key_event),
  mouse(),
  time(),
  system(),
  data(),
  id(0)
{
}

/******************************************************************************/
/**
\brief  i01


\param  mouse_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent (OEHMouseEvent mouse_event )
                     :   type(ET_Mouse),
  shortcut(),
  key(),
  mouse(mouse_event),
  time(),
  system(),
  data(),
  id(0)
{
}

/******************************************************************************/
/**
\brief  i02


\param  system_event
\param  lID_w
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent (OEHInternalEvent system_event, int32 lID_w )
                     :   type(ET_System),
  shortcut(),
  key(),
  mouse(),
  time(),
  system(system_event),
  data(),
  id(lID_w)
{
}

/******************************************************************************/
/**
\brief  i03


\param  data_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent (DB_Event data_event )
                     :   type(ET_Data),
  shortcut(),
  key(),
  mouse(),
  time(),
  system(),
  data(data_event),
  id(0)
{
}

/******************************************************************************/
/**
\brief  i04


\param  time_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent (OEHTimeEvent time_event )
                     :   type(ET_Time),
  shortcut(),
  key(),
  mouse(),
  time(time_event),
  system(),
  data(),
  id(0)
{
}

/******************************************************************************/
/**
\brief  i05


\param  short_cut
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent (OEHShortcut short_cut )
                     :   type(ET_Shortcut),
  shortcut(short_cut),
  key(),
  mouse(),
  time(),
  system(),
  data(),
  id(0)
{
}

/******************************************************************************/
/**
\brief  i06


\param  int_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent (int int_event )
                     :   type(ET_System),
  shortcut(),
  key(),
  mouse(),
  time(),
  system(int_event),
  data(),
  id(0)
{
}

/******************************************************************************/
/**
\brief  i07


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHEvent"

     OEHEvent :: OEHEvent ( )
                     :   type(ET_none),
  key(),
  mouse(),
  time(),
  system(),
  data(),
  id(0)
{
}

/******************************************************************************/
/**
\brief  operator==

\return cond

\param  rOEHEvent - Event reference
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical OEHEvent :: operator== (OEHEvent &rOEHEvent )
{
  logical                 cond = YES;
BEGINSEQ
  if ( type != rOEHEvent.type )                      ERROR
  
  switch ( type )
  {
    case ET_System   : cond = (system == rOEHEvent.system && id == rOEHEvent.id);
                       break;
    case ET_Data     : cond = (data == rOEHEvent.data);
                       break;
    case ET_Shortcut : cond = (shortcut == rOEHEvent.shortcut);
                       break;
    case ET_Key      : cond = (key == rOEHEvent.key);
                       break;
    case ET_Mouse    : cond = (mouse == rOEHEvent.mouse);
                       break;
    case ET_Time     : cond = (time == rOEHEvent.time);
                       break;
    case ET_none     :
    default          : ;
  }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}


