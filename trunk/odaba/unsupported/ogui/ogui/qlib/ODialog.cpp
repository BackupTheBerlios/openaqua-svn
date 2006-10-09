/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    ODialog



\date     $Date: 2006/05/15 16:54:52,59 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODialog"

#include  <pogui7.h>
#include  <mODialog.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sODialog.hpp>


/******************************************************************************/
/**
\brief  Initialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ODialog :: Initialize ( )
{



}

/******************************************************************************/
/**
\brief  InitializeButtons


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeButtons"

void ODialog :: InitializeButtons ( )
{

  qbOK      = new QPushButton(this->WidgetQ());
  qbCancel  = new QPushButton(this->WidgetQ());
  
  qbOK->setMaximumWidth(80);
  qbCancel->setMaximumWidth(80);
  
  qbOK->setText(SZ2QS("OK"));
  qbCancel->setText(SZ2QS("Cancel"));  
  
  connect(qbOK    ,SIGNAL(clicked()),this,SLOT(accept()));
  connect(qbCancel,SIGNAL(clicked()),this,SLOT(reject()));


}

/******************************************************************************/
/**
\brief  ODialog - Konstruktor


-------------------------------------------------------------------------------
\brief  i0


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  create_ods
\param  ctitle
\param  is_modal
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODialog"

     ODialog :: ODialog (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, const char *ctitle, logical is_modal )
                     : QDialog(pODataWidget ? pODataWidget->WidgetQ() :NULL),
OEHDataWidget (pODataWidget,oODataWidget,create_ods)
,qbOK(NULL)
,qbCancel(NULL)
,qGrid(NULL)
{

//  WidgetQ()->setAttribute(Qt::WA_DeleteOnClose);
  
  setModal(is_modal);
  setWindowTitle(SZ2QS(ctitle));

  Initialize();

}

/******************************************************************************/
/**
\brief  i01


\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS
\param  is_modal
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODialog"

     ODialog :: ODialog (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical is_modal )
                     : QDialog(pODataWidget ? pODataWidget->WidgetQ() :NULL),
OEHDataWidget (pODataWidget,oODataWidget,pODS)
,qbOK(NULL)
,qbCancel(NULL)
,qGrid(NULL)
{
  Qt::WindowFlags    flg = windowFlags();
//iniq3:,"No Title", YES, 0
  WidgetQ()->setAttribute(Qt::WA_DeleteOnClose);
  
  flg |=  Qt::WindowTitleHint;
  flg |=  Qt::WindowSystemMenuHint;

  setWindowFlags(flg);
  
//  setWindowTitle(SZ2QS("No Title"));
  setModal(is_modal);
  Initialize();
}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return qwidget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *ODialog :: WidgetQ ( )
{

  return(this);
}

/******************************************************************************/
/**
\brief  accept


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "accept"

void ODialog :: accept ( )
{
  QDialog::accept();
}

/******************************************************************************/
/**
\brief  closeEvent


\param  pQCloseEvent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "closeEvent"

void ODialog :: closeEvent (QCloseEvent *pQCloseEvent )
{
  QDialog::closeEvent(pQCloseEvent);
}

/******************************************************************************/
/**
\brief  reject


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "reject"

void ODialog :: reject ( )
{
  QDialog::reject();
}

/******************************************************************************/
/**
\brief  ~ODialog - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODialog"

     ODialog :: ~ODialog ( )
{
  Deactivate(NO);
  
  if ( qbOK )
    delete qbOK;
    
  if ( qbCancel )
    delete qbCancel;
    
  if ( qGrid )
    delete qGrid;
}


