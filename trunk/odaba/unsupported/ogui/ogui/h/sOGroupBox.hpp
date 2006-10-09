/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OGroupBox

\brief    


\date     $Date: 2006/03/13 21:34:17,87 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OGroupBox_HPP
#define   OGroupBox_HPP

class     OGroupBox;

#include  <sODataWidget.hpp>
class  OGroupBox :public QGroupBox,
public ODataWidget
{
protected  :                                                      Q_OBJECT;                                                  //

public     :
public     : virtual                             QFrame *FrameQ ( );
public     :                                                             OGroupBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     : virtual                             QWidget *WidgetQ ( );
};

#endif
