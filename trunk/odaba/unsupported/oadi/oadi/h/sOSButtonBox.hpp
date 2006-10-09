/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    OSButtonBox

\brief    


\date     $Date: 2006/06/19 18:45:07,39 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSButtonBox_HPP
#define   OSButtonBox_HPP

class     OSButtonBox;

#include  <sOStyle.hpp>
#pragma pack(4)

class  OSButtonBox :public OStyle
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSButtonBox ( );
public     :                                             OSButtonBox (OStyle bcOStyle );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSButtonBox ( );
};

#pragma pack()
#endif
