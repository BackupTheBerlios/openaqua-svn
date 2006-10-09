#include "coasingletonwatch.h"
#include <cassert>
#include <iostream>
#include <CoaIoStream>
#include <QMutex>

using namespace std;

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//DO NOT USE ANY CoaDebug Methods!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

COAMAKRO_DEFINE_SINGLETONTHREADMETHODS(CoaSingletonWatch)


CoaSingletonWatch::CoaSingletonWatch()
:   CoaBaseThread("watchdog")
{
   m_singletonList.clear();
}



CoaSingletonWatch::~CoaSingletonWatch()
{
   if (m_singletonList.count() != 0) {
      cout << "Warning: Still registered Singletons:" <<endl;
      listRegisteredSingletons();
   }
}


bool CoaSingletonWatch::registerSingleton(const QString singleton)
{
   QWriteLocker locker(&m_lock);
   m_singletonList<< singleton;
   return true;
}



bool CoaSingletonWatch::unregisterSingleton(const QString singleton)
{
   QWriteLocker locker(&m_lock);
   return m_singletonList.remove(singleton);
}

void CoaSingletonWatch::listRegisteredSingletons() const
{
   foreach (QString singleton, m_singletonList){
      cout << "registered Singleton:" << singleton <<std::endl;
   }
}

