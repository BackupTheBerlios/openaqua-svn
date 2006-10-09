#include "coamainthreadmaker.h"
#include <cassert>
#include <CoaWatchdog>
#include <CoaDebugThread>
#include <CoaSingletonWatch>
#include <CoaIoStream>
#include <iostream>
using namespace std;
#include <QObject>
#include <CoaApplication>




CoaMainThreadMaker::CoaMainThreadMaker( const QApplication *app )
{
   Q_UNUSED(app);
   StartMainThreads ();
}


CoaMainThreadMaker::~CoaMainThreadMaker( )
{
   StopMainThreads ();
}


/****************************************************
WARNING WARNING WARNING WARNING WARNING WARNING WARNING

The Thread stuff is a little tricky!

Do this steps
1. Create the Application
2. Create the watchdog and debug thread
3. Register them on watchdog
4. Enable AutoPing (if you want)
5. Create the wanted external widgets

6. show the wanted external widgets
7. exec() the app

8. delete the external widgets
9. delete the app
10. stop autoping
11. unregister the threads
12. delete the threads
13. check the debug messages

****************************************************/


bool CoaMainThreadMaker::StartMainThreads ()
{
   //Warning this must be the very first!
   CoaWatchdog *watchdog = CoaWatchdog::getInstance();
   assert(watchdog);
   watchdog->registerOnWatchdog();
   watchdog->setAutoPingOnWatchdog();

   //must be 2nd!
   CoaDebug *debug = CoaDebug::getInstance();
   assert(debug);
   debug->registerOnWatchdog();
   debug->setAutoPingOnWatchdog();

   //must be the 3th
   CoaDebugThread *debugthread = CoaDebugThread::getInstance();
   assert(debugthread);
   debugthread->registerOnWatchdog();
   debugthread->setAutoPingOnWatchdog();

   //must be the 4th
   CoaSingletonWatch *watch = CoaSingletonWatch::getInstance();
   assert(watch);
   watch->registerOnWatchdog();
   watch->setAutoPingOnWatchdog();

   return true;

}



bool CoaMainThreadMaker::StopMainThreads ()
{
   //delete other threads

   //Get the special threads:
   CoaDebug *debug = CoaDebug::getInstance();
   CoaWatchdog *watchdog = CoaWatchdog::getInstance();
   CoaDebugThread *debugthread = CoaDebugThread::getInstance();
   CoaSingletonWatch *singltonwatch = CoaSingletonWatch::getInstance();



   //unregister them
   singltonwatch->setAutoPingOnWatchdog(0); //turn off AutoPing
   singltonwatch->unregisterOnWatchdog();//
   debugthread->setAutoPingOnWatchdog(0); //turn off AutoPing
   debugthread->unregisterOnWatchdog();//
   debug->setAutoPingOnWatchdog(0); //turn off AutoPing
   debug->unregisterOnWatchdog();//
   watchdog->setAutoPingOnWatchdog(0); //turn off AutoPing
   watchdog->unregisterOnWatchdog();

   //stop them
   singltonwatch->stopInstance();
   debugthread->stopInstance();
   debug->stopInstance();
   watchdog->stopInstance();

   return true;

}
