#ifndef __CoaSingletonWatch_h__
#define __CoaSingletonWatch_h__

#include <CoaBaseThread>
#include <CoaMakros>
#include <QString>
#include <QWriteLocker>
#include <QSet>

#define REGISTERSINGLETON(classname) CoaSingletonWatch::getInstance()->registerSingleton(classname)
#define UNREGISTERSINGLETON(classname) CoaSingletonWatch::getInstance()->unregisterSingleton(classname)


class CoaSingletonWatch: public CoaBaseThread {
    Q_OBJECT

    COAMAKRO_DEKLARE_SINGLETONMETHODS ( CoaSingletonWatch );

public:

   bool registerSingleton(const QString singleton);
   bool unregisterSingleton(const QString singleton);
   void listRegisteredSingletons() const;


private:

   QReadWriteLock               m_lock;
   QSet<QString>                m_singletonList;

   //not implemented
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaSingletonWatch);
   COAMAKRO_NO_COMPARE(CoaSingletonWatch);

};




#endif //__CoaSingletonWatch_h__

