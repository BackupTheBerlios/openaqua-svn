/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    opai

\brief    


\date     $Date: 2006/08/24 20:41:29,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   opai_H
#define   opai_H

class     CClient;
class     CS_Handle;
class     DBObjectHandle;
class     DLL_Handle;
class     InitArea;
class     ProcessInfo;
class     Services;
class     UtilityHandle;
#include  <cMAT_Types.h>
#include  <cProcessVariableNames.h>
#include  <sError.hpp>
#include  <sODABAClient.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

OPAImpExp          Error &__cdecl CTXError ( );
OPAImpExp          DLL_Handle *__cdecl DLLHandle ( );
OPAImpExp          int64 __cdecl GetActiveHandle ( );
OPAImpExp          DBObjectHandle &__cdecl GetDataCatalogue ( );
OPAImpExp          void *__cdecl GetFunctionPtr (char *dllname, char *fnames, logical check_opt );
OPAImpExp          int32 __cdecl GetHandleCount ( );
OPAImpExp          ODABAClient &__cdecl GetMainClient ( );
                   MAT_Types __cdecl GetMetaAttributeType (char *prop_names );
OPAImpExp          void *__cdecl GetOPAProcessVariable (ProcessVariableNames pv_name );
OPAImpExp          DBObjectHandle &__cdecl GetSystemDBObject ( );
OPAImpExp          DictionaryHandle &__cdecl GetSystemDictionary ( );
OPAImpExp          InitArea *__cdecl INITArea ( );
                   logical __cdecl LockGlobal ( );
OPAImpExp          char *__cdecl ODABA2Version ( );
                   ProcessInfo *__cdecl OPAInitProcessInfo ( );
OPAImpExp          void __cdecl OPAResources ( );
OPAImpExp          Error &__cdecl OQLError ( );
                   logical __cdecl RegisterTA ( );
OPAImpExp          logical __cdecl RootBaseShared ( );
OPAImpExp          Error &__cdecl SDBError ( );
OPAImpExp          void __cdecl SetActiveHandle (int64 client_handle );
OPAImpExp          void __cdecl SetUtilityCB (UtilityHandle *utilitycb );
OPAImpExp          void __cdecl SetUtilityHandle (UtilityHandle *utilitycb );
OPAImpExp          void __cdecl ShareRootBase ( );
OPAImpExp          void __cdecl ShutDownODABA ( );
                   logical __cdecl StartPause (int32 wait_sec );
                   void __cdecl StopPause ( );
OPAImpExp          Services *__cdecl SystemServices ( );
                   void __cdecl ThreadException (int sign );
                   logical __cdecl UnlockGlobal ( );
                   void __cdecl UnregisterTA ( );
OPAImpExp          UtilityHandle *__cdecl UtilityControlBlock ( );
OPAImpExp          int32 __cdecl __TraceNodes (int32 max_count );

#if defined (__cplusplus)
             }
#endif
#endif
