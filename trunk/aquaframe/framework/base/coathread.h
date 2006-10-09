#ifndef __CoaThread_h__
#define __CoaThread_h__
#include "coabasethread.h"
#include <CoaMakros>



/**
@brief The common thread class for the Coa Framework

@warning Except of some very rare situations should you NEVER use the CoaBaseThread.
*/
class CoaThread: public CoaBaseThread {
   Q_OBJECT

   public:
   CoaThread( const QString& threadName, QObject * parent = 0);
   virtual ~CoaThread( );



private:
   //not implemented
   CoaThread( QObject * parent = 0 );

   //not implemented
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaThread);
   COAMAKRO_NO_COMPARE(CoaThread);
};


#endif //__CoaThread_h__

