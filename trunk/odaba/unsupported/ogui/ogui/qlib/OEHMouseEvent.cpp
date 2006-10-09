/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHMouseEvent

\brief    


\date     $Date: 2006/03/13 21:35:51,23 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHMouseEvent"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sOEHMouseEvent.hpp>


/******************************************************************************/
/**
\brief  OEHMouseEvent - 


-------------------------------------------------------------------------------
\brief  i00


\param  qevent -
\param  keystate -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHMouseEvent"

                        OEHMouseEvent :: OEHMouseEvent (QEvent qevent, int keystate )
                     :   type(qevent),
  state(keystate)
{



}

/******************************************************************************/
/**
\brief  i01


\param  clicks -
\param  key_alt -
\param  key_shift -
\param  key_ctrl -
\param  mouse_right -
\param  mouse_mid -
\param  mouse_left -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHMouseEvent"

                        OEHMouseEvent :: OEHMouseEvent (char clicks, logical key_alt, logical key_shift, logical key_ctrl, logical mouse_right, logical mouse_mid, logical mouse_left )
                     :   type(QEvent::None),
  state(0)
{

  if ( clicks == 1 )
    type = QEvent::MouseButtonRelease;
  else if ( clicks > 1 )
    type = QEvent::MouseButtonDblClick;
    
  if ( key_alt )
    state = state | Qt::AltModifier;
  if ( key_shift )
    state = state | Qt::ShiftModifier;
  if ( key_ctrl )
    state = state | Qt::ControlModifier;
  
  if ( mouse_right )
    state = state | Qt::RightButton;
  if ( mouse_mid )
    state = state | Qt::MidButton;
  if ( mouse_left )
    state = state | Qt::LeftButton;

        
    


}

/******************************************************************************/
/**
\brief  i02


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHMouseEvent"

                        OEHMouseEvent :: OEHMouseEvent ( )
                     :   type(QEvent::None),
  state(0)
{



}

/******************************************************************************/
/**
\brief  operator== - 


\return cond -

\param  rOEHMouseEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical OEHMouseEvent :: operator== (OEHMouseEvent &rOEHMouseEvent )
{

  return ( state == rOEHMouseEvent.get_state() );

}


