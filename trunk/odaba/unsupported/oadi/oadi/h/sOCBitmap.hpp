/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OCBitmap

\brief    


\date     $Date: 2006/07/09 14:35:42,12 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OCBitmap_HPP
#define   OCBitmap_HPP

class     OCBitmap;

class     OBitmap;
class     PropertyHandle;
#include  <sOPersistent.hpp>
class  OCBitmap :public OResource
{
protected  :         OBitmap                                     *active;                                                    // 
protected  :         OBitmap                                     *inactive;                                                  // 
protected  :         OBitmap                                     *disabled;                                                  // 

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        OBitmap *GetActiveBitmap ( );
public     :                                        OBitmap *GetDisabledBitmap ( );
public     :                                        OBitmap *GetInactiveBitmap ( );
public     :                                             OCBitmap ( );
public     :                                             OCBitmap (OResource bcOResource, OBitmap *pOBitmapActive, OBitmap *pOBitmapInactive, OBitmap *pOBitmapDisabled );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : static                                 OCBitmap *__cdecl ReadFromResource (char *bitmap_name );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OCBitmap ( );
};

#endif
