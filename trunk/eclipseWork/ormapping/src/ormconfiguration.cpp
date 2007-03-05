//
// C++ Implementation: ormconfiguration
//
// Description: 
//
//
//
//
#include "ormconfiguration.h"
#include "ormsessionfactory.h"

OrmConfiguration::OrmConfiguration(QObject *parent)
 : QObject(parent)
{
}


OrmConfiguration::~OrmConfiguration()
{
}



OrmSessionFactory* OrmConfiguration::buildSessionFactory()
{
	return new OrmSessionFactory(this);
}