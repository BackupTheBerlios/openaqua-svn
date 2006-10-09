#include "coatreewidgetitem.h"
#include <CoaDebug>


CoaTreeWidgetItem::CoaTreeWidgetItem ( int type)
:QTreeWidgetItem(type)
{
   BEGIN;
}


CoaTreeWidgetItem::CoaTreeWidgetItem ( QTreeWidget * parent, int type)
:QTreeWidgetItem(parent, type)
{
   BEGIN;
}


CoaTreeWidgetItem::CoaTreeWidgetItem ( QTreeWidget * parent, QTreeWidgetItem * preceding, int type)
:QTreeWidgetItem(parent, preceding, type)
{
   BEGIN;
}


CoaTreeWidgetItem::CoaTreeWidgetItem ( QTreeWidgetItem * parent, int type)
:QTreeWidgetItem(parent, type)
{
   BEGIN;
}


CoaTreeWidgetItem::CoaTreeWidgetItem ( QTreeWidgetItem * parent, QTreeWidgetItem * preceding, int type)
:QTreeWidgetItem(parent, preceding, type)
{
   BEGIN;
}


CoaTreeWidgetItem::~CoaTreeWidgetItem()
{
   BEGIN;
}

