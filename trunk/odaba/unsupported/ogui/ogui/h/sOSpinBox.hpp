/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSpinBox

\brief    


\date     $Date: 2006/03/13 21:34:41,28 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSpinBox_HPP
#define   OSpinBox_HPP

class     OSpinBox;

class     ODS;
class     ODataWidget;
#include  <sOEHControlValue.hpp>
#include  <sOEHDataWidget.hpp>
class  OSpinBox :public QSpinBox,
public OEHControlValue
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //

public     :
public     : virtual OGUI7ImpExp                 logical Activate ( );
public     :                                     void ClearData ( );
public     : virtual OGUI7ImpExp                 logical Deactivate (logical data_only=NO );
public     :                                     void FillData ( );
public     :         OGUI7ImpExp                                         OSpinBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :         OGUI7ImpExp                                         OSpinBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     void SetReadOnly (logical fReadOnly );
public     :                                     QWidget *WidgetQ ( );
public     :                                     public slots: void storeToValue ( );
};

#endif
