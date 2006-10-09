#ifndef __CoaAboutBox_h_
#define __CoaAboutBox_h_

#include <CoaToolWindow>
#include <CoaMakros>



/**
@brief


The Object destroyes itself after closing.
*/
class CoaAboutBox: public CoaToolWindow
{
    Q_OBJECT

private:
   void initLicencePage();
   void initApplicationPage();

   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaAboutBox);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaAboutBox);
   COAMAKRO_NO_COMPARE(CoaAboutBox);

};

#endif //__CoaAboutBox_h_
