/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TControl

\brief    Control interface
          The  control  interface  procides  the  connection between the control
          resource  definition  and  the  GUI  object  for displaying the design
          resource.  Control  interfaces  can  be  more specialized as widget or
          menu items. 
          Control  interfaces  form  a  hierarchy,  which  is  implemented  as 
          children/parent relationship.

\date     $Date: 2006/04/30 19:05:42,70 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TControl_HPP
#define   TControl_HPP

class     TControl;

#ifndef   DLL_TControl_HPP
#define   DLL_TControl_HPP
#include  <sTControl.hpp>
#include  <sDLL.h>
#endif
class     OAction;
class     OElementStyle;
class     OFieldControl;
class     OFrameStyle;
class     OStyle;
class     OWidget;
class     PropertyHandle;
class     TControl;
class     TWidgetControl;
#include  <sTComponent.hpp>
#pragma pack(4)

class  TControl :public TComponent
{
protected  :         OElementStyle                               *elementStyle;                                              
protected  :         OStyle                                      *style;                                                     
protected  :         OFrameStyle                                 *frameStyle;                                                

public     :
                     OElementStyle                               *get_elementStyle() { return(elementStyle); }
                     OStyle                                      *get_style() { return(style); }
public     : virtual          OADIImpExp            void Activate ( );
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                void Close ( );
public     :                                        logical Create (TControl *pTControl, OElementStyle *pOElementStyle, OFrameStyle *pOFrameStyle );
public     :                                        OFieldControl *FieldControl ( );
public     :                                        logical IsCreated ( );
public     : virtual                                void Show (logical fShow );
public     :                                             TControl ( );
public     : virtual                                     ~TControl ( );
};

#pragma pack()
#endif
