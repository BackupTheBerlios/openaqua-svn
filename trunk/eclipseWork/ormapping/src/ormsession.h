#ifndef __ormsession_h___h__
#define __ormsession_h___h__

#include <QObject>
#include "ormentity.h"

class OrmTransaction;

class OrmSession: public QObject {
public:

	explicit OrmSession (QObject *parent = 0);
	virtual ~OrmSession ();

	virtual OrmTransaction* beginTransaction();
	//virtual void commitTransaction();
	//virtual void rollbackTransaction();

	virtual void save(OrmEntity *entity);
	virtual void load(OrmEntity *entity);

private:




};

#endif //__ormsession_h___h__

