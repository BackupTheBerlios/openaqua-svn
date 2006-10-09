#include "coasqlerror.h"
#include <CoaDebug>
#include <cassert>





CoaSqlError::CoaSqlError ( const QString & driverText, const QString & databaseText, ErrorType type, int number)
:QSqlError(driverText, databaseText, type, number)
{
   BEGIN;
}


CoaSqlError::CoaSqlError ( const CoaSqlError & other )
:QSqlError(other)
{
   BEGIN;
}


CoaSqlError::CoaSqlError ( const QSqlError & other )
:QSqlError(other)
{
   BEGIN;
}


CoaSqlError::~CoaSqlError ()
{
   BEGIN;
}


