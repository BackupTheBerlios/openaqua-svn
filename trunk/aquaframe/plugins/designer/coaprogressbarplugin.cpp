#include "coaprogressbarplugin.h"
#include "CoaProgressBar"

CoaProgressBarPlugin::CoaProgressBarPlugin(QObject *parent)
:CoaDisplayPlugin(QString("CoaProgressBar"), QString("CoaProgressBar"), parent)
{
}


QWidget * CoaProgressBarPlugin::createWidget(QWidget *parent)
{
   return new CoaProgressBar(parent);
}


QIcon CoaProgressBarPlugin::icon() const
{
   return QIcon(":/widgets/images/progress");
}


