#include "coalineedit.h"
#include <CoaDebug>
#include <CoaApplication>
#include <CoaMenu>
#include <CoaActionFactory>


#include <QContextMenuEvent>



CoaLineEdit::CoaLineEdit( QWidget *parent )
      : QLineEdit( parent )
      , IoaDataSetWidget()
{
   BEGIN;
}

CoaLineEdit::~CoaLineEdit()
{
   BEGIN;
}


void CoaLineEdit::contextMenuEvent( QContextMenuEvent *e )
{
   BEGIN;

   QMenu *menu = createStandardContextMenu();
   menu->exec( e->globalPos() );
   delete menu;
}


QMenu *CoaLineEdit::createStandardContextMenu()
{
   BEGIN;
   CoaMenu *menu = new CoaMenu( this );
   menu->addAction( "foo" );
   menu->addAction( "bar" );
   return menu;
}

void CoaLineEdit::updateValue(const QVariant& v)
{
   BEGIN;
   setText(v.toString());
}

#if 0
QMenu *CoaLineEdit::createStandardContextMenu()
{
   BEGIN;

   CoaMenu *menu = new CoaMenu( this );

   QAction *a;

   if ( !isReadOnly() )
   {
      //Add Undo
      a = new CoaActionEditUndo( this );
      a->setEnabled( isUndoAvailable() );
      menu->addAction( a );

      //Add Redo
      a = new CoaActionEditRedo( this );
      a->setEnabled( isRedoAvailable() );
      menu->addAction( a );

      //Add Seperator
      menu->addSeparator();

      //Add Cut
      a = new CoaActionEditCut( this );
      a->setEnabled( hasSelectedText() );
      menu->addAction( a );
   }

   //Add Copy
   a = new CoaActionEditCopy( this );
   a->setEnabled( hasSelectedText() );
   menu->addAction( a );

   //Add Paste
   if ( !isReadOnly() )
   {
      a = new CoaActionEditPaste( this );
      a->setEnabled( !CoaApplication::clipboard() ->text().isEmpty() );
      menu->addAction( a );
   }


   //Add Seperator
   menu->addSeparator();

   //Add Select all
   a = new CoaActionEditSelectAll( this );
   a->setEnabled( !text().isEmpty() );
   menu->addAction( a );

   return menu;

}
#endif
