/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OToolBox

\brief    Toolbox for a Toggleable Controlstack
          the  toolbox accepts a endless count  of odatawidgets, that are hidden
          (TODO:settings) by default and assigned to a button.
          When  pressing the assigned  button the odw  shows, moving all buttons
          below to get space.
          several odws can be visible at the same time.

\date     $Date: 2006/03/13 21:34:47,32 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OToolBox_HPP
#define   OToolBox_HPP

class     OToolBox;

class     ODS;
#include  <sODataWidget.hpp>
class  OToolBox :public QWidget,
public ODataWidget
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         QVBoxLayout                                 *box;                                                       //
protected  :         QVBoxLayout                                 *stack;                                                     //
protected  :         QButtonGroup                                *toggler;                                                   //
protected  :         QScrollArea                                 *scrollarea;                                                //
protected  :         QWidget                                     *scrollsurface;                                             //
protected  :         std::vector<ODataWidget*>                    items;                                                     //
protected  :         std::vector<int>                             sizes;                                                     //

public     :
public     :         OGUI7ImpExp                 int32 AddWidget (ODataWidget *pODataWidget );
public     :         OGUI7ImpExp                 int32 AddWidget (ODataWidget *pODataWidget, QString qsText );
public     :         OGUI7ImpExp                 QAbstractButton *GetButton (int32 indx0 );
public     :         OGUI7ImpExp                 ODataWidget *GetWidget (int32 indx0 );
public     :                                     logical HideWidget (int32 indx0 );
public     :                                     logical Initialize ( );
public     :         OGUI7ImpExp                                         OToolBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     :                                     logical SetLabel (int32 indx0, QString qsText );
public     :                                     logical ShowWidget (int32 indx0 );
public     :         OGUI7ImpExp                 logical UpdateSize ( );
public     :                                     public slots: void slotToggle (int index );
public     :         OGUI7ImpExp                                         ~OToolBox ( );
};

#endif
