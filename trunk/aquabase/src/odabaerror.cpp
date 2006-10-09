#include "odabaerror.h"

#include  <sError.hpp>
using namespace std;

OdabaError::OdabaError( QObject *const parent, Error* error)
: QObject( parent )
{
   m_error=error;
}




OdabaError::~OdabaError()
{
   delete m_error;
}


const QString OdabaError::getTitle() const
{
   if (m_error != 0)    return(m_error->get_title());
   else                 return "";
}

const QString OdabaError::getDescription() const
{
   if (m_error != 0)  return(m_error->get_text());
   else               return "";
}