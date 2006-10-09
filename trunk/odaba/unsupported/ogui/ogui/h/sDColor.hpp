/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DColor

\brief    


\date     $Date: 2006/03/13 21:33:35,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DColor_HPP
#define   DColor_HPP

class     DColor;

#include  <sDColor.hpp>
class  DColor
{
protected  :         char                                        *string;                                                    //
protected  :         int32                                        red;                                                       //
protected  :         int32                                        green;                                                     //
protected  :         int32                                        blue;                                                      //

public     :
public     :         OGUI7ImpExp                 int32 Blue ( ) const;
public     :         OGUI7ImpExp                                         DColor ( );
public     :         OGUI7ImpExp                                         DColor (int32 clr_red, int32 clr_green, int32 clr_blue );
public     :         OGUI7ImpExp                 int32 Green ( ) const;
public     :         OGUI7ImpExp                 int32 Hue ( ) const;
public     :         OGUI7ImpExp                 logical IsValid ( ) const;
public     :         OGUI7ImpExp                 int32 Red ( ) const;
public     :                                     void ReleaseString ( );
public     :         OGUI7ImpExp                 int32 Saturation ( ) const;
public     :         OGUI7ImpExp                 void SetBlue (int32 clr_blue );
public     :         OGUI7ImpExp                 void SetGreen (int32 clr_green );
public     :         OGUI7ImpExp                 void SetHSV (int32 clr_hue, int32 clr_saturation, int32 clr_value );
public     :         OGUI7ImpExp                 void SetRGB (int32 clr_red, int32 clr_green, int32 clr_blue );
public     :         OGUI7ImpExp                 void SetRed (int32 clr_red );
public     :         OGUI7ImpExp                 logical SetString (char *color_string );
public     :         OGUI7ImpExp                 int32 Value ( ) const;
public     :         OGUI7ImpExp                 logical operator!= (const DColor &rcDColor ) const;
public     :         OGUI7ImpExp                 logical operator== (const DColor &rcDColor ) const;
public     :         OGUI7ImpExp                                         ~DColor ( );
};

#endif
