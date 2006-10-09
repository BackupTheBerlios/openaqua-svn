/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OColorGroup

\brief    


\date     $Date: 2006/06/23 18:00:30,06 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OColorGroup_HPP
#define   OColorGroup_HPP

class     OColorGroup;

class     OBrush;
class     PropertyHandle;
#include  <sOResource.hpp>
class  OColorGroup :public OResource
{
protected  :         OBrush                                      *brushs[20];                                                // 

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        OBrush *GetBrush (int32 indx0 );
public     :                                             OColorGroup ( );
public     :                                             OColorGroup (OResource bcOResource, OBrush **pOBrush );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OColorGroup ( );
};

#endif
