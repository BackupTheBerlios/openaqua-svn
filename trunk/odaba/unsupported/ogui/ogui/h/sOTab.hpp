/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OTab

\brief    Tab-Control
          The  class defines a  tab-control, which might  consist of one or more
          tab-items.  Tabs for the items can be  arranged on top or on buttom as
          large  (round)  or  small  (triangular)  tabs. Each item is associated
          with  a  separate  control  (window),  which is shown, when the tab is
          selected.  A tab-control may contain one  fixed child window, which is
          displayed for all tab items.

\date     $Date: 2006/07/03 17:13:19,23 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTab_HPP
#define   OTab_HPP

class     OTab;

class     DBStructDef;
class     DPixmap;
class     ODS;
class     OIconSet;
class     OWidget;
class     OWidgetStack;
class     PropertyHandle;
#include  <sODataWidget.hpp>
#include  <sOFrame.hpp>
class  OTab :public OFrame
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         QVBoxLayout                                 *vlayout;                                                   // 
protected  :         QTabBar                                     *tabbar;                                                    // 
protected  :         OWidgetStack                                *panels;                                                    // 
protected  :         logical                                      tab_top;                                                   // 
protected  :         logical                                      fix_top;                                                   // 
protected  :         OWidget                                     *static_area;                                               // 
protected  :         int32                                        tab_count;                                                 // 

public     :
                     OWidget                                     *get_static_area() { return(static_area); }
                     int32                                        get_tab_count() { return(tab_count); }
public     : virtual          OGUIImpExp            logical Activate ( );
public     :                                        void ActivateFirstTab ( );
public     : public slots:                          void ActivateTab (int int_index );
public     :                  OGUIImpExp            logical AddElement (ODataWidget *child, const QString label, int32 tab_index );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
public     :                                        QFrame *FrameQ ( );
public     :                                        ODataWidget *GetActiveTab ( );
public     :                                        PropertyHandle *GetCurrentPropertyHandle ( );
public     :                  OGUIImpExp                 OTab (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL, logical tb_upper=YES, logical tb_normal=YES, logical stb_upper=YES, char dyn_opt=NO );
public     :                                        OWidgetStack *Panels ( );
public     : virtual                                logical SetDefaultReactions ( );
public     : virtual                                logical SetDisplayLevel (int16 dsp_level );
public     : public slots:                          void SetDynamicTab ( );
public     :                  OGUIImpExp            void SetFixed (ODataWidget *child );
public     :                  OGUIImpExp            void SetFrame (int64 fstyle, int64 lwidth );
public     :                  OGUIImpExp            void SetMargin (int width );
public     :                  OGUIImpExp            void SetTabIcon (QIcon *pQIcon, int16 dsp_level );
public     :                  OGUIImpExp            void SetTabText (char *label_text, int16 dsp_level );
public     : virtual                                logical SetType (PropertyHandle *prophdl );
public     : virtual                                logical SetType (char *typenames );
public     : virtual                                logical SetType (DBStructDef *struct_def );
public     :                                        logical UpdateLayout ( );
public     : virtual                                void polish ( );
protected  : virtual          OGUIImpExp            void resizeEvent (QResizeEvent *resize_event );
public     : virtual                                void show ( );
protected  : virtual          OGUIImpExp            void showEvent (QShowEvent *show_event );
public     :                  OGUIImpExp                 ~OTab ( );
};

#endif
