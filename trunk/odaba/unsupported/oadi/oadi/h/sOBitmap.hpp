/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OBitmap



\date     $Date: 2006/04/28 16:12:30,17 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OBitmap_HPP
#define   OBitmap_HPP

class     OBitmap;

class     PropertyHandle;
#include  <sDPixmap.hpp>
#include  <sOResource.hpp>
class  OBitmap :public OResource,
public DPixmap
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OBitmap ( );
public     :                                             OBitmap (OResource bcOResource, DPixmap bcDPixmap );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OBitmap ( );
};

#endif
