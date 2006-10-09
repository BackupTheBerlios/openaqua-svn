/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OButtonGroup

\brief    


\date     $Date: 2006/03/13 21:33:45,00 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OButtonGroup_HPP
#define   OButtonGroup_HPP

class     OButtonGroup;

#include  <sODataWidget.hpp>
class  OButtonGroup :public QButtonGroup,
public ODataWidget
{
protected  :                                                      Q_OBJECT;                                                  //

public     :
public     :                                                             OButtonGroup (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     : virtual                             QObject *ObjectQ ( );
public     : virtual                             QFrame *xxFrameQ ( );
public     : virtual                             QWidget *xxWidgetQ ( );
};

#endif
