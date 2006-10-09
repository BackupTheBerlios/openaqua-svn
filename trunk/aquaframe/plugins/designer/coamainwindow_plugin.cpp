#include "coamainwindow_plugin.h"
#include "coamainwindow_container.h"

#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QExtensionManager>

#include <QtCore/qplugin.h>
#include <CoaMainWindow>

CoaMainWindowPlugin::CoaMainWindowPlugin(QObject *parent)
    : QObject(parent), m_initialized(false)
{}

QString CoaMainWindowPlugin::name() const
{ return QLatin1String("CoaMainWindow"); }



QString CoaMainWindowPlugin::group() const
{ return QLatin1String("Coa Framework"); }



QString CoaMainWindowPlugin::toolTip() const
{ return QString(); }



QString CoaMainWindowPlugin::whatsThis() const
{ return QString(); }



QString CoaMainWindowPlugin::includeFile() const
{ return QLatin1String("CoaMainWindow"); }



QIcon CoaMainWindowPlugin::icon() const
{ return QIcon(); }



bool CoaMainWindowPlugin::isContainer() const
{ return true; }



QWidget *CoaMainWindowPlugin::createWidget(QWidget *parent)
{
   return new CoaMainWindow("CoaMainWindow", parent);
}



bool CoaMainWindowPlugin::isInitialized() const
{ return m_initialized; }



void CoaMainWindowPlugin::initialize(QDesignerFormEditorInterface *core)
{
    Q_UNUSED(core);

    if (m_initialized)
        return;

    m_initialized = true;
    QExtensionManager *mgr = core->extensionManager();
    mgr->registerExtensions(new CoaMainWindowContainerFactory(mgr), Q_TYPEID(QDesignerContainerExtension));
}



QString CoaMainWindowPlugin::codeTemplate() const
{
   return QString();
}




QString CoaMainWindowPlugin::domXml() const
{
    return QLatin1String("\
    <widget class=\"CoaMainWindow\" name=\"widgetStack\">\
        <property name=\"geometry\">\
            <rect>\
                <x>0</x>\
                <y>0</y>\
                <width>100</width>\
                <height>80</height>\
            </rect>\
        </property>\
        <widget class=\"QWidget\" name=\"centralWidget\" />\
    </widget>\
    ");
}

