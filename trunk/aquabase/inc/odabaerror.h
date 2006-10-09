#ifndef __Odaba_Error_h__
#define __Odaba_Error_h__

#include <QObject>
//#include <QString>
#include "odaba_namespace.h"

class OdabaError: public QObject
{
Q_OBJECT

public:
   OdabaError( QObject *const parent, Error* error);
   virtual ~OdabaError();
   const QString getTitle() const;
   const QString getDescription() const;


private:
   Error* m_error;

   OdabaError( );
};

#endif //__Odaba_Error_h__

