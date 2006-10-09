/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODataLayout

\brief    


\date     $Date: 2006/03/13 21:34:00,87 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODataLayout_HPP
#define   ODataLayout_HPP

class     ODataLayout;

#include  <sDFont.hpp>
class  ODataLayout
{
protected  :         QIcon                                       *icon;                                                      //
protected  :         QFont                                       *font;                                                      //
protected  :         QColor                                      *text_color;                                                //
protected  :         QColor                                      *bg_color;                                                  //
protected  :         char                                        *help;                                                      //
protected  :         char                                        *tooltip;                                                   //
protected  :         logical                                      owner;                                                     //

public     :
                     QFont                                       *get_font() { return(font); }
                     QColor                                      *get_text_color() { return(text_color); }
                     QColor                                      *get_bg_color() { return(bg_color); }
                     char                                        *get_help() { return(help); }
                     char                                        *get_tooltip() { return(tooltip); }
                     logical                                      get_owner() { return(owner); }
public     :                                     QColor *GetBackgroundColor ( );
public     :                                     QFont *GetFont ( );
public     :                                     char *GetHelp ( );
public     :                                     QIcon *GetIcon ( );
public     :                                     DFont GetLayout ( );
public     :                                     QColor *GetTextColor ( );
public     :                                     char *GetToolTip ( );
public     :                                     logical HasLayout ( );
public     :                                                             ODataLayout (logical is_owner );
public     :                                     void Reset ( );
public     :                                     void SetBackgroundColor (QColor *pQColor );
public     :                                     void SetFont (QFont *pQFont );
public     :                                     void SetHelp (char *string );
public     :                                     void SetIcon (QIcon *pQIcon );
public     :                                     void SetLayout (DFont *pDFont );
public     :                                     void SetTextColor (QColor *pQColor );
public     :                                     void SetToolTip (char *string );
public     :                                                             ~ODataLayout ( );
};

#endif
