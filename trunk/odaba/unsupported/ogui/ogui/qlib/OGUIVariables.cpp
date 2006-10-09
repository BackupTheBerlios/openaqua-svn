/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OGUIVariables

\brief    


\date     $Date: 2006/03/13 21:35:54,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OGUIVariables"

#include  <pogui7.h>
#include  <sOPA_Variables.hpp>
#include  <sOGUIVariables.hpp>


/******************************************************************************/
/**
\brief  CreateProcessVariable - 


\return term -

\param  _pv_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateProcessVariable"

void *OGUIVariables :: CreateProcessVariable (ProcessVariableNames _pv_name )
{
  ProcessVariable    &pvar     = process_variables->GetVarObject(_pv_name);
  void               *variable = NULL;
BEGINSEQ
  switch ( _pv_name )
  {
    case PVN_GUIError     : variable = new Error(OGUI_ERROR,"OGUI","ogui_err","ODABA GUI Functions");
                            break;
    case PVN_GUISQLError  : variable = new Error(SQL_ERROR,"SQL","sql_err","Expression Error");
                            break;
    case PVN_GUIDCError   : variable = new Error(DC_ERROR,"DC","dc_err","Document Composer Error");
                            break;
    default               : variable = OPA_Variables::CreateProcessVariable(_pv_name);
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
\brief  OGUIVariables - 


\return term -

\param  _proc_variables -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OGUIVariables"

                        OGUIVariables :: OGUIVariables (ProcessVariables *_proc_variables )
                     : OPA_Variables(_proc_variables)
{

  manager_type = PVT_GUI;

}

/******************************************************************************/
/**
\brief  ReleaseProcessVariable - 



\param  _pv_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseProcessVariable"

void OGUIVariables :: ReleaseProcessVariable (ProcessVariableNames _pv_name )
{
  ProcessVariable    &pvar     = process_variables->GetVarObject(_pv_name);
  void               *variable = pvar.variable_ptr;
BEGINSEQ
  if ( !variable || !pvar.stscdel() )                LEAVESEQ
  switch ( _pv_name )
  {
    case PVN_GUIError     :
    case PVN_GUISQLError  :
    case PVN_GUIDCError   : delete (Error *)variable;
                            break;
    default               : OPA_Variables::ReleaseProcessVariable(_pv_name);
                            LEAVESEQ
  }
  pvar.Remove();
ENDSEQ

}

/******************************************************************************/
/**
\brief  ~OGUIVariables - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OGUIVariables"

                        OGUIVariables :: ~OGUIVariables ( )
{



}


