/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ProcessVariables

\brief    


\date     $Date: 2006/03/12 19:20:11,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ProcessVariables_HPP
#define   ProcessVariables_HPP

class     ProcessVariables;

class     ANY_Variables;
#include  <cProcessVariableNames.h>
#include  <sProcessVariable.hpp>
#pragma pack(8)

class  ProcessVariables
{
protected  :         ANY_Variables                               *variable_manager;                                          
protected  :         ProcessVariable                              process_variables[50];                                     

public     :
                     ANY_Variables                               *get_variable_manager() { return(variable_manager); }
public     :                                     void *CreateProcessVariable (ProcessVariableNames pv_name );
public     :                                     void *GetProcessVariable (ProcessVariableNames pv_name );
public     :         SOS7ImpExp                  ProcessVariable &GetVarObject (ProcessVariableNames pv_name );
public     :                                                             ProcessVariables ( );
public     :                                     void ReleaseProcessVariable (ProcessVariableNames pv_name );
public     :                                     void *RemoveProcessVariable (ProcessVariableNames pv_name );
public     :                                     logical SetDeleteOption (ProcessVariableNames pv_name, logical del_opt );
public     :                                     void SetProcessVariable (ProcessVariableNames pv_name, void *var_ptr );
public     :                                     void SetVariableManager (ANY_Variables *var_manager );
public     :                                                             ~ProcessVariables ( );
};

#pragma pack()
#endif
