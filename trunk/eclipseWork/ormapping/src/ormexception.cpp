//
// C++ Implementation: ormexception
//
// Description: 
//
//
//
//
#include "ormexception.h"

OrmException::OrmException()
{
}


OrmException::OrmException(const std::string& description) throw()
: m_description(description)

{
}


OrmException::~OrmException()
throw()
{
}


