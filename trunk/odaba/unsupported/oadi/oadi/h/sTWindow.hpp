/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TWindow



\date     $Date: 2006/04/28 15:25:08,54 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TWindow_HPP
#define   TWindow_HPP

class     TWindow;

class     OSWindow;
#include  <cOEH_Frame.h>
#include  <sTField.hpp>
#pragma pack(4)

class  TWindow :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
protected  : virtual                                logical DoCreated ( );
public     : virtual                                OEH_Frame EventFrame ( );
public     :                                        OSWindow *Style ( ) const;
public     :                                             TWindow ( );
};

#pragma pack()
#endif
