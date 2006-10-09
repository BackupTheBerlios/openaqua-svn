#ifndef __Workbench_h__
#define __Workbench_h__

#include <CoaWorkbench>



class CoaGuiThreadMaker;
class CoaToolBar;
class ActionDocument;

class Workbench: public CoaWorkbench
{
Q_OBJECT

public:
   Workbench (CoaGuiThreadMaker const*const );
   virtual ~Workbench();
   virtual void initialize();

   virtual CoaMenuBar*const createGlobalMenuBar();
   virtual CoaToolBar*const createGlobalToolBar();

   virtual void addDocument(ActionDocument *document);

public slots:
   virtual void slotApplicationQuit();

   virtual void slotFileNew();
   virtual void slotFileOpen();
   virtual void slotFileSave();
   virtual void slotFileSaveAs();
   virtual void slotFileSaveAll();
   virtual void slotFileClose();
   virtual bool slotFileCloseAll();

private:
   void initActions();

};

#endif //__Workbench_h__

