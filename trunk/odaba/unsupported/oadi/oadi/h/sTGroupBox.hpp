/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TGroupBox



\date     $Date: 2006/04/28 15:34:05,20 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TGroupBox_HPP
#define   TGroupBox_HPP

class     TGroupBox;

class     OSGroupBox;
#include  <sTField.hpp>
#pragma pack(4)

class  TGroupBox :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
protected  : virtual                                logical DoCreated ( );
public     :                                        OSGroupBox *Style ( ) const;
public     :                                             TGroupBox ( );
};

#pragma pack()
#endif
