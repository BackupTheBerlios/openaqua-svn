/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    GUIVariables

\brief    


\date     $Date: 2006/07/05 14:04:38,33 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "GUIVariables"

#include  <podcp8.h>
#include  <sOGUIVariables.hpp>
#include  <sUCTX_dll.hpp>
#include  <sGUIVariables.hpp>


/******************************************************************************/
/**
\brief  CreateProcessVariable - 



\return instptr - 

\param  pv_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProcessVariable"

void *GUIVariables :: CreateProcessVariable (ProcessVariableNames pv_name )
{
  ProcessVariable    &pvar     = process_variables->GetVarObject(pv_name);
  void               *variable = NULL;
BEGINSEQ
  switch ( pv_name )
  {
    case PVN_GUIUserError : variable = new Error(APPL_ERROR,"Appl","p_err","Application Error");
                            break;
    case PVN_GUIDLLHandle : variable = new UCTX_dll();
                            break;
    default               : variable = OGUIVariables::CreateProcessVariable(pv_name);
                            LEAVESEQ
  }
  
  if ( variable )
  {
    pvar.stssdel();
    pvar.variable_ptr = variable;
  }
RECOVER
  variable = NULL;
ENDSEQ
  return(variable);
}

/******************************************************************************/
/**
\brief  GUIVariables - 




\param  prc_variables - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GUIVariables"

     GUIVariables :: GUIVariables (ProcessVariables *prc_variables )
                     : OGUIVariables (prc_variables)
{



}

/******************************************************************************/
/**
\brief  ReleaseProcessVariable - 




\param  pv_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProcessVariable"

void GUIVariables :: ReleaseProcessVariable (ProcessVariableNames pv_name )
{
  ProcessVariable    &pvar     = process_variables->GetVarObject(pv_name);
  void               *variable = pvar.variable_ptr;
BEGINSEQ
  if ( !variable || !pvar.stscdel() )                LEAVESEQ
  switch ( pv_name )
  {
    case PVN_GUIUserError : delete (Error *)variable;
                            break;
    case PVN_GUIDLLHandle : delete (UCTX_dll *)variable;
                            break;
    default               : OGUIVariables::ReleaseProcessVariable(pv_name);
                            LEAVESEQ
  }
  pvar.Remove();
ENDSEQ

}

/******************************************************************************/
/**
\brief  ~GUIVariables - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~GUIVariables"

     GUIVariables :: ~GUIVariables ( )
{



}


