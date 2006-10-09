#include "coaactionbuilderdatabase.h"

#include <CoaDebug>
#include <cassert>
#include <CoaAction>

#include <CoaDefaultActions>
using namespace CoaDefaultActions;

#include <QMutex>
COAMAKRO_DEFINE_SINGLETONMETHODS(CoaActionBuilderDatabase);

actionDatabase CoaActionBuilderDatabase::mapInt2Enum(const int i, bool *works) const
{
   if (works != 0)
      *works=true;

   switch(i){
      case actionDatabaseCreate                   : return actionDatabaseCreate;
      case actionDatabaseImportFromXml            : return actionDatabaseImportFromXml;
      case actionDatabaseExportToXml              : return actionDatabaseExportToXml;

      case actionDatabaseOpenConnection           : return actionDatabaseOpenConnection;
      case actionDatabaseCloseConnection          : return actionDatabaseCloseConnection;

      case actionDatabaseGotoFirst                : return actionDatabaseGotoFirst;
      case actionDatabaseGotoPrevius              : return actionDatabaseGotoPrevius;
      case actionDatabaseGotoNext                 : return actionDatabaseGotoNext;
      case actionDatabaseGotoLast                 : return actionDatabaseGotoLast;

      case actionDatabaseLookup                   : return actionDatabaseLookup;
      case actionDatabaseSqlBrowser               : return actionDatabaseSqlBrowser;
      case actionDatabaseSqlEditor                : return actionDatabaseSqlEditor;

   }

   if (works != 0)
      *works=false;

   return actionDatabaseOpenConnection;

}


////////////////////////////////////////////////////////////
CoaActionBuilderDatabase::CoaActionBuilderDatabase()
:CoaActionBuilder()
{
   BEGIN;
   QObject::setObjectName("CoaActionBuilderDatabase");
}



////////////////////////////////////////////////////////////
CoaActionBuilderDatabase::~CoaActionBuilderDatabase()
{
   BEGIN;
   INSTANCE=0;
}


////////////////////////////////////////////////////////////
bool CoaActionBuilderDatabase::mapActionString2ActionId(const QString& type, int *const actionId)
{
   BEGIN;


   if (type == "actionDatabaseCreate") {
      *actionId = actionDatabaseCreate;
      RETURN(true);
   }
   if (type == "actionDatabaseImportFromXml") {
      *actionId = actionDatabaseImportFromXml;
      RETURN(true);
   }
   if (type == "actionDatabaseOpenConnection") {
      *actionId = actionDatabaseOpenConnection;
      RETURN(true);
   }
   if (type == "actionDatabaseGotoFirst") {
      *actionId = actionDatabaseGotoFirst;
      RETURN(true);
   }
   if (type == "actionDatabaseGotoPrevius") {
      *actionId = actionDatabaseGotoPrevius;
      RETURN(true);
   }
   if (type == "actionDatabaseGotoNext") {
      *actionId = actionDatabaseGotoNext;
      RETURN(true);
   }
   if (type == "actionDatabaseGotoLast") {
      *actionId = actionDatabaseGotoLast;
      RETURN(true);
   }

   if (type == "actionDatabaseLookup") {
      *actionId = actionDatabaseLookup;
      RETURN(true);
   }

   if (type == "actionDatabaseSqlBrowser") {
      *actionId = actionDatabaseSqlBrowser;
      RETURN(true);
   }

   if (type == "actionDatabaseSqlEditor") {
      *actionId = actionDatabaseSqlEditor;
      RETURN(true);
   }

   RETURN(false);
}





////////////////////////////////////////////////////////////
bool CoaActionBuilderDatabase::checkType                    (const int type)
{
   BEGIN;
   bool works=false;
   mapInt2Enum(type, &works);
   RETURN(works);
}





////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setObjectName                (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   //get and check the type
   bool works = false;
   CoaDefaultActions::actionDatabase myType = mapInt2Enum(type, &works);
   assert(works == true);

   //do the work
   switch(myType) {

      case actionDatabaseCreate                   : action->setObjectName("actionDatabaseCreate"); break;
      case actionDatabaseImportFromXml            : action->setObjectName("actionDatabaseImportFromXml"); break;
      case actionDatabaseExportToXml              : action->setObjectName("actionDatabaseExportToXml"); break;

      case actionDatabaseOpenConnection           : action->setObjectName("actionDatabaseOpenConnection"); break;
      case actionDatabaseCloseConnection          : action->setObjectName("actionDatabaseCloseConnection"); break;

      case actionDatabaseGotoFirst                : action->setObjectName("actionDatabaseGotoFirst"); break;
      case actionDatabaseGotoPrevius              : action->setObjectName("actionDatabaseGotoPrevius"); break;
      case actionDatabaseGotoNext                 : action->setObjectName("actionDatabaseGotoNext"); break;
      case actionDatabaseGotoLast                 : action->setObjectName("actionDatabaseGotoLast"); break;

      case actionDatabaseLookup                   : action->setObjectName("actionDatabaseLookup"); break;
      case actionDatabaseSqlBrowser               : action->setObjectName("actionDatabaseSqlBrowser"); break;
      case actionDatabaseSqlEditor                : action->setObjectName("actionDatabaseSqlEditor"); break;

      //no default to get compiler warnings!
   }

}


