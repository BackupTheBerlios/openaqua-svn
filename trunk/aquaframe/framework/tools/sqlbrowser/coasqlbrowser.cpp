#include "coasqlbrowser.h"

#include <CoaDebug>
#include <CoaFormFactory>
#include <CoaSqlTableModel>
#include <CoaSqlConnectionWidget>
#include <CoaSqlQueryModel>
#include <CoaSqlQuery>
#include <CoaSqlDatabase>
#include <CoaTextEdit>
#include <CoaTableView>
#include <CoaSqlConnectionWidget>
#include <CoaPushButton>

#include <QMessageBox>


COAMAKRO_DEFINE_SINGLETONMETHODS(CoaToolsSqlBrowser);

CoaToolsSqlBrowser::CoaToolsSqlBrowser()
: CoaToolWindow("CoaToolsSqlBrowser", 0)
, m_isValid(false)
, m_sqlEdit(0)
, m_table(0)
, m_connectionWidget(0)
, m_submitButton(0)
, m_clearButton(0)
{
   BEGIN;

   //Create the central form
   Q_INIT_RESOURCE(tools);
   CoaFormFactory factory(this);
   m_isValid = factory.formBuild(":/tools/sqlbrowser/coasqlbrowser.ui");
   if (m_isValid == true) {
      m_isValid = setInternalGuiPointers();
   }
   setWindowTitle(tr("COA SQL Browser"));

   if (m_isValid == true) {
      if (CoaSqlDatabase::drivers().isEmpty())
         QMessageBox::information(this, tr("No database drivers found"),
                                       tr("This Tools needs Coa SQL Database drivers. Please check your installation!"));
      else {
         QMetaObject::invokeMethod(this, "addConnection", Qt::QueuedConnection);
         QMetaObject::invokeMethod(this, "connectSignals", Qt::QueuedConnection);
      }
      emit statusMessage(tr("Ready."));
   } else {
      emit statusMessage(tr("Error while loading"));
   }


   REGISTERSINGLETON("CoaToolsSqlBrowser");
   readSettings();
}


bool CoaToolsSqlBrowser::isValid() const
{
   BEGIN;
   RETURN(m_isValid);
}


void CoaToolsSqlBrowser::setIsValid(const bool isValid)
{
   BEGIN;
   m_isValid = isValid;
}


CoaToolsSqlBrowser::~CoaToolsSqlBrowser()
{
   BEGIN;
   INSTANCE=0;
   UNREGISTERSINGLETON("CoaToolsSqlBrowser");
   writeSettings();
}

bool CoaToolsSqlBrowser::setInternalGuiPointers()
{
   BEGIN;
   if (m_isValid != true) RETURN(false);

   m_sqlEdit = qFindChild<CoaTextEdit*>(this, "sqlEdit");
   m_table = qFindChild<CoaTableView*>(this, "table");
   m_connectionWidget  = qFindChild<CoaSqlConnectionWidget*>(this, "connectionWidget");

   m_clearButton  = new CoaPushButton("Clear");
   m_submitButton = new CoaPushButton("Submit");
   m_submitButton->setDefault(true);


   addButtonStretch();
   addButton(m_clearButton);
   addButton(m_submitButton);

   RETURN(true);
}



void CoaToolsSqlBrowser::connectSignals()
{
   BEGIN;
   if (m_isValid != true) return;

   connect (m_submitButton,      SIGNAL(clicked(bool)), this, SLOT(slotSubmitButton()));
   connect (m_clearButton,       SIGNAL(clicked(bool)), this, SLOT(slotClearButton()));
   connect (m_connectionWidget,  SIGNAL(tableActivated(const CoaString&)), this, SLOT(slotShowTable(const CoaString&)));

}


