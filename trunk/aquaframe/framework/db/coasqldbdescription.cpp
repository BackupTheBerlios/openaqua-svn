#include "coasqldbdescription.h"
#include <CoaDebug>
#include <cassert>
#include <CoaSqlDatabase>
#include <CoaSqlQuery>
#include <CoaSqlError>
#include <CoaApplication>




/*********************************************************************************************
*********************************************************************************************/

CoaSqlColumnDescription::CoaSqlColumnDescription(QObject *const parent)
: QObject(parent)
{
   BEGIN;
   resetToDefaults();
}


CoaSqlColumnDescription::~CoaSqlColumnDescription()
{
   BEGIN;
   m_isValid = false;
}


void CoaSqlColumnDescription::setIsValid(const bool isValid)
{
   BEGIN;
   m_isValid = isValid;
}


bool CoaSqlColumnDescription::isValid() const
{
   BEGIN;
   RETURN(m_isValid);
}


void CoaSqlColumnDescription::resetToDefaults(void)
{
   BEGIN;

   m_isValid      = false;
   m_colName      = "<empty>";
   m_colType      = typeInteger;
   m_unique       = false;
   m_null         = false;
   m_defaultValue = "";
   m_comment      = "";
}


bool CoaSqlColumnDescription::getAndCheckAAttribute(QVariant*const value, const QDomElement& element, const QString& attribute)
{
   //BEGIN;
   bool result = false;

   if ((element.hasAttribute (attribute)) && (!element.attribute (attribute).isEmpty())) {
      *value = element.attribute(attribute);
      result = true;
   }

   //RETURN(result);
   return result;
}


bool CoaSqlColumnDescription::getAndCheckAAttribute(QString*const value, const QDomElement& element, const QString& attribute)
{
   //BEGIN;
   bool result = false;

   if ((element.hasAttribute (attribute)) && (!element.attribute (attribute).isEmpty())) {
      *value = element.attribute(attribute);
      result = true;
   }

   //RETURN(result);
   return result;
}


