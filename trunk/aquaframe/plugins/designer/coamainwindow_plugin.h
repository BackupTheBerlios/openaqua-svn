#ifndef COAMAINWINDOW_PLUGIN_H
#define COAAINWINDOW_PLUGIN_H

#include <QtDesigner/QDesignerCustomWidgetInterface>

class CoaMainWindowPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    CoaMainWindowPlugin(QObject *parent = 0);

    virtual QString name() const;
    virtual QString group() const;
    virtual QString toolTip() const;
    virtual QString whatsThis() const;
    virtual QString includeFile() const;
    virtual QIcon icon() const;
    virtual bool isContainer() const;
    virtual QWidget *createWidget(QWidget *parent);
    virtual bool isInitialized() const;
    virtual void initialize(QDesignerFormEditorInterface *core);
    virtual QString codeTemplate() const;
    virtual QString domXml() const;

private:
    bool m_initialized;
};


#endif 

