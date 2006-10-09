#ifndef __CoaActionFactory_h__
#define __CoaActionFactory_h__

#include <CoaThread>
#include <CoaMakros>


#include <QMap>
#include <QSet>
#include <QWriteLocker>



// Makros for easy access:
#define GETACTION(type) CoaActionFactory::getInstance()->getAction(type)


//Forward declaration
class CoaAction;
class CoaActionBuilder;

class CoaActionFactory: public CoaThread {
    Q_OBJECT
public:

   CoaAction*const getAction(const int type);
   CoaAction*const getAction(const QString& action);

   //!@brief returns a list with the ID of all known actions
   QList<int> getActionsList() const;

   //!@brief add a new ActionBuilder
   void addActionBuilder(CoaActionBuilder*const builder);

   //!@brief removes (but don't delete) an ActionBuilder
   void remActionBuilder(CoaActionBuilder*const builder);

   void generateShortcutHtmlString (QString *const html) const;

signals:
   void newActionAdded(int);

private slots:


private:

   QSet<CoaActionBuilder*const>m_actionBuilder;
   QMap<int, CoaAction*>       m_actionList;
   QReadWriteLock              m_Lock;

   COAMAKRO_DEKLARE_SINGLETONMETHODS ( CoaActionFactory );
   COAMAKRO_NO_COPYCONSTRUCTOR( CoaActionFactory );
   COAMAKRO_NO_COMPARE( CoaActionFactory );

};



#endif //__CoaActionFactory_h__

