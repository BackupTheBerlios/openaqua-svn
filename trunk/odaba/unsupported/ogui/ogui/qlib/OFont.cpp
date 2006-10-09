/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OFont

\brief    Internal Font definition
          The   internal   font   definition   contains   the  QT-Font and color
          specifications for text and background.
          IMPORTANT: DFont must be included as pointer.

\date     $Date: 2006/03/13 21:35:53,10 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OFont"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#include  <sDFont.hpp>
#include  <sOFont.hpp>


/******************************************************************************/
/**
\brief  FromDFont - 



\param  rDFont -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromDFont"

void OFont :: FromDFont (DFont &rDFont )
{
  int       size = rDFont.get_size();
  setFamily(SZ2QS(rDFont.get_family_name()));
  setWeight(rDFont.get_weight());
  setItalic(rDFont.get_italic());
  setUnderline(rDFont.get_underline());
  setStrikeOut(rDFont.get_strike_out());
  setFixedPitch(rDFont.get_fixed_pitch());
  setStretch(rDFont.get_stretch() <= 0 ? 100 : rDFont.get_stretch());
  setStyleHint((QFont::StyleHint)rDFont.get_style_hint());
  setStyleStrategy((QFont::StyleStrategy)(rDFont.get_style_strategy()+
                                          rDFont.get_prefer_quality() ? QFont::PreferQuality : 0));

  if ( size )
  {
    if ( rDFont.get_use_pixel() )
      setPixelSize(size);
    else 
      setPointSize(size);
  }
  if ( rDFont.get_text_color().IsValid() )
    text_color = DCOLOR2QCOLOR(rDFont.get_text_color());
  if ( rDFont.get_bg_color().IsValid() )
    bg_color = DCOLOR2QCOLOR(rDFont.get_bg_color());


}

/******************************************************************************/
/**
\brief  OFont - Konstruktor


-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFont"

                        OFont :: OFont ( )
                     : QFont (),
  text_color(),
  bg_color()
{



}

/******************************************************************************/
/**
\brief  i01


\param  rDFont -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFont"

                        OFont :: OFont (DFont &rDFont )
                     : QFont (),
  text_color(),
  bg_color()
{

  FromDFont(rDFont);

}

/******************************************************************************/
/**
\brief  i02


\param  rcQFont -
\param  rcQForegroundColor -
\param  rcQBackgroundColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFont"

                        OFont :: OFont (const QFont &rcQFont, const QColor &rcQForegroundColor, const QColor &rcQBackgroundColor )
                     : QFont(rcQFont),
text_color(rcQForegroundColor),
bg_color(rcQBackgroundColor)

{



}

/******************************************************************************/
/**
\brief  SetBGColor - Set background color



\param  qbg_color - QT background color
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBGColor"

void OFont :: SetBGColor (QColor &qbg_color )
{

  bg_color = qbg_color;

}

/******************************************************************************/
/**
\brief  SetFont - Set font



\param  rQFont -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

void OFont :: SetFont (QFont &rQFont )
{

  *(QFont *)this = rQFont;

}

/******************************************************************************/
/**
\brief  SetTextColor - Set text color



\param  qtext_color - QT text color
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextColor"

void OFont :: SetTextColor (QColor &qtext_color )
{

  text_color = qtext_color;

}

/******************************************************************************/
/**
\brief  ToDFont - Convert to DFont


\return font -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToDFont"

DFont OFont :: ToDFont ( )
{
  DFont           font;
  if ( this )
    font.FromOFont(*this);
  return(font);
}


