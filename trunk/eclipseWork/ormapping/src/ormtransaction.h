#ifndef __ormtransaction_h__
#define __ormtransaction_h__


class OrmSession;

class OrmTransaction: public QObject {
public:

	explicit OrmTransaction(OrmSession* parent = 0);
	virtual ~OrmTransaction();

	virtual void beginTransaction();
	virtual void commitTransaction();
	virtual void rollbackTransaction();

private:


};

#endif //__ormtransaction_h__

