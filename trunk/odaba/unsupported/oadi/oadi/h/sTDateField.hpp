/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TDateField

\brief    


\date     $Date: 2006/06/19 19:34:52,34 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TDateField_HPP
#define   TDateField_HPP

class     TDateField;

class     TControl;
#include  <sTField.hpp>
#pragma pack(4)

class  TDateField :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     : virtual                                logical DoCreated ( );
public     :                                             TDateField ( );
};

#pragma pack()
#endif
