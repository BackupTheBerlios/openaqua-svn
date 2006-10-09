#include "coatextbrowser.h"
#include <CoaDebug>
#include <CoaApplication>
#include <CoaMenu>


#include <QContextMenuEvent>


CoaTextBrowser::CoaTextBrowser(QWidget *parent)
:QTextBrowser(parent)
{
   BEGIN;
}


void CoaTextBrowser::contextMenuEvent(QContextMenuEvent *e)
{
   BEGIN;

   QMenu *menu = createStandardContextMenu();
   menu->exec(e->globalPos());
   delete menu;
}

QMenu *CoaTextBrowser::createStandardContextMenu()
{
   BEGIN;

   CoaMenu *menu = new CoaMenu(this);
   //menu->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupEdit));
   return menu;

}

