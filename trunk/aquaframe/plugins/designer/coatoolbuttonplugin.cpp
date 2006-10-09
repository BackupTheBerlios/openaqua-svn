#include "coatoolbuttonplugin.h"
#include "CoaToolButton"

CoaToolButtonPlugin::CoaToolButtonPlugin(QObject *parent)
:CoaBasePlugin(QString("CoaToolButton"), QString("CoaToolButton"), parent)
{
}


QWidget * CoaToolButtonPlugin::createWidget(QWidget *parent)
{

   return new CoaToolButton(parent);
}


QIcon CoaToolButtonPlugin::icon() const
{
   return QIcon();
}


