/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OSplitter



\date     $Date: 2006/03/23 11:48:07,76 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSplitter_HPP
#define   OSplitter_HPP

class     OSplitter;

class     ODS;
#include  <sODataWidget.hpp>
#include  <sOEHDataWidget.hpp>
class  OSplitter :public QSplitter,
public OEHDataWidget
{
protected  :                                                      Q_OBJECT;                                                  //

public     :
public     : virtual OGUIImpExp                  logical Activate ( );
public     : virtual OGUIImpExp                  logical Deactivate (logical data_only=NO );
public     : virtual                             QFrame *FrameQ ( );
public     :         OGUIImpExp                                          OSplitter (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :         OGUIImpExp                                          OSplitter (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     void SetCollapsible (bool toggle=FALSE );
public     :                                     logical SetHandleWidth (int16 handle_width );
public     :                                     QWidget *WidgetQ ( );
public     :                                     public slots: void activateHandle ( );
public     :                                     QSplitterHandle *createHandle ( );
public     :                                     public slots: void loadValue ( );
public     :                                     public slots: void openValue ( );
public     :                                     public slots: void resizeEvent ( );
public     : virtual OGUIImpExp                                          ~OSplitter ( );
};

#endif
