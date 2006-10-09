/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DMouseButtons

\brief    Mouse Button
          This  class stores any  combination of the  three Mouse Buttons (Left,
          Right, Middle) and the three Modifier Keys (Control, Alt, Shift).

          All  functions are related  to the members  of this class, they do NOT
          modify the state or behavior of the real mouse or keyboard.

\date     $Date: 2006/03/13 21:35:01,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DMouseButtons"

#include  <pogui7.h>
#include  <sDMouseButtons.hpp>


/******************************************************************************/
/**
\brief  Alt - alt key
        Returns the value of the Alt Modifier Key.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Alt"

logical DMouseButtons :: Alt ( )
{


  return(modifier_alt);
}

/******************************************************************************/
/**
\brief  Any - any mouse button
        Returns YES if any Mouse Button is set.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Any"

logical DMouseButtons :: Any ( )
{


  return( button_left || button_right || button_middle );
}

/******************************************************************************/
/**
\brief  AnyModifier - any modifier key
        Returns YES if any Modifier Key is set.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AnyModifier"

logical DMouseButtons :: AnyModifier ( )
{


  return( modifier_control || modifier_alt || modifier_shift );
}

/******************************************************************************/
/**
\brief  Buttons - mouse buttons
        Returns a DMouseButton Object with only Mouse Buttons set.

\return buttons -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Buttons"

DMouseButtons DMouseButtons :: Buttons ( )
{


  return DMouseButtons(button_left, button_right, button_middle, NO, NO, NO);
}

/******************************************************************************/
/**
\brief  Control - control key
        Returns the value of the Control Modifier Key.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Control"

logical DMouseButtons :: Control ( )
{


  return(modifier_control);
}

/******************************************************************************/
/**
\brief  DMouseButtons - 


\return term -
-------------------------------------------------------------------------------
\brief  i00


\param  fLeft -
\param  fRight -
\param  fMiddle -
\param  fShift -
\param  fControl -
\param  fAlt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DMouseButtons"

                        DMouseButtons :: DMouseButtons (logical fLeft, logical fRight, logical fMiddle, logical fShift, logical fControl, logical fAlt )
                     : button_left(fLeft),
  button_right(fRight),
  button_middle(fMiddle),
  modifier_shift(fShift),
  modifier_control(fControl),
  modifier_alt(fAlt)
{



}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DMouseButtons"

                        DMouseButtons :: DMouseButtons ( )
                     : button_left(NO),
  button_right(NO),
  button_middle(NO),
  modifier_shift(NO),
  modifier_control(NO),
  modifier_alt(NO)
{



}

/******************************************************************************/
/**
\brief  Left - left mouse button
        Returns the value of the Left Mouse Button.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Left"

logical DMouseButtons :: Left ( )
{


  return(button_left);
}

/******************************************************************************/
/**
\brief  Middle - middle mouse button
        Returns the value of the Middle Mouse Button.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Middle"

logical DMouseButtons :: Middle ( )
{


  return(button_middle);
}

/******************************************************************************/
/**
\brief  Modifiers - modifier keys
        Returns a DMouseButton Object with only Modifier Keys set.

\return buttons -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modifiers"

DMouseButtons DMouseButtons :: Modifiers ( )
{


  return DMouseButtons(NO, NO, NO, modifier_shift, modifier_control, modifier_alt);
}

/******************************************************************************/
/**
\brief  Reset - reset ;)
        Resets all Mouse Buttons and Modifier Keys.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void DMouseButtons :: Reset ( )
{

button_left   = NO;
button_right  = NO;
button_middle = NO;

modifier_shift   = NO;
modifier_control = NO;
modifier_alt     = NO;

}

/******************************************************************************/
/**
\brief  Right - right mouse button
        Returns the value of the Right Mouse Button.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Right"

logical DMouseButtons :: Right ( )
{


  return(button_right);
}

/******************************************************************************/
/**
\brief  SetAlt - set alt key
        Sets the Alt Modifier Key to the value in 'pressed'.


\param  pressed -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAlt"

void DMouseButtons :: SetAlt (logical pressed )
{

  modifier_alt = pressed;

}

/******************************************************************************/
/**
\brief  SetControl - set control key
        Sets the Control Modifier Key to the value in 'pressed'.


\param  pressed -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetControl"

void DMouseButtons :: SetControl (logical pressed )
{

  modifier_control = pressed;

}

/******************************************************************************/
/**
\brief  SetLeft - set left button
        Sets the Left Mouse Button to the value in 'pressed'.


\param  pressed -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLeft"

void DMouseButtons :: SetLeft (logical pressed )
{

  button_left = pressed;

}

/******************************************************************************/
/**
\brief  SetMiddle - set middle button
        Sets the Middle Mouse Button to the value in 'pressed'.


\param  pressed -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMiddle"

void DMouseButtons :: SetMiddle (logical pressed )
{

  button_middle = pressed;

}

/******************************************************************************/
/**
\brief  SetRight - set right button
        Sets the Right Mouse Button to the value in 'pressed'.


\param  pressed -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRight"

void DMouseButtons :: SetRight (logical pressed )
{

  button_right = pressed;

}

/******************************************************************************/
/**
\brief  SetShift - set shift key
        Sets the Shift Modifier Key to the value in 'pressed'.


\param  pressed -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetShift"

void DMouseButtons :: SetShift (logical pressed )
{

  modifier_shift = pressed;

}

/******************************************************************************/
/**
\brief  Shift - shift key
        Returns the value of the Shift Modifier Key.

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Shift"

logical DMouseButtons :: Shift ( )
{


  return(modifier_shift);
}


