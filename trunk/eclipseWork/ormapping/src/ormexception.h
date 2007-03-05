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
#include <exception>

/**

*/
class OrmException{
public:
	OrmException(const std::string& description) throw();
	~OrmException() throw();


protected:
	OrmException();


private:
	const std::string m_description;

};

#endif
