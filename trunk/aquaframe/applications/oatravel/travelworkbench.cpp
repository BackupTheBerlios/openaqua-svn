#include "travelworkbench.h"
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
#include <CoaApplication>
#include <CoaFile>

#include "travelmainwindow.h"
#include "contact/contactwindow.h"


TravelWorkbench::TravelWorkbench (CoaGuiThreadMaker const*const threadmaker)
: CoaWorkbench(threadmaker)
{
   BEGIN;


}



TravelWorkbench::~TravelWorkbench()
{
   BEGIN;
}


void TravelWorkbench::initialize()
{
   CoaWorkbench::initialize();
   initActions();

#ifdef Q_WS_MAC
   slotSwitchToSDIMode();
   slotFileNew(); //create a first, empty window
#else
   slotSwitchToMDIMode();
   //slotFileNew(); //create a first, empty window
#endif


}


void TravelWorkbench::initActions()
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

   action = GETACTION (CoaDefaultActions::actionFileSaveAs);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileSaveAs()));

   action = GETACTION (CoaDefaultActions::actionFileSaveAll);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileSaveAll()));

   action = GETACTION (CoaDefaultActions::actionFileClose);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileClose()));

   action = GETACTION (CoaDefaultActions::actionFileCloseAll);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotFileCloseAll()));

   action = 0;
}



void TravelWorkbench::slotFileOpen()
{
   BEGIN;
   CoaWorkspace *workspace = getWorkspace();
   if (workspace != 0){
      //MDI Handle
      QWidget *widget = workspace->activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->slotFileOpen();
      }


   } else {
      //SDI Handle
      QWidget *widget = CoaApplication::activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->slotFileOpen();
      }
   }

}



void TravelWorkbench::slotFileNew()
{
   BEGIN;
   TravelMainWindow *window = new TravelMainWindow("TravelMainWindow", this);
   window->initialize(); //init the DataModel?
   if (window->slotFileNew() == true) {
      initWindow(window);
      addWindow(window);
      showWindow(window);
   } else {
      delete window;
   }

}



void TravelWorkbench::slotFileNewContact()
{
   BEGIN;
   ContactWindow *window = new ContactWindow("ContactWindow", this);
   window->initialize(); //init the DataModel?
   if (window->slotFileNew() == true) {
      initWindow(window);
      addWindow(window);
      showWindow(window);
   } else {
      delete window;
   }

}


void TravelWorkbench::slotFileSave()
{
   BEGIN;
   CoaWorkspace *workspace = getWorkspace();
   if (workspace != 0){
      //MDI Handle
      QWidget *widget = workspace->activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->slotFileSave();
      }


   } else {
      //SDI Handle
      QWidget *widget = CoaApplication::activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->slotFileSave();
      }
   }

}





void TravelWorkbench::slotFileSaveAs()
{
   BEGIN;

   CoaWorkspace *workspace = getWorkspace();
   if (workspace != 0){
      //MDI Handle
      QWidget *widget = workspace->activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->saveChangesAs();
      }


   } else {
      //SDI Handle
      QWidget *widget = CoaApplication::activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->saveChangesAs();
      }
   }



}


void TravelWorkbench::slotFileSaveAll()
{
   BEGIN;
}


void TravelWorkbench::slotFileClose()
{
   BEGIN;

   CoaWorkspace *workspace = getWorkspace();
   if (workspace != 0){
      //MDI Handle
      QWidget *widget = workspace->activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->close();
      }


   } else {
      //SDI Handle
      QWidget *widget = CoaApplication::activeWindow();
      if (widget != 0) {
         TravelMainWindow *window = qobject_cast<TravelMainWindow*>(widget);
         if (window != 0) window->slotFileClose();
         if (window != 0) window->close();
      }
   }

}



bool TravelWorkbench::slotFileCloseAll()
{
   BEGIN;
   RETURN(true);
}


CoaMenuBar*const TravelWorkbench::createGlobalMenuBar()
{
   BEGIN;
   Q_INIT_RESOURCE(oatravel);
   CoaMenuBarBuilder builder;
   CoaFile file(":/form/menubardescription.xml");
   return builder.getMenuBar(&file);
}


CoaToolBar*const TravelWorkbench::createGlobalToolBar()
{
   BEGIN;
   Q_INIT_RESOURCE(oatravel);
   CoaToolBarBuilder builder;
   CoaFile file(":/form/toolbardescription.xml");
   return builder.getToolBar(&file);
}


void TravelWorkbench::slotApplicationQuit()
{
   BEGIN;
   if (slotFileCloseAll() == true) {
      CoaWorkbench::slotApplicationQuit();
   }
}

