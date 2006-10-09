#include "travelsqlmainwindowmodel.h"

#include <CoaDebug>

TravelSqlMainWindowModel::TravelSqlMainWindowModel ( QObject * parent, QSqlDatabase db)
: CoaSqlTableModel(parent, db)
{
   BEGIN;
}


TravelSqlMainWindowModel::~TravelSqlMainWindowModel()
{
   BEGIN;
}



bool TravelSqlMainWindowModel::saveChanges()
{
   BEGIN;
   return false;
}

int TravelSqlMainWindowModel::rowCount ( const QModelIndex & parent)
{
   BEGIN;
   RETURN(CoaSqlTableModel::rowCount (parent));
}
