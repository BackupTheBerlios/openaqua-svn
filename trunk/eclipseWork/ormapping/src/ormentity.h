//
// C++ Interface: ormentity
//
// Description: 
//
//
//
//
#ifndef ORMENTITY_H
#define ORMENTITY_H

#include <qobject.h>

/**
	@author Andrey Behrens <Andrey.Behrens@external.t-mobile.de>
*/
class OrmEntity : public QObject
{
public:
    OrmEntity(QObject *parent=0);

    ~OrmEntity();

};

#endif
