#include "coadockwidgetplugin.h"
#include "CoaDockWidget"

CoaDockWidgetPlugin::CoaDockWidgetPlugin(QObject *parent)
:CoaContainerPlugin(QString("CoaDockWidget"), QString("CoaDockWidget"), parent)
{
}


QWidget * CoaDockWidgetPlugin::createWidget(QWidget *parent)
{
   return new CoaDockWidget(parent);
}


QIcon CoaDockWidgetPlugin::icon() const
{
   return QIcon(":/widgets/images/frame");
}


