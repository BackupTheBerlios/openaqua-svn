#ifndef __LetterWorkbench_h__
#define __LetterWorkbench_h__

#include <CoaWorkbench>

class CoaGuiThreadMaker;
class CoaToolBar;

class LetterWorkbench: public CoaWorkbench
{
Q_OBJECT

public:
   LetterWorkbench (CoaGuiThreadMaker const*const );
   virtual ~LetterWorkbench();
   virtual void initialize();

   virtual CoaMenuBar*const createGlobalMenuBar();
   virtual CoaToolBar*const createGlobalToolBars();


/**/
public slots:
   virtual void slotFileNew();
   virtual void slotFileOpen();
   virtual void slotFileSave();
   virtual void slotFileSaveAs();
   virtual void slotFileSaveAll();
   virtual void slotFileClose();
   virtual void slotFileCloseAll();

private:
   void initActions();

};

#endif //__LetterWorkbench_h__

