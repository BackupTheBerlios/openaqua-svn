#include "coaactionfactory.h"
#include <CoaDebug>
#include <cassert>
#include <CoaAction>
#include <CoaActionBuilder>
#include <CoaApplication>

#include <QIcon>
#include <QMutex>
#include <QList>


COAMAKRO_DEFINE_SINGLETONTHREADMETHODS(CoaActionFactory);


CoaActionFactory::CoaActionFactory()
:   CoaThread("actionfa")
{
   BEGIN;
}



CoaActionFactory::~CoaActionFactory()
{
   BEGIN;
   INSTANCE=0;

   //dont delete the actions, will be deleteted automaticly
   m_actionBuilder.clear();
   //m_actionList.clear();

   QList<CoaAction*> actionList = m_actionList.values();
   while(!actionList.isEmpty()){
      CoaAction *action = actionList.takeLast();
      if (action->parentWidget() != 0) {
         ERR(QString ("Parent of Action <%1> is not NULL").arg(action->objectName()));
         action->setParent(0);
      }
      //don't delete Actions. Can be still in use somewwhere!
      //delete action;
   }

}




CoaAction*const CoaActionFactory::getAction(const QString& action)
{
   BEGIN;

   //map string to int
   foreach(CoaActionBuilder*const builder, m_actionBuilder) {
      int actionId=0;
      if (builder->mapActionString2ActionId(action, &actionId)==true) {
         RETURN(getAction(actionId));
      }
   }
   CoaAction *c=0;
   RETURN(c);

}




CoaAction*const CoaActionFactory::getAction(const int type)
{
   BEGIN;

   //allready there?
   QMap<int, CoaAction*>::const_iterator i = m_actionList.find(type);
   if (i != m_actionList.end()) {
      //INF(QString("Found Action type %1").arg(type));
      RETURN(i.value());
   }


   //create a new one
   QWriteLocker locker(&m_Lock);
   foreach(CoaActionBuilder*const builder, m_actionBuilder) {
      if (builder->checkType(type) == true){
         CoaAction *action = builder->getAction(type);

         //add the new action
         if (action != 0) {
            action->setParent(this);

            //store the pointer
            m_actionList[type] = action;
            //INF(QString("New Action for type %1 created").arg(type));

            emit newActionAdded(type);
            RETURN(action);

         } else {
            ERR(QString("check fine, but builder did not create action for id %1, builder is %2").arg(type).arg(builder->objectName()));
         }

      }
   }


   //check for errors
   ERR(QString("could not create action for id %1").arg(type));
   assert(0);
   return 0;
}


QList<int> CoaActionFactory::getActionsList() const
{
   BEGIN;
   return m_actionList.keys();
}


/**

The methods adds the builder to the internal set of known builders.
The parent of the new builder will be set to this object

@code

CoaActionBuilder *builder = new MyOwnActionBuilder(0);
CoaActionFactory::getInstance()->addActionBuilder(builder);
CoaAction = CoaActionFactory::getInstance()->getAction(sampleActionId);

@endcode

*/
void CoaActionFactory::addActionBuilder(CoaActionBuilder*const builder)
{
   BEGIN;
   assert(builder);
   if (builder !=0 ){
      QWriteLocker locker(&m_Lock);
      builder->setParent(this);
      m_actionBuilder.insert(builder);
   }
}


/**

The methods removes the builder from the internal set of known builders.
The parent of the removed builder will be set to 0.

@warn The removed builder won't be deleted

*/
void CoaActionFactory::remActionBuilder(CoaActionBuilder*const builder)
{
   BEGIN;
   assert(builder);
   if (builder != 0) {
      QWriteLocker locker(&m_Lock);
      m_actionBuilder.remove(builder);
      builder->setParent(0);
   }
}






void CoaActionFactory::generateShortcutHtmlString (QString *const html) const
{
   BEGIN;
   html->clear();


   //Add html header
   html->append(QString ( "<HTML>"
                 "<HEAD>"
                 "<TITLE>%1: %2</TITLE>"
                 "</HEAD>"
                 "<BODY>"
                 ).arg(COAAPP->applicationName()).arg(tr("Keyboard Shortcuts")));


   //Add a table Header
   html->append(QString  ("<TABLE WIDTH=100% BORDER=0>\n"
//                          "<COL WIDTH=42*>\n"
//                          "<COL WIDTH=115*>\n"
                          //"<COL WIDTH=35*>\n"
                          //"<COL WIDTH=64*>\n"
                         )
               );



   const QList<int> actionsList = CoaActionFactory::getInstance()->getActionsList();
   QList<QString>                      m_blocks;
   QMap<QString, QList<CoaAction*>*>   m_actions;

   //Get the ActionBlocks
   foreach (int iAction, actionsList) {
      CoaAction *action = GETACTION(iAction);
      CoaApplication::processEvents();

      QString block = action->actionBlock();
      QMap<QString, QList<CoaAction*>*>::iterator j;
      j = m_actions.find(block);
      if (j == m_actions.end()) {
         QList<CoaAction*> *list = new QList<CoaAction*>;
         *list << action;
         m_blocks << block;
         m_actions.insert(block, list);
      } else {
         QList<CoaAction*> *list = *j;
         *list << action;
      }
   }

   //Sort the stuff
   qSort(m_blocks.begin(), m_blocks.end());
   foreach (QList<CoaAction*> *list, m_actions){
      qSort(list->begin(), list->end(), CoaAction::compareActionsOnText);
   }



   //Iterate blockwise over all actions for output
   foreach (QString block, m_blocks) {
      html->append(QString("<TR><TD COLSPAN=4 VALIGN=TOP><B>%1</B></TD></TR>").arg(block));
      QList <CoaAction*> *list = m_actions.value(block);
      foreach (CoaAction* action, *list) {
         QKeySequence seq = action->shortcut();
         html->append(QString("<TR VALIGN=TOP><TD>%1</TD><TD>%2</TD><TD>%3</TD><TD>%4</TD></TR>")
                           .arg("")
                           .arg(action->pureText())
                           .arg(action->defaultWhatsThisText())
                           .arg(QString(seq))
                      );

      }//foreach
   } //foreach


   //Append the doc end
   html->append(QString ("</TABLE>"));
   html->append(QString ("</BODY>" ));
}


