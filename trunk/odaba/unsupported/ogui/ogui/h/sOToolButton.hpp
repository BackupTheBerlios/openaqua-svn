/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OToolButton

\brief    


\date     $Date: 2006/03/13 21:34:48,12 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OToolButton_HPP
#define   OToolButton_HPP

class     OToolButton;

class     OToolBar;
#include  <sODataWidget.hpp>
class  OToolButton :public QToolButton,
public ODataWidget
{

public     :
public     : virtual                             logical Activate ( );
public     : virtual                             logical Deactivate (logical data_only=NO );
public     :         OGUI7ImpExp                                         OToolButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, int8 toggle_state );
public     :         OGUI7ImpExp                                         OToolButton (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods, const QIconSet &riconSet, const QString &qscLabel, const QString &qscGroup, QObject *pQObject, const char *szcSlot, OToolBar *pOToolBar );
public     :         OGUI7ImpExp                                         OToolButton (const QIconSet &riconSet, const QString &qscLabel, const QString &qscGroup, QObject *pQObject, const char *szcSlot, OToolBar *pOToolBar, const char *szcName );
public     : virtual OGUI7ImpExp                 logical SetStandardAction (const char *act_namesc, char *loid );
public     : virtual                             QWidget *WidgetQ ( );
};

#endif
