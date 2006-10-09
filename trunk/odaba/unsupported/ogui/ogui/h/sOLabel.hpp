/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OLabel

\brief    


\date     $Date: 2006/03/13 21:34:19,25 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OLabel_HPP
#define   OLabel_HPP

class     OLabel;

#include  <sODataWidget.hpp>
#include  <sOWidget.hpp>
class  OLabel :public QLabel,
public ODataWidget
{
protected  :         logical                                      drawFocusRect;                                             //

public     :
public     :                                     void EnableDesignMode ( );
public     : virtual                             QFrame *FrameQ ( );
public     : virtual                             char *GetText ( );
public     :         OGUI7ImpExp                                         OLabel (ODataWidget *pODataWidget, ODataWidget *oODataWidget );
public     :         OGUI7ImpExp                 void SetDrawFocusRect (logical f );
public     : virtual                             void SetText (const QString &rcQString );
public     :                                     QWidget *WidgetQ ( );
public     :                                     void drawContents (QPainter *pQPainter );
public     :         OGUI7ImpExp                 bool eventFilter (QObject *watched, QEvent *e );
public     :         OGUI7ImpExp                 void setBuddy (QWidget *pQWidget );
};

#endif
