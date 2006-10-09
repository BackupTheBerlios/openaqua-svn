/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    ProcessVariables

\brief    


\date     $Date: 2006/08/27 14:27:21,54 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ProcessVariables"

#include  <pdefault.h>
#include  <sANY_Variables.hpp>
#include  <sSOS_Variables.hpp>
#include  <sProcessVariables.hpp>


/******************************************************************************/
/**
\brief  CreateProcessVariable - 



\return var_ptr - 

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProcessVariable"

void *ProcessVariables :: CreateProcessVariable (ProcessVariableNames pv_name )
{

  return(variable_manager->CreateProcessVariable(pv_name));

}

/******************************************************************************/
/**
\brief  GetProcessVariable - 



\return proc_variable - Process variable

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProcessVariable"

void *ProcessVariables :: GetProcessVariable (ProcessVariableNames pv_name )
{

  if ( !process_variables[pv_name].variable_ptr )
    CreateProcessVariable(pv_name);
  return(process_variables[pv_name].variable_ptr);

}

/******************************************************************************/
/**
\brief  GetVarObject - 



\return pvar - 

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVarObject"

ProcessVariable &ProcessVariables :: GetVarObject (ProcessVariableNames pv_name )
{

  return(process_variables[pv_name]);

}

/******************************************************************************/
/**
\brief  ProcessVariables - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessVariables"

     ProcessVariables :: ProcessVariables ( )
                     : variable_manager(new SOS_Variables(this))
{

  memset(process_variables,0,sizeof(process_variables));

}

/******************************************************************************/
/**
\brief  ReleaseProcessVariable - 




\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProcessVariable"

void ProcessVariables :: ReleaseProcessVariable (ProcessVariableNames pv_name )
{

  variable_manager->ReleaseProcessVariable(pv_name);

}

/******************************************************************************/
/**
\brief  RemoveProcessVariable - 



\return var_ptr - 

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveProcessVariable"

void *ProcessVariables :: RemoveProcessVariable (ProcessVariableNames pv_name )
{
  void                   *var_ptr = NULL;
  if ( this )
    var_ptr = (process_variables[pv_name]).Remove();
  return(var_ptr);
}

/******************************************************************************/
/**
\brief  SetDeleteOption - 



\return del_opt - 

\param  pv_name - Process variable name
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDeleteOption"

logical ProcessVariables :: SetDeleteOption (ProcessVariableNames pv_name, logical del_opt )
{
  logical   old_opt = process_variables[pv_name].stscdel();
  if ( del_opt )  
    process_variables[pv_name].stssdel();
  else
    process_variables[pv_name].stsrdel();

  return(old_opt);
}

/******************************************************************************/
/**
\brief  SetProcessVariable - 




\param  pv_name - Process variable name
\param  var_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProcessVariable"

void ProcessVariables :: SetProcessVariable (ProcessVariableNames pv_name, void *var_ptr )
{

BEGINSEQ
  if ( this )
  {
    if ( process_variables[pv_name].variable_ptr == var_ptr )
                                                     LEAVESEQ
    ReleaseProcessVariable(pv_name);
    process_variables[pv_name].variable_ptr = var_ptr;
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetVariableManager - 




\param  var_manager - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVariableManager"

void ProcessVariables :: SetVariableManager (ANY_Variables *var_manager )
{

  if ( variable_manager )
    delete variable_manager;
    
  variable_manager = var_manager;


}

/******************************************************************************/
/**
\brief  ~ProcessVariables - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ProcessVariables"

     ProcessVariables :: ~ProcessVariables ( )
{
  int       i=50;
  while ( --i )
    ReleaseProcessVariable((ProcessVariableNames)i);

  delete variable_manager;
  variable_manager = NULL;

}


