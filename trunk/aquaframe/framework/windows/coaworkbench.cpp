#include "coaworkbench.h"
#include <CoaDebug>
#include <CoaDebugThread>

#include <CoaApplication>
#include <CoaMainWindow>
#include <CoaWorkspace>
#include <CoaMenuBar>
#include <CoaToolBar>
#include <CoaApplicationWindow>
#include <CoaSingletonWatch>
#include <CoaGuiThreadMaker>
#include <CoaMenuBar>
#include <CoaStatusBar>
#include <CoaActionFactory>
#include <CoaAction>
#include <CoaFormFactory>
#include <CoaToolsChangeShortcuts>
#include <CoaToolsChangeDebugSettings>
#include <CoaToolsSqlBrowser>
#include <CoaToolsSqlEditor>
#include <CoaPrintDialog>
#include <CoaTextBrowser>
#include <CoaTextDocument>
#include <CoaAboutBox>
#include <CoaToolWindow>
#include <CoaTextEdit>
#include <CoaLineEdit>


//Actions
#include <CoaDefaultActions>
#include <CoaActionFactory>
#include <CoaActionBuilderFile>
#include <CoaActionBuilderEdit>
#include <CoaActionBuilderHelp>
#include <CoaActionBuilderDebug>
#include <CoaActionBuilderApplication>
#include <CoaActionBuilderDatabase>


#include <CoaToolsSettings>

#include <cassert>


#include <QClipboard>
#include <QDesktopWidget>
#include <QWhatsThis>
#include <QWidget>

CoaWorkbench* CoaWorkbench::INSTANCE =  0;

CoaWorkbench *const CoaWorkbench::getInstance()
{
   return INSTANCE;
}




/**
Hint: The CoaGuiThreadMaker isn't used. The param is here to make sure
that the final customer use a well defined approach for creating/destroying
threads
*/
CoaWorkbench::   CoaWorkbench (CoaGuiThreadMaker const*const )
: m_workspace(0)
, m_masterwindow(0)
, m_printer(CoaPrinter::HighResolution)
, m_globalMenuBar(0)
, m_globalToolBar(0)

{
   BEGIN;
   m_initializing = true;
   REGISTERSINGLETON("CoaWorkbench");
   INSTANCE = this;
}





CoaWorkbench::~CoaWorkbench()
{
   BEGIN;
   UNREGISTERSINGLETON("CoaWorkbench");
   INSTANCE = 0;


   //delete workspace
   //delete m_workspace;



   //delete m_globalToolBar;
   //delete m_globalMenuBar;

   //still known windows
   //foreach(CoaMainWindow* window, m_setWindows) {
   //   ERR(QString("Still known Window in Workbench: %1").arg(window->objectName()));
   //}

}



