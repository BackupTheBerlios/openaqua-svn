#ifndef __CoaWorkbench_h__
#define __CoaWorkbench_h__

#include <CoaPrinter>
#include <CoaToolWindow>
#include <CoaMainWindow>

#include <QObject>
#include <QList>
#include <QMap>
#include <QSet>
#include <QHash>
#include <QRect>

class CoaWorkspace;
class CoaApplicationWindow;
class CoaGuiThreadMaker;
class CoaMenuBar;
class CoaToolBar;
class CoaStatusBar;
class CoaMainWindow;

#define WORKBENCH CoaWorkbench::getInstance()


/**

@brief Main class for dealing with windows in a application


The normal way to create a window is
@code
SampleWindow *window = new SampleWindow("name"); //no parent!
window->initialize();
registerNewWindow(window);
@endcode

After that can you forget the window


*/

class CoaWorkbench : public QObject
{
   Q_OBJECT

public:
   enum UIMode
   {
      NeutralMode,
      //!Many Documents in a Workspace
      MDIMode,
      //!Single Document per Window
      SDIMode
   };


   //!constructor
   CoaWorkbench (CoaGuiThreadMaker const*const );
   //!destructor
   virtual ~CoaWorkbench();
   static CoaWorkbench *const getInstance();

   UIMode mode() const;

   virtual void initialize();


   virtual void registerNewWindow(CoaMainWindow *const window);

   //Methods for Window Handling
   virtual void showWindow(CoaMainWindow *const window);
   virtual void initWindow(CoaMainWindow *const window);
   virtual void addWindow(CoaMainWindow *const window);
   virtual void remWindow(CoaMainWindow *const window);


signals:
   void modeChanged(UIMode mode);
   void initialized();


protected slots:
   virtual void slotApplicationQuit();
   virtual void slotApplicationAboutBox();
   virtual void slotApplicationSetShortcuts();
   virtual void slotApplicationPrintShortcuts();
   virtual void slotDatabaseSqlBrowser();
   virtual void slotDatabaseSqlEditor();
   virtual void slotHelpShowWhatsThis();

   virtual void slotEditPaste();
   virtual void slotEditCopy();
   virtual void slotEditCut();
   virtual void slotEditUndo();
   virtual void slotEditRedo();
   virtual void slotEditSelectAll();

   virtual void slotSwitchToSDIMode();
   virtual void slotSwitchToMDIMode();
   virtual void slotSwitchToNeutralMode();


   virtual void slotDebugSettings();
   virtual void slotDebugOnOff();
   virtual void slotDebugShowTimeOnOff();

   virtual void slotDebugFileDefaultsOff();
   virtual void slotDebugFileDefaultsErr();
   virtual void slotDebugFileDefaultsWrn();
   virtual void slotDebugFileDefaultsInf();
   virtual void slotDebugFileDefaultsDbg();

   virtual void slotToolsSettings();


protected:
   virtual CoaMenuBar*const createGlobalMenuBar() = 0;
   virtual CoaToolBar*const createGlobalToolBar() = 0;


   CoaWorkspace *magicalParent() const;
   Qt::WindowFlags magicalWindowFlags(const QWidget *widgetForFlags) const;
   CoaWorkspace *const getWorkspace();

   QRect availableGeometry() const;

   //!List of all known windows
   QSet<CoaMainWindow*const>       m_setWindows;


private:
   QHash<CoaMainWindow*, bool>     m_hashVisibilities;
   QHash<CoaMainWindow*, QRect>    m_hashGeometries;

   static CoaWorkbench            *INSTANCE;
   CoaWorkspace                   *m_workspace;
   UIMode                          m_mode;
   bool                            m_initializing;
   CoaMainWindow                  *m_masterwindow; //The Master in MDI mode
   CoaPrinter                      m_printer;

   CoaMenuBar                      *m_globalMenuBar;
   CoaToolBar                      *m_globalToolBar;

};

#endif //__CoaWorkbench_h__
