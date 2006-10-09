/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    DMouse

\brief    Mouse Event
          This  class  stores  the  state  of  the  Mouse at the time of a Mouse
          Event.

          All  functions are related  to the members  of this class, they do NOT
          modify the state or behavior of the real mouse or keyboard.

\date     $Date: 2006/04/28 17:04:45,34 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DMouse"

#include  <pogui7.h>
#include  <sDMouse.hpp>


/******************************************************************************/
/**
\brief  Button - button caused the event
        Returns  a  DMouseButtons  Object  with  only the Mouse Button set which
        caused the Event.
        It is possible that NO Mouse Button is set (ex. Move Event).

\return dmbutton - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Button"

DMouseButtons DMouse :: Button ( )
{

  return(button);
}

/******************************************************************************/
/**
\brief  DMouse - 


\return term - 
-------------------------------------------------------------------------------
\brief  i00


\param  rcDMouseButtonsButton
\param  rcDMouseButtonsStateBefore
\param  rcDMouseButtonsStateAfter
\param  rcDPointPos
\param  rcDPointGlobalPos
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DMouse"

     DMouse :: DMouse (const DMouseButtons &rcDMouseButtonsButton, const DMouseButtons &rcDMouseButtonsStateBefore, const DMouseButtons &rcDMouseButtonsStateAfter, const DPoint &rcDPointPos, const DPoint &rcDPointGlobalPos )
                     : button(rcDMouseButtonsButton),
  state_before(rcDMouseButtonsStateBefore),
  state_after(rcDMouseButtonsStateAfter),
  global_pos(rcDPointGlobalPos),
  pos(rcDPointPos)
{


}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DMouse"

     DMouse :: DMouse ( )
                     : button(),
  state_before(),
  state_after(),
  global_pos(),
  pos()
{
}

/******************************************************************************/
/**
\brief  GlobalPos - global position
        Returns the Global Position of the Mouse Pointer.

\return dpoint - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GlobalPos"

DPoint DMouse :: GlobalPos ( )
{

  return(global_pos);
}

/******************************************************************************/
/**
\brief  Pos - position (relative to parent)
        Returns  the Position of the Mouse Pointer relative to the Parent of the
        Event Reciever.

\return dpoint - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pos"

DPoint DMouse :: Pos ( )
{

  return(pos);
}

/******************************************************************************/
/**
\brief  StateAfter - state after event
        Returns  a  DMouseButtons  Object  which  represents  the  state  of the
        Modifier Keys and Mouse Buttons  immediately after the Event.

\return dmbutton - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StateAfter"

DMouseButtons DMouse :: StateAfter ( )
{

  return(state_after);
}

/******************************************************************************/
/**
\brief  StateBefore - state before event
        Returns  a  DMouseButtons  Object  which  represents  the  state  of the
        Modifier Keys and Mouse Buttons  immediately before the Event.

\return dmbutton - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StateBefore"

DMouseButtons DMouse :: StateBefore ( )
{

  return(state_before);
}


