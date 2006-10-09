/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OMenuBar

\brief    Menu bar


\date     $Date: 2006/03/13 21:36:07,65 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OMenuBar"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOMenu.hpp>
#include  <sOMenuBar.hpp>


/******************************************************************************/
/**
\brief  OMenuBar - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OMenuBar"

                        OMenuBar :: OMenuBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget )
                     : QMenuBar(pODataWidget ? pODataWidget->WidgetQ() : NULL), 
OMenu(pODataWidget,oODataWidget)
{

BEGINSEQ
  if ( !pODataWidget )                               OGUIERR(99)
    
  if ( pODataWidget->WidgetQ()->layout() )
    pODataWidget->WidgetQ()->layout()->setMenuBar(this);

  qwidget = this;
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OMenuBar :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  ~OMenuBar - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OMenuBar"

                        OMenuBar :: ~OMenuBar ( )
{



}


