#ifndef __CoaApplication_h__
#define __CoaApplication_h__

#include <QApplication>
#define COAAPP (static_cast<CoaApplication*>(QCoreApplication::instance()))




/**
@class CoaApplication
*/
class CoaApplication: public QApplication
{
    Q_OBJECT

public:

   CoaApplication(const QString organisationDomain, const QString applicationName, int argc, char **argv, bool GUIenabled = true);
   virtual ~CoaApplication();

   //Load and store settings
   void saveSettings();
   void loadSettings();

private:

};

#endif //__CoaApplication_h__
