#include "coamenu.h"
#include <CoaDebug>
#include <CoaTypedefs>
#include <CoaMenu>
#include <CoaActionGroup>
#include <QList>
#include <CoaAction>


CoaMenu::CoaMenu( QWidget * parent )
:QMenu(parent)
{
   BEGIN;
  // setMenuButtonStyle(Qt::MenuButtonTextOnly);
}

CoaMenu::CoaMenu ( const QString & title, QWidget * parent)
:QMenu(title, parent)
{
   BEGIN;
}



CoaMenu::~CoaMenu()
{
   BEGIN;
}


void CoaMenu::addActionGroup(CoaActionGroup * grp)
{
   BEGIN;
   QList<QAction*> list = grp->actions();

   QList<QAction*> ::const_iterator i;
   for (i = list.constBegin(); i != list.constEnd(); ++i) {
      addAction(*i);
   }
}

