#include "coalineeditplugin.h"
#include "CoaLineEdit"

CoaLineEditPlugin::CoaLineEditPlugin(QObject *parent)
:CoaBasePlugin(QString("CoaLineEdit"), QString("CoaLineEdit"), parent)
{
}


QWidget * CoaLineEditPlugin::createWidget(QWidget *parent)
{

   return new CoaLineEdit(parent);
}


QIcon CoaLineEditPlugin::icon() const
{
   return QIcon(":/widgets/images/lineedit");
}


