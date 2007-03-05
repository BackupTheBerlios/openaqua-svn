//
// C++ Interface: ormexception
//
// Description: 
//
//
//
//
#ifndef ORMEXCEPTION_H
#define ORMEXCEPTION_H

#include <string>

/**

*/
class OrmException{
public:
	OrmException(const std::string& description);
	~OrmException();


protected:
	OrmException();


private:
	const std::string m_description;

};

#endif
