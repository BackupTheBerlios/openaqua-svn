/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OJumpAction



\date     $Date: 2006/04/28 11:23:13,46 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OJumpAction_HPP
#define   OJumpAction_HPP

class     OJumpAction;

#include  <sDString.hpp>
#include  <sOAction.hpp>
#pragma pack(4)

class  OJumpAction :public OAction
{
protected  :         DString                                      target;                                                    

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                             OJumpAction ( );
public     :                                        logical SetTarget (const DString &rcdsText );
public     : virtual                                     ~OJumpAction ( );
};

#pragma pack()
#endif
