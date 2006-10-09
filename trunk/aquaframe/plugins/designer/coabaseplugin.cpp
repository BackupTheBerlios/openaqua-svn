#include "coabaseplugin.h"

CoaBasePlugin::CoaBasePlugin(  QString widgetName,
                               QString includeFile,
                               QObject *parent )
:QObject(parent)
,_width(100)
,_height(20)
, _isInitialized (false)
, _isContainer (false)
, _codeTemplate()
, _group()
, _includeFile()
, _toolTip()
, _whatsThis()

{
   setObjectName(widgetName);
   _includeFile = includeFile;
   _group = "Coa Framework";
}



bool CoaBasePlugin::isContainer() const
{

   return _isContainer;
}

bool CoaBasePlugin::isInitialized() const
{

   return _isInitialized;
}




QString CoaBasePlugin::codeTemplate() const
{

   return _codeTemplate;

}


QString CoaBasePlugin::group() const
{

   return _group;
}


QString CoaBasePlugin::includeFile() const
{

   return _includeFile;
}


QString CoaBasePlugin::name() const
{

   return objectName();
}


QString CoaBasePlugin::toolTip() const
{

   return _toolTip;
}


QString CoaBasePlugin::whatsThis() const
{

   return _whatsThis;
}




void CoaBasePlugin::initialize(QDesignerFormEditorInterface *core)
{
   Q_UNUSED(core);
   if (true != _isInitialized) {
      _isInitialized = true;
   }
}


void CoaBasePlugin::setWhatsThis(QString& s)
{
   _whatsThis = s;
}



void CoaBasePlugin::setToolTip(QString& s)
{
   _toolTip = s;
}


void CoaBasePlugin::setGroup(QString& s)
{
   _group = s;
}


void CoaBasePlugin::setIsContainer(bool b)
{
   _isContainer = b;
}


void CoaBasePlugin::setInitWidth(const int i)
{
   _width=i;
}


void CoaBasePlugin::setInitHeight(const int i)
{
   _height=i;
}


int CoaBasePlugin::initWidth() const
{
   return _width;
}


int CoaBasePlugin::initHeight() const
{
   return _height;
}



QString CoaBasePlugin::domXml() const
{
   return QString::fromUtf8("<widget class=\"%1\" name=\"%2\"/>")
           .arg(objectName())
           .arg(name())
           ;
}

QIcon CoaBasePlugin::icon() const
{
   return QIcon();
}


CoaDisplayPlugin::CoaDisplayPlugin(  QString widgetName, //not PluginName!!!
                                     QString includeFile,
                                     QObject *parent )
:CoaBasePlugin(widgetName, includeFile, parent)
{
   QString a = "Coa Display Widgets";
   setGroup(a);
};


CoaContainerPlugin::CoaContainerPlugin(  QString widgetName, //not PluginName!!!
                                     QString includeFile,
                                     QObject *parent )
:CoaBasePlugin(widgetName, includeFile, parent)
{
   QString a = "Coa Container Widgets";
   setGroup(a);
   setIsContainer(true);
};


QString CoaContainerPlugin::domXml() const
{

   return QString::fromUtf8
   (
   "<widget class=\"%1\" name=\"%2\">"
   "   <property name=\"geometry\">"
   "      <rect>"
   "         <x>0</x>"
   "         <y>0</y>"
   "         <width>150</width>"
   "         <height>150</height>"
   "      </rect>"
   "   </property>"
   "</widget>"
   ).arg(objectName()).arg(name());
}
