#include "coatableview.h"
#include <CoaDebug>

#include <QHeaderView>
#include <QSqlTableModel>
#include <CoaMenu>


CoaTableView::CoaTableView ( QWidget * parent)
:QTableView(parent)
{
   BEGIN;
   QHeaderView *header = horizontalHeader ();
   connect (header, SIGNAL(sectionDoubleClicked ( int )), this, SLOT(slotSortOnColumn(const int )));


}



CoaTableView::~CoaTableView()
{
   BEGIN;
}

void CoaTableView::setModel ( QAbstractItemModel * model )
{
   BEGIN;
   QTableView::setModel(model);
}


void CoaTableView::slotSortOnColumn(const int col)
{
   BEGIN;

   QSqlTableModel* m = qobject_cast<QSqlTableModel*>(model());
   if (m != 0) {
      m->sort ( col, Qt::AscendingOrder );
   }

}


CoaMenu *CoaTableView::createStandardContextMenu()
{
   BEGIN;
   CoaMenu *menu = new CoaMenu(this);
   menu->addAction("CoaTableView");
   menu->addAction("createStandardContextMenu");
   return menu;
}


void CoaTableView::contextMenuEvent ( QContextMenuEvent * event )
{
   BEGIN;
   CoaMenu *menu = createStandardContextMenu();
   menu->exec(event->globalPos());
   delete menu;

}
