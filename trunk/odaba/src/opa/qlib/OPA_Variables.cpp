/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    OPA_Variables

\brief    SOS-Process variables


\date     $Date: 2006/03/12 19:17:59,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPA_Variables"

#include  <popa7.h>
#include  <ljump.h>
#include  <cProcessVariableNames.h>
#include  <sDLL_Handle.hpp>
#include  <sError.hpp>
#include  <sInitArea.hpp>
#include  <sSOS_Variables.hpp>
#include  <sUtilityHandle.hpp>
#include  <sOPA_Variables.hpp>


/******************************************************************************/
/**
\brief  CreateProcessVariable - Initialize vaiables


\return var_ptr

\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProcessVariable"

void *OPA_Variables :: CreateProcessVariable (ProcessVariableNames pv_name )
{
  ProcessVariable &pvar = process_variables->GetVarObject(pv_name);
  void            *variable = NULL;
BEGINSEQ
  switch ( pv_name )
  {
    case PVN_OPASDBError     : variable = new Error(ODABA_ERROR,"SDB","sdb_err","Database Error");
                               ConnectErrorHandle((Error *)variable,PVT_OPA,PVN_OPASDBError);
                               break;
    case PVN_OPACTXError     : variable = new Error(CONTEXT_ERROR,"CTX","p_err","DB-Context Error");
                               ConnectErrorHandle((Error *)variable,PVT_OPA,PVN_OPACTXError);
                               break;
    case PVN_OPAOQLError     : variable = new Error(OQL_ERROR,"OQL","oql_err","Expression Error");
                               ConnectErrorHandle((Error *)variable,PVT_OPA,PVN_OPAOQLError);
                               break;
    case PVN_OPADLLHandle    : variable = new DLL_Handle();
                               break;
    case PVN_OPAInitArea     : variable = new InitArea();
                               break;
    case PVN_OPAUtilityCB    : variable = new UtilityHandle(ODABAClient(),"","","","",APT_Console);
                               break;
    case PVN_OPAActiveHandle : variable = new int64;
                               *(int64 *)variable = 0;
                               break;
    case PVN_GlobalVariables : variable = new ParmList(YES);
                               break;
    default                  : variable = SOS_Variables::CreateProcessVariable(pv_name);
                               LEAVESEQ
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
\brief  OPA_Variables - Konstruktor
        The  constructor  provides  the  process  variables  either  from  the 
        ThreadEntry or creates them by its own.


\param  proc_variables
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPA_Variables"

                        OPA_Variables :: OPA_Variables (ProcessVariables *proc_variables )
                     : SOS_Variables (proc_variables)
{

  manager_type = PVT_OPA;

}

/******************************************************************************/
/**
\brief  ReleaseProcessVariable - 



\param  pv_name - Process variable name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProcessVariable"

void OPA_Variables :: ReleaseProcessVariable (ProcessVariableNames pv_name )
{
  ProcessVariable &pvar = process_variables->GetVarObject(pv_name);
  void            *variable = pvar.variable_ptr;
BEGINSEQ
  if ( !pvar.stscdel() )                             ERROR
  pvar.Remove();
  
  switch ( pv_name )
  {
    case PVN_OPASDBError     : delete (Error *)variable;
                               break;
    case PVN_OPACTXError     : delete (Error *)variable;
                               break;
    case PVN_OPAOQLError     : delete (Error *)variable;
                               break;
    case PVN_OPADLLHandle    : delete (DLL_Handle *)variable;
                               break;
    case PVN_OPAInitArea     : delete (InitArea *)variable;
                               break;
    case PVN_OPAUtilityCB    : delete (UtilityHandle *)variable;
                               break;
    case PVN_OPAActiveHandle : delete (int64 *)variable;
                               break;
    case PVN_GlobalVariables : delete (ParmList *)variable;
                               break;
    default                  : SOS_Variables::ReleaseProcessVariable(pv_name);
                               LEAVESEQ
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OPA_Variables - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPA_Variables"

                        OPA_Variables :: ~OPA_Variables ( )
{



}


