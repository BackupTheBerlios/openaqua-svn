/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OSDate

\brief    


\date     $Date: 2006/06/19 18:45:29,54 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSDate_HPP
#define   OSDate_HPP

class     OSDate;

#include  <sOStyle.hpp>
#pragma pack(4)

class  OSDate :public OStyle
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSDate ( );
public     :                                             OSDate (OStyle bcOStyle );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSDate ( );
};

#pragma pack()
#endif
