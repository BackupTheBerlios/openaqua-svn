/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHKeyEvent

\brief    
          Default actions for key events are:
          F1: Help
          F2: Edit
          F3: Find
          F4: Close
          F5: Copy
          F6: Move
          ALT-Del: Delete
          ALT-Ins: Insert
          ALT-Up: MoveUp
          ALT-Down: MoveDown

\date     $Date: 2006/03/13 21:35:51,09 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHKeyEvent"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sOEHKeyEvent.hpp>


/******************************************************************************/
/**
\brief  OEHKeyEvent - 


-------------------------------------------------------------------------------
\brief  i00


\param  keycode -
\param  keystate -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHKeyEvent"

                        OEHKeyEvent :: OEHKeyEvent (int keycode, int keystate )
                     :   type(QEvent::KeyRelease),
  key(keycode,keystate,UNDEF)
{



}

/******************************************************************************/
/**
\brief  i01


\param  keycode -
\param  key_alt -
\param  key_shift -
\param  key_ctrl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHKeyEvent"

                        OEHKeyEvent :: OEHKeyEvent (int keycode, logical key_alt, logical key_shift, logical key_ctrl )
                     :   type(QEvent::KeyRelease),
  key(keycode,0,UNDEF)
{

  if ( key_alt )
    key.state = key.state | Qt::AltModifier;

  if ( key_shift )
    key.state = key.state | Qt::ShiftModifier;

  if ( key_ctrl )
    key.state = key.state | Qt::ControlModifier;

}

/******************************************************************************/
/**
\brief  i02


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHKeyEvent"

                        OEHKeyEvent :: OEHKeyEvent ( )
                     :   type(QEvent::None),
  key(0,0,UNDEF)
{



}

/******************************************************************************/
/**
\brief  operator== - 


\return cond -

\param  rOEHKeyEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical OEHKeyEvent :: operator== (OEHKeyEvent &rOEHKeyEvent )
{

  return ( key == rOEHKeyEvent.get_key() );

}


