#include "coaactionbuilderapplication.h"
#include <CoaDebug>
#include <CoaAction>
#include <CoaApplication>
#include <cassert>
#include <CoaDefaultActions>
using namespace CoaDefaultActions;

#include <QMutex>

COAMAKRO_DEFINE_SINGLETONMETHODS(CoaActionBuilderApplication)


////////////////////////////////////////////////////////////
CoaActionBuilderApplication::CoaActionBuilderApplication()
:CoaActionBuilder()
{
   BEGIN;
   QObject::setObjectName("CoaActionBuilderApplication");
}




////////////////////////////////////////////////////////////
CoaActionBuilderApplication::~CoaActionBuilderApplication()
{
   BEGIN;
   INSTANCE=0;
}







////////////////////////////////////////////////////////////
bool CoaActionBuilderApplication::mapActionString2ActionId(const QString& type, int *const actionId)
{
   BEGIN;

   if (type == "actionApplicationQuit") {
      *actionId = actionApplicationQuit;
      RETURN(true);
   }
   if (type == "actionApplicationSettings") {
      *actionId = actionApplicationSettings;
      RETURN(true);
   }
   if (type == "actionApplicationSetShortcuts") {
      *actionId = actionApplicationSetShortcuts;
      RETURN(true);
   }
   if (type == "actionApplicationPrintShortcuts") {
      *actionId = actionApplicationPrintShortcuts;
      RETURN(true);
   }
   if (type == "actionApplicationSwitchNeutralMode") {
      *actionId = actionApplicationSwitchNeutralMode;
      RETURN(true);
   }
   if (type == "actionApplicationSwitchSDIMode") {
      *actionId = actionApplicationSwitchSDIMode;
      RETURN(true);
   }
   if (type == "actionApplicationSwitchMDIMode") {
      *actionId = actionApplicationSwitchMDIMode;
      RETURN(true);
   }
   if (type == "actionApplicationAboutApplication") {
      *actionId = actionApplicationAboutApplication;
      RETURN(true);
   }

   RETURN(false);
}



////////////////////////////////////////////////////////////
bool CoaActionBuilderApplication::checkType                    (const int type)
{
   BEGIN;
   switch(type) {
      case actionApplicationQuit:
      case actionApplicationSettings:
      case actionApplicationSetShortcuts:

      case actionApplicationPrintShortcuts:
      case actionApplicationSwitchNeutralMode:

      case actionApplicationSwitchSDIMode:
      case actionApplicationSwitchMDIMode:
      case actionApplicationAboutApplication:   RETURN(true);
      //no default to get compiler warnings!
   }

   RETURN(false);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setObjectName                (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionApplicationQuit:             action->setObjectName("actionApplicationQuit"); break;
      case actionApplicationSettings:         action->setObjectName("actionApplicationSettings"); break;
      case actionApplicationSetShortcuts:     action->setObjectName("actionApplicationSetShortcuts"); break;
      case actionApplicationPrintShortcuts:   action->setObjectName("actionApplicationPrintShortcuts"); break;
      case actionApplicationSwitchNeutralMode:action->setObjectName("actionApplicationSwitchNeutralMode"); break;
      case actionApplicationSwitchSDIMode:    action->setObjectName("actionApplicationSwitchSDIMode"); break;
      case actionApplicationSwitchMDIMode:    action->setObjectName("actionApplicationSwitchMDIMode"); break;
      case actionApplicationAboutApplication: action->setObjectName("actionApplicationAboutApplication"); break;
      //no default to get compiler warnings!
   }

}


////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setDefaultShortcut           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionApplicationQuit:             action->setDefaultShortcut(tr("Ctrl+Q")); break;
      case actionApplicationSettings:
      case actionApplicationSetShortcuts:
      case actionApplicationPrintShortcuts:
      case actionApplicationSwitchNeutralMode:
      case actionApplicationSwitchSDIMode:
      case actionApplicationSwitchMDIMode:
      case actionApplicationAboutApplication: break;
      //no default to get compiler warnings!
   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setShortcutContext           (CoaAction*const  action, const int type)
{
   BEGIN;
   Q_UNUSED(type);
   assert(action);
   action->setShortcutContext(Qt::ApplicationShortcut);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setIcon                      (CoaAction*const  action, const int type)
{
   BEGIN;
   Q_UNUSED(type);
   Q_UNUSED(action);
   //no Icons yet
}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setToolTip                   (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionApplicationQuit:             action->setToolTip(tr("Quit the Application"));  break;
      case actionApplicationSettings:         action->setToolTip(tr("Change Application Settings"));  break;
      case actionApplicationSetShortcuts:     action->setToolTip(tr("Change Shortcuts"));  break;
      case actionApplicationPrintShortcuts:   action->setToolTip(tr("Print a List of Shortcuts"));  break;
      case actionApplicationSwitchNeutralMode:break; //should never be shown in a menu!!
      case actionApplicationSwitchSDIMode:    action->setToolTip(tr("Switch the Application GUI mode to a SDI Mode"));  break;
      case actionApplicationSwitchMDIMode:    action->setToolTip(tr("Switch the Application GUI mode to a MDI Mode"));  break;
      case actionApplicationAboutApplication: action->setToolTip(tr("Show Information about this Application"));  break;
      //no default to get compiler warnings!
   }


}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setStatusTip                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setStatusTip(action->toolTip());
}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setText                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionApplicationQuit:             action->setText(tr("&Quit"));  break;
      case actionApplicationSettings:         action->setText(tr("&Settings..."));  break;
      case actionApplicationSetShortcuts:     action->setText(tr("Set Short&cuts..."));  break;
      case actionApplicationPrintShortcuts:   action->setText(tr("&Print Shortcuts..."));  break;
      case actionApplicationSwitchNeutralMode:action->setText(tr("Switch to &Neutral Mode"));  break;
      case actionApplicationSwitchSDIMode:    action->setText(tr("Switch to SD&I Mode"));  break;
      case actionApplicationSwitchMDIMode:    action->setText(tr("Switch to &MDI Mode"));  break;
      case actionApplicationAboutApplication: action->setText(QString (tr("about %1")).arg(COAAPP->applicationName()));  break;
      //no default to get compiler warnings!
   }

}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setEnabledForDefaultToolbar  (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   switch(type) {
      case actionApplicationQuit:             action->setEnabledForDefaultToolbar( true ); break;
      case actionApplicationSettings:         action->setEnabledForDefaultToolbar( false ); break;
      case actionApplicationSetShortcuts:     action->setEnabledForDefaultToolbar( false ); break;
      case actionApplicationPrintShortcuts:   action->setEnabledForDefaultToolbar( false ); break;
      case actionApplicationSwitchNeutralMode:action->setEnabledForDefaultToolbar( false ); break;
      case actionApplicationSwitchSDIMode:    action->setEnabledForDefaultToolbar( false ); break;
      case actionApplicationSwitchMDIMode:    action->setEnabledForDefaultToolbar( false ); break;
      case actionApplicationAboutApplication: action->setEnabledForDefaultToolbar( false ); break;
      //no default to get compiler warnings!
   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setEnabledForToolbar         (CoaAction*const  action, const int type)
{
   BEGIN;
   Q_UNUSED(type);
   Q_UNUSED(action);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setWhatsThis                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setWhatsThis(action->toolTip());

}





////////////////////////////////////////////////////////////
void CoaActionBuilderApplication::setActionBlock               (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setActionBlock(tr("Application"));
}


