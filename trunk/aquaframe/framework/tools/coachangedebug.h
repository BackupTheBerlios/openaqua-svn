#ifndef __CoaToolsChangeDebugSettings_h_
#define __CoaToolsChangeDebugSettings_h_

#include <CoaToolWindow>
#include <CoaMakros>



/**
@brief

The Object destroyes itself after closing.
*/
class CoaToolsChangeDebugSettings: public CoaToolWindow
{
   Q_OBJECT
   void buildGui();

   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaToolsChangeDebugSettings);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaToolsChangeDebugSettings);
   COAMAKRO_NO_COMPARE(CoaToolsChangeDebugSettings);

};

#endif //__CoaToolsChangeDebugSettings_h_
