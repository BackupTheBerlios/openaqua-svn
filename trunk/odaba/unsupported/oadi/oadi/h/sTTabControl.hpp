/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TTabControl



\date     $Date: 2006/04/28 15:22:52,84 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TTabControl_HPP
#define   TTabControl_HPP

class     TTabControl;

class     ODTabControl;
class     OSTabControl;
#include  <sTField.hpp>
class  TTabControl :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
public     : virtual                                logical DoCreated ( );
public     :                                        OSTabControl *Style ( ) const;
public     :                                             TTabControl ( );
};

#endif
