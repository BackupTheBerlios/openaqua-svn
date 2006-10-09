/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OFixedText

\brief    


\date     $Date: 2006/03/13 21:34:16,50 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OFixedText_HPP
#define   OFixedText_HPP

class     OFixedText;

class     ODataWidget;
#include  <sODS.hpp>
#include  <sOEHControlValue.hpp>
#include  <sOWidget.hpp>
#pragma pack(4)

class  OFixedText :public QLabel,
public OEHControlValue
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //

public     :
protected  :                                     private slots: void ClearData ( );
protected  :                                     private slots: void FillData ( );
public     : virtual                             QFrame *FrameQ ( );
public     :         OGUI7ImpExp                                         OFixedText (ODataWidget *pODataWidget, ODataWidget *oODataWidget );
public     :         OGUI7ImpExp                 logical SetText (QString qsText );
public     :                                     QWidget *WidgetQ ( );
public     : virtual                                                     ~OFixedText ( );
};

#pragma pack()
#endif
