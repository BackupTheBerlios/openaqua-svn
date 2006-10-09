#include "letterworkbench.h"
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

#include <CoaFile>



LetterWorkbench::LetterWorkbench (CoaGuiThreadMaker const*const threadmaker)
: CoaWorkbench(threadmaker)
{
   BEGIN;


}



LetterWorkbench::~LetterWorkbench()
{
   BEGIN;
}


void LetterWorkbench::initialize()
{
   CoaWorkbench::initialize();
   initActions();


#ifdef Q_WS_MAC
   slotFileNew(); //create a first, empty window
   slotSwitchToSDIMode();
#else
   slotSwitchToMDIMode();
   //slotFileNew(); //create a first, empty window
#endif


}


void LetterWorkbench::initActions()
{
   BEGIN;

   CoaAction *action;

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



void LetterWorkbench::slotFileOpen()
{
   BEGIN;
}



void LetterWorkbench::slotFileNew()
{
   BEGIN;
   Q_INIT_RESOURCE(oaletter);
   CoaApplicationWindow *win = createNewApplicationWindow(":/form/mainwindow.ui", "Letter: ");
   win->setWindowTitle("LetterWindow: %1 [*]");
}



void LetterWorkbench::slotFileSave()
{
   BEGIN;
}


void LetterWorkbench::slotFileSaveAs()
{
   BEGIN;
}


void LetterWorkbench::slotFileSaveAll()
{
   BEGIN;
}


void LetterWorkbench::slotFileClose()
{
   BEGIN;

}



void LetterWorkbench::slotFileCloseAll()
{
   BEGIN;
}


CoaMenuBar*const LetterWorkbench::createGlobalMenuBar()
{
   BEGIN;
   Q_INIT_RESOURCE(oaletter);
   CoaMenuBarBuilder builder;
   CoaFile file(":/form/menubardescription.xml");
   return builder.getMenuBar(&file);
}


CoaToolBar*const LetterWorkbench::createGlobalToolBars()
{
   BEGIN;
   Q_INIT_RESOURCE(oaletter);
   CoaToolBarBuilder builder;
   CoaFile file(":/form/toolbardescription.xml");
   return builder.getToolBar(&file);
}



