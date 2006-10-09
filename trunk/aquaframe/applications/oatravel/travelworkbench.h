#ifndef __TravelWorkbench_h__
#define __TravelWorkbench_h__

#include <CoaWorkbench>



class CoaGuiThreadMaker;
class CoaToolBar;

class TravelWorkbench: public CoaWorkbench
{
Q_OBJECT

public:
   TravelWorkbench (CoaGuiThreadMaker const*const );
   virtual ~TravelWorkbench();
   virtual void initialize();

   virtual CoaMenuBar*const createGlobalMenuBar();
   virtual CoaToolBar*const createGlobalToolBar();


public slots:
   virtual void slotApplicationQuit();

   virtual void slotFileNew();
   virtual void slotFileNewContact();
   virtual void slotFileOpen();
   virtual void slotFileSave();
   virtual void slotFileSaveAs();
   virtual void slotFileSaveAll();
   virtual void slotFileClose();
   virtual bool slotFileCloseAll();

private:
   void initActions();

};

#endif //__TravelWorkbench_h__

