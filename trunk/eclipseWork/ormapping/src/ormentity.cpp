//
// C++ Implementation: ormentity
//
// Description: 
//
//
//
//
#include "ormentity.h"
#include "ormentityfactory.h"

OrmEntity::OrmEntity(const int type, QObject *parent)
	: QObject(parent)
	, m_type(type)
{
	if (m_type == 0) {
		OrmEntityFactory *factory = OrmEntityFactory::getInstance();
		m_type = factory->getTypeId(this);
	}

}


OrmEntity::~OrmEntity()
{
}


const int OrmEntity::getType() const
{
	return m_type;
}
