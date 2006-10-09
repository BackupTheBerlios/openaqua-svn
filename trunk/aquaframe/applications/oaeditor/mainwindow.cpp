#include "mainwindow.h"
#include <CoaDebug>

#include <CoaToolBar>
#include <CoaMenuBar>
#include <cassert>
#include <CoaFormFactory>

MainWindow::MainWindow(QWidget* owner)
:CoaMainWindow("MainWindow", owner)
{
   BEGIN;

   //Create the central form

   CoaFormFactory factory(this);
   factory.formBuild(":/form/mainwindow.ui");

#if 0
   //Create toolbars
   CoaToolBar *toolBar = new CoaToolBar(this);
   addToolBar(Qt::TopToolBarArea, toolBar);
   toolBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupApplication));
   toolBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupFile));
   toolBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupEdit));
   toolBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupHelp));

   //Create menubars
   CoaMenuBar *menuBar = new CoaMenuBar(this);
   setMenuBar(menuBar);
   menuBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupApplication));
   menuBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupFile));
   menuBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupEdit));
   menuBar->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupHelp));
#endif
}

