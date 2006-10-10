#include "ab_error.h"

#include  <sError.hpp>
using namespace std;


AquaBase::AB_Error::AB_Error( QObject *const parent )
      : QObject( parent )
{
   reset();
}



AquaBase::AB_Error::AB_Error( QObject *const parent, Error * const error )
      : QObject( parent )
{
   reset();
   if ( error != 0 )
   {
      m_title = error->get_title();
      m_description = error->get_text();
   }

}




AquaBase::AB_Error::~AB_Error()
{
}

void AquaBase::AB_Error::reset()
{
   m_title.clear();
   m_description.clear();
   m_module.clear();
   m_object.clear();
   setThreadId();
}


const QString AquaBase::AB_Error::title() const
{
   return m_title;
}


void AquaBase::AB_Error::setTitle( const QString& s )
{
   m_title = s;
}


const QString AquaBase::AB_Error::description() const
{
   return m_description;
}


void AquaBase::AB_Error::setDescription( const QString& s )
{
   m_description = s;
}


const QString AquaBase::AB_Error::module() const
{
   return m_module;
}


void AquaBase::AB_Error::setModule(const QString& s)
{
   m_module=s;
}



const QString AquaBase::AB_Error::object() const
{
   return m_object;
}


void AquaBase::AB_Error::setObject(const QString& s)
{
   m_object = s;
}



const int AquaBase::AB_Error::threadId() const
{
   return m_threadId;
}


void AquaBase::AB_Error::setThreadId(const int i)
{
   m_threadId = i;
}

void AquaBase::AB_Error::setThreadId(const QString& s)
{
   m_threadId = s.toInt();
}