//
// C++ Implementation: ormsessionfactory
//
// Description: 
//
//
//
//
#include "ormsessionfactory.h"
#include "ormconfiguration.h"
#include "ormsession.h"

OrmSessionFactory::OrmSessionFactory(OrmConfiguration *parent )
 : QObject(parent)
{
}


OrmSessionFactory::~OrmSessionFactory()
{
}



OrmSession* OrmSessionFactory::openSession()
{
	return new OrmSession(this);
}