/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TTimeField

\brief    


\date     $Date: 2006/06/19 19:35:35,50 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TTimeField_HPP
#define   TTimeField_HPP

class     TTimeField;

class     TControl;
#include  <sTField.hpp>
#pragma pack(4)

class  TTimeField :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     : virtual                                logical DoCreated ( );
public     :                                             TTimeField ( );
};

#pragma pack()
#endif
