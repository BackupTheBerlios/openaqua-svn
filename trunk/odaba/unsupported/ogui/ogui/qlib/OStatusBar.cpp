/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OStatusBar

\brief    


\date     $Date: 2006/03/13 21:36:16,78 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OStatusBar"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODataWidget.hpp>
#include  <sOWidget.hpp>
#include  <sOStatusBar.hpp>


/******************************************************************************/
/**
\brief  AddElement - 



\param  o_element -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddElement"

void OStatusBar :: AddElement (OWidget *o_element )
{

  addWidget(o_element->WidgetQ());


}

/******************************************************************************/
/**
\brief  OStatusBar - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  show_grip -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStatusBar"

                        OStatusBar :: OStatusBar (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical show_grip )
                     : QStatusBar(pODataWidget ? pODataWidget->WidgetQ() : NULL),
ODataWidget(pODataWidget,oODataWidget,YES)
{

  setSizeGripEnabled(show_grip);

}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OStatusBar :: WidgetQ ( )
{


  return(this);
}


