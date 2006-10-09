/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TDesktop



\date     $Date: 2006/04/28 15:19:52,21 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TDesktop_HPP
#define   TDesktop_HPP

class     TDesktop;

class     TControl;
#include  <sTWidgetControl.hpp>
#include  <sTWindow.hpp>
#pragma pack(4)

class  TDesktop :public TWidgetControl
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     :                                             TDesktop ( );
public     : virtual                                     ~TDesktop ( );
};

#pragma pack()
#endif
