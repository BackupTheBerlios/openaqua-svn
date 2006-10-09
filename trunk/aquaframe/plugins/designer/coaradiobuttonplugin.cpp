#include "coaradiobuttonplugin.h"
#include "CoaRadioButton"

CoaRadioButtonPlugin::CoaRadioButtonPlugin(QObject *parent)
:CoaBasePlugin(QString("CoaRadioButton"), QString("CoaRadioButton"), parent)
{
}


QWidget * CoaRadioButtonPlugin::createWidget(QWidget *parent)
{

   return new CoaRadioButton(parent);
}


