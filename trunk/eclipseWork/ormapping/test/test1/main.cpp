#include <ormsession.h>
#include <ormtransaction.h>


#include <iostream>
using namespace std;



int main() {
	OrmSession *session = new OrmSession();
	delete session;
	cout << "hello" <<endl;
	return 0;
}

