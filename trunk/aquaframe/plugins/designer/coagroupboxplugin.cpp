#include "coagroupboxplugin.h"
#include "CoaGroupBox"

CoaGroupBoxPlugin::CoaGroupBoxPlugin(QObject *parent)
:CoaContainerPlugin(QString("CoaGroupBox"), QString("CoaGroupBox"), parent)
{
}


QWidget * CoaGroupBoxPlugin::createWidget(QWidget *parent)
{
   return new CoaGroupBox(parent);
}


QIcon CoaGroupBoxPlugin::icon() const
{
   return QIcon(":/widgets/images/groupbox");
}


