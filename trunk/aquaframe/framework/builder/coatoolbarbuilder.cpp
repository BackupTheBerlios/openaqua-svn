#include "coatoolbarbuilder.h"
#include <cassert>
#include <CoaDebug>

#include <CoaMainWindow>
#include <CoaToolBar>
#include <CoaMenu>
#include <CoaAction>
#include <CoaDomDocument>
#include <CoaActionFactory>
#include <CoaToolBar>
#include <CoaPushButton>

#include <QErrorMessage>



CoaToolBarBuilder::CoaToolBarBuilder(QObject *parent)
:QObject(parent)
{
   BEGIN;
}



CoaToolBar*const CoaToolBarBuilder::getToolBar(CoaFile *const file)
{
   BEGIN;

   //load the xml file
   CoaDomDocument doc("CoaToolBarDescription");

   QString errorStr;
   int errorLine;
   int errorColumn;


   //set the content
   if (!doc.setContent(file, true, &errorStr, &errorLine, &errorColumn)) {
      QString error = QString(tr("Error while loading the ToolBar XML File <%1> in line %2, column %3.\nThe error was \"%4\""))
                   .arg(file->fileName())
                   .arg(errorLine)
                   .arg(errorColumn)
                   .arg(errorStr);
      ERR(error);

      QErrorMessage msgBox(0);
      msgBox.showMessage ( error );
      return 0;
   }

   //correct root node?
   QDomElement root = doc.documentElement();
   if (root.tagName() != "CoaToolBarDescription") {
      QString error = QString(tr("Error while loading the ToolBar XML File <%1>.\nThe Document isn't a CoaToolBarDescription File"))
                   .arg(file->fileName());
      ERR(error);

      QErrorMessage msgBox(0);
      msgBox.showMessage ( error );
      return 0;
   }



   //correct version?
   if (!root.hasAttribute("version") || root.attribute("version") != "1.0"  ) {
      QString error = QString(tr("Error while loading the ToolBar XML File <%1>.\nThe Document isn't a CoaToolBarDescription File with Version 1.0"))
                   .arg(file->fileName());

      ERR(error);
      QErrorMessage msgBox(0);
      msgBox.showMessage ( error );
      return 0;
   }

   //create the menubar
   CoaToolBar *toolBar = new CoaToolBar();
   assert(toolBar);

   //parse the file
   QDomNode node = root.firstChildElement();
   while (!node.isNull()){

      //get the tag
      const QString tag(node.toElement().tagName());

      //react on different tags
      if (tag == "menu") {               addMenu (node, toolBar);
      } else if (tag == "group") {       addGroup (node, toolBar);
      } else if (tag == "action") {      addAction (node, toolBar);
      } else if (tag == "separator") {   addSeparator (node, toolBar);
      } else if (tag.isEmpty()){         //do nothing
      } else {                           ERR(QString("Found unknown Tag <%1> in Xml File").arg(tag));
      }

      node = node.nextSibling();
   }

   return toolBar;
}



void CoaToolBarBuilder::addMenu   (const QDomNode& node, CoaToolBar *const toolBar)
{
   BEGIN;
   if (node.toElement().tagName() != "menu") return;
   if (!node.toElement().hasAttribute("name")) return;
   QString menuTitle = node.toElement().attribute("name");
   if (menuTitle.isEmpty()) return;

   CoaPushButton *button = new CoaPushButton(menuTitle, toolBar);
   CoaMenu *menu = new CoaMenu(menuTitle, button);
   button->setMenu(menu);
   toolBar->addWidget(button);
   parseMenu(node, menu);


}



void CoaToolBarBuilder::addAction (const QDomNode& node, CoaToolBar *const toolBar)
{
   BEGIN;

   if (node.toElement().tagName() != "action") return;
   if (!node.toElement().hasAttribute("type")) return;

   QString type = node.toElement().attribute("type");
   CoaAction * const action = CoaActionFactory::getInstance()->getAction(type);
   if (action != 0) {
      toolBar->addAction(action);
   } else {
      ERR(QString("Unknown Actiontype <%1> requested").arg(type));
   }

   //INF(QString("node = <%1 type=\"%2\">").arg(node.toElement().tagName()).arg(type));

}



void CoaToolBarBuilder::addGroup  (const QDomNode& node, CoaToolBar *const toolBar)
{
   BEGIN;
   Q_UNUSED(node);
   Q_UNUSED(toolBar);
   WRN("Group in CoaToolBarBuilder requested, cannot handle that yet");
   //INF(QString("node = <%1>").arg(node.toElement().tagName()));
}




void CoaToolBarBuilder::addSeparator (const QDomNode& node, CoaToolBar *const toolBar)
{
   BEGIN;

   if (node.toElement().tagName() != "separator") return;
   toolBar->addSeparator();

   //INF(QString("node = <%1 type=\"%2\">").arg(node.toElement().tagName()).arg(type));

}


void CoaToolBarBuilder::parseMenu(const QDomNode &node, CoaMenu* const menu)
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

