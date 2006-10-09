/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OFont

\brief    Internal Font definition
          The   internal   font   definition   contains   the  QT-Font and color
          specifications for text and background.
          IMPORTANT: DFont must be included as pointer.

\date     $Date: 2006/03/13 21:34:16,67 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OFont_HPP
#define   OFont_HPP

class     OFont;

class     DFont;
class  OFont :public QFont
{
protected  :         char                                         name[40];                                                  // QT Text color
protected  :         QColor                                       text_color;                                                // QT background color
protected  :         QColor                                       bg_color;                                                  //

public     :
                     char                                        *get_name() { return(name); }
                     QColor                                      &get_text_color() { return(text_color); }
                     QColor                                      &get_bg_color() { return(bg_color); }
public     :                                     void FromDFont (DFont &rDFont );
public     :         OGUI7ImpExp                                         OFont ( );
public     :         OGUI7ImpExp                                         OFont (DFont &rDFont );
public     :         OGUI7ImpExp                                         OFont (const QFont &rcQFont, const QColor &rcQForegroundColor, const QColor &rcQBackgroundColor );
public     :         OGUI7ImpExp                 void SetBGColor (QColor &qbg_color );
public     :         OGUI7ImpExp                 void SetFont (QFont &rQFont );
public     :         OGUI7ImpExp                 void SetTextColor (QColor &qtext_color );
public     :                                     DFont ToDFont ( );
};

#endif
