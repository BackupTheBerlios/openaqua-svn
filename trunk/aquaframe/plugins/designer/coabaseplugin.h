#ifndef __CoaBasePlugin_h__
#define __CoaBasePlugin_h__

#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerCustomWidgetInterface>

#include <QtCore/qplugin.h>

#include <QString>

class CoaBasePlugin:  public QObject,
                      public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    CoaBasePlugin(    QString widgetName, //not PluginName!!!
                      QString includeFile,
                      QObject *parent = 0);

    virtual bool isContainer()    const;
    virtual bool isInitialized()  const;
    virtual QString codeTemplate() const;
    virtual QString group() const;
    virtual QString includeFile() const;
    virtual QString name() const;
    virtual QString toolTip() const;
    virtual QString whatsThis() const;
    virtual void initialize(QDesignerFormEditorInterface *core);
    virtual QString domXml() const;
    virtual QIcon icon() const;

protected:

    virtual void setWhatsThis(QString&);
    virtual void setToolTip(QString&);
    virtual void setGroup(QString&);
    virtual void setIsContainer(bool);
    virtual void setInitWidth(const int);
    virtual void setInitHeight(const int);
    virtual int initWidth() const;
    virtual int initHeight() const;


private:
   int     _width;
   int     _height;
   bool    _isInitialized;
   bool    _isContainer;
   QString _codeTemplate;
   QString _group;
   QString _includeFile;
   QString _toolTip;
   QString _whatsThis;
};


class CoaDisplayPlugin:  public CoaBasePlugin {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    CoaDisplayPlugin(    QString widgetName, //not PluginName!!!
                         QString includeFile,
                         QObject *parent = 0);

};



class CoaContainerPlugin:  public CoaBasePlugin {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)


public:
    CoaContainerPlugin(    QString widgetName, //not PluginName!!!
                           QString includeFile,
                           QObject *parent = 0);
    virtual QString domXml() const;

};



#endif
