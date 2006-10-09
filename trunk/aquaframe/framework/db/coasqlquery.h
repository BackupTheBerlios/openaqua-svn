#ifndef __CoaSqlQuery_h__
#define __CoaSqlQuery_h__

#include <CoaSqlDatabase>

#include <QSqlQuery>
#include <QString>

class CoaSqlResult;

class CoaSqlQuery: public QSqlQuery {


public:
   CoaSqlQuery ( CoaSqlResult * result );
   CoaSqlQuery ( const QString & query = QString(), CoaSqlDatabase db = CoaSqlDatabase() );
   CoaSqlQuery ( CoaSqlDatabase db );
   CoaSqlQuery ( const CoaSqlQuery & other );
   virtual ~CoaSqlQuery ();

   //exec a prints a error message if the query went wrong
   bool execChecked (const QString& query);
   bool execChecked ();
   void check (const bool exec);

private:

};

#endif //__CoaSqlQuery_h__

