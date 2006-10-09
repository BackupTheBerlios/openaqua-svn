#include "coatexteditplugin.h"
#include "CoaTextEdit"

CoaTextEditPlugin::CoaTextEditPlugin(QObject *parent)
:CoaBasePlugin(QString("CoaTextEdit"), QString("CoaTextEdit"), parent)
{
}


QWidget * CoaTextEditPlugin::createWidget(QWidget *parent)
{

   return new CoaTextEdit(parent);
}


QIcon CoaTextEditPlugin::icon() const
{
   return QIcon(":/widgets/images/textedit");
}


