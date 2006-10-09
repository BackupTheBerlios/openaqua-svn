/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHDataWidgetEventFilter

\brief    Basic event filter for OEHDataWidget (an O-Control)
          This  event filter handles the basic events for any O-Control, such as
          focus in and out.

\date     $Date: 2006/03/13 21:34:14,64 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHDataWidgetEventFilter_HPP
#define   OEHDataWidgetEventFilter_HPP

class     OEHDataWidgetEventFilter;

class     OEHDataWidget;
class  OEHDataWidgetEventFilter :public QObject
{
protected  :         OEHDataWidget                               *oeh_dw;                                                    //

public     :
                     OEHDataWidget                               *get_oeh_dw() { return(oeh_dw); }
public     :                                                             OEHDataWidgetEventFilter (OEHDataWidget *pOEHDataWidget );
public     :                                     bool eventFilter (QObject *pQObject, QEvent *pQEvent );
};

#endif
