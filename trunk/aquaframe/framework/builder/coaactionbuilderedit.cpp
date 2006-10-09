#include "coaactionbuilderedit.h"
#include <CoaDebug>
#include <CoaAction>
#include <cassert>

#include <CoaDefaultActions>
using namespace CoaDefaultActions;

#include <QMutex>

COAMAKRO_DEFINE_SINGLETONMETHODS(CoaActionBuilderEdit)


////////////////////////////////////////////////////////////
CoaActionBuilderEdit::CoaActionBuilderEdit()
:CoaActionBuilder()
{
   BEGIN;
   QObject::setObjectName("CoaActionBuilderEdit");
}


////////////////////////////////////////////////////////////
CoaActionBuilderEdit::~CoaActionBuilderEdit()
{
   BEGIN;
   INSTANCE=0;
}



////////////////////////////////////////////////////////////
bool CoaActionBuilderEdit::mapActionString2ActionId(const QString& type, int *const actionId)
{
   BEGIN;

   if (type == "actionEditSelectAll") {
      *actionId = actionEditSelectAll;
      RETURN(true);
   }
   if (type == "actionEditCut") {
      *actionId = actionEditCut;
      RETURN(true);
   }
   if (type == "actionEditCopy") {
      *actionId = actionEditCopy;
      RETURN(true);
   }
   if (type == "actionEditPaste") {
      *actionId = actionEditPaste;
      RETURN(true);
   }
   if (type == "actionEditUndo") {
      *actionId = actionEditUndo;
      RETURN(true);
   }
   if (type == "actionEditRedo") {
      *actionId = actionEditRedo;
      RETURN(true);
   }

   RETURN(false);
}






////////////////////////////////////////////////////////////
bool CoaActionBuilderEdit::checkType                    (const int type)
{
   BEGIN;
   switch(type) {
      case actionEditSelectAll:
      case actionEditCut:
      case actionEditCopy:
      case actionEditPaste:
      case actionEditUndo:
      case actionEditRedo: RETURN(true);
      //no default to get compiler warnings!
   }

   RETURN(false);
}







////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setObjectName                (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionEditSelectAll:            action->setObjectName("actionEditSelectAll"); break;
      case actionEditCut:                  action->setObjectName("actionEditCut"); break;
      case actionEditCopy:                 action->setObjectName("actionEditCopy"); break;
      case actionEditPaste:                action->setObjectName("actionEditPaste"); break;
      case actionEditUndo:                 action->setObjectName("actionEditUndo"); break;
      case actionEditRedo:                 action->setObjectName("actionEditRedo"); break;
      //no default to get compiler warnings!
   }

}


////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setDefaultShortcut           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionEditSelectAll:            action->setDefaultShortcut(tr("Ctrl+A")); break;
      case actionEditCut:                  action->setDefaultShortcut(tr("Ctrl+X")); break;
      case actionEditCopy:                 action->setDefaultShortcut(tr("Ctrl+C")); break;
      case actionEditPaste:                action->setDefaultShortcut(tr("Ctrl+P")); break;
      case actionEditUndo:                 action->setDefaultShortcut(tr("Ctrl+Z")); break;
      case actionEditRedo:                 action->setDefaultShortcut(tr("Ctrl+Shift+Z")); break;
      //no default to get compiler warnings!
   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setShortcutContext           (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   Q_UNUSED(type);
   action->setShortcutContext(Qt::ApplicationShortcut);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setIcon                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   switch(type) {
      case actionEditSelectAll:            break;
      case actionEditCut:                  action->setIcon(":/openaqua/icons/editcut.png");           break;
      case actionEditCopy:                 action->setIcon(":/openaqua/icons/editcopy.png");           break;
      case actionEditPaste:                action->setIcon(":/openaqua/icons/editpaste.png");           break;
      case actionEditUndo:                 action->setIcon(":/openaqua/icons/editundo.png");           break;
      case actionEditRedo:                 action->setIcon(":/openaqua/icons/editredo.png");           break;
      //no default to get compiler warnings!
   }
}



////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setToolTip                   (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionEditSelectAll:            action->setToolTip(tr("Select All"));  break;
      case actionEditCut:                  action->setToolTip(tr("Cut the selection to the clipboard"));  break;
      case actionEditCopy:                 action->setToolTip(tr("Copy the selection to the clipboard"));  break;
      case actionEditPaste:                action->setToolTip(tr("Paste from Clipboard"));  break;
      case actionEditUndo:                 action->setToolTip(tr("Undo the last operation"));  break;
      case actionEditRedo:                 action->setToolTip(tr("Redo the last operation"));  break;
      //no default to get compiler warnings!
   }


}




////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setStatusTip                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setStatusTip(action->toolTip());
}




////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setText                      (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);

   switch(type) {
      case actionEditSelectAll:            action->setText(tr("Select &All")); break;
      case actionEditCut:                  action->setText(tr("Cu&t")); break;
      case actionEditCopy:                 action->setText(tr("&Copy")); break;
      case actionEditPaste:                action->setText(tr("&Paste")); break;
      case actionEditUndo:                 action->setText(tr("&Undo")); break;
      case actionEditRedo:                 action->setText(tr("&Redo")); break;
      //no default to get compiler warnings!
   }

}




////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setEnabledForDefaultToolbar  (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   switch(type) {
      case actionEditSelectAll:            action->setEnabledForDefaultToolbar( true ); break;
      case actionEditCut:                  action->setEnabledForDefaultToolbar( true ); break;
      case actionEditCopy:                 action->setEnabledForDefaultToolbar( true ); break;
      case actionEditPaste:                action->setEnabledForDefaultToolbar( true ); break;
      case actionEditUndo:                 action->setEnabledForDefaultToolbar( false ); break;
      case actionEditRedo:                 action->setEnabledForDefaultToolbar( false ); break;
      //no default to get compiler warnings!

   }
}




////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setEnabledForToolbar         (CoaAction*const  action, const int type)
{
   BEGIN;
   Q_UNUSED(type);
   Q_UNUSED(action);
}




////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setWhatsThis                 (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setWhatsThis(action->toolTip());

}





////////////////////////////////////////////////////////////
void CoaActionBuilderEdit::setActionBlock               (CoaAction*const  action, const int type)
{
   BEGIN;
   assert(action);
   Q_UNUSED(type);
   action->setActionBlock(tr("Editing"));
}


