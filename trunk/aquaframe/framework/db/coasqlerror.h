#ifndef __CoaSqlError_h__
#define __CoaSqlError_h__

#include <QSqlError>
#include <QString>


class CoaSqlError: public QSqlError {


public:
   CoaSqlError ( const QString & driverText = QString(), const QString & databaseText = QString(), ErrorType type = NoError, int number = -1 );
   CoaSqlError ( const CoaSqlError & other );
   CoaSqlError ( const QSqlError & other );
   virtual ~CoaSqlError ();

private:

};

#endif //__CoaSqlError_h__

