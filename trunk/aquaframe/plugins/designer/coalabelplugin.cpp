#include "coalabelplugin.h"
#include <CoaLabel>

CoaLabelPlugin::CoaLabelPlugin(QObject *parent)
:CoaDisplayPlugin(QString("CoaLabel"), QString("CoaLabel"), parent)
{
}


QWidget * CoaLabelPlugin::createWidget(QWidget *parent)
{
   CoaLabel *label = new CoaLabel(parent);
   label->setText("Label");
   setInitWidth(100);
   setInitHeight(22);

   return label;
}


QIcon CoaLabelPlugin::icon() const
{
   return QIcon(":/widgets/images/label");
}


