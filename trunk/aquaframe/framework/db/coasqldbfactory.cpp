#include "coasqldbfactory.h"
#include <CoaDebug>
#include <cassert>
#include <CoaSqlDatabase>
#include <CoaSqlDBDescription>
#include <CoaSqlDBDescription>
#include <CoaSqlDBBuilderSQLite>
#include <CoaDomDocument>
#include <CoaFile>

#include <QDomElement>

CoaSqlDBFactory::CoaSqlDBFactory(CoaSqlDatabase* db, QObject *parent)
: QObject(parent)
, m_database(db)
{
   BEGIN;
   assert(m_database);
}


CoaSqlDBFactory::~CoaSqlDBFactory()
{
   BEGIN;
}


bool CoaSqlDBFactory::loadAndCheckCoaDatabaseDescription(const CoaString& dbDescription, QDomElement *const domStructure)
{
   BEGIN;

   //some checks
   assert(domStructure);
   if (dbDescription.isEmpty())   RETURN (false);
   if (domStructure == 0)         RETURN (false);

   //create the xml doc
   CoaDomDocument xmlDescription("CoaDatabaseDescription");
   CoaString errorStr;
   int errorLine;
   int errorColumn;

   //set the content
   CoaFile file(dbDescription);
   if (!xmlDescription.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
      CoaString error = CoaString(tr("Error while loading the CoaDatabaseDescription File <%1> in line %2, column %3.\nThe error was \"%4\""))
                   .arg(dbDescription)
                   .arg(errorLine)
                   .arg(errorColumn)
                   .arg(errorStr);
      ERR(error);
      RETURN(false);
   }


   //correct root element?
   *domStructure = xmlDescription.documentElement();
   if (domStructure->tagName() != "CoaDatabaseDescription") {
      CoaString error = CoaString(tr("Error while loading the CoaDatabaseDescription XML File <%1>.\nThe Document isn't a CoaDatabaseDescription File"))
                   .arg(dbDescription);
      ERR(error);
      RETURN(false);
   }

   //correct version?
   if (!domStructure->hasAttribute("version") || domStructure->attribute("version") != "1.0"  ) {
      CoaString error = CoaString(tr("Error while loading the CoaDatabaseDescription XML File <%1>.\nThe Document isn't a CoaDatabaseDescription File with Version 1.0"))
                   .arg(dbDescription);

      ERR(error);
      RETURN(false);
   }

   RETURN(true);
}





/**

@warning read and parse the first database description only
*/
CoaSqlDBDescription*const CoaSqlDBFactory::parseDatabaseDescription(const CoaString& dbDescription)
{
   BEGIN;
   if (dbDescription.isEmpty()) return 0;

   QDomElement domDescription;
   bool result = loadAndCheckCoaDatabaseDescription(dbDescription, &domDescription);
   if (result == true) {
      QDomNode db = domDescription.firstChildElement("database");
      //init the Databases (maybe more than one?)
      if (!db.isNull()){
         CoaSqlDBDescription *const description = new CoaSqlDBDescription();

         if (description->parseDatabaseDescription(db) == true)
         {
            return description;
         }

      }
   }
   return 0;

}




bool CoaSqlDBFactory::initNewSqlDatabase(CoaSqlDBDescription*const description)
{
   BEGIN;
   assert(description);

   //some checks
   if (description == 0) {  ERR("No Description given");  RETURN(false);  }
   if (m_database == 0)  {  ERR("No Database found");     RETURN(false);  }

   //get the driver name
   const CoaString driverName = m_database->driverName ();
   INF(CoaString("Init new Database with driverName %1").arg(driverName));


   //init the db, depending on the driver
   if (driverName == "QSQLITE"){
      CoaSqlDBBuilderSQLite builder (m_database);
      if (! builder.initNewSqlDatabase(description)) {
         ERR("Could not init the new database");
         RETURN(false);
      }

      //builder.initDatabasePreSetData(description);
      //builder.initDatabaseIndexes(description);
      //builder.initDatabaseForeignKeys(description);
   }



   RETURN(true);
}




