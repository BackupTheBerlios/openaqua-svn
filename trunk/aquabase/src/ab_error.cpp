#include "ab_error.h"

#include  <sError.hpp>
using namespace std;


AquaBase::AB_Error::AB_Error( QObject *const parent )
      : QObject( parent )
{
      m_title = "";
      m_description = "";
}



AquaBase::AB_Error::AB_Error( QObject *const parent, Error * const error )
      : QObject( parent )
{
   if ( error == 0 ){
      m_title = "";
      m_description = "";
   } else {
      m_title = error->get_title();
      m_description = error->get_text();
   }

}




AquaBase::AB_Error::~AB_Error()
{

}



const QString AquaBase::AB_Error::title() const
{
   return m_title;
}


void AquaBase::AB_Error::setTitle(const QString& s)
{
   m_title=s;
}


void AquaBase::AB_Error::resetTitle()
{
   m_title.clear();
}



const QString AquaBase::AB_Error::description() const
{
   return m_description;
}


void AquaBase::AB_Error::setDescription(const QString& s)
{
   m_description=s;
}


void AquaBase::AB_Error::resetDescription()
{
   m_description.clear();
}



