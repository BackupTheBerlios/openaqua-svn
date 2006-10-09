#ifndef __CoaBaseThread_h__
#define __CoaBaseThread_h__

#include <QThread>
class QTimer;


/**


@bug queued connect doesent work. This matters CoaDebug and
   CoaWatchdog. The reason seems to be that queue mechanism needs that those
   classes known as QMetaType. But registering doesn't work cause register
   needs a public constructor. So it is not compatible with singletons.
   Solution: connect from a remote object

*/
class CoaBaseThread: public QThread {
   Q_OBJECT

public:
   CoaBaseThread( const QString& threadName, QObject * parent = 0);
   virtual ~CoaBaseThread( );

   bool registerOnWatchdog(int IntervalSeconds=300);
   bool unregisterOnWatchdog();
   void setAutoPingOnWatchdog(int IntervalSeconds=100);


signals:
   void sendWatchdogPing(CoaBaseThread *const);

private slots:
   inline void getWatchdogTimerTimeout();


protected:
   virtual void run();

private:
   //Watchdog Stuff
   QTimer   *m_watchDogTimer;


   //not implemented
   CoaBaseThread( QObject * parent = 0 );
   void operator=(CoaBaseThread const&);
};


inline void CoaBaseThread::getWatchdogTimerTimeout()
{
   emit sendWatchdogPing(this);
}

#endif

