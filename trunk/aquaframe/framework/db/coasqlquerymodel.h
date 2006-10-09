#ifndef __CoaSqlQueryModel_h__
#define __CoaSqlQueryModel_h__

#include <CoaSqlDatabase>

#include <QSqlQueryModel>
#include <QString>

class CoaSqlResult;

class CoaSqlQueryModel: public QSqlQueryModel {


public:
   CoaSqlQueryModel ( QObject * parent = 0 );
   virtual ~CoaSqlQueryModel ();

private:

};

#endif //__CoaSqlQueryModel_h__

