#include "coatoolboxplugin.h"
#include "CoaToolBox"

CoaToolBoxPlugin::CoaToolBoxPlugin(QObject *parent)
:CoaContainerPlugin(QString("CoaToolbox"), QString("CoaToolBox"), parent)
{
}


QWidget * CoaToolBoxPlugin::createWidget(QWidget *parent)
{
   CoaToolBox* box = new CoaToolBox(parent);
   box->addItem ( new QWidget(box), "Page 1");
   box->addItem ( new QWidget(box), "Page 2");
   return box;
}


QIcon CoaToolBoxPlugin::icon() const
{
   return QIcon(":/widgets/images/toolbox");
}


