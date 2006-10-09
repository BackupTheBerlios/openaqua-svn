#include "coabasethread.h"
#include <CoaWatchdog>
#include <cassert>

#include <QTimer>
#include <QMutexLocker>

////////////////////////////////////////////////////////////////
//WARNING DO NOT USE CoaDebug HERE////////////////

CoaBaseThread::CoaBaseThread( const QString& threadName, QObject * parent )
      : QThread( parent )
      , m_watchDogTimer( 0 )
{
   setObjectName( threadName );
}



CoaBaseThread::~CoaBaseThread( )
{}


void CoaBaseThread::run()
{
   QThread::exec();
}


bool CoaBaseThread::registerOnWatchdog( int IntervalSeconds )
{
   CoaWatchdog * dog = CoaWatchdog::getInstance();
   assert( dog );
   if ( dog != 0 )
   {
      return dog->registerThread( this, IntervalSeconds );
   }
   else
   {
      return false;
   }

}


bool CoaBaseThread::unregisterOnWatchdog()
{
   CoaWatchdog * dog = CoaWatchdog::getInstance();
   assert( dog );
   if ( dog != 0 )
   {
      return dog->unregisterThread( this );
   }
   else
   {
      return false;
   }
}




/**
   @param IntervalSeconds if 0 sec set, the AutoPing will be disabled
*/
void CoaBaseThread::setAutoPingOnWatchdog( int IntervalSeconds )
{
   if ( IntervalSeconds == 0 )
   {
      //Disable AutoPing
      if ( m_watchDogTimer != 0 )
      {
         disconnect( m_watchDogTimer, 0, 0, 0 );
         delete m_watchDogTimer;
         m_watchDogTimer = 0;
      }

   }
   else
   {
      //enable or set AutoPing

      if ( m_watchDogTimer != 0 )
      {
         //reset the timer
         m_watchDogTimer->start( IntervalSeconds * 1000 );
      }
      else
      {
         //build and set a new timer
         m_watchDogTimer = new QTimer( this );
         m_watchDogTimer->start( IntervalSeconds * 1000 );
         connect( m_watchDogTimer, SIGNAL( timeout() ), this, SLOT( getWatchdogTimerTimeout() ) );
         connect( this, SIGNAL( sendWatchdogPing( CoaBaseThread * const ) ), CoaWatchdog::getInstance(), SLOT( handlePing( CoaBaseThread * const ) ) );
      }

   }
}

