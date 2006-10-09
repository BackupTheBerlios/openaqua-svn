#ifndef __CoaSqlResult_h__
#define __CoaSqlResult_h__

#include <QSqlResult>
#include <QVariant>

class CoaSqlDriver;

class CoaSqlResult: public QSqlResult {

public:
   virtual ~CoaSqlResult ();
   virtual QVariant handle () const;
   
   
protected:
   explicit CoaSqlResult ( const CoaSqlDriver * db );

   
private:

};

#endif //__CoaSqlResult_h__

