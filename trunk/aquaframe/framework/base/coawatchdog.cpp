#include "coawatchdog.h"
#include <cassert>
#include <iostream>
#include <CoaIoStream>
#include <QMutex>

using namespace std;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DO NOT USE ANY CoaDebug Methods!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




CoaWatchdog* CoaWatchdog::INSTANCE =  0;


CoaWatchdog::CoaWatchdog()
:   CoaBaseThread("watchdog")
{
   m_threadlist.clear();
}


CoaWatchdog::~CoaWatchdog()
{
   if (m_threadlist.count() != 0) {
      cout << "Warning: Still registered Threads:" <<endl;
      listRegisteredThreads();
   }
}


/**
@warning this method must not have any access to other methods than its own! Befor you call this method you have to unregister any threads from any threads and you have to stop the autoping
*/
void CoaWatchdog::stopInstance()
{
   static QMutex mutex;
   mutex.lock();

   if (INSTANCE != 0) {
      INSTANCE->quit();
      INSTANCE->wait();
      delete INSTANCE;
      INSTANCE=0;
   }

   mutex.unlock();

}

CoaWatchdog* CoaWatchdog::getInstance()
{
   if (INSTANCE == 0) {
      INSTANCE  = new CoaWatchdog();
      INSTANCE->start();
   }
   return INSTANCE;
}


bool CoaWatchdog::isInstance()
{
   if ( INSTANCE == 0 ) {
      return false;
   } else {
      return true;
   }
}


bool CoaWatchdog::registerThread(CoaBaseThread *thread, int IntervalSeconds)
{
   Q_UNUSED(IntervalSeconds);
   QWriteLocker locker(&m_lock);
   m_threadlist<< thread->objectName ();
   return true;
}



bool CoaWatchdog::unregisterThread(CoaBaseThread *thread)
{
   QWriteLocker locker(&m_lock);
   return m_threadlist.remove(thread->objectName ());
}

void CoaWatchdog::handlePing(CoaBaseThread * const thread)
{
   cout << "got ping from thread " << thread->objectName()<<std::endl;
}

void CoaWatchdog::listRegisteredThreads() const
{
   foreach (QString thread, m_threadlist){
      cout << "registered Thread:" << thread <<std::endl;
   }
}

