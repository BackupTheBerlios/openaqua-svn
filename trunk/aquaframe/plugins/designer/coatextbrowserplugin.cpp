#include "coatextbrowserplugin.h"
#include "CoaTextBrowser"

CoaTextBrowserPlugin::CoaTextBrowserPlugin(QObject *parent)
:CoaDisplayPlugin(QString("CoaTextBrowser"), QString("CoaTextBrowser"), parent)
{
}


QWidget * CoaTextBrowserPlugin::createWidget(QWidget *parent)
{
   return new CoaTextBrowser(parent);
}


QIcon CoaTextBrowserPlugin::icon() const
{
   return QIcon(":/widgets/images/textedit");
}


