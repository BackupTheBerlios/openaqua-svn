#include "ormsession.h"
#include "ormtransaction.h"



OrmSession::OrmSession (QObject *parent)
: QObject(parent)
{
}





OrmSession::~OrmSession ()
{
}



OrmTransaction* OrmSession::beginTransaction()
{
	OrmTransaction *result;
	result = new OrmTransaction(this);
	return result;
}





void OrmSession::save(OrmEntity *entity)
{
}


void OrmSession::load(OrmEntity *entity)
{
}


