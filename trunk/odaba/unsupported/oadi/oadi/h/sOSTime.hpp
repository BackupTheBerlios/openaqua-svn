/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OSTime

\brief    


\date     $Date: 2006/06/19 18:45:55,07 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSTime_HPP
#define   OSTime_HPP

class     OSTime;

#include  <sOStyle.hpp>
#pragma pack(4)

class  OSTime :public OStyle
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSTime ( );
public     :                                             OSTime (OStyle bcOStyle );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSTime ( );
};

#pragma pack()
#endif
