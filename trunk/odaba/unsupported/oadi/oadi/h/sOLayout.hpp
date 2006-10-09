/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OLayout

\brief    


\date     $Date: 2006/06/23 18:00:02,89 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OLayout_HPP
#define   OLayout_HPP

class     OLayout;

class     PropertyHandle;
#include  <sDBrush.hpp>
#include  <sDLayout.hpp>
#include  <sOBitmap.hpp>
#include  <sOColorGroup.hpp>
#include  <sOResource.hpp>
class  OLayout :public OResource,
public DLayout
{
protected  :         OBitmap                                     *lshape;                                                    // 
protected  :         OColorGroup                                 *lactive;                                                   // 
protected  :         OColorGroup                                 *linactive;                                                 // 
protected  :         OColorGroup                                 *ldisabled;                                                 // 

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                void DoDestroying ( );
public     :                                             OLayout ( );
public     :                                             OLayout (OResource bcOResource, DLayout bcDLayout, OBitmap *lshape, OColorGroup *lactive, OColorGroup *linactive, OColorGroup *ldisabled );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OLayout ( );
};

#endif
