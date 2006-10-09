/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    DBrush

\brief    


\date     $Date: 2006/08/29 19:39:01,85 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBrush"

#include  <pogui7.h>
#include  <cguimac.h>
#include  <sOPixmap.hpp>
#include  <sDBrush.hpp>


/******************************************************************************/
/**
\brief  DBrush - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  brush_role - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBrush"

     DBrush :: DBrush (ADK_ColorRole brush_role )
                     :   role(brush_role),
  style(BS_Undefined),
  color(0,0,0),
  pixmap()
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  brush_role - 
\param  brush_style - 
\param  brush_color - 
\param  brush_pixmap - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBrush"

     DBrush :: DBrush (ADK_ColorRole brush_role, ADK_BrushStyle brush_style, DColor brush_color, DPixmap brush_pixmap )
                     :   role(brush_role),
  style(brush_style),
  color(brush_color),
  pixmap(brush_pixmap)
{



}

/******************************************************************************/
/**
\brief  FromQBrush - 




\param  rQBrush - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromQBrush"

void DBrush :: FromQBrush (QBrush &rQBrush )
{

  style = (ADK_BrushStyle)rQBrush.style();
  color = QCOLOR2DCOLOR(rQBrush.color());
//  pixmap = FromQPixmap(rQBrush.pixmap());

}

/******************************************************************************/
/**
\brief  GetRole - 



\return brole - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRole"

ADK_ColorRole DBrush :: GetRole ( )
{

  return(role);

}

/******************************************************************************/
/**
\brief  ToQBrush - 



\return brush - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToQBrush"

QBrush DBrush :: ToQBrush ( )
{
  QBrush     b;
  b.setColor(DCOLOR2QCOLOR(color));
  
  if ( style != BS_Undefined )
    b.setStyle((Qt::BrushStyle)style);
  else{
    OPixmap opm(pixmap);
    b.setTexture(opm);
  }
  return(b);
}


