/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    odei



\date     $Date: 2006/05/22 11:14:04,96 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   odei_H
#define   odei_H

class     pODE;

#if defined (__cplusplus)
  extern "C" {
#endif

                   pODE *__cdecl ODEContext (CTX_GUIBase *ctxptr );
                   char *__cdecl ODEOption (CTX_GUIBase *ctxptr, char *option_name );
                   logical __cdecl ODEOptionIsOn (CTX_GUIBase *ctxptr, char *option_name );
                   logical __cdecl ODEOutput (CTX_GUIBase *ctxptr, char *string, logical clear_opt );

#if defined (__cplusplus)
             }
#endif
#endif
