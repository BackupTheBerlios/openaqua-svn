#include "coapushbuttonplugin.h"
#include "CoaPushButton"

CoaPushButtonPlugin::CoaPushButtonPlugin(QObject *parent)
:CoaBasePlugin(QString("CoaPushButton"), QString("CoaPushButton"), parent)
{
}


QWidget * CoaPushButtonPlugin::createWidget(QWidget *parent)
{

   return new CoaPushButton(parent);
}


