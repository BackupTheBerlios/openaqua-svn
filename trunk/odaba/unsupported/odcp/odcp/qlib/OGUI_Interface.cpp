/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    OGUI_Interface

\brief    


\date     $Date: 2006/07/05 14:04:38,60 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OGUI_Interface"

#include  <podcp8.h>
#include  <exthrde.h>
#include  <sGUIVariables.hpp>
#include  <sTProjectManager.hpp>
#include  <sUCTX_dll.hpp>
#include  <standard.hpp>

#include  <iOGUI_Interface.h>

/******************************************************************************/
/**
\brief  CreateAppl - 

        function that gets called from woe80
        - sets up a windows application that does not need a console

\return rc - 

\param  hInstance - 
\param  hPrevInst - 
\param  lpszCmdLine - 
\param  nCmdShow - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAppl"

int __cdecl CreateAppl (HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow )
{
  TProjectManager        *pmanager = NULL;
  logical                 term     = NO;
  RegisterProcess();   // c in sosi
  GUIInitProcessInfo();
  
  pmanager = new TProjectManager();
  pmanager->Create(hInstance,hPrevInst,lpszCmdLine,nCmdShow);
  pmanager->Run();
  
  delete pmanager;
  pmanager = NULL;
  
  UnregisterProcess();   // c in sosi

  return(term);
}

/******************************************************************************/
/**
\brief  CreateConsoleAppl - 

        creates a console attaced application - called from coe

\return rc - 

\param  argc - 
\param  argv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateConsoleAppl"

int __cdecl CreateConsoleAppl (int argc, char **argv )
{
  TProjectManager        *pmanager = NULL;
  logical                 term     = NO;
  RegisterProcess();   // c in sosi
  GUIInitProcessInfo();
  
  pmanager = new TProjectManager();
  term |= term || pmanager->Create(argc,argv);
  term |= term || pmanager->Run();
  
  delete pmanager;
  pmanager = NULL;
  
  UnregisterProcess();   // c in sosi

  return(term);
}

/******************************************************************************/
/**
\brief  GUIInitProcessInfo - 



\return proc_info - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GUIInitProcessInfo"

ProcessInfo *__cdecl GUIInitProcessInfo ( )
{
  ProcessInfo   *proc_info;
  if ( thread_list )
    if ( !(proc_info = ThreadEntry::GetCurProcInfo()) )
      proc_info = ThreadEntry::CreateCurProcInfo(NULL);
  
  if ( proc_info && !proc_info->GetVariableManager(PVT_GUI) )
  {
    proc_info->SetVariableManager(new GUIVariables(proc_info->GetProcessVariables()));
    if ( TProjectManager::TPM )
      TProjectManager::TPM->SetErrHandle();
  }
  return(proc_info);
}

/******************************************************************************/
/**
\brief  GetGUIErrorObject - 



\return error_obkect - 

\param  pv_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGUIErrorObject"

Error &__cdecl GetGUIErrorObject (ProcessVariableNames pv_name )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_GUI);
  Error       *error = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = GUIInitProcessInfo()) )          ERROR
 
  error = (Error *)proc_info->GetProcessVariable(pv_name);

RECOVER

ENDSEQ
  return(*error);
}

/******************************************************************************/
/**
\brief  OADIError - 



\return error_object - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OADIError"

Error &__cdecl OADIError ( )
{

  return OGUIError();

}

/******************************************************************************/
/**
\brief  OGUIError - 



\return error_object - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OGUIError"

Error &__cdecl OGUIError ( )
{

  return ( GetGUIErrorObject(PVN_GUIError) );

}

/******************************************************************************/
/**
\brief  P_Error - 



\return error_object - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "P_Error"

Error &__cdecl P_Error ( )
{

  return ( GetGUIErrorObject(PVN_GUIUserError) );

}

/******************************************************************************/
/**
\brief  UDLL_Handle - 



\return uctx_dll - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UDLL_Handle"

UCTX_dll *__cdecl UDLL_Handle ( )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_GUI);
  UCTX_dll    *uctx_dll  = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = GUIInitProcessInfo()) )          ERROR

  uctx_dll = (UCTX_dll *)proc_info->GetProcessVariable(PVN_GUIDLLHandle);
RECOVER

ENDSEQ
  return(uctx_dll);
}

