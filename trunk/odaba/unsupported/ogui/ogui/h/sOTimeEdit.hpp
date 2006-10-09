/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OTimeEdit

\brief    


\date     $Date: 2006/06/26 15:43:10,06 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OTimeEdit_HPP
#define   OTimeEdit_HPP

class     OTimeEdit;

class     ODS;
class     ODataWidget;
#include  <sOEHControlValue.hpp>
class  OTimeEdit :public QTimeEdit,
public OEHControlValue
{
protected  :                                                      Q_OBJECT;                                                  // 

public     :
public     : virtual          OGUIImpExp            logical Activate ( );
public     : public slots:                          void ClearData ( );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
public     : public slots:                          void FillData ( );
public     :                  OGUIImpExp                 OTimeEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                  OGUIImpExp                 OTimeEdit (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                        void SetReadOnly (logical fReadOnly );
public     :                                        QWidget *WidgetQ ( );
public     :                                        void paintEvent (QPaintEvent *pQPaintEvent );
public     : public slots:                          void storeToValue ( );
};

#endif
