#ifndef __CoaWatchdog_h__
#define __CoaWatchdog_h__

#include <CoaBaseThread>

#include <QString>
#include <QWriteLocker>
#include <QSet>


class CoaWatchdog: public CoaBaseThread {
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0.0")


public:

   static CoaWatchdog* getInstance();
   static void stopInstance();
   static bool isInstance();

   bool registerThread(CoaBaseThread *thread, int IntervalSeconds);
   bool unregisterThread(CoaBaseThread *thread);
   void listRegisteredThreads() const;

public slots:
   void handlePing(CoaBaseThread * const thread);


private:
   static CoaWatchdog  *INSTANCE; //singleton
   CoaWatchdog();  //private for singleton
   virtual ~CoaWatchdog(); //private for singleton

   QReadWriteLock               m_lock;
   QSet<QString>                m_threadlist;
   //not implemented
   CoaWatchdog(CoaWatchdog const& );
   void operator=(CoaWatchdog const&);

};



#endif //__CoaWatchdog_h__

