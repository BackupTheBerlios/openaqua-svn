/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    DFont

\brief    Font definiton
          The  font  definition  defines  colors  and fonds for the text and the
          background color.

\date     $Date: 2006/06/01 16:57:26,32 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DFont"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <cqt.h>
#include  <sODataLayout.hpp>
#include  <sOFont.hpp>
#include  <sPropertyHandle.hpp>
#include  <sDFont.hpp>


/******************************************************************************/
/**
\brief  DFont - Konstruktor


-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DFont"

     DFont :: DFont ( )
                     : family_name(),
  weight(FW_Normal),
  size(12),
  use_pixel(NO),
  italic(NO),
  underline(NO),
  overline(NO),
  strike_out(NO),
  fixed_pitch(NO),
  text_color(),
  bg_color(),
  style_hint(FS_undefined),
  style_strategy(FSS_undefined),
  prefer_quality(NO),
  stretch(100)
{

  family_name[0] = 0;

}

/******************************************************************************/
/**
\brief  i01 - 


\param  rOFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DFont"

     DFont :: DFont (OFont &rOFont )
                     : family_name(),
  weight(FW_Normal),
  size(12),
  use_pixel(NO),
  italic(NO),
  underline(NO),
  overline(NO),
  strike_out(NO),
  fixed_pitch(NO),
  text_color(),
  bg_color(),
  style_hint(FS_undefined),
  style_strategy(FSS_undefined),
  prefer_quality(NO),
  stretch(100)
{

  FromOFont(rOFont);

}

/******************************************************************************/
/**
\brief  i02 - 


\param  family_name - 
\param  weight - 
\param  font_size - 
\param  use_pixel - 
\param  italic - 
\param  underline - 
\param  overline - 
\param  strike_out - 
\param  fixed_pitch - 
\param  dtext_color - 
\param  dbg_color - 
\param  style_hint - 
\param  style_strategy - 
\param  prefer_quality - 
\param  stretch - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DFont"

     DFont :: DFont (char *family_name, int16 weight, int16 font_size, logical use_pixel, logical italic, logical underline, logical overline, logical strike_out, logical fixed_pitch, DColor dtext_color, DColor dbg_color, int16 style_hint, int16 style_strategy, logical prefer_quality, int32 stretch )
                     : family_name(), //strdup
  weight((ADK_FontWeight)weight),
  size(font_size),
  use_pixel(use_pixel),
  italic(italic),
  underline(underline),
  overline(overline),
  strike_out(strike_out),
  fixed_pitch(fixed_pitch),
  text_color(dtext_color),
  bg_color(dbg_color),
  style_hint((ADK_FontStyle)style_hint),
  style_strategy(
    (ADK_FontStyleStrategy)style_strategy
  ),
  prefer_quality(prefer_quality),
  stretch(stretch)
{

memset(this->family_name,0,sizeof(this->family_name));
if(family_name && *family_name)
  strncpy(this->family_name,family_name,sizeof(this->family_name));
/*
  "DFont("
  + "\"" + family + "\""
  + ", " + weight
  + ", " + size
  + ", " + size_is_pixel
  + ", " + italic
  + ", " + underline
  + ", " + overline
  + ", " + strike_out
  + ", " + fixed_pitch
  + ", " + fg_color.Generate()
  + ", " + bg_color.Generate()
  + ", " + style_hint
  + ", " + style_strategy
  + ", " + prefer_quality
  + ", " + stretch
  + ")";

*/

}

