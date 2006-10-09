/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TButtonBoxField

\brief    


\date     $Date: 2006/06/19 19:38:14,84 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TButtonBoxField_HPP
#define   TButtonBoxField_HPP

class     TButtonBoxField;

class     TControl;
#include  <sTField.hpp>
#pragma pack(4)

class  TButtonBoxField :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     : virtual                                logical DoCreated ( );
public     :                                             TButtonBoxField ( );
};

#pragma pack()
#endif
