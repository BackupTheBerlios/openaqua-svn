/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DLayout

\brief    


\date     $Date: 2006/03/13 21:33:36,84 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DLayout_HPP
#define   DLayout_HPP

class     DLayout;

#define  QT_MAXCOLOR_ROLES                         16
class     DBrush;
#include  <sDPixmap.hpp>
class  DLayout
{
protected  :         DPixmap                                      shape;                                                     //
protected  :         DBrush                                      *active[20];                                                //
protected  :         DBrush                                      *inactive[20];                                              //
protected  :         DBrush                                      *disabled[20];                                              //

public     :
                     DPixmap                                     &get_shape() { return(shape); }
public     :         OGUI7ImpExp                                         DLayout ( );
public     :                                     void Initialize ( );
public     :         OGUI7ImpExp                 void Reset (logical del_opt );
public     :                                     void SetActive (QPalette &rQPalette );
public     :                                     void SetColorGroup (QPalette &rQPalette, QPalette::ColorGroup color_group, DBrush *brushs[20] );
public     :                                     void SetDisabled (QPalette &rQPalette );
public     :                                     void SetInactive (QPalette &rQPalette );
public     :                                     void SetPalette (QPalette &rQPalette );
public     :         OGUI7ImpExp                                         ~DLayout ( );
};

#endif
