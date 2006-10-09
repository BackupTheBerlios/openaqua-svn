/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OGUI

\brief    Static service functions
          This  class summerizes  a number  of static service functions availble
          for GUI applications.

\date     $Date: 2006/03/13 21:34:17,23 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OGUI_H
#define   OGUI_H

class     OApplicationO;
class     ODataWidget;
class     OEHDataWidget;
class     OListView;

#if defined (__cplusplus)
  extern "C" {
#endif

OGUI7ImpExp        void __cdecl FlushEvents ( );
                   OApplicationO *__cdecl GetApplication ( );
OGUI7ImpExp        Error &__cdecl GetOGUIErrorObject (ProcessVariableNames pv_name );
                   logical __cdecl GetSearchString (OEHDataWidget *pOEHDataWidget, char *caption, char *clabel );
OGUI7ImpExp        char *__cdecl GetString (char *caption, char *clabel, char *init_string, ODataWidget *parent_widget );
OGUI7ImpExp        logical __cdecl IsBusy (logical wait_opt );
OGUI7ImpExp        Error &__cdecl OGUIError ( );
OGUI7ImpExp        ProcessInfo *__cdecl OGUIInitProcessInfo ( );
OGUI7ImpExp        logical __cdecl Quit ( );
OGUI7ImpExp        void __cdecl SetBusy (logical wait_opt );

#if defined (__cplusplus)
             }
#endif
#endif
