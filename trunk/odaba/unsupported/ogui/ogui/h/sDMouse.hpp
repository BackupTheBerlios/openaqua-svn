/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    DMouse

\brief    Mouse Event
          This  class  stores  the  state  of  the  Mouse at the time of a Mouse
          Event.

          All  functions are related  to the members  of this class, they do NOT
          modify the state or behavior of the real mouse or keyboard.

\date     $Date: 2006/04/28 17:04:31,82 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DMouse_HPP
#define   DMouse_HPP

class     DMouse;

#include  <sDMouseButtons.hpp>
#include  <sDPoint.hpp>
#pragma pack(4)

class  DMouse
{
protected  :         DMouseButtons                                button;                                                    
protected  :         DMouseButtons                                state_before;                                              
protected  :         DMouseButtons                                state_after;                                               
protected  :         DPoint                                       global_pos;                                                
protected  :         DPoint                                       pos;                                                       

public     :
public     :                                        DMouseButtons Button ( );
public     :                  OGUIImpExp                 DMouse (const DMouseButtons &rcDMouseButtonsButton, const DMouseButtons &rcDMouseButtonsStateBefore, const DMouseButtons &rcDMouseButtonsStateAfter, const DPoint &rcDPointPos, const DPoint &rcDPointGlobalPos );
public     :                  OGUIImpExp                 DMouse ( );
public     :                                        DPoint GlobalPos ( );
public     :                                        DPoint Pos ( );
public     :                                        DMouseButtons StateAfter ( );
public     :                                        DMouseButtons StateBefore ( );
};

#pragma pack()
#endif
