#include "coasqlquerymodel.h"
#include <CoaDebug>


CoaSqlQueryModel::CoaSqlQueryModel ( QObject * parent )
:QSqlQueryModel(parent)
{
   BEGIN;
}


CoaSqlQueryModel::~CoaSqlQueryModel ()
{
   BEGIN;
}


