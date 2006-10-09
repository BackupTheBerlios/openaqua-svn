/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    DAction

\brief    


\date     $Date: 2006/07/09 13:28:55,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DAction_HPP
#define   DAction_HPP

class     DAction;

class     DFont;
class     DPixmap;
class     OFont;
class     OIconSet;
class  DAction
{
protected  :         char                                         name[40];                                                  // 
protected  :         logical                                      disabled;                                                  // 
protected  :         char                                        *text;                                                      // 
protected  :         char                                        *tool_tip;                                                  // 
protected  :         char                                        *help;                                                      // 
protected  :         char                                        *short_cut;                                                 // 
protected  :         OIconSet                                    *icon;                                                      // 
protected  :         OFont                                       *font;                                                      // 

public     :
                     char                                        *get_name() { return(name); }
                     logical                                      get_disabled() { return(disabled); }
                     char                                        *get_text() { return(text); }
                     char                                        *get_tool_tip() { return(tool_tip); }
                     char                                        *get_help() { return(help); }
                     char                                        *get_short_cut() { return(short_cut); }
                     OIconSet                                    *get_icon() { return(icon); }
                     OFont                                       *get_font() { return(font); }
public     :                  OGUIImpExp                 DAction (char *act_names );
public     :                                        logical HasText ( );
public     :                  OGUIImpExp            void Initialize (char *names, logical fDisabled, char *displ_text, char *tip, char *what, char *shortcut, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, DFont *pDFont );
public     :                  OGUIImpExp            logical IsDisabled ( );
public     :                  OGUIImpExp                 ~DAction ( );
};

#endif
