/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    TLabel

\brief    


\date     $Date: 2006/03/13 21:32:58,00 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TLabel_HPP
#define   TLabel_HPP

class     TLabel;

class     OLabelDefinition;
#include  <sTControl.hpp>
#include  <sTWidgetControl.hpp>
#pragma pack(4)

class  TLabel :public TWidgetControl
{
protected  :         TWidgetControl                              *target ATTR_ALIGN(4);                                      
protected  :         logical                                      drawFocusRect;                                             

public     :
public     :                                     logical Create (TControl *pTControl, OLabelDefinition *pOLabelDefinition );
public     :                                     logical DoCreate ( );
public     :                                     void SetDrawFocusRect (logical fEnable );
public     :                                                             TLabel ( );
public     :                                     logical loadText ( );
TYPE_DATA
#define HAS_RTTI_TLabel
};

#pragma pack()
#endif
