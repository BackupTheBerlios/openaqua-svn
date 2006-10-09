/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    sosi

\brief    Global interface class


\date     $Date: 2006/08/27 20:29:22,65 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sosi_H
#define   sosi_H
#include "csosdll.h"

class     BNFParser;
class     ProcessInfo;
class     svel;
#include  <cProcVariableTypes.h>
#include  <cProcessVariableNames.h>
#include  <sError.hpp>
#include  <sNBuffer.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

SOSImpExp          logical __cdecl ConnectErrorHandle (Error *error_obj, ProcVariableTypes proc_vt, ProcessVariableNames pv_name );
SOSImpExp          void __cdecl ConnectSystemVariables (svel *svelptr );
SOSImpExp          BNFParser *__cdecl CreateParser (char *path, logical list_symbols, char *trace_path, char *bnf_path );
SOSImpExp          void __cdecl DisconnectSystemVariables (svel *svelptr );
SOSImpExp          int32 __cdecl ExecuteCommand (char *cmdline, NBuffer &nresult, logical err2out, logical erronly );
SOSImpExp          logical __cdecl ExecuteProgram (char *prgnams, char *pgmparm1, char *pgmparm2, char *pgmparm3, char *pgmparm4, char *pgmparm5 );
SOSImpExp          logical __cdecl GenerateParser (char *path, char *outpath, char *trace_path, char *bnf_path );
SOSImpExp          CTX_Base *__cdecl GetApplicationContext ( );
SOSImpExp          Error &__cdecl GetErrorObject (ProcessVariableNames pv_name );
SOSImpExp          char *__cdecl GetPosSysVariable (int16 indx, char *vnames );
SOSImpExp          int32 __cdecl GetProcessUseCount ( );
SOSImpExp          void *__cdecl GetProcessVariable (ProcessVariableNames pv_name );
SOSImpExp          char *__cdecl GetSectionVariable (char *vnames, char *sectionname );
SOSImpExp          char *__cdecl GetSysVariable (char *vnames );
SOSImpExp          char *__cdecl GetSysVariableINIFile (char *vnames );
SOSImpExp          char *__cdecl GetSysVariablePath (char *vnames, char *path, int32 maxlen );
SOSImpExp          int32 __cdecl GetThreadID ( );
SOSImpExp          void __cdecl PopSystemVariables ( );
SOSImpExp          void __cdecl PushSystemVariables ( );
SOSImpExp          char *__cdecl ReadSysVariable (char *vnames );
SOSImpExp          void __cdecl RegisterProcess ( );
SOSImpExp          void __cdecl RemoveSysVariable (char *vnames );
SOSImpExp          char *__cdecl ReplaceSysVariable (char *textstr, int32 maxlen );
SOSImpExp          Error &__cdecl SOSError ( );
SOSImpExp          ProcessInfo *__cdecl SOSInitProcessInfo ( );
SOSImpExp          void __cdecl SOSResources ( );
SOSImpExp          logical __cdecl SetApplicationContext (CTX_Base *ctxptr );
SOSImpExp          void __cdecl SetProcessVariable (ProcessVariableNames pv_name, void *proc_variable );
SOSImpExp          void __cdecl SetSysVarINIFile (char *inipath, char *sectionname );
SOSImpExp          logical __cdecl SetSysVariable (char *vnames, char *vtext );
SOSImpExp          logical __cdecl SetSystemVariables (svel *svelptr );
SOSImpExp          void __cdecl ShutDownProcess ( );
SOSImpExp          char *__cdecl SystemInput (char *string );
SOSImpExp          logical __cdecl SystemOutput (char *string, logical clear_opt, logical flush_opt );
SOSImpExp          svel *__cdecl SystemVariables ( );
SOSImpExp          logical __cdecl TestSysVariable (char *vnames, char *vtext );
SOSImpExp          void __cdecl UnregisterProcess ( );
SOSImpExp          char *__cdecl UpdateSysVariable (char *vnames, char *vtext );
SOSImpExp          int64 __cdecl htonb (int64 big_int );
SOSImpExp          int64 __cdecl ntohb (int64 big_val );

#if defined (__cplusplus)
             }
#endif
#endif
