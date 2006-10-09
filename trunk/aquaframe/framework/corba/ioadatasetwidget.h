#ifndef __IoaDataSetWidget_h__
#define __IoaDataSetWidget_h__

#include <QString>
#include <QVariant>


/**
@interface IoaDatabaseWidget

@brief makes widgets database aware

common properties:

@code
   Q_PROPERTY( QString dataSetName    READ dataSetName    WRITE setDataSetName      RESET resetDataSetName      STORED true )
   Q_PROPERTY( QString dataSetColName READ dataSetColName WRITE setDataSetColName   RESET resetDataSetColName   STORED true )
@endcode
*/

class IoaDataSetWidget
{
public:
   IoaDataSetWidget();
   virtual ~IoaDataSetWidget();

   virtual void setDataSetName( const QString& );
   virtual void resetDataSetName();
   virtual const QString& dataSetName() const;

   virtual void setDataSetColName( const QString& );
   virtual void resetDataSetColName();
   virtual const QString& dataSetColName() const;

   virtual void updateValue(const QVariant&) = 0;
   
private:
   QString m_dataSet;
   QString m_dataSetColumn;
};





#endif //__IoaDataSetWidget_h__

