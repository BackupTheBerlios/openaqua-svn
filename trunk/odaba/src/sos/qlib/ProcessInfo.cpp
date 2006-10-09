/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    ProcessInfo

\brief    Process Info


\date     $Date: 2006/05/28 19:39:05,17 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ProcessInfo"

#include  <pdefault.h>
#include  <sANY_Variables.hpp>
#include  <sProcessInfo.hpp>
#include  <sProcessVariable.hpp>
#include  <sProcessVariables.hpp>
#include  <ssvel.hpp>
#include  <sProcessInfo.hpp>


/******************************************************************************/
/**
\brief  CopyParentVariable


\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyParentVariable"

void ProcessInfo :: CopyParentVariable (ProcessVariableNames pv_name )
{

  if ( parent_info )
    SetProcessVariable(pv_name,parent_info->GetProcessVariable(pv_name));


}

/******************************************************************************/
/**
\brief  GetDisplay

\return display

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDisplay"

logical ProcessInfo :: GetDisplay ( )
{

  return(this ? display : NO);

}

/******************************************************************************/
/**
\brief  GetParentVariable

\return proc_variable - Process variable

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParentVariable"

void *ProcessInfo :: GetParentVariable (ProcessVariableNames pv_name )
{

  return( parent_info->GetProcessVariable(pv_name) );

}

/******************************************************************************/
/**
\brief  GetProcessVariable

\return proc_variable - Process variable

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProcessVariable"

void *ProcessInfo :: GetProcessVariable (ProcessVariableNames pv_name )
{

  return( process_variables->GetProcessVariable(pv_name) );

}

/******************************************************************************/
/**
\brief  GetProcessVariables

\return proc_variables - Process variables

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProcessVariables"

ProcessVariables *ProcessInfo :: GetProcessVariables ( )
{

  return(process_variables);

}

/******************************************************************************/
/**
\brief  GetProtocolFile

\return cpath - Complete path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProtocolFile"

char *ProcessInfo :: GetProtocolFile ( )
{

  return(this ? error_file : NULL);

}

/******************************************************************************/
/**
\brief  GetVariableManager

\return proc_variables - Process variables

\param  proc_vt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVariableManager"

ANY_Variables *ProcessInfo :: GetVariableManager (ProcVariableTypes proc_vt )
{
  ANY_Variables  *vm = NULL;
  if ( this && process_variables )
    vm = process_variables->get_variable_manager();
    
  return( vm && vm->get_manager_type() >= proc_vt ? vm : NULL );

}

/******************************************************************************/
/**
\brief  ILock

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical ProcessInfo :: ILock ( )
{

  return( res_lock.ILock(YES) );

}

/******************************************************************************/
/**
\brief  IUnlock

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical ProcessInfo :: IUnlock ( )
{

  return( res_lock.IUnlock() );

}

/******************************************************************************/
/**
\brief  ProcessInfo

-------------------------------------------------------------------------------
\brief  i0


\param  cpath - Complete path
\param  display_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessInfo"

     ProcessInfo :: ProcessInfo (char *cpath, logical display_opt )
                     : error_file(new char[256]),
  display(display_opt),
  is_deleting(NO),
  process_variables(new ProcessVariables()),
  parent_info(NULL),
  res_lock(NO)
{
  memset(error_file,0,256);

}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessInfo"

     ProcessInfo :: ProcessInfo ( )
                     : error_file(new char[256]),
  display(YES),
  is_deleting(NO),
  process_variables(new ProcessVariables()),
  parent_info(NULL),
  res_lock(NO)
{
  memset(error_file,0,sizeof(error_file));

}

/******************************************************************************/
/**
\brief  RemoveProcessVariable

\return var_ptr

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveProcessVariable"

void *ProcessInfo :: RemoveProcessVariable (ProcessVariableNames pv_name )
{

  return( process_variables->RemoveProcessVariable(pv_name) );

}

/******************************************************************************/
/**
\brief  ResetParentInfo


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetParentInfo"

void ProcessInfo :: ResetParentInfo ( )
{
  svel     *svelptr;
  svel     *parent_svel;
BEGINSEQ
  if ( !parent_info )                                LEAVESEQ
    
  parent_svel = (svel *)parent_info->GetProcessVariable(PVN_SOSSysVariables);
  if ( svelptr = (svel *)GetProcessVariable(PVN_SOSSysVariables) )
    svelptr->DisconnectAll(parent_svel);

  parent_info->ILock();
  parent_info->children.Remove(this);
  parent_info->IUnlock();
  parent_info = NULL; 

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetDisplay


\param  display_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplay"

void ProcessInfo :: SetDisplay (logical display_opt )
{
  if ( this )
    display = display_opt;
}

/******************************************************************************/
/**
\brief  SetParentInfo


\param  proc_info
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParentInfo"

void ProcessInfo :: SetParentInfo (ProcessInfo *proc_info )
{
  svel     *svelptr;
  svel     *parent_svel;
BEGINSEQ
  if ( !proc_info )                                  ERROR
    
  parent_info = proc_info; 
  parent_info->ILock();
  proc_info->children.AddTail(this);
  parent_info->IUnlock();
  
  if ( svelptr = (svel *)GetProcessVariable(PVN_SOSSysVariables) )
  {
    svelptr->SetPopStop(YES);
    if ( parent_svel = (svel *)proc_info->GetProcessVariable(PVN_SOSSysVariables) )
      svelptr->ConnectTail(parent_svel);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetProcessVariable


\param  pv_name - Process variable name
\param  var_ptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProcessVariable"

void ProcessInfo :: SetProcessVariable (ProcessVariableNames pv_name, void *var_ptr )
{
 process_variables->SetProcessVariable(pv_name,var_ptr);
}

/******************************************************************************/
/**
\brief  SetProcessVariables


\param  proc_variables - Process variables
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProcessVariables"

void ProcessInfo :: SetProcessVariables (ProcessVariables *proc_variables )
{

  if ( process_variables )
    delete process_variables;
    
  process_variables = proc_variables;

}

/******************************************************************************/
/**
\brief  SetProtocolFile


\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProtocolFile"

void ProcessInfo :: SetProtocolFile (char *cpath )
{
  if ( this && error_file)
    strncpy(error_file,cpath,255);
}

/******************************************************************************/
/**
\brief  SetVariableManager


\param  var_manager
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVariableManager"

void ProcessInfo :: SetVariableManager (ANY_Variables *var_manager )
{

  process_variables->SetVariableManager(var_manager);

}

/******************************************************************************/
/**
\brief  ~ProcessInfo


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ProcessInfo"

     ProcessInfo :: ~ProcessInfo ( )
{
  ProcessInfo      *proc_info;
  is_deleting = YES;

  while ( proc_info = children.GetHead() )
    proc_info->ResetParentInfo();  // removes ProcessInfo from list
  
  delete error_file;
  error_file = NULL;
  delete process_variables;
  process_variables = NULL;
}


