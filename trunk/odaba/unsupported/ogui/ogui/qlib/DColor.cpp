/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DColor

\brief    


\date     $Date: 2006/03/13 21:34:59,87 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DColor"

#include  <pogui7.h>
#include  <sDColor.hpp>


/******************************************************************************/
/**
\brief  Blue - 


\return blue -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Blue"

int32 DColor :: Blue ( ) const
{


  return(blue);
}

/******************************************************************************/
/**
\brief  DColor - Konstruktor


-------------------------------------------------------------------------------
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DColor"

                        DColor :: DColor ( )
                     :   string(NULL),
  red(-1),
  green(-1),
  blue(-1)
{



}

/******************************************************************************/
/**
\brief  i01


\param  clr_red -
\param  clr_green -
\param  clr_blue -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DColor"

                        DColor :: DColor (int32 clr_red, int32 clr_green, int32 clr_blue )
                     :   string(NULL),
  red(clr_red),
  green(clr_green),
  blue(clr_blue)
{



}

/******************************************************************************/
/**
\brief  Green - 


\return green -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Green"

int32 DColor :: Green ( ) const
{


  return(green);
}

/******************************************************************************/
/**
\brief  Hue - 


\return hue -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Hue"

int32 DColor :: Hue ( ) const
{
  long                    hue;
  long                    sub_hue;
  long                    lcolor;
  long                    rcolor;
  long                    delta;

  if ( (red >= green) && (red >= blue) )
  {
    hue    = 360;
    delta  = red;
    lcolor = blue;
    rcolor = green;
  } else if ( green >= blue )
  {
    hue    = 120;
    delta  = green;
    lcolor = red;
    rcolor = blue;
  } else
  {
    hue    = 240;
    delta  = blue;
    lcolor = green;
    rcolor = red;
  }
  
  delta -= ( lcolor < rcolor
    ? lcolor
    : rcolor
  );
  sub_hue  = 120 * (rcolor - lcolor);
  sub_hue += ( sub_hue < 0
    ? -delta
    :  delta
  );
  hue += ( delta
    ? sub_hue / (2 * delta)
    : 0
  );

  return (hue % 360);
}

/******************************************************************************/
/**
\brief  IsValid - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical DColor :: IsValid ( ) const
{

  return ( this && !( (red   < 0) ||
                      (green < 0) ||
                      (blue  < 0)    ) );


}

/******************************************************************************/
/**
\brief  Red - 


\return red -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Red"

int32 DColor :: Red ( ) const
{


  return(red);
}

/******************************************************************************/
/**
\brief  ReleaseString - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseString"

void DColor :: ReleaseString ( )
{

  if ( string )
    free(string);
  string = NULL;


}

/******************************************************************************/
/**
\brief  Saturation - 


\return saturation -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Saturation"

int32 DColor :: Saturation ( ) const
{
  long                    saturation;
  long                    mini;
  long                    maxi;

  mini = maxi = red;

  if ( maxi < green )
    maxi = green;
  if ( maxi < blue )
    maxi = blue;
  if ( mini > green )
    mini = green;
  if ( mini > blue )
    mini = blue;

  saturation = (maxi
    ? (510 * (maxi - mini) + maxi) / (2 * maxi)
    : 0
  );
  return (saturation);
}

/******************************************************************************/
/**
\brief  SetBlue - 



\param  clr_blue -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBlue"

void DColor :: SetBlue (int32 clr_blue )
{

  blue = clr_blue;


}

/******************************************************************************/
/**
\brief  SetGreen - 



\param  clr_green -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetGreen"

void DColor :: SetGreen (int32 clr_green )
{

  blue = clr_green;


}

/******************************************************************************/
/**
\brief  SetHSV - 



\param  clr_hue -
\param  clr_saturation -
\param  clr_value -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHSV"

void DColor :: SetHSV (int32 clr_hue, int32 clr_saturation, int32 clr_value )
{

  long delta  = (2 * clr_value * clr_saturation + 255) / 510;
  long hue    = ( clr_hue < 0 ? 360 + (clr_hue % 360) : clr_hue % 360 );
  
  long color0 = clr_value;
  long color2 = color0 - delta;

  long sub_hue = ((hue + 60) % 120) - 60;
  
  long color1 = color2 + (abs(sub_hue) * delta + 30) / 60;

  switch ( (hue + 60 ) / 120 )
  {
    case 0:
    case 3:
      red   = color0;
      green = ( sub_hue < 0 ? color2 : color1 );
      blue  = ( sub_hue < 0 ? color1 : color2 );
    break;
    case 1:
      green = color0;
      blue  = ( sub_hue < 0 ? color2 : color1 );
      red   = ( sub_hue < 0 ? color1 : color2 );
    break;
    case 2:
      blue  = color0;
      red   = ( sub_hue < 0 ? color2 : color1 );
      green = ( sub_hue < 0 ? color1 : color2 );
    break;
  }


}

/******************************************************************************/
/**
\brief  SetRGB - 



\param  clr_red -
\param  clr_green -
\param  clr_blue -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRGB"

void DColor :: SetRGB (int32 clr_red, int32 clr_green, int32 clr_blue )
{

  red   = clr_red;
  green = clr_green;
  blue  = clr_blue;


}

/******************************************************************************/
/**
\brief  SetRed - 



\param  clr_red -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRed"

void DColor :: SetRed (int32 clr_red )
{

  blue = clr_red;


}

/******************************************************************************/
/**
\brief  SetString - 


\return term -

\param  color_string -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetString"

logical DColor :: SetString (char *color_string )
{
  logical              term = NO;
BEGINSEQ
  ReleaseString();
  if ( !color_string )                               LEAVESEQ
    
  string = strdup(color_string);
ENDSEQ
  return (term);
}

/******************************************************************************/
/**
\brief  Value - 


\return value -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Value"

int32 DColor :: Value ( ) const
{
  long                    value;
  value = red;
  if ( value < green )
    value = green;
  if ( value < blue )
    value = blue;

  return(value);
}

/******************************************************************************/
/**
\brief  operator!= - 


\return term -

\param  rcDColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical DColor :: operator!= (const DColor &rcDColor ) const
{
  logical                 term;
  term = (
    (rcDColor.red   != red)   ||
    (rcDColor.green != green) ||
    (rcDColor.blue  != blue)
  );

  return(term);
}

/******************************************************************************/
/**
\brief  operator== - 


\return term -

\param  rcDColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DColor :: operator== (const DColor &rcDColor ) const
{
  logical                 term;
  term = (
    (rcDColor.red   == red)   &&
    (rcDColor.green == green) &&
    (rcDColor.blue  == blue)
  );

  return(term);
}

/******************************************************************************/
/**
\brief  ~DColor - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DColor"

                        DColor :: ~DColor ( )
{

  ReleaseString();

}


