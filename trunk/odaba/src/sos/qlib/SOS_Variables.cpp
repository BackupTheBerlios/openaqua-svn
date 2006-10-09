/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    SOS_Variables

\brief    SOS-Process variables


\date     $Date: 2006/08/27 10:52:20,15 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SOS_Variables"

#include  <pdefault.h>
#include  <deferr.h>
#include  <isosi.h>
#include  <sError.hpp>
#include  <sSystemIO.hpp>
#include  <sdfs.hpp>
#include  <isosi.h>
#include  <ssvel.hpp>
#include  <strcc.hpp>
#include  <sSOS_Variables.hpp>


/******************************************************************************/
/**
\brief  CreateProcessVariable - Initialize vaiables



\return var_ptr - 

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProcessVariable"

void *SOS_Variables :: CreateProcessVariable (ProcessVariableNames pv_name )
{
  ProcessVariable &pvar = process_variables->GetVarObject(pv_name);
  void            *variable = NULL;
BEGINSEQ
  switch ( pv_name )
  {
    case PVN_SOSError        : variable = new Error(SOS_ERROR,"SOS","sos_err","Service Functions");
                               ConnectErrorHandle((Error *)variable,PVT_SOS,PVN_SOSError);
                               break;
    case PVN_SOSSysVariables : variable = new svel(50);
                               break;
    case PVN_SOSDataFormat   : variable = new dfs();
                               break;
    case PVN_SOSSystemIO     : variable = new SystemIO();
                               break;
    case PVN_SOSTraceObject  : variable = new trcc();
                               break;
#ifdef __unix__
    case PVN_SOSLONG_JUMP    : variable = new jmp_buf();
                               break;
#endif
    default                  : variable = ANY_Variables::CreateProcessVariable(pv_name);
  }
  
  if ( variable )
  {
    pvar.stssdel();
    pvar.variable_ptr = variable;
  }
RECOVER

ENDSEQ
  return(variable);
}

/******************************************************************************/
/**
\brief  ReleaseProcessVariable - Remove variables




\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProcessVariable"

void SOS_Variables :: ReleaseProcessVariable (ProcessVariableNames pv_name )
{
  ProcessVariable &pvar = process_variables->GetVarObject(pv_name);
  void            *variable = pvar.variable_ptr;
  svel            *svelptr;
BEGINSEQ
  if ( !pvar.stscdel() )                             ERROR
  pvar.Remove();
      
  switch ( pv_name )
  {
    case PVN_SOSError        : delete (Error *)variable;
                               break;
    case PVN_SOSSysVariables : svelptr = (svel *)variable;
                               while ( svelptr = svelptr->Pop() ) 
                                 variable = svelptr;
                               delete (svel *)variable;
                               break;
    case PVN_SOSDataFormat   : delete (dfs *)variable;
                               break;
    case PVN_SOSSystemIO     : delete (SystemIO *)variable;
                               break;
    case PVN_SOSTraceObject  : delete (trcc *)variable;
                               break;
#ifdef __unix__
    case PVN_SOSLONG_JUMP    : delete (jmp_buf *)variable;
                               break;
#endif
    default                  : ANY_Variables::ReleaseProcessVariable(pv_name);
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SOS_Variables - 




\param  proc_variables - Process variables
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SOS_Variables"

     SOS_Variables :: SOS_Variables (ProcessVariables *proc_variables )
                     : ANY_Variables (proc_variables)
{

  manager_type = PVT_SOS;

}

/******************************************************************************/
/**
\brief  ~SOS_Variables - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SOS_Variables"

     SOS_Variables :: ~SOS_Variables ( )
{



}


