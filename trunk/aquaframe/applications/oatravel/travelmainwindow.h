#ifndef __TravelMainWindow_h__
#define __TravelMainWindow_h__

#include <CoaApplicationWindow>
#include <CoaSqlDatabase>
#include <CoaString>


class CoaWorkbench;
class TravelSqlMainWindowModel;

class TravelMainWindow: public CoaApplicationWindow
{
Q_OBJECT
public:

   TravelMainWindow(const CoaString& objectName,  CoaWorkbench *const parent=0, Qt::WFlags flags=0);
   virtual ~TravelMainWindow();
   virtual void initialize();
   virtual void saveChanges();
   virtual void saveChangesAs();

public slots:
   virtual bool slotFileSave();
   virtual bool slotFileNew();
   virtual void slotFileClose();
   virtual void slotFileOpen();

   virtual void slotAddRow();
   virtual void slotRemRow();

protected:
   virtual void initDatabaseModel();
   virtual void closeDatabaseModel();
   virtual bool copyCurrentDatabaseToNewDatabaseFile(const CoaString& fileName);

protected:
   virtual void closeEvent(QCloseEvent *ev);


private:
   CoaSqlDatabase            m_database;
   TravelSqlMainWindowModel *m_sqlDataModel;
};


#endif //__TravelMainWindow_h__


