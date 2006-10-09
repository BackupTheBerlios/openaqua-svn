/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    GUIVariables

\brief    


\date     $Date: 2006/03/12 19:40:02,51 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   GUIVariables_HPP
#define   GUIVariables_HPP

class     GUIVariables;

#include  <sOGUIVariables.hpp>
class  GUIVariables :public OGUIVariables
{

public     :
public     : virtual                             void *CreateProcessVariable (ProcessVariableNames pv_name );
public     :                                                             GUIVariables (ProcessVariables *prc_variables );
public     : virtual                             void ReleaseProcessVariable (ProcessVariableNames pv_name );
public     : virtual                                                     ~GUIVariables ( );
};

#endif
