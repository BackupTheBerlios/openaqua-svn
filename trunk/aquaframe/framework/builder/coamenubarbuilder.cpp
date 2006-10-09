#include "coamenubarbuilder.h"
#include <cassert>
#include <CoaDebug>
#include <CoaMainWindow>
#include <CoaMenuBar>
#include <CoaMenu>
#include <CoaAction>
#include <CoaDomDocument>
#include <CoaActionFactory>
#include <CoaMenuBar>

#include <QErrorMessage>



CoaMenuBarBuilder::CoaMenuBarBuilder(QObject *parent)
:QObject(parent)
{
   BEGIN;
}



CoaMenuBar*const CoaMenuBarBuilder::getMenuBar(CoaFile *const file)
{
   BEGIN;

   //load the xml file
   CoaDomDocument doc("CoaMenuBarDescription");

   QString errorStr;
   int errorLine;
   int errorColumn;


   //set the content
   if (!doc.setContent(file, true, &errorStr, &errorLine, &errorColumn)) {
      QString error = QString(tr("Error while loading the MenuBar XML File <%1> in line %2, column %3.\nThe error was \"%4\""))
                   .arg(file->fileName())
                   .arg(errorLine)
                   .arg(errorColumn)
                   .arg(errorStr);
      ERR(error);

      QErrorMessage msgBox(0);
      msgBox.showMessage ( error );
      return 0;
   }

   //correct root element?
   QDomElement root = doc.documentElement();
   if (root.tagName() != "CoaMenuBarDescription") {
      QString error = QString(tr("Error while loading the MenuBar XML File <%1>.\nThe Document isn't a CoaMenuBarDescription File"))
                   .arg(file->fileName());
      ERR(error);

      QErrorMessage msgBox(0);
      msgBox.showMessage ( error );
      return 0;
   }



   //correct version?
   if (!root.hasAttribute("version") || root.attribute("version") != "1.0"  ) {
      QString error = QString(tr("Error while loading the MenuBar XML File <%1>.\nThe Document isn't a CoaMenuBarDescription File with Version 1.0"))
                   .arg(file->fileName());

      ERR(error);
      QErrorMessage msgBox(0);
      msgBox.showMessage ( error );
      return 0;
   }

   //create the menubar
   CoaMenuBar *menuBar = new CoaMenuBar();
   assert(menuBar);

   //parse the file
   QDomNode node = root.firstChildElement("menu");
   while (!node.isNull()){
      QString menuTitle = node.toElement().attribute("name");
      if (!menuTitle.isEmpty()){
         CoaMenu *menu = new CoaMenu(menuTitle);
         menuBar->addMenu(menu);
         parseMenu(node, menu);
      }

      node = node.nextSiblingElement("menu");
   }

   return menuBar;
}




/**
@warning method does a self recursive call
*/
void CoaMenuBarBuilder::parseMenu(const QDomNode &node, CoaMenu* const menu)
{
   BEGIN;
   assert(menu);
   if (menu == 0) return;

   QDomNode subNode = node.firstChildElement();
   while (!subNode.isNull()){
      //handle sub menus, warning recursive call
      if (subNode.toElement().tagName() == "menu") {
         QString menuTitle = subNode.toElement().attribute("name");
         if (!menuTitle.isEmpty()){
            CoaMenu *subMenu = new CoaMenu(menuTitle);
            menu->addMenu(subMenu);
            parseMenu(subNode, subMenu);
         }

      //handle action entries
      } else if (subNode.toElement().tagName() == "action") {
         QString type = subNode.toElement().attribute("type");
         CoaAction * const action = CoaActionFactory::getInstance()->getAction(type);
         if (action != 0){
            menu->addAction(action);
            //INF(QString("Action <%1> added").arg(type));
         } else {
            ERR(QString("Unknown Actiontype <%1> requested").arg(type));
         }

      //handle separators
      } else if (subNode.toElement().tagName() == "separator") {
         menu->addSeparator();

      //handle errors
      } else {
         ERR(QString("Unknown Tag in CoaMenuBarDescription xml file: <%1>").arg(subNode.toElement().tagName()));
      }
      subNode = subNode.nextSibling();
   }
   return;
}