//return true if successfull
bool CoaSqlColumnDescription::mapStringToDataType(CoaSqlColumnDescription::colType *type, QString str)
{
   BEGIN;

   if        (str.startsWith("int",        Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeInteger;

   } else if (str.startsWith("seq",        Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeSequence;

   } else if (str.startsWith("varchar",    Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeVarChar;

   } else if (str.startsWith("char",       Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeChar;

   } else if (str.startsWith("bool",       Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeBoolean;

   } else if (str.startsWith("text",       Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeText;

   } else if (str.startsWith("blob",       Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeBlob;

   } else if (str.startsWith("real",       Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeReal;

   } else if (str.startsWith("DateTime",   Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeDateTime;

   } else if (str.startsWith("Date",       Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeDate;

   } else if (str.startsWith("timestamp",  Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeTimestamp;

   } else if (str.startsWith("time",       Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeTime;

   } else if (str.startsWith("rational",   Qt::CaseInsensitive)) {
      *type = CoaSqlColumnDescription::typeRational;

   } else {
      ERR(QString("Unknown element type \"%1\"").arg(str));
      RETURN(false);
   }

   RETURN(true);

}


bool CoaSqlColumnDescription::parseColumnDescription(const QDomNode& description)
{
   BEGIN;

   m_isValid = false;

   if (description.isNull()) {
      ERR(QString("Error while parsing the XML Column Description: Empty description"));
      return false;
   }

   resetToDefaults();
   QDomElement element = description.toElement();
   QVariant varValue;
   QString  strValue;


   //the name
   if (getAndCheckAAttribute(&strValue, element, "name")){
      setColumnName(strValue);
   } else {
      ERR(QString("Error while parsing the XML Column Description: No column name"));
      RETURN(false);
   }

   //the type
   if (getAndCheckAAttribute(&strValue, element, "type")){
      colType type;
      if (mapStringToDataType(&type, strValue) == true){
         setColumnType(type);
      } else {
         ERR(QString("Error while parsing the XML Column Description: Column has unkown type"));
         RETURN(false);
      }
   } else {
      ERR(QString("Error while parsing the XML Column Description: No column type"));
      RETURN(false);
   }

   //the optional comment
   if (getAndCheckAAttribute(&strValue, element, "comment")){
      setComment(strValue);
   }


   //the optional default
   if (getAndCheckAAttribute(&strValue, element, "default")){
      setDefaultValue(strValue);
   }

   //the optional null value
   if (getAndCheckAAttribute(&varValue, element, "null")){
      setCannotHaveNull(varValue.toBool());
   }

   //the optional null value
   if (getAndCheckAAttribute(&varValue, element, "unique")){
      setMustBeUnique(varValue.toBool());
   }

   m_isValid = true;
   RETURN(true);
}

void CoaSqlColumnDescription::setMustBeUnique(const bool unique)
{
   BEGIN;
   m_unique = unique;
}


bool CoaSqlColumnDescription::isMustBeUnique() const
{
   BEGIN;
   RETURN(m_unique);
}



void CoaSqlColumnDescription::setCannotHaveNull(const bool isNull)
{
   BEGIN;
   m_null = isNull;
}


bool CoaSqlColumnDescription::cannotHaveNull() const
{
   BEGIN;
   RETURN(m_null);
}



void CoaSqlColumnDescription::setDefaultValue(const QString& defaultValue)
{
   BEGIN;
   m_defaultValue = defaultValue;
}


QString CoaSqlColumnDescription::defaultValue() const
{
   BEGIN;
   RETURN(m_defaultValue);
}

void CoaSqlColumnDescription::setComment(const QString& comment)
{
   BEGIN;
   m_comment = comment;
}


QString CoaSqlColumnDescription::comment() const
{
   BEGIN;
   RETURN(m_comment);
}


void CoaSqlColumnDescription::setColumnName(const QString& name)
{
   BEGIN;
   m_colName = name;
}

const QString CoaSqlColumnDescription::columnName() const
{
   BEGIN;
   RETURN(m_colName);
}


void CoaSqlColumnDescription::setColumnType(const CoaSqlColumnDescription::colType type)
{
   BEGIN;
   m_colType = type;
}


const CoaSqlColumnDescription::colType CoaSqlColumnDescription::columnType() const
{
   BEGIN;
   return m_colType;
}







/*********************************************************************************************
*********************************************************************************************/


CoaSqlPrimaryDescription::CoaSqlPrimaryDescription(QObject *const parent)
: QObject(parent)
{
   BEGIN;
}


CoaSqlPrimaryDescription::~CoaSqlPrimaryDescription()
{
   BEGIN;
}



void CoaSqlPrimaryDescription::setIsValid(const bool isValid)
{
   BEGIN;
   m_isValid = isValid;
}


bool CoaSqlPrimaryDescription::isValid() const
{
   BEGIN;
   RETURN(m_isValid);
}



bool CoaSqlPrimaryDescription::getAndCheckAAttribute(QString*const value, const QDomElement& element, const QString& attribute) const
{
   //BEGIN;
   bool result = false;

   if ((element.hasAttribute (attribute)) && (!element.attribute (attribute).isEmpty())) {
      *value = element.attribute(attribute);
      result = true;
   }

   //RETURN(result);
   return result;
}


bool CoaSqlPrimaryDescription::parsePrimaryDescription(const QDomNode& description)
{
   BEGIN;
   m_isValid = false;

   if (description.isNull()) {
      ERR(QString("Error while parsing the XML Column Description: Empty description"));
      RETURN(false);
   }


   QDomElement element = description.toElement();
   QString  value;

   if (getAndCheckAAttribute(&value, element, "comment")){
      setComment(value);
   }


   //iterate over primary columns
   {
      QDomNode columnDescription = description.firstChildElement("column");
      while (!columnDescription.isNull()){
         if (parseColumnDescription(columnDescription) != true){
            RETURN(false);
         }
         columnDescription = columnDescription.nextSiblingElement ("column");
      }
   }


   m_isValid = true;
   RETURN(true);
}


bool CoaSqlPrimaryDescription::parseColumnDescription(const QDomNode& description)
{
   BEGIN;

   if (description.isNull()) {
      ERR(QString("Error while parsing the XML Column Description: Empty description"));
      RETURN(false);
   }

   QDomElement element = description.toElement();
   QString  value;

   if (getAndCheckAAttribute(&value, element, "name")){
      addColumn(value);
   } else {
      ERR(QString("Error while parsing the XML Column Description: No column name"));
      RETURN(false);
   }

   RETURN(true);
}


void CoaSqlPrimaryDescription::addColumn(const CoaString& col)
{
   BEGIN;
   m_columns.insert(col);
}


void CoaSqlPrimaryDescription::remColumn(const CoaString& col)
{
   BEGIN;
   m_columns.remove(col);
}



const CoaList<CoaString> CoaSqlPrimaryDescription::columns() const
{
   BEGIN;
   return m_columns.toList();
}



void CoaSqlPrimaryDescription::setComment(const CoaString& comment)
{
   BEGIN;
   m_comment = comment;
}


CoaString CoaSqlPrimaryDescription::comment() const
{
   BEGIN;
   RETURN(m_comment);
}



/*********************************************************************************************
*********************************************************************************************/
CoaSqlTableDescription::CoaSqlTableDescription(QObject *const parent)
: QObject(parent)
, m_tableName("<empty")
, m_isValid(false)
{
   BEGIN;
   m_columns.clear();
}

CoaSqlTableDescription::~CoaSqlTableDescription()
{
   m_isValid = false;
   m_columns.clear();
}




bool  CoaSqlTableDescription::isValid() const
{
   BEGIN;
   RETURN(m_isValid);
}



bool  CoaSqlTableDescription::parseTableDescription(const QDomNode& tableDescription)
{
   BEGIN;
   m_isValid = false;

   //get the table name
   QString tableName = tableDescription.toElement().attribute("name");
   if (tableName.isEmpty()) RETURN(isValid());
   setTableName(tableName);
   INF(QString("Try to parse Table %1").arg(tableName));

   //iterate over columns
   {
      QDomNode columnDescription = tableDescription.firstChildElement("column");
      while (!columnDescription.isNull()){
            CoaSqlColumnDescription *column = new CoaSqlColumnDescription(this);
            if (column->parseColumnDescription(columnDescription) != true){
            RETURN(false);
            } else {
               addColumn(column);
               columnDescription = columnDescription.nextSiblingElement ("column");
            }
      }
   }

   //iterate over primary keys
   {
      QDomNode primaryDescription = tableDescription.firstChildElement("primary");
      while (!primaryDescription.isNull()){
            CoaSqlPrimaryDescription *primary = new CoaSqlPrimaryDescription(this);
            if (primary->parsePrimaryDescription(primaryDescription) != true){
               RETURN(false);
            } else {
               addPrimary(primary);
               primaryDescription = primaryDescription.nextSiblingElement ("primary");
            }
      }
   }

   //bye, bye
   m_isValid = true;
   RETURN(true);
}



const QList<CoaSqlColumnDescription*> CoaSqlTableDescription::getColumns()const
{
   BEGIN;
   return m_columns.values();
}


const CoaList<CoaSqlPrimaryDescription*> CoaSqlTableDescription::getPrimaries()const
{
   BEGIN;
   return m_primaries.values();
}


void CoaSqlTableDescription::addColumn(CoaSqlColumnDescription*const col)
{
   BEGIN;

   assert(col);
   if (col == 0) return;
   m_columns.insert(col->columnName(), col);
}



void CoaSqlTableDescription::remColumn(CoaSqlColumnDescription*const col)
{
   BEGIN;

   assert(col);
   if (col == 0) return;

   m_columns.remove(col->columnName());
}



void CoaSqlTableDescription::remColumn(const QString& columnName)
{
   BEGIN;
   m_columns.remove(columnName);
}

void CoaSqlTableDescription::addPrimary(CoaSqlPrimaryDescription*const col)
{
   BEGIN;
   m_primaries.insert(col);
}


void CoaSqlTableDescription::remPrimary(CoaSqlPrimaryDescription*const col)
{
   BEGIN;
   m_primaries.remove(col);
}




void CoaSqlTableDescription::setTableName(const QString& name)
{
   BEGIN;
   m_tableName = name;
}


const QString CoaSqlTableDescription::tableName() const
{
   BEGIN;
   RETURN(m_tableName);
}


void CoaSqlTableDescription::setComment(const QString& comment)
{
   BEGIN;
   m_comment = comment;
}


QString CoaSqlTableDescription::comment() const
{
   BEGIN;
   RETURN(m_comment);
}


bool CoaSqlTableDescription::hasColumn(const CoaString& name) const
{
   BEGIN;
   bool result = m_columns.contains( name );
   RETURN(result);
}



/*********************************************************************************************
*********************************************************************************************/
CoaSqlDBDescription::CoaSqlDBDescription(QObject *parent)
: QObject(parent)
, m_isValid(false)
{
   BEGIN;
}


CoaSqlDBDescription::~CoaSqlDBDescription()
{
   BEGIN;
}


bool CoaSqlDBDescription::isValid() const
{
   BEGIN;
   RETURN(m_isValid);
}


bool CoaSqlDBDescription::parseDatabaseDescription(const QDomNode& dbDescription)
{
   BEGIN;
   m_isValid=false;

   QDomNode table = dbDescription.firstChildElement("table");
   while (!table.isNull()){
         CoaSqlTableDescription *tableDescr = new CoaSqlTableDescription(this);
         if (tableDescr->parseTableDescription(table) != true){
            RETURN(isValid());
         } else {
            addTable(tableDescr);
            table = table.nextSiblingElement ("table");
         }
         COAAPP->processEvents();
   }

   //QDomNode index = dbDescription.firstChildElement("index");
   //while (!index.isNull()){
   //      if (initIndex(index) != true){
   //         RETURN(false);
   //      } else {
   //         index = index.nextSibling();
   //      }
   //      COAAPP->processEvents();
   //}

   m_isValid = true;
   RETURN(isValid());

}


void CoaSqlDBDescription::addTable(CoaSqlTableDescription*const tab)
{
   BEGIN;

   assert(tab);
   if (tab == 0) return;

   m_tables[tab->tableName()]=tab;

}


void CoaSqlDBDescription::remTable(CoaSqlTableDescription*const tab)
{
   BEGIN;

   assert(tab);
   if (tab == 0) return;

   m_tables.remove(tab->tableName());
}


void CoaSqlDBDescription::remTable(const QString& tableName)
{
   BEGIN;
   m_tables.remove(tableName);
}

const QList<CoaSqlTableDescription*> CoaSqlDBDescription::getTables()const
{
   BEGIN;
   return m_tables.values();
}

