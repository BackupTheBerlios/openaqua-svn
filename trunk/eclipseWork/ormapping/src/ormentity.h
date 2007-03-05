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
	OrmEntity(const int type = 0, QObject *parent=0);
	virtual ~OrmEntity();
	
	const int getType() const;


private:
	int m_type;

};

#endif
