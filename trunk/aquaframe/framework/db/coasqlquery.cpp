#include "coasqlquery.h"
#include <CoaDebug>
#include <cassert>
#include <CoaSqlResult>
#include <CoaSqlError>


CoaSqlQuery::CoaSqlQuery ( CoaSqlResult * result )
:QSqlQuery(result)
{
   BEGIN;
}


CoaSqlQuery::CoaSqlQuery ( const QString & query, CoaSqlDatabase db)
:QSqlQuery(query, db)
{
   BEGIN;
}

CoaSqlQuery::CoaSqlQuery ( CoaSqlDatabase db )
:QSqlQuery(db)
{
   BEGIN;
}


CoaSqlQuery::CoaSqlQuery ( const CoaSqlQuery & other )
:QSqlQuery(other)
{
   BEGIN;
}


CoaSqlQuery::~CoaSqlQuery ()
{
   BEGIN;
}


bool CoaSqlQuery::execChecked ()
{
   BEGIN;
   bool job = exec();
   check(job);
   RETURN(job);
}


bool CoaSqlQuery::execChecked (const QString& query)
{
   BEGIN;

   bool job = exec(query);
   check(job);
   RETURN(job);
}


void CoaSqlQuery::check (const bool exec)
{
   BEGIN;
   if ( exec == false){

      CoaSqlError error = lastError();
      QString err = QString("Got DB Error: ID=%1, Database-Message=\"%2\", Driver-Message=\"%3\", Last Query=\"%4\"")
                           .arg(error.databaseText())
                           .arg(error.driverText())
                           .arg(error.number())
                           .arg(executedQuery())
                     ;
      ERR(err);

   }
}
