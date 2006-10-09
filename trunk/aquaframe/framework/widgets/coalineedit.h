#ifndef __CoaLineEdit_h__
#define __CoaLineEdit_h__


#include <QLineEdit>
#include <QObject>
#include <IoaDataSetWidget>

class QContextMenuEvent;




class CoaLineEdit: public QLineEdit
         , public IoaDataSetWidget
{
      Q_OBJECT
      //Dataset Properties
      Q_PROPERTY( QString dataSetName READ dataSetName WRITE setDataSetName RESET resetDataSetName STORED true )
      Q_PROPERTY( QString dataSetColName READ dataSetColName WRITE setDataSetColName RESET resetDataSetColName STORED true )

   public:
      CoaLineEdit( QWidget *parent = 0 );
      virtual ~CoaLineEdit();

      QMenu *createStandardContextMenu();

   public slots:
      /**
      @warning not thread safe
       */
      virtual void updateValue( const QVariant& );

   protected:
      virtual void contextMenuEvent( QContextMenuEvent *e );

   private:
      Q_DISABLE_COPY( CoaLineEdit );

};



#endif
