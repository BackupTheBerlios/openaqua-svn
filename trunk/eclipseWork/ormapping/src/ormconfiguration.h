//
// C++ Interface: ormconfiguration
//
// Description: 
//
//
//
//
#ifndef ORMCONFIGURATION_H
#define ORMCONFIGURATION_H

#include <QObject>


/**

*/
class OrmSessionFactory;
class OrmConfiguration : public QObject
{
public:
	OrmConfiguration(QObject *parent = 0);

	virtual ~OrmConfiguration();	
	virtual OrmSessionFactory* buildSessionFactory();

};

#endif
