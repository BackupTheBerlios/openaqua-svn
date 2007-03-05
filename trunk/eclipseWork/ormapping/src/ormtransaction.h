#ifndef __ormtransaction_h__
#define __ormtransaction_h__

#include <QObject>

class OrmTransaction: public QObject {
public:

	OrmTransaction(QObject* parent = 0);
	~OrmTransaction();

private:


};

#endif //__ormtransaction_h__

