/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODataLayoutRef

\brief    


\date     $Date: 2006/03/13 21:35:32,10 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODataLayoutRef"

#include  <pogui7.h>
#include  <sDFont.hpp>
#include  <sDPixmap.hpp>
#include  <sODataLayout.hpp>
#include  <sOIconSet.hpp>
#include  <sODataLayoutRef.hpp>


/******************************************************************************/
/**
\brief  GetBackgroundColor - 


\return pQColor -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBackgroundColor"

QColor *ODataLayoutRef :: GetBackgroundColor ( )
{

  return ( this ? layout->GetBackgroundColor() : NULL );

}

/******************************************************************************/
/**
\brief  GetFont - 


\return pQFont - QT - Font

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

QFont *ODataLayoutRef :: GetFont ( )
{

  return ( this ? layout->GetFont() : NULL );

}

/******************************************************************************/
/**
\brief  GetHelp - 


\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHelp"

char *ODataLayoutRef :: GetHelp ( )
{

  return ( this ? layout->GetHelp() : NULL );

}

/******************************************************************************/
/**
\brief  GetIcon - 


\return pQIcon -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIcon"

QIcon *ODataLayoutRef :: GetIcon ( )
{

  return ( this ? layout->GetIcon() : NULL );

}

/******************************************************************************/
/**
\brief  GetLayout - 


\return dfont -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLayout"

DFont ODataLayoutRef :: GetLayout ( )
{
  static DFont  empty_dfont;
  return ( this && layout ? layout->GetLayout() : empty_dfont );

}

/******************************************************************************/
/**
\brief  GetTextColor - 


\return pQColor -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextColor"

QColor *ODataLayoutRef :: GetTextColor ( )
{

  return ( this ? layout->GetTextColor() : NULL );

}

/******************************************************************************/
/**
\brief  GetToolTip - 


\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetToolTip"

char *ODataLayoutRef :: GetToolTip ( )
{

  return ( this ? layout->GetToolTip() : NULL );

}

/******************************************************************************/
/**
\brief  HasLayout - 


\return cond -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasLayout"

logical ODataLayoutRef :: HasLayout ( )
{

  return ( this && layout ? layout->HasLayout() : NO );

}

/******************************************************************************/
/**
\brief  ODataLayoutRef - 



\param  is_owner -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODataLayoutRef"

                        ODataLayoutRef :: ODataLayoutRef (logical is_owner )
                     :   layout(NULL)
{

  if ( is_owner )
    ProvideDataLayout(is_owner);

}

/******************************************************************************/
/**
\brief  ProvideDataLayout - 



\param  is_owner -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDataLayout"

void ODataLayoutRef :: ProvideDataLayout (logical is_owner )
{

  if ( !layout ) 
    layout = new ODataLayout(is_owner);

}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void ODataLayoutRef :: Reset ( )
{

  if ( layout )
    layout->Reset();

}

/******************************************************************************/
/**
\brief  SetBackgroundColor - 



\param  pQColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBackgroundColor"

void ODataLayoutRef :: SetBackgroundColor (QColor *pQColor )
{

  ProvideDataLayout(NO);

  layout->SetBackgroundColor(pQColor);

}

/******************************************************************************/
/**
\brief  SetFont - 



\param  pQFont - QT - Font
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

void ODataLayoutRef :: SetFont (QFont *pQFont )
{

  ProvideDataLayout(NO);

  layout->SetFont(pQFont);

}

/******************************************************************************/
/**
\brief  SetHelp - 



\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHelp"

void ODataLayoutRef :: SetHelp (char *string )
{

  ProvideDataLayout(NO);

  layout->SetHelp(string);

}

/******************************************************************************/
/**
\brief  SetIcon - 


-------------------------------------------------------------------------------
\brief  i0


\param  pQIcon -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

void ODataLayoutRef :: SetIcon (QIcon *pQIcon )
{

  ProvideDataLayout(NO);

  layout->SetIcon(pQIcon);

}

/******************************************************************************/
/**
\brief  i01


\param  pDPixmap_normal -
\param  pDPixmap_active -
\param  pDPixmap_disabled -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIcon"

void ODataLayoutRef :: SetIcon (DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled )
{

BEGINSEQ
  ProvideDataLayout(YES);

  if ( !layout->get_owner() )                        OGUIERR(99)
  
  OIconSet  icon(pDPixmap_normal,pDPixmap_active,pDPixmap_disabled);
  layout->SetIcon(&icon);
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

void ODataLayoutRef :: SetLayout (DFont *pDFont )
{

  ProvideDataLayout(NO);

  layout->SetLayout(pDFont);

}

/******************************************************************************/
/**
\brief  SetTextColor - 



\param  pQColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTextColor"

void ODataLayoutRef :: SetTextColor (QColor *pQColor )
{

  ProvideDataLayout(NO);

  layout->SetTextColor(pQColor);

}

/******************************************************************************/
/**
\brief  SetToolTip - 



\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetToolTip"

void ODataLayoutRef :: SetToolTip (char *string )
{

  ProvideDataLayout(NO);

  layout->SetToolTip(string);

}

/******************************************************************************/
/**
\brief  ~ODataLayoutRef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODataLayoutRef"

                        ODataLayoutRef :: ~ODataLayoutRef ( )
{



}


