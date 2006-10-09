#include "coaguithreadmaker.h"
#include <cassert>
#include <CoaWatchdog>
#include <CoaDebugThread>
#include <CoaSingletonWatch>
#include <CoaIoStream>
#include <iostream>
using namespace std;
#include <QObject>
#include <CoaApplication>
#include <CoaActionFactory>



/**************************************************************************

WARNING! NO DEBUG CODE HERE!!!!!!!!!!!!!!!!!!!!!!!

**************************************************************************/


CoaGuiThreadMaker::CoaGuiThreadMaker( const QApplication *app )
:CoaMainThreadMaker(app)
{
   Q_UNUSED(app);
}


CoaGuiThreadMaker::~CoaGuiThreadMaker( )
{
   StopMainThreads ();
}





bool CoaGuiThreadMaker::StopMainThreads ()
{
   //delete other threads
   CoaActionFactory::stopInstance();
   return true;
}
