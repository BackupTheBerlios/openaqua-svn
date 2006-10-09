#ifndef __CoaMainThreadMaker_h__
#define __CoaMainThreadMaker_h__


class QApplication;

class CoaMainThreadMaker {
public:
   CoaMainThreadMaker( const QApplication *app);
   virtual ~CoaMainThreadMaker( );

protected:
   virtual bool StartMainThreads ();
   virtual bool StopMainThreads ();

private:

};


#endif //__CoaMainThreadMaker_h__

