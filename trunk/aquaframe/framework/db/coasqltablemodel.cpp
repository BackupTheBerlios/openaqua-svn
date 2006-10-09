#include "coasqltablemodel.h"
#include <CoaDebug>
#include <cassert>



CoaSqlTableModel::CoaSqlTableModel ( QObject * parent, QSqlDatabase db)
: QSqlTableModel(parent, db)
{
   BEGIN;
}


CoaSqlTableModel::~CoaSqlTableModel ()
{
   BEGIN;
}


QSqlDatabase CoaSqlTableModel::database () const
{
   BEGIN;
   return QSqlTableModel::database();
}
