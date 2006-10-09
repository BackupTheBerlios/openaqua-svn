/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OMainWindow

\brief    


\date     $Date: 2006/03/13 21:36:07,29 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OMainWindow"

#include  <pogui7.h>
#include  <sOMainWindow.hpp>


/******************************************************************************/
/**
\brief  OMainWindow - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OMainWindow"

                        OMainWindow :: OMainWindow ( )
                     : QMainWindow (NULL),
ODataWidget (NULL,NULL,YES)
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

QWidget *OMainWindow :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  ~OMainWindow - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OMainWindow"

                        OMainWindow :: ~OMainWindow ( )
{



}


