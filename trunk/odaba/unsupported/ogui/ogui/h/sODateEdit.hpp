/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    ODateEdit

\brief    


\date     $Date: 2006/07/07 16:52:52,28 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODateEdit_HPP
#define   ODateEdit_HPP

class     ODateEdit;

class     ODS;
class     ODataWidget;
class     QGridLayout;
class     QPushButton;
#include  <cDataFormSpec.h>
#include  <sOEHControlValue.hpp>
#include  <sOEHDataWidget.hpp>
class  ODateEdit :public QDateEdit,
public OEHControlValue
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         logical                                      ignore;                                                    // 
protected  :         QDate                                        pickDateCurrent;                                           // 
protected  :         QPushButton                                 *pickButton;                                                // 
protected  :         QWidget                                     *pickCalendar;                                              // 
protected  :         QWidget                                     *pickWindow;                                                // 
protected  :         QGridLayout                                 *pickWindowGrid;                                            // 
protected  :         QComboBox                                   *pickMonthDrop;                                             // 
protected  :         QComboBox                                   *pickYearDrop;                                              // 
protected  :         int32                                        buttonSize;                                                // 
protected  :         QString                                      defaultformat;                                             // 

public     :
                     int32                                        get_buttonSize() { return(buttonSize); }
public     : virtual          OGUIImpExp            logical Activate ( );
protected  : private slots:                         void ClearData ( );
public     :                                        logical DA_PickDate ( );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
public     : virtual                                int8 ExecuteAction (char *act_names );
protected  : private slots:                         void FillData ( );
public     :                                        logical Init ( );
public     :                  OGUIImpExp                 ODateEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                  OGUIImpExp                 ODateEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                  OGUIImpExp                 ODateEdit (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL );
public     :                                        logical ProvideContextMenu (QObject *watched );
public     :                                        logical SetButtonSize (int width );
public     :                                        logical SetFormat (const DataFormSpec dbdtFormat );
public     :                                        void SetReadOnly (logical fReadOnly );
public     : virtual                                QWidget *WidgetQ ( );
public     :                                        logical changeCalendar (QDate pickDate );
public     :                                        logical createCalendar ( );
public     :                                        void paintEvent (QPaintEvent *pQPaintEvent );
protected  : private slots:                         void pickDate ( );
protected  : private slots:                         void pickDay (int iDay );
protected  : private slots:                         void pickMonth (int iMonth );
protected  : private slots:                         void pickNextMonth ( );
protected  : private slots:                         void pickPrevMonth ( );
protected  : private slots:                         void pickScroll (int iDelta );
protected  : private slots:                         void pickYear (int iYear );
public     : public slots:                          void resetDate ( );
public     : public slots:                          void slotContextMenu ( );
protected  : private slots:                         void storeToValue ( );
};

#endif
