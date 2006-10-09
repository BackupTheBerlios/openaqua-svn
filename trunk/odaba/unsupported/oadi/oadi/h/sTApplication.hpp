/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TApplication



\date     $Date: 2006/04/28 15:20:34,14 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TApplication_HPP
#define   TApplication_HPP

class     TApplication;

class     CTX_Application;
class     OApplication;
class     ODApplication;
class     ODataWidget;
class     OElementStyle;
class     TControl;
#include  <cOEH_Frame.h>
#include  <sTActionHandler.hpp>
#include  <sTWindow.hpp>
class  TApplication :public TWindow
{
protected  :         OApplication                                *application;                                               

public     :
                     OApplication                                *get_application() { return(application); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     :                                        logical DoCreate ( );
public     :                                        logical DoCreated ( );
public     : virtual                                OEH_Frame EventFrame ( );
public     :                                             TApplication ( );
};

#endif
