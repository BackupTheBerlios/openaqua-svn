#ifndef __CoaToolsChangeShortCuts_h__
#define __CoaToolsChangeShortCuts_h__

#include <CoaToolWindow>
#include <CoaMakros>


/**
@brief

The Object destroyes itself after closing.
*/
class CoaToolsChangeShortcuts: public CoaToolWindow
{
   Q_OBJECT
   void buildGui();

   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaToolsChangeShortcuts);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaToolsChangeShortcuts);
   COAMAKRO_NO_COMPARE(CoaToolsChangeShortcuts);

};

#endif //__CoaToolsChangeShortCuts_h__
