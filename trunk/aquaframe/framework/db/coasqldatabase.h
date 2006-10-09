#ifndef __CoaSqlDatabase_h__
#define __CoaSqlDatabase_h__

#include <QSqlDatabase>


class CoaSqlDatabase: public QSqlDatabase {


public:
   CoaSqlDatabase ();
   CoaSqlDatabase ( const QSqlDatabase & other );
   virtual ~CoaSqlDatabase ();

private:

};

#endif //__CoaSqlDatabase_h__

