//
// C++ Interface: ormentityfactory
//
// Description: 
//
//
//
//
#ifndef ORMENTITYFACTORY_H
#define ORMENTITYFACTORY_H

#include <qobject.h>
#include "coamakros.h"
#include <QApplication>
#include <typeinfo>
#include <map>
#include "ormentity.h"

/**

*/
class OrmEntityFactory : public QObject
{
public:
	int getTypeId(OrmEntity const * const entity);

private:
	COAMAKRO_DEKLARE_SINGLETONMETHODS (OrmEntityFactory);
	std::map <const std::type_info, int> m_type2id;
	int m_nextId;
};

#endif
