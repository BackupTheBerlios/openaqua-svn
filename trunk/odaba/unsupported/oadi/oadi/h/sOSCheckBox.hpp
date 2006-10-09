/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSCheckBox



\date     $Date: 2006/04/28 16:53:37,59 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSCheckBox_HPP
#define   OSCheckBox_HPP

class     OSCheckBox;

#include  <sOStyle.hpp>
#pragma pack(4)

class  OSCheckBox :public OStyle
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSCheckBox ( );
public     :                                             OSCheckBox (OStyle bcOStyle );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSCheckBox ( );
};

#pragma pack()
#endif