void CoaWorkbench::initialize()
{
   BEGIN;

   if (m_initializing == false) return;

   m_mode = NeutralMode;

   //Init the Action Factory
   CoaActionFactory::getInstance()->addActionBuilder(CoaActionBuilderFile::getInstance());
   CoaActionFactory::getInstance()->addActionBuilder(CoaActionBuilderEdit::getInstance());
   CoaActionFactory::getInstance()->addActionBuilder(CoaActionBuilderHelp::getInstance());
   CoaActionFactory::getInstance()->addActionBuilder(CoaActionBuilderDebug::getInstance());
   CoaActionFactory::getInstance()->addActionBuilder(CoaActionBuilderApplication::getInstance());
   CoaActionFactory::getInstance()->addActionBuilder(CoaActionBuilderDatabase::getInstance());

   //Create Menu- and Toolbar
   m_globalMenuBar = createGlobalMenuBar();
   if (m_globalMenuBar == 0) return;
   m_globalToolBar = createGlobalToolBar();
   if (m_globalToolBar == 0) return;

   #ifdef Q_WS_MAC
   //Show the MenuBar on a Mac
   m_globalMenuBar->show();
   #endif


   //Connect Actions
   CoaAction *action;

   action = GETACTION (CoaDefaultActions::actionApplicationSettings);
   QObject::connect (action, SIGNAL(triggered()), this, SLOT(slotToolsSettings()));

   action = GETACTION (CoaDefaultActions::actionApplicationSwitchSDIMode);
   connect (action, SIGNAL(triggered()), this, SLOT(slotSwitchToSDIMode()), Qt::QueuedConnection);

   action = GETACTION (CoaDefaultActions::actionApplicationSwitchMDIMode);
   connect (action, SIGNAL(triggered()), this, SLOT(slotSwitchToMDIMode()), Qt::QueuedConnection);

   action = GETACTION (CoaDefaultActions::actionEditSelectAll);
   connect (action, SIGNAL(triggered()), this, SLOT(slotEditSelectAll()) );

   action = GETACTION (CoaDefaultActions::actionEditCut);
   connect (action, SIGNAL(triggered()), this, SLOT(slotEditCut()) );

   action = GETACTION (CoaDefaultActions::actionEditCopy);
   connect (action, SIGNAL(triggered()), this, SLOT(slotEditCopy()) );

   action = GETACTION (CoaDefaultActions::actionEditPaste);
   connect (action, SIGNAL(triggered()), this, SLOT(slotEditPaste()) );

   action = GETACTION (CoaDefaultActions::actionEditUndo);  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotEditUndo()) );

   action = GETACTION (CoaDefaultActions::actionEditRedo);   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotEditRedo()) );


   action = GETACTION (CoaDefaultActions::actionApplicationAboutApplication);   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotApplicationAboutBox()), Qt::QueuedConnection );

   action = GETACTION (CoaDefaultActions::actionApplicationQuit);   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotApplicationQuit()), Qt::QueuedConnection );

   action = GETACTION (CoaDefaultActions::actionApplicationSetShortcuts);   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotApplicationSetShortcuts()), Qt::QueuedConnection );

   action = GETACTION (CoaDefaultActions::actionDatabaseSqlBrowser);   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDatabaseSqlBrowser()), Qt::QueuedConnection );

   action = GETACTION (CoaDefaultActions::actionDatabaseSqlEditor);   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDatabaseSqlEditor()), Qt::QueuedConnection );


   action = GETACTION (CoaDefaultActions::actionApplicationPrintShortcuts);   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotApplicationPrintShortcuts()), Qt::QueuedConnection );


   //Get the Debug Settings Tool window
   action = GETACTION (CoaDefaultActions::actionDebugSettings);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugSettings()), Qt::QueuedConnection );

   //show time in debug
   action = GETACTION (CoaDefaultActions::actionDebugShowTimeOnOff);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugShowTimeOnOff()), Qt::QueuedConnection );

   //enable/disable Debugging
   action = GETACTION (CoaDefaultActions::actionDebugOnOff);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugOnOff()), Qt::QueuedConnection );


   //set up action for debug levels
   action = GETACTION (CoaDefaultActions::actionDebugFileDefaultsOff);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugFileDefaultsOff()), Qt::QueuedConnection );
   action = GETACTION (CoaDefaultActions::actionDebugFileDefaultsErr);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugFileDefaultsErr()), Qt::QueuedConnection );
   action = GETACTION (CoaDefaultActions::actionDebugFileDefaultsWrn);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugFileDefaultsWrn()), Qt::QueuedConnection );
   action = GETACTION (CoaDefaultActions::actionDebugFileDefaultsInf);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugFileDefaultsInf()), Qt::QueuedConnection );
   action = GETACTION (CoaDefaultActions::actionDebugFileDefaultsDbg);                  assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotDebugFileDefaultsDbg()), Qt::QueuedConnection );

   action = GETACTION (CoaDefaultActions::actionHelpWhatsthis);
   assert(action);
   connect (action, SIGNAL(triggered()), this, SLOT(slotHelpShowWhatsThis()), Qt::QueuedConnection );

   action = 0;

   m_initializing = false;
   emit initialized();

}







CoaWorkbench::UIMode CoaWorkbench::mode() const
{
   BEGIN;
   return m_mode;
}



