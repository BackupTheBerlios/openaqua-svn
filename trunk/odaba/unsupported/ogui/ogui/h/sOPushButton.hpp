/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OPushButton

\brief    Push button
          The  push  button  is  a  button  associated  with an action, which is
          called, when clicking the button.

\date     $Date: 2006/03/13 21:34:29,71 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPushButton_HPP
#define   OPushButton_HPP

class     OPushButton;

class     OEHAction;
class     OIconSet;
#include  <sODataWidget.hpp>
#include  <sOWidget.hpp>
class  OPushButton :public QPushButton,
public ODataWidget
{
protected  :                                                      Q_OBJECT;                                                  //

public     :
public     : virtual OGUI7ImpExp                 logical Activate ( );
public     : virtual OGUI7ImpExp                 logical Deactivate (logical data_only=NO );
public     :         OGUI7ImpExp                                         OPushButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, int8 toggle_state, logical default_opt );
public     : virtual OGUI7ImpExp                 logical SetStandardAction (const char *act_namesc, char *loid );
public     :                                     QWidget *WidgetQ ( );
public     :                                     public slots: logical doClicked ( );
};

#endif
