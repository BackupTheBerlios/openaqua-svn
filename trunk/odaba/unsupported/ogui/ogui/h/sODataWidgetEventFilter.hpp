/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODataWidgetEventFilter

\brief    


\date     $Date: 2006/03/13 21:34:04,40 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODataWidgetEventFilter_HPP
#define   ODataWidgetEventFilter_HPP

class     ODataWidgetEventFilter;

class     ODataWidget;
class  ODataWidgetEventFilter :public QObject
{
protected  :         ODataWidget                                 *odw;                                                       //

public     :
public     :                                                             ODataWidgetEventFilter (ODataWidget *pODataWidget );
public     : virtual                             bool eventFilter (QObject *pQObject, QEvent *pQEvent );
};

#endif