void CoaWorkbench::slotSwitchToNeutralMode()
{
   BEGIN;
   if (m_mode == NeutralMode)  return;

   //some checks
   if (m_mode == MDIMode) {
      assert(m_workspace != 0);
      //CoaApplicationWindow *masterwindow = m_workspace->window();
   }


   //get Desktop offsets
   QPoint desktopOffset = QPoint(0, 0);
   QPoint workspaceOffset = QPoint(0, 0);
   if (m_mode == SDIMode) {
      desktopOffset = CoaApplication::desktop()->availableGeometry().topLeft();
   } else if (m_mode == MDIMode) {
      workspaceOffset = m_workspace->mapToGlobal(QPoint(0, 0));
   }

   //set the new mode
   m_mode = NeutralMode;


   //iterate over all known application windows, get position, remove parent
   m_hashVisibilities.clear();
   m_hashGeometries.clear();
   foreach (CoaMainWindow *window, m_setWindows) {
      window->setMenuBar(0);

      m_hashVisibilities.insert(window, window->isVisible());
      if (window->isVisible()) {
         QPoint pos = window->window()->pos();
         if (!window->isWindow()) {
            if (QWidget *p = window->parentWidget()) {
               pos = p->pos(); // in workspace
            }
         }
         m_hashGeometries.insert(window, QRect(pos - desktopOffset, window->size()));
      }
      window->setParent(0);
    }



   //remove parents
#ifndef Q_WS_MAC
   if (m_globalMenuBar != 0) {
      m_globalMenuBar->setParent(0);
   }
#endif
   if (m_globalToolBar != 0) {
      m_globalToolBar->setParent(0);
   }

   if (m_workspace) {
      delete m_workspace->parentWidget();
      m_workspace = 0;
      m_masterwindow = 0;
   }



}




void CoaWorkbench::slotSwitchToMDIMode()
{
   BEGIN;

   if (m_mode == MDIMode) return;

   slotSwitchToNeutralMode();
   m_mode = MDIMode;

   //Build the ApplicationWindow itself
   if (m_masterwindow == 0 ) {
      m_masterwindow = new CoaMainWindow("WorkbenchMasterWindow", 0);
   }

   assert(m_masterwindow  != 0);
   assert(m_globalMenuBar != 0);
   assert(m_globalToolBar != 0);


   //the Menubar
   m_masterwindow->setMenuBar(m_globalMenuBar);
   m_masterwindow->addToolBar(Qt::TopToolBarArea, m_globalToolBar);

   //the workspace
   m_workspace = new CoaWorkspace(m_masterwindow);
   m_workspace->setScrollBarsEnabled(true);
   m_masterwindow->setCentralWidget(m_workspace);

   if (m_masterwindow != 0)
      m_masterwindow->show();

   //Deal with each single Window
   assert(m_workspace);
   QPoint workspace_tl = m_workspace->mapToGlobal(QPoint(0, 0));
   foreach (CoaMainWindow *aw, m_setWindows) {
      aw->setParent(magicalParent(), magicalWindowFlags(aw));
      m_workspace->addWindow(aw);
      QRect g = m_hashGeometries.value(aw, aw->geometry());
      aw->resize(g.size());
      aw->move(g.topLeft());
      aw->setVisible(m_hashVisibilities[aw]);
   }

   //some optical settings
   QString appTitle = COAAPP->applicationName ();
   m_masterwindow->setWindowTitle(appTitle);
   m_masterwindow->readSettings();

}





void CoaWorkbench::slotSwitchToSDIMode()
{
   BEGIN;

   if (m_mode == SDIMode)
      return;

#ifndef Q_WS_MAC
   if (m_setWindows.count() == 0) {
      ERR("There arent any Windows. Cannot switch to SDI Mode without at least one Application Window" );
      slotSwitchToMDIMode();
      return;
   }
#endif

   slotSwitchToNeutralMode();

   QPoint desktopOffset = QApplication::desktop()->availableGeometry().topLeft();

   m_mode = SDIMode;

   foreach (CoaMainWindow *aw, m_setWindows) {
      CoaMainWindow *window = qobject_cast<CoaApplicationWindow*>(aw);
      if (window != 0) {
         CoaMenuBar *menu = createGlobalMenuBar();
         if (menu != 0){
            menu->setParent(aw);
            aw->setMenuBar(menu);
         }
      }

      aw->setParent(magicalParent(), magicalWindowFlags(aw));
      QRect g = m_hashGeometries.value(aw, aw->geometry());
      aw->resize(g.size());
      aw->move(g.topLeft() + desktopOffset);
      aw->setVisible(m_hashVisibilities[aw]);
   }


}



