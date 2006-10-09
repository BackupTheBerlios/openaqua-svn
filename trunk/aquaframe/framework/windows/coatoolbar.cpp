#include "coatoolbar.h"
#include <CoaDebug>
#include <CoaTypedefs>
#include <CoaAction>
#include <CoaActionGroup>
#include <QList>
#include <cassert>



CoaToolBar::CoaToolBar ( const QString & title, QWidget * parent)
:QToolBar(title, parent)
{
   BEGIN;
  // setToolButtonStyle(Qt::ToolButtonTextOnly);
//#ifdef Q_WS_MAC
   setMovable(false);
//#endif
}



CoaToolBar::CoaToolBar( QWidget * parent )
:QToolBar(parent)
{
   BEGIN;
  // setToolButtonStyle(Qt::ToolButtonTextOnly);
//#ifdef Q_WS_MAC
   setMovable(false);
//#endif
}



CoaToolBar::~CoaToolBar()
{
   BEGIN;
}


void CoaToolBar::addActionGroup(CoaActionGroup * grp)
{
   BEGIN;

   QList<QAction*> list = grp->actions();

   QList<QAction*> ::const_iterator i;
   for (i = list.constBegin(); i != list.constEnd(); ++i) {
      assert(*i);

      //if the action object a CoaAction????
      if ( CoaAction *a = qobject_cast<CoaAction*>(*i) ) {

         //Yepp, is it enabled for default toolbar???
         if (a->enabledForDefaultToolbar()) {
            addAction(a);
         }

      } else {
         ERR("Cannot handle QAction objects");
         assert(1==2);
      }
   }
}

void CoaToolBar::addAction(CoaAction *const action)
{
   BEGIN;
   QToolBar::addAction(action);
}



