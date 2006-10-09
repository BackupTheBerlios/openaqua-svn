#include "coaactionbuilderdebug.h"
#include <CoaDebug>
#include <CoaAction>
#include <cassert>

#include <CoaDefaultActions>
using namespace CoaDefaultActions;

#include <QMutex>

COAMAKRO_DEFINE_SINGLETONMETHODS(CoaActionBuilderDebug)



actionDebug  CoaActionBuilderDebug::mapInt2Enum(const int i, bool *works) const
{
   if (works != 0)
      *works=true;

   switch(i){
   case actionDebugSettings:       return actionDebugSettings;
   case actionDebugOnOff:          return actionDebugOnOff;
   case actionDebugShowTimeOnOff:  return actionDebugShowTimeOnOff;

   case actionDebugFileDefaultsOff: return actionDebugFileDefaultsOff;
   case actionDebugFileDefaultsErr: return actionDebugFileDefaultsErr;
   case actionDebugFileDefaultsWrn: return actionDebugFileDefaultsWrn;
   case actionDebugFileDefaultsInf: return actionDebugFileDefaultsInf;
   case actionDebugFileDefaultsDbg: return actionDebugFileDefaultsDbg;
   }

   if (works != 0)
      *works=false;
   return actionDebugFileDefaultsDbg;

}


////////////////////////////////////////////////////////////
CoaActionBuilderDebug::CoaActionBuilderDebug()
:CoaActionBuilder()
{
   BEGIN;
   QObject::setObjectName("CoaActionBuilderDebug");
}


////////////////////////////////////////////////////////////
CoaActionBuilderDebug::~CoaActionBuilderDebug()
{
   BEGIN;
   INSTANCE=0;
}


////////////////////////////////////////////////////////////
bool CoaActionBuilderDebug::mapActionString2ActionId(const QString& type, int *const actionId)
{
   BEGIN;

   if (type == "actionDebugSettings") {
      *actionId = actionDebugSettings;
      RETURN(true);
   }
   if (type == "actionDebugOnOff") {
      *actionId = actionDebugOnOff;
      RETURN(true);
   }
   if (type == "actionDebugShowTimeOnOff") {
      *actionId = actionDebugShowTimeOnOff;
      RETURN(true);
   }
   if (type == "actionDebugFileDefaultsOff") {
      *actionId = actionDebugFileDefaultsOff;
      RETURN(true);
   }
   if (type == "actionDebugFileDefaultsErr") {
      *actionId = actionDebugFileDefaultsErr;
      RETURN(true);
   }
   if (type == "actionDebugFileDefaultsWrn") {
      *actionId = actionDebugFileDefaultsWrn;
      RETURN(true);
   }
   if (type == "actionDebugFileDefaultsInf") {
      *actionId = actionDebugFileDefaultsInf;
      RETURN(true);
   }
   if (type == "actionDebugFileDefaultsDbg") {
      *actionId = actionDebugFileDefaultsDbg;
      RETURN(true);
   }

   RETURN(false);
}



////////////////////////////////////////////////////////////
bool CoaActionBuilderDebug::checkType                    (const int type)
{
   BEGIN;
   bool works=false;
   mapInt2Enum(type, &works);
   RETURN(works);
}



////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setObjectName                (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   bool works = false;
   CoaDefaultActions::actionDebug myType = mapInt2Enum(type, &works);
   assert(works == true);
   
   switch(myType) {
      case actionDebugSettings:       action->setObjectName("actionDebugSettings"); break;
      case actionDebugOnOff:          action->setObjectName("actionDebugOnOff"); break;
      case actionDebugShowTimeOnOff:  action->setObjectName("actionDebugShowTimeOnOff"); break;

      case actionDebugFileDefaultsOff: action->setObjectName("actionDebugFileDefaultsOff"); break;
      case actionDebugFileDefaultsErr: action->setObjectName("actionDebugFileDefaultsErr"); break;
      case actionDebugFileDefaultsWrn: action->setObjectName("actionDebugFileDefaultsWrn"); break;
      case actionDebugFileDefaultsInf: action->setObjectName("actionDebugFileDefaultsInf"); break;
      case actionDebugFileDefaultsDbg: action->setObjectName("actionDebugFileDefaultsDbg"); break;

      //no default to get compiler warnings!
   }

}


////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setDefaultShortcut           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   //no default shortcuts
   if (type == actionDebugSettings)
   {
      action->setDefaultShortcut(tr("Ctrl+F12"));
   }

}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setShortcutContext           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setShortcutContext(Qt::ApplicationShortcut);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setIcon                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   //no icons
   Q_UNUSED(action);
   Q_UNUSED(type);
}



////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setToolTip                   (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(mapInt2Enum(type)) {
      case actionDebugSettings:       action->setToolTip(tr("Opens a Toolwindow where you change the Debug settings"));  break;
      case actionDebugOnOff:          action->setToolTip(tr("Turns Debugging On or Off"));  break;
      case actionDebugShowTimeOnOff:  action->setToolTip(tr("Turns the Time in Debug output On or Off"));  break;

      case actionDebugFileDefaultsOff: action->setToolTip(tr("Set file debug mode defaults to \"OFF\""));  break;
      case actionDebugFileDefaultsErr: action->setToolTip(tr("Set file debug mode defaults to \"ERR\""));  break;
      case actionDebugFileDefaultsWrn: action->setToolTip(tr("Set file debug mode defaults to \"WRN\""));  break;
      case actionDebugFileDefaultsInf: action->setToolTip(tr("Set file debug mode defaults to \"INF\""));  break;
      case actionDebugFileDefaultsDbg: action->setToolTip(tr("Set file debug mode defaults to \"DBG\""));  break;

      //no default to get compiler warnings!
   }



}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setStatusTip                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setStatusTip(action->toolTip());
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setText                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(mapInt2Enum(type)) {
      case actionDebugSettings:       action->setText(tr("Debug &Settings"));  break;
      case actionDebugOnOff:          action->setText(tr("Debug En&abled"));  break;
      case actionDebugShowTimeOnOff:  action->setText(tr("&Time in Output"));  break;

      case actionDebugFileDefaultsOff: action->setText(tr("Debug Mode: &OFF"));  break;
      case actionDebugFileDefaultsErr: action->setText(tr("Debug Mode: &ERR"));  break;
      case actionDebugFileDefaultsWrn: action->setText(tr("Debug Mode: &WRN"));  break;
      case actionDebugFileDefaultsInf: action->setText(tr("Debug Mode: &INF"));  break;
      case actionDebugFileDefaultsDbg: action->setText(tr("Debug Mode: &DBG"));  break;

      //no default to get compiler warnings!
   }

}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setEnabledForDefaultToolbar  (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setEnabledForDefaultToolbar(false);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setEnabledForToolbar         (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setEnabledForDefaultToolbar(false);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setWhatsThis                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setWhatsThis(action->toolTip());

}




////////////////////////////////////////////////////////////
void CoaActionBuilderDebug::setActionBlock               (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setActionBlock(tr("Debug Functions"));
}


