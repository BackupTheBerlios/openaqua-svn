#include "coaapplicationwindow.h"
#include <CoaDebug>
#include <cassert>
#include <CoaAction>
#include <CoaApplication>
#include <CoaWorkbench>
#include <CoaWorkspace>


#include <QEvent>
#include <QCloseEvent>
#include <QMessageBox>



CoaApplicationWindow::CoaApplicationWindow(const QString& objectName,  CoaWorkspace *const parent, Qt::WFlags flags)
: CoaMainWindow(objectName, 0, flags)
, m_workspace(parent)
{
   assert(parent);

   BEGIN;
   if (objectName.isEmpty()) {
      setObjectName(objectName);
   }

   if (m_workspace != 0) {
      m_workspace->addWindow(this);
   }

}



CoaApplicationWindow::~CoaApplicationWindow()
{
   BEGIN;
   if (m_workspace!= 0) {
      //m_workspace->remWindow(this);
   }
}

void CoaApplicationWindow::setWindowTitle(const QString& windowTitle)
{
   BEGIN;
   m_windowTitle = windowTitle;
   QString title = m_windowTitle;
   //title.replace("%1", m_saveTarget);
   QMainWindow::setWindowTitle(title);
}

#if 0
void CoaApplicationWindow::workbench(CoaWorkbench *workbench)
{
   BEGIN;
   m_workbench = workbench;
}



CoaWorkbench *const CoaApplicationWindow::getWorkbench() const
{
   BEGIN;
   return m_workbench;
}
#endif

