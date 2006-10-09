#include "coachangedebug.h"
#include "settings/coachangedebugwidget.h"
#include <CoaDebug>

COAMAKRO_DEFINE_SINGLETONMETHODS(CoaToolsChangeDebugSettings);



CoaToolsChangeDebugSettings::CoaToolsChangeDebugSettings()
: CoaToolWindow("CoaToolsChangeDebugSettings", 0)
{
   BEGIN;
   REGISTERSINGLETON("CoaToolsChangeDebugSettings");
   setWindowTitle(tr("Change Debug Settings"));
   buildGui();
   readSettings();
}


void CoaToolsChangeDebugSettings::buildGui()
{
   BEGIN;

   //the elements
   CoaSettingsWidgetChangeDebug *settWidget = new CoaSettingsWidgetChangeDebug(this);
   connect(settWidget,  SIGNAL(signalIsDirty (bool)), this, SLOT(setWindowModified(bool)));
   setCentralWidget(settWidget);
}


CoaToolsChangeDebugSettings::~CoaToolsChangeDebugSettings()
{
   BEGIN;
   INSTANCE=0;
   UNREGISTERSINGLETON("CoaToolsChangeDebugSettings");
   writeSettings();
}