CoaWorkspace *CoaWorkbench::magicalParent() const
{
   BEGIN;

   switch (m_mode) {
      case SDIMode:      return 0;
      case MDIMode:      Q_ASSERT(m_workspace != 0);
                         INF("we are in MDI mode");
                         return m_workspace;
      case NeutralMode:  return 0;
   }

   assert( 1 == 2 );
   return 0;
}



Qt::WindowFlags CoaWorkbench::magicalWindowFlags(const QWidget *widgetForFlags) const
{
   BEGIN;
   switch (m_mode) {
        case SDIMode: {
            Q_ASSERT(m_workspace == 0);
            if (qobject_cast<const CoaToolWindow *>(widgetForFlags)) {
               return Qt::Tool;
            } else if(qobject_cast<const CoaApplicationWindow *>(widgetForFlags)) {
               return Qt::Window;
            } else {
               WRN("Unkown WindowType");
               return Qt::Window;
            }
        }
        case MDIMode:
            Q_ASSERT(m_workspace != 0);
            return Qt::Window | Qt::WindowShadeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint;
        case NeutralMode:
            return Qt::Window;
   }
   assert( 0 );
   return 0;
}





QRect CoaWorkbench::availableGeometry() const
{
   BEGIN;
   if (m_workspace) {
      RETURN(m_workspace->geometry());
   } else {
      RETURN(COAAPP->desktop()->availableGeometry(0));
   }

}


void CoaWorkbench::slotApplicationQuit()
{
   BEGIN;
   INF("Application will be finished...");
   COAAPP->quit();
}




void CoaWorkbench::slotApplicationAboutBox()
{
   BEGIN;
   CoaToolWindow *window;
   window = CoaAboutBox::getInstance();
   initWindow(window);
   addWindow(window);
   showWindow(window);
}




void CoaWorkbench::slotApplicationSetShortcuts()
{
   BEGIN;
   CoaToolWindow *window;
   window = CoaToolsChangeShortcuts::getInstance();
   initWindow(window);
   addWindow(window);
   showWindow(window);

}



void CoaWorkbench::slotDatabaseSqlBrowser()
{
   BEGIN;
   CoaToolWindow *window;
   window = CoaToolsSqlBrowser::getInstance();
   initWindow(window);
   addWindow(window);
   showWindow(window);

}



void CoaWorkbench::slotDatabaseSqlEditor()
{
   BEGIN;
   CoaToolWindow *window;
   window = CoaToolsSqlEditor::getInstance();
   initWindow(window);
   addWindow(window);
   showWindow(window);

}




void CoaWorkbench::slotDebugSettings()
{
   BEGIN;
   CoaToolWindow *window;
   window = CoaToolsChangeDebugSettings::getInstance();
   initWindow(window);
   addWindow(window);
   showWindow(window);

}


void CoaWorkbench::slotApplicationPrintShortcuts()
{
   BEGIN;

   m_printer.setFullPage(true);

   CoaPrintDialog dlg (&m_printer);

   if (dlg.exec() == QDialog::Accepted) {
      QString html;
      CoaActionFactory::getInstance()->generateShortcutHtmlString(&html);
      CoaTextDocument doc (this);
      doc.setPageSize(QSizeF(210, 297));
      doc.setHtml(html);
      doc.print(&m_printer);
   }

}



void CoaWorkbench::slotHelpShowWhatsThis()
{
   BEGIN;
   QWhatsThis::enterWhatsThisMode();
}




void CoaWorkbench::slotEditPaste()
{
   BEGIN;

   QWidget *widget = CoaApplication::focusWidget();
   if (widget != 0) {

      //paste in a TextEdit object
      CoaTextEdit *t = qobject_cast<CoaTextEdit*>(widget);
      if (t != 0) {  t->paste();
      } else {
         //Paste in a QLineEdit
         QLineEdit *t = qobject_cast<QLineEdit*>(widget);
         if (t != 0) {  t->paste();
         } else {
            ERR ("No Paste-Target found");
         }
      }
   }
}


