#include "coasqlresult.h"
#include <CoaDebug>
#include <cassert>
#include <CoaSqlDriver>


CoaSqlResult::CoaSqlResult ( const CoaSqlDriver * db )
: QSqlResult(db)
{
   BEGIN;
}


CoaSqlResult::~CoaSqlResult ()
{
   BEGIN;
}


QVariant CoaSqlResult::handle () const
{
   BEGIN;
   return QSqlResult::handle();
}


