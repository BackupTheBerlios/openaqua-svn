/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    ProcessInfo

\brief    Process Info


\date     $Date: 2006/05/28 19:37:25,10 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ProcessInfo_HPP
#define   ProcessInfo_HPP

#include "csosdll.h"
class     ProcessInfo;

class     ANY_Variables;
class     ProcessInfo;
class     ProcessVariables;
#include  <cProcVariableTypes.h>
#include  <cProcessVariableNames.h>
#include  <sProcessVariable.hpp>
#pragma pack(8)

class  ProcessInfo
{
protected  :         char                                        *error_file;                                                
protected  :         logical                                      display;                                                   
protected  :         logical                                      is_deleting;                                               
protected  :         ProcessVariables                            *process_variables;                                         
protected  :         ProcessInfo                                 *parent_info;                                               
protected  :         DLL(ProcessInfo)                             children;                                                  
protected  :         RessourceLock                                res_lock;                                                  

public     :
                     char                                        *get_error_file() { return(error_file); }
                     logical                                      get_display() { return(display); }
                     logical                                      get_is_deleting() { return(is_deleting); }
                     ProcessVariables                            *get_process_variables() { return(process_variables); }
                     ProcessInfo                                 *get_parent_info() { return(parent_info); }
                     DLL(ProcessInfo)                            &get_children() { return(children); }
                     RessourceLock                               &get_res_lock() { return(res_lock); }
public     :                                        void CopyParentVariable (ProcessVariableNames pv_name );
public     :                  SOSImpExp             logical GetDisplay ( );
public     :                  SOSImpExp             void *GetParentVariable (ProcessVariableNames pv_name );
public     :                  SOSImpExp             void *GetProcessVariable (ProcessVariableNames pv_name );
public     :                  SOSImpExp             ProcessVariables *GetProcessVariables ( );
public     :                  SOSImpExp             char *GetProtocolFile ( );
public     :                  SOSImpExp             ANY_Variables *GetVariableManager (ProcVariableTypes proc_vt=PVT_undefined );
public     :                                        logical ILock ( );
public     :                                        logical IUnlock ( );
public     :                  SOSImpExp                  ProcessInfo (char *cpath, logical display_opt );
public     :                  SOSImpExp                  ProcessInfo ( );
public     :                                        void *RemoveProcessVariable (ProcessVariableNames pv_name );
public     :                                        void ResetParentInfo ( );
public     :                  SOSImpExp             void SetDisplay (logical display_opt );
public     :                                        void SetParentInfo (ProcessInfo *proc_info );
public     :                  SOSImpExp             void SetProcessVariable (ProcessVariableNames pv_name, void *var_ptr );
public     :                                        void SetProcessVariables (ProcessVariables *proc_variables );
public     :                  SOSImpExp             void SetProtocolFile (char *cpath );
public     :                  SOSImpExp             void SetVariableManager (ANY_Variables *var_manager );
public     : virtual          SOSImpExp                  ~ProcessInfo ( );
};

#pragma pack()
#endif
