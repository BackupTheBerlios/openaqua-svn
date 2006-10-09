/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DBrush

\brief    


\date     $Date: 2006/03/13 21:33:35,75 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBrush_HPP
#define   DBrush_HPP

class     DBrush;

#include  <cADK_BrushStyle.h>
#include  <cADK_ColorRole.h>
#include  <sDColor.hpp>
#include  <sDPixmap.hpp>
class  DBrush
{
protected  :         ADK_ColorRole                                role;                                                      //
protected  :         ADK_BrushStyle                               style;                                                     //
protected  :         DColor                                       color;                                                     //
protected  :         DPixmap                                      pixmap;                                                    //

public     :
                     ADK_BrushStyle                               get_style() { return(style); }
                     DColor                                      &get_color() { return(color); }
public     :         OGUI7ImpExp                                         DBrush (ADK_ColorRole brush_role );
public     :         OGUI7ImpExp                                         DBrush (ADK_ColorRole brush_role, ADK_BrushStyle brush_style, DColor brush_color, DPixmap brush_pixmap );
public     :                                     void FromQBrush (QBrush &rQBrush );
public     :         OGUI7ImpExp                 ADK_ColorRole GetRole ( );
public     :                                     QBrush ToQBrush ( );
};

#endif
