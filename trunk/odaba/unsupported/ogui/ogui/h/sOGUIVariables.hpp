/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OGUIVariables

\brief    


\date     $Date: 2006/03/13 21:34:17,76 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OGUIVariables_HPP
#define   OGUIVariables_HPP

class     OGUIVariables;

#include  <sOPA_Variables.hpp>
class  OGUIVariables :public OPA_Variables
{

public     :
public     : virtual OGUI7ImpExp                 void *CreateProcessVariable (ProcessVariableNames _pv_name );
public     :         OGUI7ImpExp                                         OGUIVariables (ProcessVariables *_proc_variables );
public     : virtual OGUI7ImpExp                 void ReleaseProcessVariable (ProcessVariableNames _pv_name );
public     : virtual OGUI7ImpExp                                         ~OGUIVariables ( );
};

#endif
