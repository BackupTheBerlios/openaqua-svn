/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OConstAction



\date     $Date: 2006/04/30 16:26:11,76 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OConstAction_HPP
#define   OConstAction_HPP

class     OConstAction;

#include  <sDString.hpp>
#include  <sOAction.hpp>
#pragma pack(4)

class  OConstAction :public OAction
{
protected  :         char                                        *text;                                                      

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                char Execute ( );
public     :                                             OConstAction ( );
public     :                                             OConstAction (OAction bcOAction, char *text );
public     : virtual                                void Reset ( );
public     :                                        logical SetText (char *string );
public     : virtual                                     ~OConstAction ( );
};

#pragma pack()
#endif
