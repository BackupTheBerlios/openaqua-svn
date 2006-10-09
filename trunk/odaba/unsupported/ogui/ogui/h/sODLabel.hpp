/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    ODLabel



\date     $Date: 2006/04/28 17:05:13,85 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODLabel_HPP
#define   ODLabel_HPP

class     ODLabel;

class     ODataWidget;
#include  <sDPoint.hpp>
#include  <sDSize.hpp>
#include  <sODControl.hpp>
#include  <sOLabel.hpp>
#pragma pack(4)

class  ODLabel :public ODControl
{
protected  :         ODControl                                   *target;                                                    
protected  :         logical                                      drawFocusRect;                                             

public     :
                     ODControl                                   *get_target() { return(target); }
                     logical                                      get_drawFocusRect() { return(drawFocusRect); }
public     :                                        char *GetText ( );
public     :                                        logical Initialize (DPoint &position, DSize &dsize );
public     :                                             ODLabel (ODControl *pODControl );
public     :                                        void SetDrawFocusRect (logical fEnable );
public     :                                        logical SetText (char *label_text );
};

#pragma pack()
#endif
