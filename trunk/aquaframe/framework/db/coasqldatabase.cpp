#include "coasqldatabase.h"
#include <CoaDebug>
#include <cassert>

#include <QStringList>


CoaSqlDatabase::CoaSqlDatabase ()
:QSqlDatabase()
{
   BEGIN;

   //List all known sql drivers
   QStringList drv = drivers ();
   foreach(QString str, drv) {
      INF(QString("Known SQL Database driver: %1").arg(str));
   }
   if (drivers().count() == 0) {
      ERR("No known SQL Database drivers!");
   }


}

CoaSqlDatabase::CoaSqlDatabase ( const QSqlDatabase & other )
:QSqlDatabase(other)
{
   BEGIN;
}

CoaSqlDatabase::~CoaSqlDatabase ()
{
   BEGIN;
}

