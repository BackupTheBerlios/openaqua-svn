#include "travelmainwindow.h"
#include "travelsqlmainwindowmodel.h"

#include <CoaDebug>
#include <CoaWorkbench>
#include <CoaFormFactory>
#include <CoaTableView>
#include <CoaSqlDatabase>
#include <CoaSqlDBFactory>
#include <CoaSqlDBDescription>
#include <CoaSqlError>
#include <CoaSqlQuery>
#include <CoaApplication>
#include <CoaString>

#include <QMessageBox>
#include <QCloseEvent>
#include <QHeaderView>
#include <QTemporaryFile>
#include <CoaFileDialog>


TravelMainWindow::TravelMainWindow(const CoaString& objectName,  CoaWorkbench *const parent, Qt::WFlags flags)
:CoaApplicationWindow(objectName, parent, flags)
, m_database(CoaSqlDatabase::addDatabase("QSQLITE"))
, m_sqlDataModel(0)
{
   BEGIN;
}




TravelMainWindow::~TravelMainWindow()
{
   BEGIN;

   m_database.close();

   delete m_sqlDataModel;

   writeSettings();
}

void TravelMainWindow::slotFileClose()
{
   BEGIN;
   closeDatabaseModel();
   m_database.close();
}



void TravelMainWindow::slotFileOpen()
{
   BEGIN;
   //m_database.setDatabaseName("/tmp/footest.sql");
   //m_database.open();
   //initDatabaseModel();
}



void TravelMainWindow::initialize()
{
   BEGIN;

   //Build the Window itself
   Q_INIT_RESOURCE(oatravel);
   CoaFormFactory factory(this);
   factory.formBuild(":/form/mainwindow.ui");

   //Setup Items
   CoaTableView *tableView=qFindChild<CoaTableView*>(this, "tableViewTravel");
   assert(tableView);
   tableView->verticalHeader()->hide();


   readSettings();

}


bool TravelMainWindow::slotFileSave()
{
   BEGIN;

   if (m_database.databaseName() == ":memory:" ) {
      //get a filename
      CoaString fileName = CoaFileDialog::getSaveFileName(
                    this,
                    tr("Choose a filename to save under"),
                    "",
                    tr("Oa Travel Files (*.oat)"));

      if (fileName.isEmpty()) {
         INF("No file choosen");
         return false;
      }

      return copyCurrentDatabaseToNewDatabaseFile(fileName);

   } else {
      setWindowModified(false);
      return true;
   }

}


bool TravelMainWindow::copyCurrentDatabaseToNewDatabaseFile(const CoaString& fileName)
{
   BEGIN;
   INF(CoaString("Save File as %1").arg(fileName));
   return false;
}




/**
@brief create a new window and a new memory based database

*/
bool TravelMainWindow::slotFileNew()
{
   BEGIN;

   //Delete old data models
   if (m_sqlDataModel != 0) {
      delete m_sqlDataModel;
      m_sqlDataModel = 0;
   }

   //Setup database file
   m_database.setDatabaseName(":memory:");

   //Open and Init DB
   if (!m_database.open()) {
      CoaSqlError error(m_database.lastError ());
      CoaString err = CoaString("Error %1 of type %2: Database(\"%3\") Driver(\"%4\")")
            .arg(error.number())
            .arg(error.type())
            .arg(error.databaseText ())
            .arg(error.driverText ())
            ;
      ERR(err);
      RETURN(false);
   }


   //Init DB itself
   Q_INIT_RESOURCE(oatravel);
   CoaSqlDBFactory dbfactory(&m_database, this);
   CoaSqlDBDescription*const description = dbfactory.parseDatabaseDescription(":/form/databasedescription.xml");
   if (description != 0){
      dbfactory.initNewSqlDatabase(description);
      delete description;
   } else {
      RETURN(false);
   }

   CoaSqlQuery query(m_database);
   const CoaString foo("INSERT INTO milage (description, end, mileage_end, modified_at) "
                      "VALUES (:description, :end, :mileage_end, :modified_at);");
   query.prepare(foo);
   query.bindValue(":description", "fooo");
   query.bindValue(":end", "fooo");
   query.bindValue(":mileage_end", "fooo");
   query.bindValue(":modified_at", "fooo");
   query.execChecked();
   query.execChecked();
   query.execChecked();
   query.execChecked();
   query.execChecked();

   CoaSqlQuery query2(m_database);
   query2.execChecked("INSERT INTO milage (description, end, mileage_end, modified_at) "
                      "VALUES ('de', 'end', 'mi', 'mo');");

   //Init the db model
   initDatabaseModel();
   setWindowTitle("<unknown>[*] - oatravel");
   //setWindowModified(true);


   RETURN(true);
}



void TravelMainWindow::closeDatabaseModel()
{
   BEGIN;

   CoaTableView *tableView=qFindChild<CoaTableView*>(this, "tableViewTravel");
   assert(tableView);
   if (tableView->model() != 0)
      tableView->model()->submit();
   //delete m_sqlDataModel;
   m_sqlDataModel = 0;
}



void TravelMainWindow::initDatabaseModel()
{
   BEGIN;


   //Build new data models
   delete m_sqlDataModel;
   m_sqlDataModel = new TravelSqlMainWindowModel(this, m_database);
   assert(m_sqlDataModel);

   //Init the model
   m_sqlDataModel->setTable("milage");
   m_sqlDataModel->setEditStrategy(CoaSqlTableModel::OnRowChange);
   m_sqlDataModel->select();

   int counter = 0;
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("inserted_at"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("modified_at"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("obj_version"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("private"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("begin"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("end"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("mileage_begin"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("mileage_end"));
   m_sqlDataModel->setHeaderData(counter++, Qt::Horizontal, QObject::tr("description"));

   //Connect the DataModel
   CoaTableView *tableView=qFindChild<CoaTableView*>(this, "tableViewTravel");
   assert(tableView);
   tableView->setModel(m_sqlDataModel);
}




void TravelMainWindow::saveChanges()
{
   BEGIN;
}


void TravelMainWindow::saveChangesAs()
{
   BEGIN;
}


void TravelMainWindow::closeEvent(QCloseEvent *ev)
{
   BEGIN;

   if (isWindowModified() == true) {
      raise();

      QMessageBox box(tr("Save Changes?"),
                tr("Do you want to save the changes you made before closing?"),
                QMessageBox::Question,
                QMessageBox::Yes    | QMessageBox::Default,
                QMessageBox::No,
                QMessageBox::Cancel | QMessageBox::Escape,
                this, Qt::Sheet);
       box.setButtonText(QMessageBox::Yes,tr("Save"));
       box.setButtonText(QMessageBox::No, tr("Don't Save"));

       switch (box.exec()) {
         case QMessageBox::Yes: {
            saveChanges();
            setWindowModified(false);// Not really necessary, but stops problems if we get close again.
            getWorkbench()->remWindow(this);
            ev->accept();
            break;
         }
         case QMessageBox::No: {
            setWindowModified(false);// Not really necessary, but stops problems if we get close again.
            getWorkbench()->remWindow(this);
            ev->accept();
            break;
         }
         default: {
            ev->ignore();
            break;
         }
      }
   }
}


void TravelMainWindow::slotAddRow()
{
   BEGIN;
}


void TravelMainWindow::slotRemRow()
{
   BEGIN;
}

