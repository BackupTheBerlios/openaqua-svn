/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OGroupBox

\brief    


\date     $Date: 2006/03/13 21:35:54,32 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OGroupBox"

#include  <pogui7.h>
#include  <mOGroupBox.h>
#include  <sODataWidget.hpp>
#include  <sOGroupBox.hpp>


/******************************************************************************/
/**
\brief  FrameQ - 


\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OGroupBox :: FrameQ ( )
{

BEGINSEQ
  // is not a QFrame
  OGUIERR(99)
  return(NULL);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  OGroupBox - 



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OGroupBox"

                        OGroupBox :: OGroupBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods )
                     : QGroupBox    (pODataWidget ? pODataWidget->WidgetQ()
                           : NULL),
ODataWidget (pODataWidget,oODataWidget,create_ods)
{



}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OGroupBox :: WidgetQ ( )
{

  return(this);

}


