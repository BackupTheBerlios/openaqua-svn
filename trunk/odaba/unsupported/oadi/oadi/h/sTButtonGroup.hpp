/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TButtonGroup



\date     $Date: 2006/04/28 15:20:47,64 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TButtonGroup_HPP
#define   TButtonGroup_HPP

class     TButtonGroup;

class     OSButtonGroup;
#include  <sTField.hpp>
#pragma pack(4)

class  TButtonGroup :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
protected  : virtual                                logical DoCreated ( );
public     :                                        OSButtonGroup *Style ( ) const;
public     :                                             TButtonGroup ( );
};

#pragma pack()
#endif
