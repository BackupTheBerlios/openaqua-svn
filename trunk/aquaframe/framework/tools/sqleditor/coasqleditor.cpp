#include "coasqleditor.h"

#include <CoaDebug>
#include <CoaFormFactory>
#include <CoaTableView>
#include <CoaSqlTableModel>
#include <CoaSqlConnectionWidget>
#include <CoaSqlQueryModel>
#include <CoaSqlQuery>
#include <CoaSqlDatabase>
#include <CoaSqlTableModel>

#include <QMessageBox>
#include <QHeaderView>


COAMAKRO_DEFINE_SINGLETONMETHODS(CoaToolsSqlEditor);

CoaToolsSqlEditor::CoaToolsSqlEditor()
: CoaToolWindow("CoaToolsSqlEditor", 0)
, m_isValid(false)
, m_table(0)
{
   BEGIN;


   //Create the central form
   Q_INIT_RESOURCE(tools);
   CoaFormFactory factory(this);
   if (factory.formBuild(":/tools/sqleditor/coasqleditor.ui")==true){
      m_isValid  = setInternalGuiPointers();
   }


   setWindowTitle(tr("COA SQL Editor"));

   if (CoaSqlDatabase::drivers().isEmpty())
      QMessageBox::information(this, tr("No database drivers found"),
                                       tr("This Tools needs Coa SQL Database drivers. Please check your installation!"));
   else {
      QMetaObject::invokeMethod(this, "addConnection", Qt::QueuedConnection);
      QMetaObject::invokeMethod(this, "connectSignals", Qt::QueuedConnection);
   }

   REGISTERSINGLETON("CoaToolsSqlEditor");
   emit statusMessage(tr("Ready."));
   readSettings();
}




CoaToolsSqlEditor::~CoaToolsSqlEditor()
{
   BEGIN;
   INSTANCE=0;
   UNREGISTERSINGLETON("CoaToolsSqlEditor");
   writeSettings();
}


bool CoaToolsSqlEditor::isValid() const
{
   BEGIN;
   RETURN(m_isValid);
}



void CoaToolsSqlEditor::setIsValid(const bool isValid)
{
   BEGIN;
   m_isValid = isValid;
}


bool CoaToolsSqlEditor::setInternalGuiPointers()
{
   BEGIN;

   m_btnAdd            = new CoaPushButton("+");
   m_btnRem            = new CoaPushButton("-");

   addButtonStretch();
   addButton(m_btnAdd);
   addButton(m_btnRem);


   m_connectionWidget  = qFindChild<CoaSqlConnectionWidget*>(this, "connectionWidget");
   m_table             = qFindChild<CoaTableView*>(this, "table");

   RETURN(true);

}

void CoaToolsSqlEditor::connectSignals()
{
   BEGIN;

   if (!isValid()) return;

   connect (m_btnAdd,           SIGNAL(clicked(bool)), this, SLOT(slotAddRecord()));
   connect (m_btnRem,           SIGNAL(clicked(bool)), this, SLOT(slotRemRecord()));
   connect (m_connectionWidget, SIGNAL(tableActivated(const CoaString&)), this, SLOT(slotShowTable(const CoaString&)));

}



void CoaToolsSqlEditor::addConnection()
{
   BEGIN;

   if (!isValid()) return;
   m_connectionWidget->refresh();

}




void CoaToolsSqlEditor::slotShowTable(const CoaString &t)
{
   BEGIN;

   if (!isValid()) return;

   CoaSqlTableModel *model = new CoaSqlTableModel(m_table, m_connectionWidget->currentDatabase());

   model->setTable(t);
   model->setEditStrategy(QSqlTableModel::OnFieldChange);
   model->select();
   if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());

   QAbstractItemModel *oldmodel = m_table->model();
   m_table->setModel(model);
   if (oldmodel != 0) oldmodel->deleteLater();

}




void CoaToolsSqlEditor::slotAddRecord()
{
   BEGIN;
   if (!isValid()) return;
}



void CoaToolsSqlEditor::slotRemRecord()
{
   BEGIN;
   if (!isValid()) return;
}


