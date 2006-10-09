#ifndef __ContactWindow_h__
#define __ContactWindow_h__

#include <CoaApplicationWindow>
#include <CoaString>




class CoaWorkbench;
class QCloseEvent;
//class QSInterpreter;

class ContactWindow: public CoaApplicationWindow
{
Q_OBJECT
public:

   ContactWindow(const CoaString& objectName,  CoaWorkbench *const parent=0, Qt::WFlags flags=0);
   virtual ~ContactWindow();
   virtual void initialize();
   virtual void saveChanges();
   virtual void saveChangesAs();

public slots:
   virtual bool slotFileSave();
   virtual bool slotFileNew();
   virtual void slotFileClose();
   virtual void slotFileOpen();


protected:
   virtual void initDatabaseModel();
   virtual void closeDatabaseModel();

protected:
//   virtual void closeEvent(QCloseEvent *ev);


private:
//   QSInterpreter *m_interpreter;

};


#endif //__ContactWindow_h__


