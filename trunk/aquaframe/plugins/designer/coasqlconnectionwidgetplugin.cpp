#include "coasqlconnectionwidgetplugin.h"
#include "CoaSqlConnectionWidget"

CoaSqlConnectionWidgetPlugin::CoaSqlConnectionWidgetPlugin(QObject *parent)
:CoaBasePlugin(QString("CoaSqlConnectionWidget"), QString("CoaSqlConnectionWidget"), parent)
{
}


QWidget * CoaSqlConnectionWidgetPlugin::createWidget(QWidget *parent)
{

   return new CoaSqlConnectionWidget(parent);
}


QIcon CoaSqlConnectionWidgetPlugin::icon() const
{
   return QIcon();
}


