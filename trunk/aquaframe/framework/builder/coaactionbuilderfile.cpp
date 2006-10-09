#include "coaactionbuilderfile.h"
#include <CoaDebug>
#include <CoaAction>

#include <CoaDefaultActions>
using namespace CoaDefaultActions;

#include <QMutex>
#include <cassert>

COAMAKRO_DEFINE_SINGLETONMETHODS(CoaActionBuilderFile)


////////////////////////////////////////////////////////////
CoaActionBuilderFile::CoaActionBuilderFile()
:CoaActionBuilder()
{
   BEGIN;
   QObject::setObjectName("CoaActionBuilderFile");
}



////////////////////////////////////////////////////////////
CoaActionBuilderFile::~CoaActionBuilderFile()
{
   BEGIN;
   INSTANCE=0;
}


////////////////////////////////////////////////////////////
bool CoaActionBuilderFile::mapActionString2ActionId(const QString& type, int *const actionId)
{
   BEGIN;

   if (type == "actionFileNew") {
      *actionId = actionFileNew;
      RETURN(true);
   }
   if (type == "actionFileOpen") {
      *actionId = actionFileOpen;
      RETURN(true);
   }
   if (type == "actionFileClose") {
      *actionId = actionFileClose;
      RETURN(true);
   }
   if (type == "actionFileCloseAll") {
      *actionId = actionFileCloseAll;
      RETURN(true);
   }
   if (type == "actionFileSave") {
      *actionId = actionFileSave;
      RETURN(true);
   }
   if (type == "actionFileSaveAs") {
      *actionId = actionFileSaveAs;
      RETURN(true);
   }
   if (type == "actionFileSaveAll") {
      *actionId = actionFileSaveAll;
      RETURN(true);
   }

   RETURN(false);
}





////////////////////////////////////////////////////////////
bool CoaActionBuilderFile::checkType                    (const int type)
{
   BEGIN;
   switch(type) {
   case actionFileNew:
   case actionFileOpen:
   case actionFileClose:
   case actionFileCloseAll:
   case actionFileSave:
   case actionFileSaveAs:
   case actionFileSaveAll: RETURN(true);
   //no default to get compiler warnings!
   }

   RETURN(false);
}





////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setObjectName                (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
   case actionFileNew:                     action->setObjectName("actionFileNew"); break;
   case actionFileOpen:                    action->setObjectName("actionFileOpen"); break;
   case actionFileClose:                   action->setObjectName("actionFileClose"); break;
   case actionFileCloseAll:                action->setObjectName("actionFileCloseAll"); break;
   case actionFileSave:                    action->setObjectName("actionFileSave"); break;
   case actionFileSaveAs:                  action->setObjectName("actionFileSaveAs"); break;
   case actionFileSaveAll:                 action->setObjectName("actionFileSaveAll"); break;
   //no default to get compiler warnings!
   }

}


////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setDefaultShortcut           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
   case actionFileNew:                     action->setDefaultShortcut(tr("Ctrl+N")); break;
   case actionFileOpen:                    action->setDefaultShortcut(tr("Ctrl+O")); break;
   case actionFileClose:                   action->setDefaultShortcut(tr("Ctrl+W")); break;
   case actionFileCloseAll:                break;
   case actionFileSave:                    action->setDefaultShortcut(tr("Ctrl+S")); break;
   case actionFileSaveAs:                  break;
   case actionFileSaveAll:                 break;
      //no default to get compiler warnings!
   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setShortcutContext           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setShortcutContext(Qt::ApplicationShortcut);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setIcon                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   switch(type) {
      case actionFileNew:        action->setIcon(":/openaqua/icons/filenew.png");     break;
      case actionFileOpen:       action->setIcon(":/openaqua/icons/fileopen.png");     break;
      case actionFileClose:      break;
      case actionFileCloseAll:   break;
      case actionFileSave:       action->setIcon(":/openaqua/icons/filesave.png");     break;
      case actionFileSaveAs:     break;
      case actionFileSaveAll:    break;
      //no default to get compiler warnings!
   }
}



////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setToolTip                   (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionFileNew:        action->setToolTip(tr("Create a New File"));  break;
      case actionFileOpen:       action->setToolTip(tr("Open File"));  break;
      case actionFileClose:      action->setToolTip(tr("Close File"));  break;
      case actionFileCloseAll:   action->setToolTip(tr("Close All Open Files"));  break;
      case actionFileSave:       action->setToolTip(tr("Save File"));  break;
      case actionFileSaveAs:     action->setToolTip(tr("Save File As"));  break;
      case actionFileSaveAll:    action->setToolTip(tr("Save All Files"));  break;
      //no default to get compiler warnings!
   }


}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setStatusTip                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setStatusTip(action->toolTip());
}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setText                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
   case actionFileNew:        action->setText(tr("&New..."));  break;
   case actionFileOpen:       action->setText(tr("&Open..."));  break;
   case actionFileClose:      action->setText(tr("&Close"));  break;
   case actionFileCloseAll:   action->setText(tr("Close all Open Files"));  break;
   case actionFileSave:       action->setText(tr("&Save"));  break;
   case actionFileSaveAs:     action->setText(tr("Save &As..."));  break;
   case actionFileSaveAll:    action->setText(tr("Save A&ll"));  break;
   //no default to get compiler warnings!
   }

}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setEnabledForDefaultToolbar  (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   switch(type) {
   case actionFileNew:        action->setEnabledForDefaultToolbar( true ); break;
   case actionFileOpen:       action->setEnabledForDefaultToolbar( true ); break;
   case actionFileClose:      action->setEnabledForDefaultToolbar( false ); break;
   case actionFileCloseAll:   action->setEnabledForDefaultToolbar( false ); break;
   case actionFileSave:       action->setEnabledForDefaultToolbar( false ); break;
   case actionFileSaveAs:     action->setEnabledForDefaultToolbar( false ); break;
   case actionFileSaveAll:    action->setEnabledForDefaultToolbar( false ); break;
   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setEnabledForToolbar         (CoaAction*const  action, const int type)
{
   BEGIN;
   Q_UNUSED(type);
   Q_UNUSED(action);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setWhatsThis                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setWhatsThis(action->toolTip());

}




////////////////////////////////////////////////////////////
void CoaActionBuilderFile::setActionBlock               (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setActionBlock(tr("File Handling"));
}


