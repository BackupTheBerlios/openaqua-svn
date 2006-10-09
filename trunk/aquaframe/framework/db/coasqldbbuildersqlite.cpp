#include "coasqldbbuildersqlite.h"

#include <CoaDebug>
#include <CoaSqlDatabase>
#include <CoaSqlDBDescription>
#include <CoaSqlQuery>


CoaSqlDBBuilderSQLite::CoaSqlDBBuilderSQLite(CoaSqlDatabase*const db, QObject *const parent)
: QObject(parent)
, m_database(db)
{
   BEGIN;
}


CoaSqlDBBuilderSQLite::~CoaSqlDBBuilderSQLite()
{
   BEGIN;
}



bool CoaSqlDBBuilderSQLite::initNewSqlDatabase(CoaSqlDBDescription const*const description)
{
   BEGIN;
   assert(description);
   bool result = false;

   //some checks
   if (description == 0)       {ERR("No Description given");    RETURN(result);  }
   if (!description->isValid()){ERR("Description is not valid");RETURN(result);  }
   if (m_database == 0)        {ERR("No Database found");       RETURN(result);  }

   if (! initTables(description)){
      RETURN(false);
   }
   result = true;

   //bye,bye
   RETURN(result);
}

bool CoaSqlDBBuilderSQLite::initTables(CoaSqlDBDescription const*const description)
{
   BEGIN;
   assert(description);
   bool result = false;
   int countErrors = 0;

   //some checks
   if (description == 0)       {ERR("No Description given");    RETURN(result);  }
   if (!description->isValid()){ERR("Description is not valid");RETURN(result);  }
   if (m_database == 0)        {ERR("No Database found");       RETURN(result);  }

   //get the tables
   QList<CoaSqlTableDescription*> tableList = description->getTables();
   foreach(CoaSqlTableDescription* table, tableList){
      if (initTable (table) != true) countErrors++;
   }

   //bye,bye
   if (countErrors == 0){
       result = true;
   }else{
      ERR(QString("Found %1 errors while initTables").arg(countErrors));
   }
   RETURN(result);
}


bool CoaSqlDBBuilderSQLite::initTable (CoaSqlTableDescription const*const description)
{
   BEGIN;
   assert(description);
   bool result = false;
   int countErrors = 0;

   //some checks
   if (description == 0)       {ERR("No Description given");    RETURN(result);  }
   if (!description->isValid()){ERR("Description is not valid");RETURN(result);  }
   if (m_database == 0)        {ERR("No Database found");       RETURN(result);  }

   QString tableName = description->tableName();
   QString colString = ""; //will contain the whole column string like "foo INTEGER NOT NULL UNIQUE, bar VARCHAR(20)"
   QString primaryKey= ""; //will contain an optional part for PRIMARY KEYs


   //get the columns
   QList<CoaSqlColumnDescription*> colList = description->getColumns();
   foreach(CoaSqlColumnDescription* col, colList){
      QString str = "";
      if (makeColumnString(str, col) == true){
         if (colString.length() > 0 ) colString += ", ";
         colString += str;
      } else {
         countErrors ++;
      }
   }

   //get the Primary Keys
   QList<CoaSqlPrimaryDescription* > priList = description->getPrimaries();
   foreach(CoaSqlPrimaryDescription* pri, priList){
      QString keys="";
      if (pri != 0) {
         CoaList<CoaString> columns = pri->columns();
         foreach(CoaString str, columns){
            if (keys.length() > 0) keys+= ", ";
            keys += str;
         }
      }
      if (keys.length() > 0 ) {
         primaryKey = QString(", PRIMARY KEY (%1)").arg(keys); //must have a comma
      }

   }



   //exec the SQL command
   if (countErrors == 0) {
      QString sqlCommand = QString("CREATE TABLE %1 (%2 %3);")
         .arg(tableName)
         .arg(colString)
         .arg(primaryKey)
         ;
      INF(QString("SQL Command: \"%1\"").arg(sqlCommand));

      CoaSqlQuery query(*m_database);
      result = query.execChecked(sqlCommand);
      if (result != true)
         countErrors++;
   }


   //bye,bye
   if (countErrors == 0){
      result = true;
   }else{
      ERR(QString("Found %1 errors while initTable. Table not created").arg(countErrors));
   }
   RETURN(result);
}




bool CoaSqlDBBuilderSQLite::makeColumnString (QString& colStr, CoaSqlColumnDescription  const*const description)
{
   BEGIN;
   assert(description);
   bool result = false;
   int countErrors = 0;

   //some checks
   if (description == 0)       {ERR("No Description given");    RETURN(result);  }
   if (!description->isValid()){ERR("Description is not valid");RETURN(result);  }
   if (m_database == 0)        {ERR("No Database found");       RETURN(result);  }

   //build the stringelements
   QString tmp;

   //the name
   colStr  = description->columnName();

   //the type
   tmp = "";
   if (mapDataTypeToString(tmp, description->columnType()) == true){
      colStr = colStr + ' ' + tmp;
   } else {
      countErrors++;
   }

   if (description->cannotHaveNull())           colStr += " NOT NULL";
   if (description->isMustBeUnique())           colStr += " UNIQUE";
   //if (description->isPrimary())                colStr += " PRIMARY";
   //if (!description->comment().isEmpty())     colStr += " COMMENT"; //not supported?
   if (!description->defaultValue().isEmpty())  colStr = colStr + " DEFAULT '" + description->defaultValue() + "'";


   //bye,bye
   if (countErrors == 0){
       result = true;
   }else{
      ERR(QString("Found %1 errors while makeColumnString").arg(countErrors));
   }
   RETURN(result);
   return false;
}


/**

@todo Support fuer Weite

*/
bool CoaSqlDBBuilderSQLite::mapDataTypeToString(QString& str, const CoaSqlColumnDescription::colType type, const int )
{
   BEGIN
   bool result = true;

   switch(type){
            case CoaSqlColumnDescription::typeSequence:   str += "INTEGER "; break;
            case CoaSqlColumnDescription::typeInteger:    str += "INTEGER"; break;
            case CoaSqlColumnDescription::typeVarChar:    str += "VARCHAR"; break;
            case CoaSqlColumnDescription::typeChar:       str += "CHAR"; break;
            case CoaSqlColumnDescription::typeBoolean:    str += "BOOLEAN"; break;
            case CoaSqlColumnDescription::typeText:       str += "TEXT"; break;
            case CoaSqlColumnDescription::typeBlob:       str += "BLOB"; break;
            case CoaSqlColumnDescription::typeReal:       str += "REAL"; break;
            case CoaSqlColumnDescription::typeTime:
            case CoaSqlColumnDescription::typeDate:
            case CoaSqlColumnDescription::typeDateTime:
            case CoaSqlColumnDescription::typeTimestamp:  str += "INTEGER"; break;
            case CoaSqlColumnDescription::typeRational:   ERR("type Rational not supported for SQLITE ");
                                                          result = false;
            //no default!
   }

   RETURN(result);
}
