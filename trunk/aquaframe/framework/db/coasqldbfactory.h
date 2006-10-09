#ifndef __CoaSqlDBFactory_h__
#define __CoaSqlDBFactory_h__



#include <QObject>
#include <QDomNode>
#include <CoaString>


class CoaSqlDatabase;
class CoaSqlDBDescription;
class CoaDomDocument;

class QDomElement;

class CoaSqlDBFactory: public QObject {
  Q_OBJECT

public:
   CoaSqlDBFactory(CoaSqlDatabase*const db, QObject *parent=0);
   virtual ~CoaSqlDBFactory();

   virtual CoaSqlDBDescription*const parseDatabaseDescription(const CoaString& dbDescription);
   virtual bool initNewSqlDatabase(CoaSqlDBDescription*const);


protected:
   //virtual void             parseMenu(const QDomNode &node, CoaMenu*const menu);
   inline CoaSqlDatabase*const   getDatabase() const;

   //!load the xml document, check it, in case result is true domStructure points to the document
   bool loadAndCheckCoaDatabaseDescription(const CoaString& dbDescription, QDomElement *const domStructure);


private:
   CoaSqlDatabase*const m_database;

};

inline CoaSqlDatabase*const   CoaSqlDBFactory::getDatabase() const
{
   return m_database;
}

#endif //__CoaSqlDBFactory_h__

