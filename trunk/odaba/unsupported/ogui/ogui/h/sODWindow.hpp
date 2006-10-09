/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    ODWindow

\brief    Complex Window
          Complex  windows  usually  consists  of  several  QT  widgets,  which 
          describe different areas within the window.

\date     $Date: 2006/05/03 14:03:12,96 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODWindow_HPP
#define   ODWindow_HPP

class     ODWindow;

class     DPixmap;
class     ODataWidget;
class     OEHActionHandler;
#include  <cADK_HoriPos.h>
#include  <cADK_VertPos.h>
#include  <cOWindowTypes.h>
#include  <cSplitterTypes.h>
#include  <sDAlign.hpp>
#include  <sDMargin.hpp>
#include  <sDPoint.hpp>
#include  <sDSize.hpp>
#include  <sODControl.hpp>
class  ODWindow :public ODControl
{
protected  :         ODataWidget                                 *clientWidget;                                              
protected  :         OWindowTypes                                 win_type;                                                  

public     :
public     : virtual          OGUIImpExp            logical Activate ( );
public     :                  OGUIImpExp            logical CreateButtonGroup (logical vertical, logical exclusive );
public     : virtual          OGUIImpExp            logical CreateClientArea (char *control_name, logical is_workspace, int16 dsp_level, logical is_control, OWindowTypes win_type, logical vertical, logical exclusive );
public     :                  OGUIImpExp            logical CreateGroupBox (logical vertical );
public     : virtual          OGUIImpExp            logical CreateLabel (DSize &dsize, ADK_VertPos verti_pos, ADK_HoriPos hori_pos, char *label_text );
public     : virtual          OGUIImpExp            void CreateLayout (DSize &grid_size, DMargin &dmargin );
public     :                  OGUIImpExp            logical CreateSimpleWindow (logical is_workspace );
public     :                  OGUIImpExp            logical CreateSplitterWindow (logical vertical );
public     : virtual          OGUIImpExp            logical CreateWindowArea (char *control_name, logical is_modal, OWindowTypes win_style );
public     :                  OGUIImpExp                 ODWindow (ODControl *pODControl, char *names );
public     : virtual          OGUIImpExp            void UpdateLayout (DPoint &position, int16 inner_dist, int16 outer_dist, DSize &dsize, DSize &frame_size, DAlign &dalign, int16 dsp_level );
public     :                  OGUIImpExp            void UpdateScrollBars (logical has_hscroll, logical has_vscroll );
public     : virtual          OGUIImpExp                 ~ODWindow ( );
};

#endif
