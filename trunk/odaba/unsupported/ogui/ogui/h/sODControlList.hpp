/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODControlList

\brief    


\date     $Date: 2006/03/13 21:33:51,51 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODControlList_HPP
#define   ODControlList_HPP

class     ODControlList;

#ifndef   DLL_ODControl_HPP
#define   DLL_ODControl_HPP
#include  <sODControl.hpp>
#include  <sDLL.h>
#endif
class     ODControl;
class  ODControlList :public DLL(ODControl)
{

public     :
public     :                                     logical Activate ( );
public     :                                     logical Deactivate (logical data_only=NO );
public     :                                     ODControl *FindControl (char *control_name );
public     :                                     ODControl *FindField (char *control_name );
public     :                                                             ODControlList ( );
public     :                                                             ~ODControlList ( );
};

#endif
