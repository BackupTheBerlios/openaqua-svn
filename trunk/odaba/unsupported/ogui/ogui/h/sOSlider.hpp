/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSlider

\brief    


\date     $Date: 2006/03/13 21:34:39,29 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSlider_HPP
#define   OSlider_HPP

class     OSlider;

class     ODS;
class     ODataWidget;
#include  <sOEHControlValue.hpp>
#include  <sOEHDataWidget.hpp>
class  OSlider :public QSlider,
public OEHControlValue
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //

public     :
public     : virtual OGUI7ImpExp                 logical Activate ( );
public     :                                     void ClearData ( );
public     : virtual OGUI7ImpExp                 logical Deactivate (logical data_only=NO );
public     :                                     void FillData ( );
public     :         OGUI7ImpExp                                         OSlider (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :         OGUI7ImpExp                                         OSlider (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     void SetReadOnly (logical fReadOnly );
public     :                                     QWidget *WidgetQ ( );
public     :                                     public slots: void storeToValue ( );
};

#endif
