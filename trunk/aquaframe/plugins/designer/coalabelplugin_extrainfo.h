#ifndef __CoaLabelExtraInfo_h__
#define __CoaLabelExtraInfo_h__

#include <QtDesigner/QDesignerExtraInfoExtension>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QExtensionFactory>

#include <QtCore/QPointer>

class CoaLabel;

class CoaLabelExtraInfo: public QObject, public QDesignerExtraInfoExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerExtraInfoExtension)
public:
    CoaLabelExtraInfo(CoaLabel *widget, QDesignerFormEditorInterface *core, QObject *parent);

    virtual QWidget *widget() const;
    virtual QDesignerFormEditorInterface *core() const;

    virtual bool saveUiExtraInfo(DomUi *ui);
    virtual bool loadUiExtraInfo(DomUi *ui);

    virtual bool saveWidgetExtraInfo(DomWidget *ui_widget);
    virtual bool loadWidgetExtraInfo(DomWidget *ui_widget);

private:
    QPointer<CoaLabel> m_widget;
    QPointer<QDesignerFormEditorInterface> m_core;
};

class CoaLabelExtraInfoFactory: public QExtensionFactory
{
    Q_OBJECT
public:
    CoaLabelExtraInfoFactory(QDesignerFormEditorInterface *core, QExtensionManager *parent = 0);

protected:
    virtual QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;

private:
    QDesignerFormEditorInterface *m_core;
};

#endif // Q3TEXTEDIT_EXTRAINFO_H
