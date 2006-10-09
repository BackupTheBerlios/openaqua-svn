/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    ODesktopO



\date     $Date: 2006/04/18 10:42:41,56 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODesktopO"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sODesktopO.hpp>


/******************************************************************************/
/**
\brief  ODesktopO


\param  pODataWidget - Parent data widget
\param  create_ods - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODesktopO"

                        ODesktopO :: ODesktopO (ODataWidget *pODataWidget, logical create_ods )
                     : ODataWidget (pODataWidget,pODataWidget,create_ods),
QDesktopWidget ()

{



}

/******************************************************************************/
/**
\brief  WidgetQ

\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ODesktopO :: WidgetQ ( )
{


  return(QApplication::desktop());
}

/******************************************************************************/
/**
\brief  ~ODesktopO


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODesktopO"

                        ODesktopO :: ~ODesktopO ( )
{



}


