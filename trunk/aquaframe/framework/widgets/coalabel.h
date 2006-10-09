#ifndef __CoaLabel_h__
#define __CoaLabel_h__

#include <CoaString>

#include <QLabel>
#include <IoaDataSetWidget>


class CoaLabel: public QLabel
         , public IoaDataSetWidget
{
      Q_OBJECT;

      //Dataset Properties
      Q_PROPERTY( QString dataSetName READ dataSetName WRITE setDataSetName RESET resetDataSetName STORED true )
      Q_PROPERTY( QString dataSetColName READ dataSetColName WRITE setDataSetColName RESET resetDataSetColName STORED true )

   public:
      CoaLabel ( QWidget * const parent = 0, Qt::WFlags f = 0 );
      CoaLabel ( const CoaString & text, QWidget * const parent = 0, Qt::WFlags f = 0 );
      virtual ~CoaLabel();

   public slots:
      /**
      @warning not thread safe
       */
      virtual void updateValue( const QVariant& );

};

#endif
