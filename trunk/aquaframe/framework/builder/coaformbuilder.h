#ifndef __CoaFormBuilder_h__
#define __CoaFormBuilder_h__

#include <QtUiTools>

#include <QString>

#include <QObject>

class QWidget;


class CoaFormBuilder:public QUiLoader
{
   Q_OBJECT
public:
   CoaFormBuilder( QObject *parent = 0 );
   virtual ~CoaFormBuilder();

   //!wahrscheinlich nicht mehr benoetigt
   virtual QWidget *createWidget2( const QString & className, QWidget * parent = 0, const QString & name = QString() );
   virtual QWidget *createWidget( const QString & className, QWidget * parent = 0, const QString & name = QString() );
};



#endif
