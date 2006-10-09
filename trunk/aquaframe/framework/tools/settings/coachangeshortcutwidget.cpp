#include "coachangeshortcutwidget.h"
#include "coachangeshortcut_model.h"
#include <CoaDebug>
#include <cassert>
#include <CoaFormFactory>
#include <CoaAction>
#include <CoaApplication>
#include <CoaSingletonWatch>
#include <CoaWorkbench>
#include <CoaWorkspace>
#include <CoaPushButton>
#include <CoaTreeView>


#include <QMessageBox>
#include <QHeaderView>
#include <QMutex>
#include <QKeyEvent>
#include <QObject>


CoaSettingsWidgetChangeShortcut::KeyRecordEdit::KeyRecordEdit(QWidget *parent)
: CoaLineEdit(parent)
{
}




void CoaSettingsWidgetChangeShortcut::KeyRecordEdit::keyPressEvent ( QKeyEvent * e )
{
   BEGIN;
   assert(e);

   int key   = e->key();
   int modifier  = e->modifiers();

   e->ignore();

   if ((key == 0) || (key == Qt::Key_unknown)) {
      return;
   } else {
      QKeySequence seq(key + modifier);
      QString strSeq(seq);
      //int i = strSeq.lastIndexOf('+');
      //if (i == -1){
         //@todo removing unprintable characters or finding a better way
         //      to match from key to string

      //}
      setText(seq);
   }
}


CoaSettingsWidgetChangeShortcut::KeyRecordDelegate::KeyRecordDelegate(QObject *parent)
: CoaItemDelegate (parent)
{
}



QWidget *CoaSettingsWidgetChangeShortcut::KeyRecordDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &/* index */) const
{
   BEGIN;
   KeyRecordEdit *editor = new KeyRecordEdit(parent);
   editor->installEventFilter(const_cast<KeyRecordDelegate*>(this));
   return editor;
}


void CoaSettingsWidgetChangeShortcut::KeyRecordDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   BEGIN;
   //some checks
   assert(editor);
   if (editor == 0)      return;
   if (!index.isValid()) return;

   QString value = index.model()->data(index, Qt::DisplayRole).toString();
   KeyRecordEdit *e = static_cast<KeyRecordEdit*>(editor);
   assert(e);
   if (e != 0){
      e->setText(value);
   }
}


void CoaSettingsWidgetChangeShortcut::KeyRecordDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
   BEGIN;
   assert(editor);
   assert(model);
   if (editor == 0) return;
   if (model  == 0) return;

   KeyRecordEdit *e = static_cast<KeyRecordEdit*>(editor);
   model->setData(index, e->text());
}



void CoaSettingsWidgetChangeShortcut::KeyRecordDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
   BEGIN;
   Q_UNUSED(index);
   assert(editor);
   if (editor == 0)      return;
   editor->setGeometry(option.rect);
}




void CoaSettingsWidgetChangeShortcut::loadActions()
{
   BEGIN;

   delete m_actionModel;
   m_actionModel = new CoaActionViewModel( this );

   m_actionView->setModel(m_actionModel);
   connect (m_actionModel,   SIGNAL(haveUnsavedShortcuts(const bool)), this, SLOT(setDirty(const bool)));


}




CoaSettingsWidgetChangeShortcut::CoaSettingsWidgetChangeShortcut( QWidget * const parent , Qt::WFlags f  )
: CoaSettingsWidget(parent, f)
, m_actionView(0)
, m_actionModel(0)
{
   BEGIN;

   QHBoxLayout *layout = new QHBoxLayout;
   setLayout(layout);

   m_actionView = new CoaTreeView(this);
   layout->addWidget(m_actionView);

   setIcon(":/tools/settings/icons/shortcuts.png");
   setShortName( tr("Shortcuts") );

   loadActions();
   assert(m_actionModel);

   QItemSelectionModel *selectionModel = m_actionView->selectionModel();
   connect (selectionModel, SIGNAL(selectionChanged ( const QItemSelection &, const QItemSelection & )),
            this,             SLOT(slotSelectionChanged ( const QItemSelection & , const QItemSelection & ))
           );


   m_actionView->setSelectionMode(QAbstractItemView::ExtendedSelection);
   m_actionView->setItemDelegate (new KeyRecordDelegate(this));

}


CoaSettingsWidgetChangeShortcut::~CoaSettingsWidgetChangeShortcut()
{
   BEGIN;
}


bool CoaSettingsWidgetChangeShortcut::applyChanges()
{
   BEGIN;
   m_actionModel->saveChangedShortcuts();
   RETURN(true);
}


bool CoaSettingsWidgetChangeShortcut::applyDefaults()
{
   BEGIN;
   assert(m_actionModel);

   QItemSelectionModel * selection = m_actionView->selectionModel ();
   QModelIndexList list = selection->selectedIndexes();
   m_actionModel->loadDefaultShortcuts(list);

   RETURN(true);
}



void CoaSettingsWidgetChangeShortcut::slotSelectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
   BEGIN;
   Q_UNUSED(deselected);
   emit signalCanApplyDefaults(!selected.isEmpty());
}


bool CoaSettingsWidgetChangeShortcut::canApplyDefaults() const
{
   BEGIN;
   RETURN(true);
}