bool CoaToolsSqlBrowser::exec()
{
   BEGIN;
   if (m_isValid != true) RETURN(false);

   CoaSqlQueryModel *model = new CoaSqlQueryModel(m_table);
   CoaSqlQuery query(m_connectionWidget->currentDatabase());
   query.execChecked(m_sqlEdit->toPlainText());
   model->setQuery(query);

   QAbstractItemModel *oldmodel = m_table->model();
   m_table->setModel(model);
   if (oldmodel != 0) oldmodel->deleteLater();
   m_table->reset();

   if (model->lastError().type() != QSqlError::NoError){
      emit statusMessage(model->lastError().text());
      RETURN(false);
   } else if (model->query().isSelect()) {
      emit statusMessage(tr("Query OK."));
      RETURN(true);
   } else {
      emit statusMessage(tr("Query OK, number of affected rows: %1").arg(model->query().numRowsAffected()));
      RETURN(true);
   }
}




void CoaToolsSqlBrowser::addConnection()
{
   BEGIN;
   if (m_isValid != true) return;

#if 0
   //the next part creates a default "in memory database"
   CoaSqlDatabase::database("in_mem_db", false).close();
   CoaSqlDatabase::removeDatabase("in_mem_db");
   CoaSqlDatabase db = CoaSqlDatabase::addDatabase("QSQLITE", "in_mem_db");
   db.setDatabaseName(":memory:");
   if (!db.open()) {
      QMessageBox::warning(   this,
                              tr("Unable to open database"),
                              tr("An error occured while opening the connection: ") + db.lastError().text());
   }
   CoaSqlQuery q("", db);
   //q.execChecked("drop table Movies;");
   //q.execChecked("drop table Names;");
   q.execChecked("create table Movies (id int primary key, Title varchar(50), Director varchar(20), Rating number(2,2))");
   q.execChecked("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");
   q.execChecked("insert into Movies values (1, 'Nosferatu, eine Symphonie des Grauens', 'F.W. Murnau', '8.1')");
   q.execChecked("insert into Movies values (2, 'Bis ans Ende der Welt', 'Wim Wenders', '6.5')");
   q.execChecked("insert into Movies values (3, 'Hardware', 'Richard Stanley', '5.2')");
   q.execChecked("insert into Movies values (4, 'Mitchell', 'Andrew V. McLaglen', '2.1')");
   q.execChecked("create table Names (id int primary key, Firstname varchar(20), Lastname varchar(20), City varchar(20))");
   q.execChecked("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
   q.execChecked("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
   q.execChecked("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
   q.execChecked("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
   q.execChecked("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");

#endif

#if 0
   //the next part creates a fix connection to a database
   static int cCount = 0;
   CoaSqlDatabase db = CoaSqlDatabase::addDatabase(dialog.driverName(),
                                                    CoaString("Browser%1").arg(++cCount));
   db.setDatabaseName(dialog.databaseName());
   db.setHostName(dialog.hostName());
   db.setUserName(dialog.userName());
   db.setPassword(dialog.password());
   db.setPort(dialog.port());
   if (!db.open())
            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occured while "
                                                                         "opening the connection: ") + db.lastError().text());
#endif

    m_connectionWidget->refresh();

}

void CoaToolsSqlBrowser::slotShowTable(const CoaString &t)
{
   BEGIN;

   if (m_isValid != true) return;
   INF(CoaString("Show Table %1").arg(t));

   CoaSqlTableModel *model = new CoaSqlTableModel(m_table, m_connectionWidget->currentDatabase());

   model->setTable(t);
   model->select();
   if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());

   QAbstractItemModel *oldmodel = m_table->model();
   m_table->setModel(model);
   if (oldmodel != 0) oldmodel->deleteLater();

}




void CoaToolsSqlBrowser::slotSubmitButton()
{
   BEGIN;
   if (m_isValid != true) return;

   exec();
   m_sqlEdit->setFocus();
}



void CoaToolsSqlBrowser::slotClearButton()
{
   BEGIN;
   if (m_isValid != true) return;

   m_sqlEdit->clear();
   m_sqlEdit->setFocus();
}

