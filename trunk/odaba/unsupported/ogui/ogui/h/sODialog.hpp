/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODialog

\brief    


\date     $Date: 2006/03/13 21:34:05,81 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODialog_HPP
#define   ODialog_HPP

class     ODialog;

class     ODS;
class     ODataWidget;
#include  <sOEHDataWidget.hpp>
class  ODialog :public QDialog,
public OEHDataWidget
{
protected  :                                                      Q_OBJECT;                                                  //
public     :         QPushButton                                 *qbOK;                                                      //
public     :         QPushButton                                 *qbCancel;                                                  //
public     :         QGridLayout                                 *qGrid;                                                     //

public     :
public     :                                     void Initialize ( );
public     :                                     void InitializeButtons ( );
public     :         OGUI7ImpExp                                         ODialog (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, const char *ctitle, logical is_modal );
public     :         OGUI7ImpExp                                         ODialog (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, logical is_modal );
public     :         OGUI7ImpExp                 QWidget *WidgetQ ( );
public     :                                     public slots: void accept ( );
public     : virtual                             void closeEvent (QCloseEvent *pQCloseEvent );
public     :                                     public slots: void reject ( );
public     :         OGUI7ImpExp                                         ~ODialog ( );
};

#endif
