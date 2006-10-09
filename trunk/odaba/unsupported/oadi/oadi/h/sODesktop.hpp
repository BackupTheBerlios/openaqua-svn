/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    ODesktop



\date     $Date: 2006/04/27 19:49:50,43 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODesktop_HPP
#define   ODesktop_HPP

class     ODesktop;

class     PropertyHandle;
class     TControl;
#include  <sOFrameStyle.hpp>
#include  <sOStyleAction.hpp>
#pragma pack(4)

class  ODesktop :public OStyleAction,
public OFrameStyle
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                             ODesktop ( );
public     :                                             ODesktop (OStyleAction bcOStyleAction, OFrameStyle bcOFrameStyle );
public     :                                        TControl *Open ( );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     : virtual                                     ~ODesktop ( );
};

#pragma pack()
#endif
