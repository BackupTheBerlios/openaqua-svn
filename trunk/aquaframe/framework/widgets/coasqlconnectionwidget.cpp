#include "coasqlconnectionwidget.h"

#include <CoaDebug>
#include <CoaTreeWidgetItem>
#include <CoaSqlDatabase>
#include <CoaStringList>

#include <QHeaderView>

CoaSqlConnectionWidget::CoaSqlConnectionWidget(QWidget *parent)
: CoaTreeWidget(parent)
{
   BEGIN;

   //add a simple refresh action
   QAction *refreshAction = new QAction(tr("Refresh"), this);
   connect(refreshAction, SIGNAL(triggered()), SLOT(refresh()));
   addAction(refreshAction);
   setContextMenuPolicy(Qt::ActionsContextMenu);

   //connect default actions
   connect (this,    SIGNAL(itemActivated ( QTreeWidgetItem*, int)),
            this,    SLOT(slotItemActivated(QTreeWidgetItem*, int )));

}

CoaSqlConnectionWidget::~CoaSqlConnectionWidget()
{
   BEGIN;
}


CoaString CoaSqlConnectionWidget::qDBCaption(const QSqlDatabase &db)
{
   BEGIN;

   CoaString nm = db.driverName();
   nm.append(QLatin1Char(':'));
   if (!db.userName().isEmpty())
        nm.append(db.userName()).append(QLatin1Char('@'));
   nm.append(db.databaseName());
   RETURN(nm);

}

void CoaSqlConnectionWidget::refresh()
{
   BEGIN;

   //set up the TreeWidget
   if (columnCount() == 0) {
      setObjectName(QLatin1String("CoaTreeWidget"));
      setHeaderLabels(CoaStringList(tr("Database")));
      header()->setResizeMode(QHeaderView::Stretch);
   }

   clear();
   CoaStringList connectionNames = QSqlDatabase::connectionNames();

   bool gotm_activeDb = false;
   for (int i = 0; i < connectionNames.count(); ++i) {
      CoaTreeWidgetItem *root = new CoaTreeWidgetItem(this);
      QSqlDatabase db = CoaSqlDatabase::database(connectionNames.at(i), false);
      root->setText(0, qDBCaption(db));
      INF(CoaString("Known Connection: %1").arg(connectionNames.at(i)));

      if (connectionNames.at(i) == m_activeDb) {
            gotm_activeDb = true;
            setActive(root);
      }

      if (db.isOpen()) {
         CoaStringList tables = db.tables();
         for (int t = 0; t < tables.count(); ++t) {
            INF(QString("Known Table: %1").arg(tables.at(t)))
            CoaTreeWidgetItem *table = new CoaTreeWidgetItem(root);
            table->setText(0, tables.at(t));
         }
      }
    }

    if (gotm_activeDb == false) {
        m_activeDb = connectionNames.value(0);
        setActive(topLevelItem(0));
    }

   doItemsLayout(); // HACK
}



CoaSqlDatabase CoaSqlConnectionWidget::currentDatabase() const
{
   BEGIN;
   return CoaSqlDatabase::database(m_activeDb);
}



static void qSetBold(QTreeWidgetItem *item, bool bold)
{
   BEGIN;

   QFont font = item->font(0);
   font.setBold(bold);
   item->setFont(0, font);

}



void CoaSqlConnectionWidget::setActive(QTreeWidgetItem *item)
{
   BEGIN;

   for (int i = 0; i < topLevelItemCount(); ++i) {
      if (topLevelItem(i)->font(0).bold())
         qSetBold(topLevelItem(i), false);
   }

   if (!item)  return;

   qSetBold(item, true);
   m_activeDb = CoaSqlDatabase::connectionNames().value(indexOfTopLevelItem(item));
   INF(CoaString("Active database connection is now: %1").arg(m_activeDb));

}

void CoaSqlConnectionWidget::slotItemActivated(QTreeWidgetItem *item, int /* column */)
{
   BEGIN;
   assert(item);
   if (item == 0)  return;

   if (!item->parent()) {
      setActive(item);
   } else {
      setActive(item->parent());
      emit tableActivated(item->text(0));
   }

}


