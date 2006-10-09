#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <CoaApplicationWindow>
#include <CoaString>


class CoaWorkbench;
class CoaWorkspace;
class ActionModel;
class CoaToolButton;
class ActionDocument;
class CoaTreeView;
class CoaLineEditView;
class CoaTextEdit;
//class CoaListView;

class MainWindow: public CoaApplicationWindow
{
Q_OBJECT
public:

   MainWindow(const CoaString& objectName,  CoaWorkspace *const parent, Qt::WFlags flags=0);
   virtual ~MainWindow();
   virtual void initialize();
   virtual void saveChanges();
   virtual void saveChangesAs();

public slots:
   virtual bool slotFileSave();
   virtual bool slotFileSaveAs();
   virtual bool slotFileNew();
   virtual void slotFileClose();
   virtual bool slotFileOpen(const CoaString& filename);

   bool addAction();
   bool remAction();
   bool addFolder();
   bool remFolder();



protected:
   virtual void closeEvent(QCloseEvent *ev);

private:
   CoaToolButton     *m_btnRemAction;
   CoaToolButton     *m_btnAddAction;

   ActionModel       *m_actionModel;

   CoaTreeView       *m_listActions;
   CoaTextEdit       *m_textWhatsThis;
   CoaLineEditView   *m_lineShortCut;
   CoaLineEditView   *m_lineToolTip;
   CoaLineEditView   *m_lineText;



};


#endif //__MainWindow_h__


