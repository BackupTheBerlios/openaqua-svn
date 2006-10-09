#include "coachangeshortcut.h"
#include "settings/coachangeshortcutwidget.h"

#include <CoaDebug>
#include <CoaPushButton>
#include <CoaWidget>
#include <CoaBorderLayout>

#include <QHBoxLayout>


COAMAKRO_DEFINE_SINGLETONMETHODS(CoaToolsChangeShortcuts);

CoaToolsChangeShortcuts::CoaToolsChangeShortcuts()
: CoaToolWindow("CoaToolsChangeShortcuts", 0)
{
   BEGIN;
   REGISTERSINGLETON("CoaToolsChangeShortcuts");
   setWindowTitle(tr("Modify Shortcuts [*]", "dont touch the [*]"));
   buildGui();
   readSettings();
}




void CoaToolsChangeShortcuts::buildGui()
{
   BEGIN;

   //the elements
   CoaPushButton *btnDefault = new CoaPushButton(tr("Default"));
   CoaPushButton *btnApply   = new CoaPushButton(tr("Apply"));
   CoaPushButton *btnClose   = new CoaPushButton(tr("Close"));
   CoaSettingsWidgetChangeShortcut *settWidget = new CoaSettingsWidgetChangeShortcut(this);

   btnDefault->setEnabled(false);
   btnApply->setEnabled(false);


   connect(btnApply,    SIGNAL(clicked (bool)), settWidget, SLOT(applyChanges()));
   connect(btnClose,    SIGNAL(clicked (bool)),       this, SLOT(close()));
   connect(settWidget,  SIGNAL(signalIsDirty (bool)), this, SLOT(setWindowModified(bool)));

   setCentralWidget(settWidget);

   addButton(btnDefault);
   addButtonStretch();
   addButton(btnApply);
   addButton(btnClose);
}





CoaToolsChangeShortcuts::~CoaToolsChangeShortcuts()
{
   BEGIN;
   INSTANCE=0;
   UNREGISTERSINGLETON("CoaToolsChangeShortcuts");
   writeSettings();
}

