/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ANY_Variables



\date     $Date: 2006/03/12 19:19:22,53 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ANY_Variables_HPP
#define   ANY_Variables_HPP

class     ANY_Variables;

class     ProcessVariables;
#include  <cProcVariableTypes.h>
#include  <cProcessVariableNames.h>
#pragma pack(8)

class  ANY_Variables
{
protected  :         ProcessVariables                            *process_variables;                                         
protected  :         ProcVariableTypes                            manager_type;                                              

public     :
                     ProcessVariables                            *get_process_variables() { return(process_variables); }
                     ProcVariableTypes                            get_manager_type() { return(manager_type); }
public     :                                                             ANY_Variables (ProcessVariables *proc_variables );
public     : virtual SOS7ImpExp                  void *CreateProcessVariable (ProcessVariableNames pv_name );
public     : virtual SOS7ImpExp                  void ReleaseProcessVariable (ProcessVariableNames pv_name );
public     : virtual SOS7ImpExp                                          ~ANY_Variables ( );
};

#pragma pack()
#endif
