/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DFont

\brief    Font definiton
          The  font  definition  defines  colors  and fonds for the text and the
          background color.

\date     $Date: 2006/03/13 21:33:36,34 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DFont_HPP
#define   DFont_HPP

class     DFont;

class     ODataLayout;
class     OFont;
class     PropertyHandle;
#include  <cADK_FontStyle.h>
#include  <cADK_FontStyleStrategy.h>
#include  <cADK_FontWeight.h>
#include  <sDColor.hpp>
class  DFont
{
protected  :         char                                         family_name[41];                                           // Family name for font
protected  :         ADK_FontWeight                               weight;                                                    // Weight
protected  :         int16                                        size;                                                      // Point size
protected  :         logical                                      use_pixel;                                                 //
protected  :         logical                                      italic;                                                    //
protected  :         logical                                      underline;                                                 //
protected  :         logical                                      overline;                                                  //
protected  :         logical                                      strike_out;                                                //
protected  :         logical                                      fixed_pitch;                                               //
protected  :         DColor                                       text_color;                                                //
protected  :         DColor                                       bg_color;                                                  //
protected  :         ADK_FontStyle                                style_hint;                                                //
protected  :         ADK_FontStyleStrategy                        style_strategy;                                            //
protected  :         logical                                      prefer_quality;                                            //
protected  :         int32                                        stretch;                                                   //

public     :
                     char                                        *get_family_name() { return(family_name); }
                     ADK_FontWeight                               get_weight() { return(weight); }
                     int16                                        get_size() { return(size); }
                     logical                                      get_use_pixel() { return(use_pixel); }
                     logical                                      get_italic() { return(italic); }
                     logical                                      get_underline() { return(underline); }
                     logical                                      get_overline() { return(overline); }
                     logical                                      get_strike_out() { return(strike_out); }
                     logical                                      get_fixed_pitch() { return(fixed_pitch); }
                     DColor                                      &get_text_color() { return(text_color); }
                     DColor                                      &get_bg_color() { return(bg_color); }
                     ADK_FontStyle                                get_style_hint() { return(style_hint); }
                     ADK_FontStyleStrategy                        get_style_strategy() { return(style_strategy); }
                     logical                                      get_prefer_quality() { return(prefer_quality); }
                     int32                                        get_stretch() { return(stretch); }
public     :         OGUI7ImpExp                                         DFont ( );
public     :         OGUI7ImpExp                                         DFont (OFont &rOFont );
public     :         OGUI7ImpExp                                         DFont (char *family_name, int16 weight, int16 font_size, logical use_pixel, logical italic, logical underline, logical overline, logical strike_out, logical fixed_pitch, DColor dtext_color, DColor dbg_color, int16 style_hint, int16 style_strategy, logical prefer_quality, int32 stretch );
public     :         OGUI7ImpExp                 logical FromADKFont (PropertyHandle *ph );
public     :                                     void FromODataLayout (ODataLayout *pODataLayout );
public     :                                     void FromOFont (OFont &rOFont );
public     :                                     logical IsEmpty ( );
public     :         OGUI7ImpExp                 void SetBGColor (DColor &bg_color );
public     :         OGUI7ImpExp                 void SetTextColor (DColor &text_color );
public     :         OGUI7ImpExp                 void SetWeight (ADK_FontWeight fweight );
public     :                                     OFont ToOFont ( );
};

#endif
