/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TCheckBoxField



\date     $Date: 2006/04/28 15:20:59,53 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TCheckBoxField_HPP
#define   TCheckBoxField_HPP

class     TCheckBoxField;

#include  <sTField.hpp>
#pragma pack(4)

class  TCheckBoxField :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     : virtual                                logical DoCreated ( );
public     :                                             TCheckBoxField ( );
};

#pragma pack()
#endif