////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setDefaultShortcut           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   //get and check the type
   bool works = false;
   CoaDefaultActions::actionDatabase myType = mapInt2Enum(type, &works);
   assert(works == true);

   //do the work
   switch(myType) {

      case actionDatabaseCreate                   :
      case actionDatabaseImportFromXml            :
      case actionDatabaseExportToXml              : break;

      case actionDatabaseOpenConnection           : action->setDefaultShortcut(tr("Ctrl+O")); break;
      case actionDatabaseCloseConnection          : action->setDefaultShortcut(tr("Ctrl+W")); break;

      case actionDatabaseGotoFirst                :
      case actionDatabaseGotoPrevius              :
      case actionDatabaseGotoNext                 :
      case actionDatabaseGotoLast                 :

      case actionDatabaseLookup                   :
      case actionDatabaseSqlBrowser               : break;
      case actionDatabaseSqlEditor                : break;

      //no default to get compiler warnings!
   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setShortcutContext           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setShortcutContext(Qt::ApplicationShortcut);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setIcon                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   //get and check the type
   bool works = false;
   CoaDefaultActions::actionDatabase myType = mapInt2Enum(type, &works);
   assert(works == true);

   //do the work
   switch(myType) {

      case actionDatabaseCreate                   :
      case actionDatabaseImportFromXml            :
      case actionDatabaseExportToXml              :

      case actionDatabaseOpenConnection           :
      case actionDatabaseCloseConnection          :

      case actionDatabaseGotoFirst                :
      case actionDatabaseGotoPrevius              :
      case actionDatabaseGotoNext                 :
      case actionDatabaseGotoLast                 : //action->setIcon(":/openaqua/icons/filenew.png");     break;

      case actionDatabaseLookup                   :
      case actionDatabaseSqlBrowser               : break;
      case actionDatabaseSqlEditor                : break;

      //no default to get compiler warnings!
   }

}



////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setToolTip                   (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);


   //get and check the type
   bool works = false;
   CoaDefaultActions::actionDatabase myType = mapInt2Enum(type, &works);
   assert(works == true);

   //do the work
   switch(myType) {

      case actionDatabaseCreate                   : action->setToolTip(tr("Create a new Database File"));  break;
      case actionDatabaseImportFromXml            : action->setToolTip(tr("Import Data from a XML File"));  break;
      case actionDatabaseExportToXml              : action->setToolTip(tr("Export Data to a XML File"));  break;

      case actionDatabaseOpenConnection           : action->setToolTip(tr("Open a Database Connection"));  break;
      case actionDatabaseCloseConnection          : action->setToolTip(tr("Close the current Database Connection"));  break;

      case actionDatabaseGotoFirst                : action->setToolTip(tr("Go to the First Record"));  break;
      case actionDatabaseGotoPrevius              : action->setToolTip(tr("Go to the Previus Record"));  break;
      case actionDatabaseGotoNext                 : action->setToolTip(tr("Go to the Next Record"));  break;
      case actionDatabaseGotoLast                 : action->setToolTip(tr("Go to the Last Record"));  break;

      case actionDatabaseLookup                   : action->setToolTip(tr("Search for Data..."));  break;
      case actionDatabaseSqlBrowser               : action->setToolTip(tr("Browse the used SQL Databases"));  break;
      case actionDatabaseSqlEditor                : action->setToolTip(tr("Edit SQL DataTables"));  break;

      //no default to get compiler warnings!
   }


}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setStatusTip                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setStatusTip(action->toolTip());
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setText                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);


   //get and check the type
   bool works = false;
   CoaDefaultActions::actionDatabase myType = mapInt2Enum(type, &works);
   assert(works == true);

   //do the work
   switch(myType) {

      case actionDatabaseCreate                   : action->setText(tr("C&reate Database..."));  break;
      case actionDatabaseImportFromXml            : action->setText(tr("&Import from XML..."));  break;
      case actionDatabaseExportToXml              : action->setText(tr("&Export to XML..."));  break;

      case actionDatabaseOpenConnection           : action->setText(tr("&Open Database"));  break;
      case actionDatabaseCloseConnection          : action->setText(tr("&Close Database"));  break;

      case actionDatabaseGotoFirst                : action->setText(tr("Goto &First"));  break;
      case actionDatabaseGotoPrevius              : action->setText(tr("Goto &Previus"));  break;
      case actionDatabaseGotoNext                 : action->setText(tr("Goto &Next"));  break;
      case actionDatabaseGotoLast                 : action->setText(tr("Goto &Last"));  break;

      case actionDatabaseLookup                   : action->setText(tr("&Lookup..."));  break;
      case actionDatabaseSqlBrowser               : action->setText(tr("&Browse SQL Database..."));  break;
      case actionDatabaseSqlEditor                : action->setText(tr("&Edit SQL Data Tables..."));  break;

      //no default to get compiler warnings!
   }



}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setEnabledForDefaultToolbar  (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);


   //get and check the type
   bool works = false;
   CoaDefaultActions::actionDatabase myType = mapInt2Enum(type, &works);
   assert(works == true);

   //do the work
   switch(myType) {

      case actionDatabaseCreate                   : 
      case actionDatabaseImportFromXml            : 
      case actionDatabaseExportToXml              : 

      case actionDatabaseOpenConnection           : 
      case actionDatabaseCloseConnection          : 

      case actionDatabaseGotoFirst                : 
      case actionDatabaseGotoPrevius              : 
      case actionDatabaseGotoNext                 : 
      case actionDatabaseGotoLast                 : 

      case actionDatabaseLookup                   : 
      case actionDatabaseSqlBrowser               : 
      case actionDatabaseSqlEditor                : action->setEnabledForDefaultToolbar( false ); break;

      //no default to get compiler warnings!
   }

}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setEnabledForToolbar         (CoaAction*const  action, const int type)
{
   BEGIN;
   Q_UNUSED(type);
   Q_UNUSED(action);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setWhatsThis                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setWhatsThis(action->toolTip());

}




////////////////////////////////////////////////////////////
void CoaActionBuilderDatabase::setActionBlock               (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setActionBlock(tr("Database Handling"));
}


