/********************************* Class Declaration ***************************/
/**
\package  OGUI
\class    OCheckBox



\date     $Date: 2006/05/09 16:28:17,96 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OCheckBox_HPP
#define   OCheckBox_HPP

class     OCheckBox;

class     ODS;
class     ODataWidget;
#include  <sOEHControlValue.hpp>
#include  <sQCheckBox.hpp>
#pragma pack(4)

class  OCheckBox :public QCheckBox,
public OEHControlValue
{
protected  :                                                      Q_OBJECT;                                                  

public     :
public     : virtual          OGUIImpExp            logical Activate ( );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
public     : virtual                                void FillData ( );
public     :                  OGUIImpExp                 OCheckBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL );
public     :                  OGUIImpExp                 OCheckBox (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL );
protected  : virtual                                void SetReadOnly (logical fReadOnly );
public     :                                        QWidget *WidgetQ ( );
protected  : private slots:                         void storeToValue ( );
public     : virtual                                     ~OCheckBox ( );
};

#pragma pack()
#endif
