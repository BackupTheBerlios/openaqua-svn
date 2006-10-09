#ifndef __CoaSettings_h__
#define __CoaSettings_h__

#include <QSettings>



/**
@class CoaSettings

*/
class CoaSettings: public QSettings
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0.0")

public:

   CoaSettings( QObject * parent = 0 );
   CoaSettings( const QString & organization, const QString & application, QObject * parent = 0 );
   virtual ~CoaSettings();


private:
   //not implemented

};

#endif //__CoaSettings_h__
