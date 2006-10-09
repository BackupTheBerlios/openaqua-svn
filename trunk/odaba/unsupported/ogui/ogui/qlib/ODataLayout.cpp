/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODataLayout

\brief    


\date     $Date: 2006/03/13 21:35:31,59 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODataLayout"

#include  <pogui7.h>
#include  <sDFont.hpp>
#include  <sOFont.hpp>
#include  <sODataLayout.hpp>


/******************************************************************************/
/**
\brief  GetBackgroundColor - 


\return pQColor -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBackgroundColor"

QColor *ODataLayout :: GetBackgroundColor ( )
{

  return ( this ? bg_color : NULL );

}

/******************************************************************************/
/**
\brief  GetFont - 


\return pQFont - QT - Font

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

QFont *ODataLayout :: GetFont ( )
{

  return ( this ? font : NULL );

}

/******************************************************************************/
/**
\brief  GetHelp - 


\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHelp"

char *ODataLayout :: GetHelp ( )
{

  return ( this ? help : NULL );

}

/******************************************************************************/
/**
\brief  GetIcon - 


\return pQIcon -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIcon"

QIcon *ODataLayout :: GetIcon ( )
{

  return ( this ? icon : NULL );

}

/******************************************************************************/
/**
\brief  GetLayout - 


\return font -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLayout"

DFont ODataLayout :: GetLayout ( )
{
  DFont     dfont;
  dfont.FromODataLayout(this);
  return(dfont);
}

/******************************************************************************/
/**
\brief  GetTextColor - 


\return pQColor -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextColor"

QColor *ODataLayout :: GetTextColor ( )
{

  return ( this ? text_color : NULL );

}

/******************************************************************************/
/**
\brief  GetToolTip - 


\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetToolTip"

char *ODataLayout :: GetToolTip ( )
{

  return ( this ? tooltip : NULL );

}

/******************************************************************************/
/**
\brief  HasLayout

\return cond -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasLayout"

logical ODataLayout :: HasLayout ( )
{

  return ( font || text_color || bg_color ? YES : NO );

}

/******************************************************************************/
/**
\brief  ODataLayout - 



\param  is_owner -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODataLayout"

                        ODataLayout :: ODataLayout (logical is_owner )
                     : icon(NULL),
  font(NULL),
  text_color(NULL),
  bg_color(NULL),
  help(NULL),
  tooltip(NULL),
  owner(is_owner)
{



}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void ODataLayout :: Reset ( )
{

  if ( owner )
  {
    delete icon;
    delete font;
    delete text_color;
    delete bg_color;
    if ( help )
      free(help);
    if ( tooltip )
      free(tooltip);
  }
  icon       = NULL;
  font       = NULL;
  text_color = NULL;
  bg_color   = NULL;
  help       = NULL;
  tooltip    = NULL;


}

/******************************************************************************/
/**
\brief  SetBackgroundColor - 



\param  pQColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBackgroundColor"

void ODataLayout :: SetBackgroundColor (QColor *pQColor )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( owner )
  {
    delete bg_color;
    bg_color = new QColor(*pQColor);
  }
  else
    bg_color = pQColor;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetFont - 



\param  pQFont - QT - Font
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

void ODataLayout :: SetFont (QFont *pQFont )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( owner )
  {
    delete font;
    font = new QFont(*pQFont);
  }
  else
    font = pQFont;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetHelp - 



\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHelp"

void ODataLayout :: SetHelp (char *string )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( owner )
  {
    if ( help ) 
      free(help);
    help = strdup(string);
  }
  else
    help = string;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetIcon - 



\param  pQIcon -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

void ODataLayout :: SetIcon (QIcon *pQIcon )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( owner )
  {
    delete icon;
    icon = new QIcon(*pQIcon);
  }
  else
    icon = pQIcon;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetLayout - 



\param  pDFont -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLayout"

void ODataLayout :: SetLayout (DFont *pDFont )
{
  OFont           ofont;
BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( owner )
  {
    delete font;
    delete bg_color;
    delete text_color;
  }
  font       = NULL;
  text_color = NULL;
  bg_color   = NULL;

  if ( !owner || !pDFont )                           OGUIERR(99)
  ofont.FromDFont(*pDFont);
  
  font       = new QFont(ofont);
  text_color = new QColor(ofont.get_text_color());
  bg_color   = new QColor(ofont.get_bg_color());

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetTextColor - 



\param  pQColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextColor"

void ODataLayout :: SetTextColor (QColor *pQColor )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( owner )
  {
    delete text_color;
    text_color = new QColor(*pQColor);
  }
  else
    text_color = pQColor;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetToolTip - 



\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetToolTip"

void ODataLayout :: SetToolTip (char *string )
{

BEGINSEQ
  if ( !this )                                       ERROR
    
  if ( owner )
  {
    if ( tooltip ) 
      free(tooltip);
    tooltip = strdup(string);
  }
  else
    tooltip = string;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~ODataLayout - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODataLayout"

                        ODataLayout :: ~ODataLayout ( )
{

  Reset();

}


