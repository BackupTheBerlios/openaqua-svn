#include "coamenubar.h"
#include <CoaDebug>
#include <CoaTypedefs>
#include <CoaMenu>
#include <CoaActionGroup>
#include <QList>


CoaMenuBar::CoaMenuBar( QWidget * parent )
:QMenuBar(parent)
{
   BEGIN;
  // setMenuButtonStyle(Qt::MenuButtonTextOnly);
}



CoaMenuBar::~CoaMenuBar()
{
   BEGIN;
}


void CoaMenuBar::addActionGroup(CoaActionGroup * grp)
{
   BEGIN;

   CoaMenu* menu = new CoaMenu(this);
   menu->setTitle(grp->objectName());
   menu->addActionGroup(grp);
   addMenu(menu);
}


