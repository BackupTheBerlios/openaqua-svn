/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OEHActionDefinition

\brief    


\date     $Date: 2006/07/05 23:34:33,68 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHActionDefinition_HPP
#define   OEHActionDefinition_HPP

class     OEHActionDefinition;

class     DFont;
class     DPixmap;
class     OFont;
class     OIconSet;
class  OEHActionDefinition
{
protected  :         char                                         name[41];                                                  // 
protected  :         char                                        *text;                                                      // 
protected  :         char                                        *short_cut;                                                 // 
protected  :         OIconSet                                    *icon;                                                      // 
protected  :         OFont                                       *font;                                                      // 

public     :
                     char                                        *get_name() { return(name); }
                     char                                        *get_text() { return(text); }
                     char                                        *get_short_cut() { return(short_cut); }
                     OIconSet                                    *get_icon() { return(icon); }
                     OFont                                       *get_font() { return(font); }
public     :                                        void Initialize (char *names, char *displ_text, char *shortcut, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, DFont *pDFont );
public     :                                             OEHActionDefinition (char *names, char *displ_text, char *shortcut, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, DFont *pDFont );
public     :                                             ~OEHActionDefinition ( );
};

#endif
