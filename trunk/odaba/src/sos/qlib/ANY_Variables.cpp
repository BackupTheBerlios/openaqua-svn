/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    ANY_Variables



\date     $Date: 2006/05/20 12:59:38,23 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ANY_Variables"

#include  <pdefault.h>
#include  <sProcessVariables.hpp>
#include  <sANY_Variables.hpp>


/******************************************************************************/
/**
\brief  ANY_Variables


\param  proc_variables - Process variables
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ANY_Variables"

     ANY_Variables :: ANY_Variables (ProcessVariables *proc_variables )
                     : process_variables(proc_variables),
  manager_type(PVT_undefined)
{
}

/******************************************************************************/
/**
\brief  CreateProcessVariable

\return var_ptr

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProcessVariable"

void *ANY_Variables :: CreateProcessVariable (ProcessVariableNames pv_name )
{

  return(NULL);
}

/******************************************************************************/
/**
\brief  ReleaseProcessVariable


\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProcessVariable"

void ANY_Variables :: ReleaseProcessVariable (ProcessVariableNames pv_name )
{
}

/******************************************************************************/
/**
\brief  ~ANY_Variables


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ANY_Variables"

     ANY_Variables :: ~ANY_Variables ( )
{
}


