#ifndef __CoaSqlDriver_h__
#define __CoaSqlDriver_h__

#include <QSqlDriver>

#include <QObject>


class CoaSqlDriver: public QSqlDriver {


public:
   CoaSqlDriver ( QObject * parent = 0 );
   virtual ~CoaSqlDriver ();
   
private:

};

#endif //__CoaSqlDriver_h__

