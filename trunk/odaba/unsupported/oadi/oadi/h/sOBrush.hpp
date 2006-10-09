/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OBrush

\brief    


\date     $Date: 2006/06/23 17:58:14,61 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OBrush_HPP
#define   OBrush_HPP

class     OBrush;

class     OBitmap;
class     PropertyHandle;
#include  <sDBrush.hpp>
#include  <sOResource.hpp>
class  OBrush :public OResource,
public DBrush
{
protected  :         OBitmap                                     *bitmap;                                                    // 

public     :
                     OBitmap                                     *get_bitmap() { return(bitmap); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OBrush ( );
public     :                                             OBrush (OResource bcOResource, DBrush bcDBrush, OBitmap *pOBitmap );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OBrush ( );
};

#endif
