/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHMouseEvent

\brief    


\date     $Date: 2006/03/13 21:34:15,21 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHMouseEvent_HPP
#define   OEHMouseEvent_HPP

class     OEHMouseEvent;

#include  <sOEHMouseEvent.hpp>
class  OEHMouseEvent
{
protected  :         QEvent                                       type;                                                      //
protected  :         int                                          state;                                                     //

public     :
                     QEvent                                      &get_type() { return(type); }
                     int                                         &get_state() { return(state); }
public     :         OGUI7ImpExp                                         OEHMouseEvent (QEvent qevent, int keystate );
public     :         OGUI7ImpExp                                         OEHMouseEvent (char clicks, logical key_alt, logical key_shift, logical key_ctrl, logical mouse_right, logical mouse_mid, logical mouse_left );
public     :         OGUI7ImpExp                                         OEHMouseEvent ( );
public     :                                     logical operator== (OEHMouseEvent &rOEHMouseEvent );
};

#endif
