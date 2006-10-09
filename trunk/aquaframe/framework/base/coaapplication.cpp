#include "coaapplication.h"





CoaApplication::CoaApplication(const QString organisationDomain, const QString applicationName, int argc, char **argv, bool GUIenabled)
:QApplication(argc, argv, GUIenabled)
{

#ifdef QSA_NO_EDITOR

//if this assertion comes you have to recompile QSA with the editor feature
COA_ASSERT_COMPILE_CHECK(1==2);

#endif
   /********************************************************
   Warning: NEVER use references here. Dunno why, but crashs
   the app at random point
   ********************************************************/

   /********************************************************
   NO DEBUG METHODS HERE or in called methods!!!!!!!!!!!!!!
   ********************************************************/


   //set the Org and App name as very first
   setOrganizationDomain(organisationDomain);
   setApplicationName(applicationName);



#ifdef Q_WS_MAC
   setQuitOnLastWindowClosed(false);
#else
   setQuitOnLastWindowClosed(true);
#endif



}



CoaApplication::~CoaApplication()
{
   /********************************************************
   NO DEBUG METHODS HERE or in called methods!!!!!!!!!!!!!!
   ********************************************************/
}

