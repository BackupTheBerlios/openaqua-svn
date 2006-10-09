/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TPushButton



\date     $Date: 2006/04/28 15:22:16,34 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TPushButton_HPP
#define   TPushButton_HPP

class     TPushButton;

class     OSButton;
#include  <sTWidgetControl.hpp>
#pragma pack(4)

class  TPushButton :public TWidgetControl
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     :                                        logical DoCreate ( );
public     :                                        logical DoCreated ( );
public     :                                        OSButton *Style ( ) const;
public     :                                             TPushButton ( );
};

#pragma pack()
#endif
