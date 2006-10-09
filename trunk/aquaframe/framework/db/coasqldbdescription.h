#ifndef __CoaSqlDBDescription_h__
#define __CoaSqlDBDescription_h__


#include <CoaList>
#include <CoaSet>
#include <CoaString>
//#include <CoaStringList>

#include <QObject>
#include <QDomNode>
#include <QDomElement>

class CoaSqlDatabase;




/**


: m_colName("<empty>")
, m_colType(typeInteger)
, m_unique(false)
, m_null (false)
, m_primary_key (false)
, m_comment("")
*/



class CoaSqlColumnDescription: public QObject{
Q_OBJECT
public:
   enum colType {
      typeSequence,
      typeInteger,
      typeVarChar,
      typeChar,
      typeBoolean,
      typeText,
      typeBlob,
      typeReal,
      typeTime,
      typeDate,
      typeDateTime,
      typeTimestamp,
      typeRational
   };


   CoaSqlColumnDescription(QObject *const parent = 0);
   virtual ~CoaSqlColumnDescription();

   void setIsValid(const bool isValid);
   bool isValid() const;

   void resetToDefaults(void);
   bool parseColumnDescription(const QDomNode& description);


   void setColumnName(const CoaString& name);
   const CoaString columnName() const;

   void setColumnType(const colType type);
   const colType columnType() const;

   void setMustBeUnique(const bool isUnique);
   bool isMustBeUnique() const;

   void setCannotHaveNull(const bool isNull);
   bool cannotHaveNull() const;

   void setDefaultValue(const CoaString& defaultValue);
   CoaString defaultValue() const;

   void setComment(const CoaString& comment);
   CoaString comment() const;


protected:
   //return true if successfull
   bool getAndCheckAAttribute (QVariant*const value, const QDomElement& element, const CoaString& attribute);
   bool getAndCheckAAttribute (CoaString*const  value, const QDomElement& element, const CoaString& attribute);
   bool mapStringToDataType(colType *type, CoaString str);


private:
   bool          m_isValid;
   CoaString     m_colName;
   colType       m_colType;
   bool          m_unique;
   bool          m_null;
   CoaString     m_defaultValue;
   CoaString     m_comment;

};



class CoaSqlPrimaryDescription: public QObject{
Q_OBJECT
public:

   CoaSqlPrimaryDescription(QObject *const parent = 0);
   virtual ~CoaSqlPrimaryDescription();

   void setIsValid(const bool isValid);
   bool isValid() const;

   bool parsePrimaryDescription(const QDomNode& description);
   bool parseColumnDescription(const QDomNode& description);

   void addColumn(const CoaString& col);
   void remColumn(const CoaString& col);

   const CoaList<CoaString> columns() const;

   void setComment(const CoaString& comment);
   CoaString comment() const;

protected:
   bool getAndCheckAAttribute(CoaString*const value, const QDomElement& element, const QString& attribute) const;

private:
   bool                m_isValid;
   CoaString           m_comment;
   CoaSet<CoaString>   m_columns;
};






class CoaSqlTableDescription: public QObject {
Q_OBJECT
public:
   CoaSqlTableDescription(QObject *const parent = 0 );
   virtual ~CoaSqlTableDescription();
   bool  isValid() const;

   bool  parseTableDescription(const QDomNode& dbDescription);
   const CoaList<CoaSqlColumnDescription*>  getColumns()const;
   const CoaList<CoaSqlPrimaryDescription*> getPrimaries()const;

   void setTableName(const CoaString& name);
   const CoaString tableName() const;

   void setComment(const CoaString& comment);
   CoaString comment() const;

   bool hasColumn(const CoaString& name) const;



protected:
   void addColumn(CoaSqlColumnDescription*const col);
   void remColumn(CoaSqlColumnDescription*const col);
   void remColumn(const CoaString& columnName);

   void addPrimary(CoaSqlPrimaryDescription*const col);
   void remPrimary(CoaSqlPrimaryDescription*const col);


private:
   QMap<CoaString, CoaSqlColumnDescription*>  m_columns;
   QSet<CoaSqlPrimaryDescription*>            m_primaries;
   CoaString                                  m_tableName;
   CoaString                                  m_comment;
   bool                                       m_isValid;
};


/**

*/
class CoaSqlDBDescription: public QObject{
Q_OBJECT
public:
   CoaSqlDBDescription(QObject *parent = 0 );
   virtual ~CoaSqlDBDescription();
   bool isValid() const;

   bool parseDatabaseDescription(const QDomNode& dbDescription);
   const CoaList<CoaSqlTableDescription*> getTables()const;


protected:

   void addTable(CoaSqlTableDescription*const tab);
   void remTable(CoaSqlTableDescription*const tab);
   void remTable(const CoaString& tableName);


private:
   QMap<CoaString, CoaSqlTableDescription*>   m_tables;
   bool                                     m_isValid;

};

#endif //__CoaSqlDBDescription_h__

