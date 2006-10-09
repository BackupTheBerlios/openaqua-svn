#include "coacheckboxplugin.h"
#include "CoaCheckBox"

CoaCheckBoxPlugin::CoaCheckBoxPlugin(QObject *parent)
   :CoaBasePlugin(QString("CoaCheckBox"), QString("CoaCheckBox"), parent)
{
}


QWidget * CoaCheckBoxPlugin::createWidget(QWidget *parent)
{

   return new CoaCheckBox(parent);
}