void CoaWorkbench::slotEditCopy()
{
   BEGIN;

   QWidget *widget = CoaApplication::focusWidget();
   if (widget != 0) {

      //paste in a TextEdit object
      CoaTextEdit *t = qobject_cast<CoaTextEdit*>(widget);
      if (t != 0) {  t->copy();
      } else {
         //Paste in a QLineEdit
         QLineEdit *t = qobject_cast<QLineEdit*>(widget);
         if (t != 0) {  t->copy();
         } else {
            ERR ("No copy-Source found");
         }
      }
   }
}


void CoaWorkbench::slotEditCut()
{
   BEGIN;

   QWidget *widget = CoaApplication::focusWidget();
   if (widget == 0)
      return;


   //IoaEditorWidget *t = qobject_cast<IoaEditorWidget*>(widget);
   //if (t != 0) {
   //   t->cut();
   //}

}


void CoaWorkbench::slotEditUndo()
{
   BEGIN;
}



void CoaWorkbench::slotEditRedo()
{
   BEGIN;
}



void CoaWorkbench::slotEditSelectAll()
{
   BEGIN;

   QWidget *widget = CoaApplication::focusWidget();
   if (widget != 0) {

      //paste in a TextEdit object
      CoaTextEdit *t = qobject_cast<CoaTextEdit*>(widget);
      if (t != 0) {  t->selectAll();
      } else {
         //Paste in a QLineEdit
         QLineEdit *t = qobject_cast<QLineEdit*>(widget);
         if (t != 0) {  t->selectAll();
         } else {
            ERR ("No SelectAll-Source found");
         }
      }
   }

}






void CoaWorkbench::slotDebugOnOff()
{
   BEGIN;
   CoaDebug::getInstance()->enableDebugging(!CoaDebugThread::getInstance()->isDebuggingEnabled());
}


void CoaWorkbench::slotDebugShowTimeOnOff()
{
   BEGIN;
   CoaDebug::getInstance()->showTimeInOutput(!CoaDebugThread::getInstance()->showTimeInOutput());
}


void CoaWorkbench::slotDebugFileDefaultsOff()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::OFF);
}


void CoaWorkbench::slotDebugFileDefaultsErr()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::ERR);
}


void CoaWorkbench::slotDebugFileDefaultsWrn()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::WRN);
}


void CoaWorkbench::slotDebugFileDefaultsInf()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::INF);
}


void CoaWorkbench::slotDebugFileDefaultsDbg()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::DBG);
}


void CoaWorkbench::registerNewWindow(CoaMainWindow *const window)
{
   BEGIN;
   initWindow(window);
   addWindow(window);
   showWindow(window);

}



void CoaWorkbench::initWindow(CoaMainWindow *const window)
{
   BEGIN;
   assert(window);
   if (window == 0) return;
   //window->statusBar(); //creates a default, empty statusbar
   window->setParent(magicalParent(), magicalWindowFlags(window));
}




void CoaWorkbench::addWindow(CoaMainWindow *const window)
{
   BEGIN;
   assert(window);
   if (window == 0) return;

   m_setWindows.insert(window);

   if (m_workspace) {
      m_workspace->addWindow(window, magicalWindowFlags(window));
      m_workspace->setActiveWindow(window);
   }

#if 0
    if (m_windowActions->actions().isEmpty())
        m_windowMenu->addSeparator();

    if (QAction *action = formWindow->action()) {
        m_windowActions->addAction(action);
        m_windowMenu->addAction(action);
        action->setChecked(true);
    }

    m_actionManager->minimizeAction()->setEnabled(true);
    m_actionManager->editWidgets()->trigger();
#endif

}



void CoaWorkbench::remWindow(CoaMainWindow *const window)
{
   BEGIN;
   assert(window);
   if (window == 0) return;

   m_setWindows.remove(window);
}



void CoaWorkbench::showWindow(CoaMainWindow *const window)
{
   BEGIN;
   assert(window);
   if (window == 0) return;

   if (window->isVisible() == false) {
      window->show();
   }

   if (m_workspace != 0) {
      m_workspace->setActiveWindow(window);
   } else {
      window->raise();
   }
}


CoaWorkspace *const CoaWorkbench::getWorkspace()
{
   BEGIN;
   return m_workspace;
}


void CoaWorkbench::slotToolsSettings()
{
   BEGIN;
   CoaToolWindow *window;
   window = CoaToolsSettings::getInstance();
   initWindow(window);
   addWindow(window);
   showWindow(window);

}

