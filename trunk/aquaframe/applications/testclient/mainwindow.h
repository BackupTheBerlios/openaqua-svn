#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <CoaApplicationWindow>
#include <CoaString>
#include <CoaDataSetModel>
#include "corbaclient.h"


class CoaWorkbench;
class CoaWorkspace;
class CoaToolButton;
class CoaTreeView;
class CoaLineEditView;
class CoaTextEdit;
class QTableWidget;


class MainWindow: public CoaApplicationWindow
{
Q_OBJECT
public:

   MainWindow(const CoaString& objectName,  CoaWorkspace *const parent, Qt::WFlags flags=0);
   virtual ~MainWindow();
   virtual void initialize();


public slots:
   virtual void saveChanges();
   virtual void saveChangesAs();

   virtual bool editingBegin();
   virtual bool editingCommit();
   virtual bool editingRollback();

   void resizeTable1(const int col, const int row);
   void reqTableContent();
   void setTableContent(int col, int row, const QVariant& value);

signals:
   void newMessage(const CoaString& str);

protected:
   virtual void closeEvent(QCloseEvent *ev);

private:
   void setSampleValues();
   CoaToolButton       *m_btnRemAction;
   CoaToolButton       *m_btnAddAction;
   QTableWidget        *m_table1;
   CoaDataSetModel::ValueMap m_valueMap;
   CoaDataSetModel      m_dataSetModel;
   CorbaClient          m_corbaClient;
};


#endif //__MainWindow_h__


