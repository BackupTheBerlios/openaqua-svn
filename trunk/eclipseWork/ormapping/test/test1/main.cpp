#include <ormsession.h>
#include <ormsessionfactory.h>
#include <ormtransaction.h>
#include <ormentity.h>
#include <ormconfiguration.h>
#include <QString>
#include <QDateTime>
#include <QDate>

#include <iostream>
using namespace std;

class Entity: public OrmEntity{
private:
	QString		name;
	QDate			date;
	QDateTime	datetime;

public:
	Entity(QObject *parent = 0): OrmEntity(parent){};

	QString 		getName()		{ return name; };
	QDate			getDate()		{ return date; };
	QDateTime	getDatetime()	{ return datetime; };

	void setName(const QString& a)			{ name = a; };
	void setDate(const QDate& a)				{ date = a; };
	void setDatetime(const QDateTime& a)	{ datetime = a; };

};


int main() {
	//setup a new sample Entity
	cout << "setup test object" <<endl;
	Entity foo;

	QString name("Hallo Ballo");
	QDate date; date.setDate(2007, 01, 01);
	QDateTime datetime; datetime.setDate(date);

	foo.setName(name);
	foo.setDate(date);
	foo.setDatetime( datetime );


	//setup a new Orm Environment
	OrmConfiguration *configuration = new OrmConfiguration(0);
	OrmSessionFactory *sessions = configuration->buildSessionFactory();
	OrmSession *session = sessions->openSession();
	

	cout << "store object" << endl;
	OrmTransaction *trx = session->beginTransaction();
	session->save(&foo);
	trx->commitTransaction();


	cout << "load object" << endl;
	//Entity *bar = session->load(Entity);

	delete session; //removes all other objects too
	cout << "hello" <<endl;
	return 0;
}