/******************************************************************************/
/**
\brief  FromADKFont - 


\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromADKFont"

logical DFont :: FromADKFont (PropertyHandle *ph )
{
  logical                 term = NO;
  strcpy(family_name,ph->GetString( "family" ));
  weight               = (ADK_FontWeight)ph->GetInt( "weight" );
  size                 = ph->GetInt( "size" );
  use_pixel            = ph->GetInt( "size_is_pixel" );
  fixed_pitch          = ph->GetInt( "fixed_pitch" );
  italic               = ph->GetInt( "italic" );
  underline            = ph->GetInt( "underline" );
  overline             = ph->GetInt( "overline" );
  strike_out           = ph->GetInt( "strike_out" );
  stretch              = ph->GetInt( "strech" );
  style_hint           = (ADK_FontStyle)ph->GetInt( "style_hint" );
  style_strategy       = (ADK_FontStyleStrategy)ph->GetInt( "style_strategy" );
  prefer_quality       = ph->GetInt( "prefer_quality" );
  text_color           = COLOR2DCOLOR(*ph->GPH("fg_color"));
  bg_color             = COLOR2DCOLOR(*ph->GPH("bg_color"));

  return(term);
}

/******************************************************************************/
/**
\brief  FromODataLayout - 



\param  pODataLayout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromODataLayout"

void DFont :: FromODataLayout (ODataLayout *pODataLayout )
{
  QFont    *qfont  = NULL;
  QColor   *qcolor = NULL;
BEGINSEQ
  if ( !pODataLayout )                               LEAVESEQ
    
  if ( qfont = pODataLayout->get_font() )
  {  
    strcpy(family_name,QS2SZ(qfont->family()));
    weight         = (ADK_FontWeight)qfont->weight();
    italic         = qfont->italic();
    underline      = qfont->underline();
    strike_out     = qfont->strikeOut();
    fixed_pitch    = qfont->fixedPitch();
    style_hint     = (ADK_FontStyle)qfont->styleHint();
    style_strategy = (ADK_FontStyleStrategy)qfont->styleStrategy();
    stretch        = qfont->stretch();
  }
  
  prefer_quality = NO;
  if ( style_strategy && QFont::PreferQuality )
  {
    prefer_quality = YES;
    style_strategy = (ADK_FontStyleStrategy)(style_strategy - QFont::PreferQuality);
  }
  
  if ( qcolor = pODataLayout->get_text_color() )
    text_color = QCOLOR2DCOLOR(*qcolor); 
  if ( qcolor = pODataLayout->get_bg_color() )
    bg_color = QCOLOR2DCOLOR(*qcolor);

  use_pixel = NO;
  if ( (size = qfont->pointSize()) == -1 )  // pixel size used
  {
    use_pixel = YES;
    size = qfont->pixelSize();
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  FromOFont - 



\param  rOFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromOFont"

void DFont :: FromOFont (OFont &rOFont )
{

  strcpy(family_name,QS2SZ(rOFont.family()));
  weight         = (ADK_FontWeight)rOFont.weight();
  italic         = rOFont.italic();
  underline      = rOFont.underline();
  strike_out     = rOFont.strikeOut();
  fixed_pitch    = rOFont.fixedPitch();
  style_hint     = (ADK_FontStyle)rOFont.styleHint();
  style_strategy = (ADK_FontStyleStrategy)rOFont.styleStrategy();
  stretch        = rOFont.stretch();
  
  prefer_quality = NO;
  if ( style_strategy && QFont::PreferQuality )
  {
    prefer_quality = YES;
    style_strategy = (ADK_FontStyleStrategy)(style_strategy - QFont::PreferQuality);
  }
  
  text_color     = QCOLOR2DCOLOR(rOFont.get_text_color()); 
  bg_color       = QCOLOR2DCOLOR(rOFont.get_bg_color());

  use_pixel = NO;
  if ( (size = rOFont.pointSize()) == -1 )  // pixel size used
  {
    use_pixel = YES;
    size = rOFont.pixelSize();
  }


}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical DFont :: IsEmpty ( )
{

  return ( *family_name );

}

/******************************************************************************/
/**
\brief  SetBGColor - Set Background color



\param  bg_color - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBGColor"

void DFont :: SetBGColor (DColor &bg_color )
{

  this->bg_color = bg_color;

  if ( !family_name ) 
    *family_name = ' ';  // not empty


}

/******************************************************************************/
/**
\brief  SetTextColor - Set text color



\param  text_color - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextColor"

void DFont :: SetTextColor (DColor &text_color )
{

  this->text_color = text_color;

  if ( !family_name ) 
    *family_name = ' ';  // not empty


}

/******************************************************************************/
/**
\brief  SetWeight - 



\param  fweight - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWeight"

void DFont :: SetWeight (ADK_FontWeight fweight )
{

  weight = fweight;

  if ( !family_name ) 
    *family_name = ' ';  // not empty


}

/******************************************************************************/
/**
\brief  ToOFont - Concert to QT font and colors


\return font - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToOFont"

OFont DFont :: ToOFont ( )
{
  OFont          font;
  font.FromDFont(*this);
  return(font);
}


