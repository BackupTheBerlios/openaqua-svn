#ifndef __CoaObject_h__
#define __CoaObject_h__

#include <QObject>


class CoaObject: public QObject
{
   Q_OBJECT

public:

   CoaObject( CoaObject * parent = 0 );
   virtual ~CoaObject();


private:
   
};

#endif //__CoaObject_h__
