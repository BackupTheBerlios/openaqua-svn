/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OHorLayout

\brief    


\date     $Date: 2006/03/13 21:35:54,64 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OHorLayout"

#include  <pogui7.h>
#include  <sOHorLayout.hpp>


/******************************************************************************/
/**
\brief  OHorLayout - Konstruktor



\param  ver_align -
\param  spacing_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OHorLayout"

                        OHorLayout :: OHorLayout (Qt::AlignmentFlag ver_align, int spacing_w )
                     : QHBoxLayout (),
  left(NULL),
  right(NULL)
{

  setSpacing(spacing_w);
  setMargin(0);
  
  left  = new QHBoxLayout();
  left->setAlignment(ver_align | Qt::AlignLeft);
  addLayout(left);
    
  right = new QHBoxLayout();
  right->setAlignment(ver_align | Qt::AlignRight);
  addLayout(right);


}

/******************************************************************************/
/**
\brief  ~OHorLayout - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OHorLayout"

                        OHorLayout :: ~OHorLayout ( )
{

  delete left;
  left = NULL;

  delete right;
  right = NULL;

}


