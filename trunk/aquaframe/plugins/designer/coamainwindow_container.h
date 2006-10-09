#ifndef COAMAINWINDOW_CONTAINER_H
#define COAMAINWINDOW_CONTAINER_H

#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QExtensionFactory>

class CoaMainWindow;

class CoaMainWindowContainer: public QObject, public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    CoaMainWindowContainer(CoaMainWindow *widget, QObject *parent = 0);

    virtual int count() const;
    virtual QWidget *widget(int index) const;
    virtual int currentIndex() const;
    virtual void setCurrentIndex(int index);
    virtual void addWidget(QWidget *widget);
    virtual void insertWidget(int index, QWidget *widget);
    virtual void remove(int index);

private:
    CoaMainWindow *m_mainWindow;
    QList<QWidget*> m_widgets;
};

class CoaMainWindowContainerFactory: public QExtensionFactory
{
    Q_OBJECT
public:
    CoaMainWindowContainerFactory(QExtensionManager *parent = 0);

protected:
    virtual QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

#endif // COAMAINWINDOW_CONTAINER_H
