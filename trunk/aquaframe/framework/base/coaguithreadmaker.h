#ifndef __CoaGuiThreadMaker_h__
#define __CoaGuiThreadMaker_h__


#include <CoaMainThreadMaker>

class QApplication;

class CoaGuiThreadMaker: public CoaMainThreadMaker {
public:
   CoaGuiThreadMaker( const QApplication *app);
   virtual ~CoaGuiThreadMaker( );

protected:
   virtual bool StopMainThreads ();


};


#endif //__CoaGuiThreadMaker_h__

