//
// C++ Interface: ormquery
//
// Description: 
//
//
//
#ifndef ORMQUERY_H
#define ORMQUERY_H

#include <qobject.h>
#include "ormsession.h"

/**

*/
class OrmQuery : public QObject
{
public:
    OrmQuery(OrmSession* parent = 0);
    ~OrmQuery();

};

#endif
