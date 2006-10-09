#include "workbench.h"
#include "mainwindow.h"

#include <CoaDebug>
#include <CoaGuiThreadMaker>
#include <CoaAction>
#include <CoaActionFactory>
#include <CoaApplicationWindow>
#include <CoaDefaultActions>
#include <CoaMenuBar>
#include <CoaToolBar>
#include <CoaMenuBarBuilder>
#include <CoaToolBarBuilder>
#include <CoaWorkspace>
#include <CoaSettings>
#include <CoaApplication>
#include <CoaStringList>
#include <CoaFile>


#include <CoaFileDialog>

const CoaString LASTFILEPATH="lastFilePath";

Workbench::Workbench (CoaGuiThreadMaker const*const threadmaker)
: CoaWorkbench(threadmaker)
{
   BEGIN;
}



Workbench::~Workbench()
{
   BEGIN;
}


void Workbench::initialize()
{
   CoaWorkbench::initialize();
   initActions();
   slotSwitchToMDIMode();
}


void Workbench::initActions()
{
   BEGIN;

   CoaAction *action;

   //action = GETACTION (CoaDefaultActions::actionApplicationSettings);
   //QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileNewContact()));

   action = GETACTION (CoaDefaultActions::actionFileNew);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileNew()));

   action = GETACTION (CoaDefaultActions::actionFileOpen);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileOpen()));

   action = GETACTION (CoaDefaultActions::actionFileSave);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileSave()));

   action = GETACTION (CoaDefaultActions::actionFileSaveAll);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileSaveAll()));

   action = GETACTION (CoaDefaultActions::actionFileClose);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileClose()));

   action = GETACTION (CoaDefaultActions::actionFileCloseAll);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileCloseAll()));

   action = 0;
}



void Workbench::slotFileOpen()
{
   BEGIN;
   MainWindow *window = new MainWindow("MainWindow", magicalParent(), 0);
   window->initialize(); //init the DataModel?
   initWindow(window);
   addWindow(window);
   showWindow(window);
}



void Workbench::slotFileNew()
{
   BEGIN;
   MainWindow *window = new MainWindow("MainWindow", magicalParent(), 0);
   window->initialize(); //init the DataModel?
   initWindow(window);
   addWindow(window);
   showWindow(window);

}





void Workbench::slotFileSave()
{
   BEGIN;
   CoaWorkspace *workspace = getWorkspace();

   if (workspace != 0){
      //MDI Handle
      QWidget *widget = workspace->activeWindow();
      if (widget != 0) {
         MainWindow *window = qobject_cast<MainWindow*>(widget);
         if (window != 0) window->editingCommit();
      }
   } else {
      //SDI Handle
      QWidget *widget = CoaApplication::activeWindow();
      if (widget != 0) {
         MainWindow *window = qobject_cast<MainWindow*>(widget);
         if (window != 0) window->editingCommit();
      }
   }
}




void Workbench::slotFileSaveAll()
{
   BEGIN;
}


void Workbench::slotFileClose()
{
   BEGIN;
#if 0
   CoaWorkspace *workspace = getWorkspace();
   if (workspace != 0){
      //MDI Handle
      QWidget *widget = workspace->activeWindow();
      if (widget != 0) {
         MainWindow *window = qobject_cast<MainWindow*>(widget);
         if (window != 0) window->close();
      }


   } else {
      //SDI Handle
      QWidget *widget = CoaApplication::activeWindow();
      if (widget != 0) {
         MainWindow *window = qobject_cast<MainWindow*>(widget);
         if (window != 0) window->slotFileClose();
         if (window != 0) window->close();
      }
   }
#endif
}



bool Workbench::slotFileCloseAll()
{
   BEGIN;
   RETURN(true);
}


CoaMenuBar*const Workbench::createGlobalMenuBar()
{
   BEGIN;
   Q_INIT_RESOURCE(actioneditor);
   CoaMenuBarBuilder builder;
   CoaFile file(":/form/menubardescription.xml");
   return builder.getMenuBar(&file);
}


CoaToolBar*const Workbench::createGlobalToolBar()
{
   BEGIN;
   Q_INIT_RESOURCE(actioneditor);
   CoaToolBarBuilder builder;
   CoaFile file(":/form/toolbardescription.xml");
   return builder.getToolBar(&file);
}


void Workbench::slotApplicationQuit()
{
   BEGIN;
   if (slotFileCloseAll() == true) {
      CoaWorkbench::slotApplicationQuit();
   }
}

