/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OApplicationO

\brief    


\date     $Date: 2006/07/31 12:15:38,81 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OApplicationO_HPP
#define   OApplicationO_HPP

class     OApplicationO;

#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     DAction;
class     DActionList;
class     ODesktopO;
#include  <sDMargin.hpp>
#include  <sODataWidget.hpp>
class  OApplicationO :public QApplication,
public ODataWidget
{
protected  :         ODesktopO                                   *desk_top;                                                  // 
protected  :         ODataWidget                                 *last_focus_out;                                            // 
protected  :         char                                       **argv;                                                      // 
protected  :         DActionList                                 *default_actions;                                           // 

public     :
                     ODesktopO                                   *get_desk_top() { return(desk_top); }
                     char                                       **get_argv() { return(argv); }
                     DActionList                                 *get_default_actions() { return(default_actions); }
public     :                  OGUIImpExp            DAction *AddDefaultAction (DAction *pDAction );
public     :                  OGUIImpExp            int8 ArgumentCount ( );
public     :                                        logical CheckQueryOption (char *option_string );
public     :                  OGUIImpExp            DAction *GetDefaultAction (const char *act_namesc );
public     :                                        ODataWidget *GetLastFocusWidget ( );
public     :                  OGUIImpExp                 OApplicationO (int &argc, char **argv, logical gui_app );
public     :                                        void SetLastFocusWidget (ODataWidget *pODataWidget );
public     :                                        QWidget *WidgetQ ( );
public     :                  OGUIImpExp            ODesktopO *desktop ( );
public     :                  OGUIImpExp                 ~OApplicationO ( );
};

#endif
