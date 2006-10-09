/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ODTabControl

\brief    Tab Control
          Tab  Controls  are  complex  windows, which are displayed on different
          levels.  Each tab  in a  tab controls  has its own window area to draw
          the elements assigned to the tab control. 
          Adding  field controls, which  are not windows,  to a tab control will
          create  static  controls  which  are  displayed  independently  on the
          selected tab. 
          New  tabs  can  be  creates  with  the  CreateSubWindow  function. The
          function  should be calles  after creating all  static elements in the
          tab  control.  The  function  determins  the  free area below the last
          static  control or  tries to  locate the  window according to size and
          position as defined for window.

\date     $Date: 2006/07/18 18:12:37,51 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODTabControl_HPP
#define   ODTabControl_HPP

class     ODTabControl;

class     ODTabControl;
class     ODWindow;
class     ODataWidget;
#include  <sDAlign.hpp>
#include  <sDMargin.hpp>
#include  <sDPoint.hpp>
#include  <sDSize.hpp>
#include  <sODControl.hpp>
class  ODTabControl :public ODControl
{

public     :
public     : virtual                                logical ActivateElements (logical act_curent );
public     : virtual          OGUIImpExp            void CreateLayout (DSize &grid_size, DMargin &dmargin );
public     : virtual          OGUIImpExp            ODWindow *CreateSubWindow (char *names );
public     :                  OGUIImpExp            logical CreateTab (ODControl *pODControl, char *label_text );
public     : virtual          OGUIImpExp            ODControl *GetActiveControl ( );
public     :                                        ODControl *GetSubWindow (int16 dsp_level );
public     : virtual          OGUIImpExp            ODTabControl *GetTabControl ( );
public     :                  OGUIImpExp                 ODTabControl (ODControl *pODControl, char *names );
public     :                                        ODataWidget *PanelWidgetParent ( );
public     :                                        void SetTabText (char *label_text, int16 dsp_level );
public     : virtual          OGUIImpExp            void UpdateLayout (DPoint &position, int16 inner_dist, int16 outer_dist, DSize &dsize, DSize &frame_size, DAlign &dalign, int16 dsp_level );
public     : virtual          OGUIImpExp                 ~ODTabControl ( );
};

#endif
