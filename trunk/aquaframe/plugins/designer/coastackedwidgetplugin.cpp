#include "coastackedwidgetplugin.h"
#include "CoaStackedWidget"

CoaStackedWidgetPlugin::CoaStackedWidgetPlugin(QObject *parent)
:CoaContainerPlugin(QString("CoaStackedWidget"), QString("CoaStackedWidget"), parent)
{
}


QWidget * CoaStackedWidgetPlugin::createWidget(QWidget *parent)
{
   return new CoaStackedWidget(parent);
}


QIcon CoaStackedWidgetPlugin::icon() const
{
   return QIcon(":/widgets/images/widgetstack");
}


