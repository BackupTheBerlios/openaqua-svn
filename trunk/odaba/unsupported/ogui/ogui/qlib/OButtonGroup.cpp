/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OButtonGroup

\brief    


\date     $Date: 2006/03/13 21:35:11,21 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OButtonGroup"

#include  <pogui7.h>
#include  <mOButtonGroup.h>
#include  <sODataWidget.hpp>
#include  <sOButtonGroup.hpp>


/******************************************************************************/
/**
\brief  OButtonGroup - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OButtonGroup"

                        OButtonGroup :: OButtonGroup (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QButtonGroup (pODataWidget ? pODataWidget->WidgetQ()
                           : NULL),
ODataWidget (pODataWidget,oODataWidget,create_ods)
{



}

/******************************************************************************/
/**
\brief  ObjectQ - 


\return pQObject -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ObjectQ"

QObject *OButtonGroup :: ObjectQ ( )
{

return this;

}

/******************************************************************************/
/**
\brief  xxFrameQ - 


\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxFrameQ"

QFrame *OButtonGroup :: xxFrameQ ( )
{

//  return(this);
return NULL;

}

/******************************************************************************/
/**
\brief  xxWidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xxWidgetQ"

QWidget *OButtonGroup :: xxWidgetQ ( )
{

//  return(this);
return NULL;

}


