#include "coatableviewplugin.h"
#include "CoaTableView"

CoaTableViewPlugin::CoaTableViewPlugin(QObject *parent)
   :CoaBasePlugin(QString("CoaTableView"), QString("CoaTableView"), parent)
{
}


QWidget * CoaTableViewPlugin::createWidget(QWidget *parent)
{

   return new CoaTableView(parent);
}


