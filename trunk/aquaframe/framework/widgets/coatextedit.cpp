#include "coatextedit.h"
#include <CoaDebug>
#include <CoaApplication>
#include <CoaMenu>


#include <QContextMenuEvent>
//#include <QTextDocument>
//#include <QTextCursor>
//#include <QClipboard>


CoaTextEdit::CoaTextEdit(QWidget *parent)
:QTextEdit(parent)
{
   BEGIN;
}


void CoaTextEdit::contextMenuEvent(QContextMenuEvent *e)
{
   BEGIN;

   QMenu *menu = createStandardContextMenu();
   menu->exec(e->globalPos());
   delete menu;
}

QMenu *CoaTextEdit::createStandardContextMenu()
{
   BEGIN;

   CoaMenu *menu = new CoaMenu(this);
   //menu->addActionGroup(GETACTIONGROUP(CoaDefaultActionGroupFactory::actiongroupEdit));
   return menu;

}


#if 0
QMenu *CoaTextEdit::createStandardContextMenu()
{
   BEGIN;

   CoaMenu *menu = new CoaMenu(this);

   QAction *a;

   if (!isReadOnly()) {
      //Add Undo
      a = new CoaActionEditUndo(this);
      a->setEnabled(document()->isUndoAvailable());
      menu->addAction(a);

      //Add Redo
      a = new CoaActionEditRedo(this);
      a->setEnabled(document()->isRedoAvailable());
      menu->addAction(a);

      //Add Seperator
      menu->addSeparator();

      //Add Cut
      a = new CoaActionEditCut(this);
      a->setEnabled(textCursor().hasSelection());
      menu->addAction(a);
   }

   //Add Copy
   a = new CoaActionEditCopy(this);
   a->setEnabled(textCursor().hasSelection());
   menu->addAction(a);

   //Add Paste
   if (!isReadOnly()) {
      a = new CoaActionEditPaste(this);
      a->setEnabled(canInsertFromMimeData(CoaApplication::clipboard()->mimeData()));
      menu->addAction(a);
   }


   //Add Seperator
   menu->addSeparator();

   //Add Select all
   a = new CoaActionEditSelectAll(this);
   a->setEnabled(!document()->isEmpty());
   menu->addAction(a);

   return menu;

}
#endif

