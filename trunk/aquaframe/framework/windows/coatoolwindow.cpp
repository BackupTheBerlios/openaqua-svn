#include "coatoolwindow.h"
#include <CoaDebug>
#include <CoaAction>
#include <CoaApplication>
#include <CoaWorkbench>
#include <CoaWorkspace>
#include <CoaWidget>
#include <CoaFrame>
#include <CoaGroupBox>
#include <CoaBorderLayout>
#include <CoaLabel>
#include <CoaPushButton>

#include <CoaVBoxLayout>

#include <QEvent>
#include <QCloseEvent>
#include <QMessageBox>


CoaToolWindow::CoaToolWindow(const QString& objectName,  CoaWorkbench *const parent, Qt::WFlags flags)
: CoaMainWindow(objectName, 0, flags)
, m_workbench(parent)
{
   BEGIN;
}

CoaToolWindow::~CoaToolWindow()
{
   BEGIN;
   if (m_workbench != 0) {
      m_workbench->remWindow(this);
   }
}


CoaWorkbench *  const CoaToolWindow::workbench() const
{
    return m_workbench;
}


void CoaToolWindow::addButton(CoaPushButton *const )
{
   BEGIN;
#if 0
   assert(button);
   assert(m_mainLayout);
   if (button == 0) return;

   if (m_btnLayout == 0){
      m_btnLayout = new QHBoxLayout;
      m_mainLayout->addLayout(m_btnLayout);
   }

   m_btnLayout->addWidget(button);
#endif
}


void CoaToolWindow::addButtonStretch()
{
   BEGIN;
#if 0
   assert(m_mainLayout);

   if (m_btnLayout == 0){
      m_btnLayout = new QHBoxLayout;
      m_mainLayout->addLayout(m_btnLayout);
   }

   m_btnLayout->addStretch();
#endif
}


