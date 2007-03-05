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


OrmException::OrmException(const std::string& description)
: m_description(description)
{
}


OrmException::~OrmException()
{
}


