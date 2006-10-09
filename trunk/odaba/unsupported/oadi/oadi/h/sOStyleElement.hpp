/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OStyleElement



\date     $Date: 2006/04/27 14:27:46,12 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OStyleElement_HPP
#define   OStyleElement_HPP

class     OStyleElement;

class     ODataSource;
class     OFrameStyle;
class     PropertyHandle;
class     TControl;
#include  <sOContextStyle.hpp>
#include  <sOResource.hpp>
#pragma pack(4)

class  OStyleElement :public OResource,
public OContextStyle
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        char *GetTitle (ODataSource *pODataSource );
public     :                                             OStyleElement ( );
public     :                                             OStyleElement (OResource bcOResource, OContextStyle bcOContextStyle );
protected  : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        logical UpdateStyleElement (PropertyHandle *ph );
public     : virtual                                     ~OStyleElement ( );
};

#pragma pack()
#endif
