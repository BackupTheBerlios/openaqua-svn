/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    igui

\brief    Static service functions
          This  class summerizes  a number  of static service functions availble
          for GUI applications.

\date     $Date: 2006/07/24 20:51:29,25 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   igui_H
#define   igui_H

class     OApplicationO;
class     ODataWidget;
class     OEHDataWidget;
class     OListView;
#include  <sError.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

OGUIImpExp         void __cdecl FlushEvents ( );
OGUIImpExp         OApplicationO *__cdecl GetApplication ( );
OGUIImpExp         char *__cdecl GetFilePath (char *caption, char *cpath, char *filter, logical write_opt, ODataWidget *parent_widget );
                   QWidget *__cdecl GetGUIParent (ODataWidget *parent_widget );
OGUIImpExp         Error &__cdecl GetOGUIErrorObject (ProcessVariableNames pv_name );
                   logical __cdecl GetSearchString (OEHDataWidget *pOEHDataWidget, char *caption, char *clabel );
OGUIImpExp         char *__cdecl GetString (char *caption, char *clabel, char *init_string, ODataWidget *parent_widget );
OGUIImpExp         logical __cdecl IsBusy (logical wait_opt );
OGUIImpExp         Error &__cdecl OGUIError ( );
OGUIImpExp         ProcessInfo *__cdecl OGUIInitProcessInfo ( );
OGUIImpExp         void __cdecl OGUIResources ( );
OGUIImpExp         logical __cdecl Quit ( );
OGUIImpExp         void __cdecl SetBusy (logical wait_opt );

#if defined (__cplusplus)
             }
#endif
#endif
