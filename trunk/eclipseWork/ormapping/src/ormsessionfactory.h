//
// C++ Interface: ormsessionfactory
//
// Description: 
//
//
//
//
#ifndef ORMSESSIONFACTORY_H
#define ORMSESSIONFACTORY_H


/**

*/
class OrmConfiguration;
class OrmSession;
class OrmSessionFactory : public QObject
{
public:
	OrmSessionFactory(OrmConfiguration *parent = 0);
	virtual ~OrmSessionFactory();
	virtual OrmSession* openSession();


};

#endif
