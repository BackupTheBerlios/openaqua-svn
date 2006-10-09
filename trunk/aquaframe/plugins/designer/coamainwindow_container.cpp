#include "coamainwindow_container.h"

#include <CoaMainWindow>

#include <CoaDebug>
#include <CoaToolBar>
#include <CoaMenuBar>
#include <CoaStatusBar>


CoaMainWindowContainer::CoaMainWindowContainer(CoaMainWindow *widget, QObject *parent)
    : QObject(parent),
      m_mainWindow(widget)
{}



int CoaMainWindowContainer::count() const
{
    return m_widgets.count();
}



QWidget *CoaMainWindowContainer::widget(int index) const
{
    if (index == -1)
        return 0;

    return m_widgets.at(index);
}



int CoaMainWindowContainer::currentIndex() const
{
    return m_mainWindow->centralWidget() ? 0 : -1;
}



void CoaMainWindowContainer::setCurrentIndex(int index)
{
    Q_UNUSED(index);
}

void CoaMainWindowContainer::addWidget(QWidget *widget)
{
    if (qobject_cast<CoaToolBar*>(widget)) {
        m_widgets.append(widget);
    } else if (qobject_cast<CoaToolBar*>(widget)) {
        m_widgets.append(widget);
    } else if (qobject_cast<CoaMenuBar*>(widget)) {
        (void) m_mainWindow->menuBar();
        m_widgets.append(widget);
    } else if (qobject_cast<CoaStatusBar*>(widget)) {
        (void) m_mainWindow->statusBar();
        m_widgets.append(widget);
    } else {
        Q_ASSERT(m_mainWindow->centralWidget() == 0);
        widget->setParent(m_mainWindow);
        m_mainWindow->setCentralWidget(widget);
        m_widgets.prepend(widget);
    }
}

void CoaMainWindowContainer::insertWidget(int index, QWidget *widget)
{
    m_widgets.insert(index, widget);
}

void CoaMainWindowContainer::remove(int index)
{
    m_widgets.removeAt(index);
}

CoaMainWindowContainerFactory::CoaMainWindowContainerFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{
}



QObject *CoaMainWindowContainerFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerContainerExtension))
        return 0;

    if (CoaMainWindow *w = qobject_cast<CoaMainWindow*>(object))
        return new CoaMainWindowContainer(w, parent);

    return 0;
}

