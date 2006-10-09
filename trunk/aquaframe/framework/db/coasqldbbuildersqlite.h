#ifndef __CoaSqlDBBuilderSQLite_h__
#define __CoaSqlDBBuilderSQLite_h__


#include <CoaSqlDBDescription>

class CoaSqlDatabase;


class CoaSqlDBBuilderSQLite: public QObject {
public:
   CoaSqlDBBuilderSQLite(CoaSqlDatabase *const db, QObject *const parent=0 );
   virtual ~CoaSqlDBBuilderSQLite();

   virtual bool initNewSqlDatabase(CoaSqlDBDescription const*const description);

protected:
   virtual bool initTables(CoaSqlDBDescription             const*const description);
   virtual bool initTable (CoaSqlTableDescription          const*const description);
   virtual bool makeColumnString (QString& colStr, CoaSqlColumnDescription  const*const description);
   //virtual bool makePrimaryString (QString& colStr, CoaSqlColumnDescription  const*const description);
   virtual bool mapDataTypeToString(QString& str, const CoaSqlColumnDescription::colType type, const int width = -1);


private:
   CoaSqlDatabase*const m_database;
};


#endif //__CoaSqlDBBuilderSQLite_h__

