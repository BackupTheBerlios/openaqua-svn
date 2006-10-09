/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OVerLayout

\brief    


\date     $Date: 2006/03/13 21:36:22,82 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OVerLayout"

#include  <pogui7.h>
#include  <sOVerLayout.hpp>


/******************************************************************************/
/**
\brief  OVerLayout - Konstruktor



\param  hor_align -
\param  spacing_w -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OVerLayout"

                        OVerLayout :: OVerLayout (Qt::AlignmentFlag hor_align, int spacing_w )
                     : QVBoxLayout (),
  top(NULL),
  bottom(NULL)
{

  setSpacing(spacing_w);
  setMargin(0);
    
  top  = new QVBoxLayout();
  top->setAlignment(hor_align | Qt::AlignTop);
  addLayout(top);
  
  bottom = new QVBoxLayout();
  bottom->setAlignment(hor_align | Qt::AlignBottom);
  addLayout(bottom);


}

/******************************************************************************/
/**
\brief  ~OVerLayout - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OVerLayout"

                        OVerLayout :: ~OVerLayout ( )
{

  delete top;
  top = NULL;

  delete bottom;
  bottom = NULL;

}


