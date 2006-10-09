#include "coaactionbuilderhelp.h"
#include <CoaDebug>
#include <CoaAction>
#include <cassert>

#include <CoaDefaultActions>
using namespace CoaDefaultActions;

#include <QMutex>

COAMAKRO_DEFINE_SINGLETONMETHODS(CoaActionBuilderHelp)


////////////////////////////////////////////////////////////
CoaActionBuilderHelp::CoaActionBuilderHelp()
:CoaActionBuilder()
{
   BEGIN;
   QObject::setObjectName("CoaActionBuilderHelp");
}


////////////////////////////////////////////////////////////
CoaActionBuilderHelp::~CoaActionBuilderHelp()
{
   BEGIN;
   INSTANCE=0;
}


////////////////////////////////////////////////////////////
bool CoaActionBuilderHelp::mapActionString2ActionId(const QString& type, int *const actionId)
{
   BEGIN;

   if (type == "actionHelpHandbook") {
      *actionId = actionHelpHandbook;
      RETURN(true);
   }
   if (type == "actionHelpWhatsthis") {
      *actionId = actionHelpWhatsthis;
      RETURN(true);
   }
   if (type == "actionHelpTipOfTheDay") {
      *actionId = actionHelpTipOfTheDay;
      RETURN(true);
   }

   RETURN(false);
}



////////////////////////////////////////////////////////////
bool CoaActionBuilderHelp::checkType                    (const int type)
{
   BEGIN;
   switch(type) {
      case actionHelpHandbook:
      case actionHelpWhatsthis:
      case actionHelpTipOfTheDay: RETURN(true);
      //no default to get compiler warnings!
   }

   RETURN(false);
}



////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setObjectName                (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionHelpHandbook:            action->setObjectName("actionHelpHandbook"); break;
      case actionHelpWhatsthis:           action->setObjectName("actionHelpWhatsthis"); break;
      case actionHelpTipOfTheDay:         action->setObjectName("actionHelpTipOfTheDay"); break;
      //no default to get compiler warnings!
   }

}


////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setDefaultShortcut           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionHelpHandbook:            action->setDefaultShortcut("F1"); break;
      case actionHelpWhatsthis:           action->setDefaultShortcut("Shift+F1"); break;
      case actionHelpTipOfTheDay:         break;
      //no default to get compiler warnings!
   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setShortcutContext           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setShortcutContext(Qt::ApplicationShortcut);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setIcon                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   switch(type) {
      case actionHelpHandbook:            break;
      case actionHelpWhatsthis:           action->setIcon(":/openaqua/icons/systemWhatsthis.png");          break;
      case actionHelpTipOfTheDay:         break;
      //no default to get compiler warnings!
   }
}



////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setToolTip                   (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionHelpHandbook:            action->setToolTip(tr("Opens the Handbook"));  break;
      case actionHelpWhatsthis:           action->setToolTip(tr("Give some short information about the widget your mouse in pointing to"));  break;
      case actionHelpTipOfTheDay:         action->setToolTip(tr("Shows some usefull tips. One for each day"));  break;
      //no default to get compiler warnings!
   }


}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setStatusTip                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setStatusTip(action->toolTip());
}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setText                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionHelpHandbook:            action->setText(tr("&Handbook"));  break;
      case actionHelpWhatsthis:           action->setText(tr("&Whats This?"));  break;
      case actionHelpTipOfTheDay:         action->setText(tr("&Tip of the Day"));  break;
      //no default to get compiler warnings!
   }

}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setEnabledForDefaultToolbar  (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   switch(type) {
      case actionHelpHandbook:            action->setEnabledForDefaultToolbar( true ); break;
      case actionHelpWhatsthis:           action->setEnabledForDefaultToolbar( false ); break;
      case actionHelpTipOfTheDay:         action->setEnabledForDefaultToolbar( false ); break;
      //no default to get compiler warnings!

   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setEnabledForToolbar         (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   Q_UNUSED(action);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setWhatsThis                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setWhatsThis(action->toolTip());

}




////////////////////////////////////////////////////////////
void CoaActionBuilderHelp::setActionBlock               (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setActionBlock(tr("Help Functions"));
}


