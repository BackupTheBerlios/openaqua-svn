/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OFrame

\brief    Splitter Window
          The  class provides a number of  areas separated by a splitter handle.
          The  controlls  are  added  to  this area according to the sequence of
          definition. Each control will get its own area.

\date     $Date: 2006/05/07 17:56:58,68 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OFrame_HPP
#define   OFrame_HPP

class     OFrame;

class     ODS;
#include  <sODataWidget.hpp>
#include  <sOEHControlValue.hpp>
#include  <sOEHDataWidget.hpp>
class  OFrame :public QFrame,
public OEHControlValue
{
protected  :                                                      Q_OBJECT;                                                  

public     :
public     : virtual          OGUIImpExp            logical Activate ( );
public     : virtual                                logical DA_CancelClose ( );
public     : virtual                                logical DA_Refresh ( );
public     : virtual                                logical DA_SaveClose ( );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
public     : public slots:                          void FillData ( );
public     : virtual                                QFrame *FrameQ ( );
public     :                  OGUIImpExp                 OFrame (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                  OGUIImpExp                 OFrame (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     : virtual                                void ValueReset ( );
public     :                                        QWidget *WidgetQ ( );
public     : virtual                                logical getEnabled ( );
public     :                                        void resizeEvent ( );
public     : virtual          OGUIImpExp                 ~OFrame ( );
};

#endif
