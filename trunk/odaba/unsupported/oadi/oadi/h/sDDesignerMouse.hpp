/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    DDesignerMouse



\date     $Date: 2006/04/28 15:38:32,89 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DDesignerMouse_HPP
#define   DDesignerMouse_HPP

class     DDesignerMouse;

class     OFieldControl;
#include  <sDMouse.hpp>
#pragma pack(4)

class  DDesignerMouse
{
protected  :         OFieldControl                               *Target;                                                    
public     :         DMouse                                      &Mouse;                                                     
protected  :         OFieldControl                               *ControlUnderMouse;                                         

public     :
public     :                                             DDesignerMouse (OFieldControl *pOFieldControlTarget, DMouse &rDMouse, OFieldControl *pOFieldControlUndMouse )                     : Target(pOFieldControlTarget),
  Mouse(rDMouse),
  ControlUnderMouse(pOFieldControlUndMouse)
{


}

};

#pragma pack()
#endif
