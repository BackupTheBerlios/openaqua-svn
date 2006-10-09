/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    OGUI_Interface

\brief    


\date     $Date: 2006/03/12 19:40:03,03 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OGUI_Interface_H
#define   OGUI_Interface_H

class     UCTX_dll;
#include  <standard.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

ODCP8ImpExp        int __cdecl CreateAppl (HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow );
ODCP8ImpExp        int __cdecl CreateConsoleAppl (int argc, char **argv );
                   ProcessInfo *__cdecl GUIInitProcessInfo ( );
ODCP8ImpExp        Error &__cdecl GetGUIErrorObject (ProcessVariableNames pv_name );
ODCP8ImpExp        Error &__cdecl OADIError ( );
ODCP8ImpExp        Error &__cdecl OGUIError ( );
ODCP8ImpExp        Error &__cdecl P_Error ( );
                   UCTX_dll *__cdecl UDLL_Handle ( );

#if defined (__cplusplus)
             }
#endif
#endif
