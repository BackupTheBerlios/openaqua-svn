/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OLabelDesignMode

\brief    


\date     $Date: 2006/03/13 21:34:19,48 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OLabelDesignMode_HPP
#define   OLabelDesignMode_HPP

class     OLabelDesignMode;

class     OLabel;
class     OWidget;
#include  <sOWidgetDesignMode.hpp>
class  OLabelDesignMode :public OWidgetDesignMode
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         OLabel                                      *olabel;                                                    //

public     :
public     :                                     public slots: void CMChangeText ( );
public     : virtual                             logical CreateContextMenu ( );
public     :                                                             OLabelDesignMode (OLabel *pOLabel );
public     : virtual                                                     ~OLabelDesignMode ( );
};

#endif
