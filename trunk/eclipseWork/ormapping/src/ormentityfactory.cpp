//
// C++ Implementation: ormentityfactory
//
// Description: 
//
//
//
//
#include "ormentityfactory.h"
#include <QApplication>

COAMAKRO_DEFINE_SINGLETONMETHODS(OrmEntityFactory);

OrmEntityFactory::OrmEntityFactory(QApplication *parent)
	: QObject(parent)
	, m_nextId(1)
{
}


OrmEntityFactory::~OrmEntityFactory()
{
}

int OrmEntityFactory::getTypeId(OrmEntity const * const entity)
{
	//const std::type_info ff = typeid(*entity);
	std::map <const std::type_info, int>::iterator i = m_type2id.find(typeid(*entity));
	//if (m_type2id.find(*entity) == m_type2id.end
	return 0;	
}

