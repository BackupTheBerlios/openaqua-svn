/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TRadioGroup



\date     $Date: 2006/04/28 15:22:28,03 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TRadioGroup_HPP
#define   TRadioGroup_HPP

class     TRadioGroup;

#include  <sOSRadioGroup.hpp>
#include  <sTField.hpp>
class  TRadioGroup :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     :                                        logical DoCreate ( );
public     :                                        logical DoCreated ( );
public     :                                        OSRadioGroup *Style ( );
public     :                                             TRadioGroup ( );
};

#endif
