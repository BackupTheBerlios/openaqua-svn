#include "coaactiongroup.h"
#include <CoaAction>
#include <CoaDebug>
#include <CoaSignals>

#include <QActionGroup>
#include <QObject>



CoaActionGroup::CoaActionGroup( QObject * parent  )
:QActionGroup(parent)
{
   BEGIN;
}


CoaActionGroup::~CoaActionGroup()
{
   BEGIN;
}

void CoaActionGroup::handleSignal(CoaSignal const*const)
{
   BEGIN;
}



CoaAction* CoaActionGroup::addAction (CoaAction* action)
{
   BEGIN;
   QActionGroup::addAction(action);
   //assert(a == action);

   //Connect action-signlas to the group handle
   connect (   action,  SIGNAL(signal(CoaSignal const* const)),
               this,    SLOT(handleSignal(CoaSignal const*const)),
               Qt::AutoConnection
            );

   //Connect action-signlas to the group handle
   connect (   this,    SIGNAL(signalIntern(CoaSignal const* const)),
               action,  SLOT(handleSignal(CoaSignal const*const)),
               Qt::AutoConnection
            );

   return action;
}
