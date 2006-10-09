/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OButtonControl



\date     $Date: 2006/04/27 15:06:01,79 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OButtonControl_HPP
#define   OButtonControl_HPP

class     OButtonControl;

class     PropertyHandle;
#include  <sDMargin.hpp>
#include  <sDSize.hpp>
#include  <sOActionControl.hpp>
#pragma pack(4)

class  OButtonControl :public OActionControl
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                DSize GetFrameSize (DSize dsize, DMargin &field_margin );
public     :                                             OButtonControl ( );
public     :                                             OButtonControl (OActionControl bcOActionControl );
public     :                                        logical Read (PropertyHandle *ph );
public     : virtual                                     ~OButtonControl ( );
};

#pragma pack()
#endif
