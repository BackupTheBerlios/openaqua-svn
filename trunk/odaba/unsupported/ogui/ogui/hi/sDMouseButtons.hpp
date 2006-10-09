/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DMouseButtons

\brief    Mouse Button
          This  class stores any  combination of the  three Mouse Buttons (Left,
          Right, Middle) and the three Modifier Keys (Control, Alt, Shift).

          All  functions are related  to the members  of this class, they do NOT
          modify the state or behavior of the real mouse or keyboard.

\date     $Date: 2006/03/13 21:33:37,39 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DMouseButtons_HPP
#define   DMouseButtons_HPP

class     DMouseButtons;

#include  <sDMouseButtons.hpp>
#pragma pack(4)

class  DMouseButtons
{
protected  :         bit                                          button_left: 1;                                            
protected  :         bit                                          button_right: 1;                                           
protected  :         bit                                          button_middle: 1;                                          
protected  :         bit                                          modifier_control: 1;                                       
protected  :         bit                                          modifier_alt: 1;                                           
protected  :         bit                                          modifier_shift: 1;                                         

public     :
public     :                                     logical Alt ( );
public     :                                     logical Any ( );
public     :                                     logical AnyModifier ( );
public     :                                     DMouseButtons Buttons ( );
public     :                                     logical Control ( );
public     :         OGUI7ImpExp                                         DMouseButtons (logical fLeft, logical fRight, logical fMiddle, logical fShift, logical fControl, logical fAlt );
public     :         OGUI7ImpExp                                         DMouseButtons ( );
public     :                                     logical Left ( );
public     :                                     logical Middle ( );
public     :                                     DMouseButtons Modifiers ( );
public     :                                     void Reset ( );
public     :                                     logical Right ( );
public     :                                     void SetAlt (logical pressed );
public     :                                     void SetControl (logical pressed );
public     :                                     void SetLeft (logical pressed );
public     :                                     void SetMiddle (logical pressed );
public     :                                     void SetRight (logical pressed );
public     :                                     void SetShift (logical pressed );
public     :                                     logical Shift ( );
};

#pragma pack()
#endif
