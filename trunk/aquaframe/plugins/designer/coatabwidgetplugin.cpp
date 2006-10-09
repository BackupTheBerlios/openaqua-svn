#include "coatabwidgetplugin.h"
#include "CoaTabWidget"

CoaTabWidgetPlugin::CoaTabWidgetPlugin(QObject *parent)
:CoaContainerPlugin(QString("CoaTabWidget"), QString("CoaTabWidget"), parent)
{
}


QWidget * CoaTabWidgetPlugin::createWidget(QWidget *parent)
{
   CoaTabWidget* tab = new CoaTabWidget(parent);
   tab->addTab ( new QWidget(), "Tab 1");
   tab->addTab ( new QWidget(), "Tab 2");
   return tab;
}


QIcon CoaTabWidgetPlugin::icon() const
{
   return QIcon(":/widgets/images/tabwidget");
}


