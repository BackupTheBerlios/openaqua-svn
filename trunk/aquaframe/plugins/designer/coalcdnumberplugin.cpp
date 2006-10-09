#include "coalcdnumberplugin.h"
#include "CoaLCDNumber"

CoaLCDNumberPlugin::CoaLCDNumberPlugin(QObject *parent)
:CoaDisplayPlugin(QString("CoaLCDNumber"), QString("CoaLCDNumber"), parent)
{
}


QWidget * CoaLCDNumberPlugin::createWidget(QWidget *parent)
{
   return new CoaLCDNumber(parent);
}


QIcon CoaLCDNumberPlugin::icon() const
{
   return QIcon(":/widgets/images/lcdnumber");
}


