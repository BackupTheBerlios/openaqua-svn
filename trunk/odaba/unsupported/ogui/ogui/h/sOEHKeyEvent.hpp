/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/03/13 21:34:15,10 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHKeyEvent_HPP
#define   OEHKeyEvent_HPP

class     OEHKeyEvent;

#include  <sDKey.hpp>
#include  <sOEHKeyEvent.hpp>
class  OEHKeyEvent
{
protected  :         QEvent                                       type;                                                      //
protected  :         DKey                                         key;                                                       //

public     :
                     QEvent                                      &get_type() { return(type); }
                     DKey                                        &get_key() { return(key); }
public     :         OGUI7ImpExp                                         OEHKeyEvent (int keycode, int keystate );
public     :         OGUI7ImpExp                                         OEHKeyEvent (int keycode, logical key_alt, logical key_shift, logical key_ctrl );
public     :         OGUI7ImpExp                                         OEHKeyEvent ( );
public     :                                     logical operator== (OEHKeyEvent &rOEHKeyEvent );
};

#endif
