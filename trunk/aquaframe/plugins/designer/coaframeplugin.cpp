#include "coaframeplugin.h"
#include "CoaFrame"

CoaFramePlugin::CoaFramePlugin(QObject *parent)
:CoaContainerPlugin(QString("CoaFrame"), QString("CoaFrame"), parent)
{
}


QWidget * CoaFramePlugin::createWidget(QWidget *parent)
{
   return new CoaFrame(parent);
}


QIcon CoaFramePlugin::icon() const
{
   return QIcon(":/widgets/images/frame");
}


