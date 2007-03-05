#include "ormtransaction.h"
#include "ormsession.h"

OrmTransaction::OrmTransaction(OrmSession* parent )
: QObject(parent)
{
}


OrmTransaction::~OrmTransaction()
{
}


void OrmTransaction::beginTransaction()
{
}


void OrmTransaction::commitTransaction()
{
}


void OrmTransaction::rollbackTransaction()
{
}

