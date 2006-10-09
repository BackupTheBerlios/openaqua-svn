#include "coathread.h"
#include <CoaWatchdog>
#include <QTimer>
#include <cassert>
#include <CoaDebug>



CoaThread::CoaThread( const QString& threadName, QObject * parent)
:CoaBaseThread(threadName, parent)
{
   BEGIN;
   registerOnWatchdog();
   setAutoPingOnWatchdog();
}



CoaThread::~CoaThread( )
{
   BEGIN;
   unregisterOnWatchdog();
}

