#include "coaactionbuilder.h"
#include <CoaDebug>
#include <CoaAction>


CoaActionBuilder::CoaActionBuilder()
:QObject()
{
   BEGIN;
   QObject::setObjectName("CoaActionBuilder");
}

CoaActionBuilder::~CoaActionBuilder()
{
   BEGIN;
}

CoaAction*const CoaActionBuilder::getAction(const int type)
{
   BEGIN;

   if (true == checkType (type)) {
      CoaAction *const action = new CoaAction(type);
      setObjectName                (action, type);
      setDefaultShortcut           (action, type);
      setShortcutContext           (action, type);
      setIcon                      (action, type);
      setToolTip                   (action, type);
      setStatusTip                 (action, type);
      setText                      (action, type);
      setEnabledForDefaultToolbar  (action, type);
      setEnabledForToolbar         (action, type);
      setWhatsThis                 (action, type);
      setActionBlock               (action, type);
      QKeySequence key = action->loadSavedShortcut(action->defaultShortcut());
      action->setShortcut(key);
      RETURN(action);
   }

   return 0;
}

CoaAction*const CoaActionBuilder::getAction(const QString& type)
{
   BEGIN;
   int actionId=0;
   if (mapActionString2ActionId(type, &actionId)){
      RETURN(getAction(actionId));
   } else  {
      return (0);
   }
}


bool  CoaActionBuilder::checkType(const QString& type){
   BEGIN;
   int actionId=0;
   RETURN (mapActionString2ActionId(type, &actionId));
}
