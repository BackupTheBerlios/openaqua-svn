#include <ormsession.h>
#include <ormsessionfactory.h>
#include <ormtransaction.h>
#include <ormentity.h>
#include <ormconfiguration.h>
#include <QString>
#include <QDateTime>
#include <QDate>


#include <iostream>
#include <typeinfo>
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



class Person: public OrmEntity{
private:
	QString	   lastname;
	QString		firstname;

public:
	Person(QObject *parent = 0): OrmEntity(parent){};

	QString 		getLastname()		{ return lastname; };
	QString 		getFirstname()		{ return firstname; };

	void setLastname(const QString& n)		{ lastname = n; };
	void setFirstname(const QString& n)		{ firstname = n; };
};


int mytype(OrmEntity *entity) {
	if (typeid(*entity) == typeid(Person)) {
		cout << "Class if of Type Person" <<endl;
	}
	return 0;
}


int main() {
	//---------------------------------
	cout << "setup test object" <<endl;
	Entity foo;
	Person person;

	QString name("Hallo Ballo");
	QDate date; date.setDate(2007, 01, 01);
	QDateTime datetime; datetime.setDate(date);

	foo.setName(name);
	foo.setDate(date);
	foo.setDatetime( datetime );
	person.setLastname("Gates");
	person.setFirstname("Bill");


	//---------------------------------
	cout << "setup Orm Environment" << endl;
	OrmConfiguration *configuration = new OrmConfiguration(0);
	OrmSessionFactory *sessions = configuration->buildSessionFactory();
	OrmSession *session = sessions->openSession();
	

	//---------------------------------
	cout << "store object" << endl;
	OrmTransaction *trx = session->beginTransaction();
	session->save(&foo);
	session->save(&person);
	trx->commitTransaction();
	mytype(&foo);
	mytype(&person);


	//---------------------------------
	cout << "load object" << endl;
	//Entity *bar = session->load(Entity);


	//---------------------------------
	cout << "clear everything" << endl;
	delete configuration; //removes all other objects too
	return 0;
}


