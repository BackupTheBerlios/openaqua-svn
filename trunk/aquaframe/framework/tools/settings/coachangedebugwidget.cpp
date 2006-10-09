#include "coachangedebugwidget.h"
#include "coachangedebug_model.h"
#include <CoaDebug>

#include <CoaDebug>
#include <CoaDebugThread>
#include <cassert>
#include <CoaFormFactory>
#include <CoaApplication>
#include <CoaSingletonWatch>
#include <CoaWorkbench>
#include <CoaCheckBox>
#include <CoaPushButton>
#include <CoaTableView>
#include <CoaComboBox>



#include <QMessageBox>
#include <QHeaderView>
#include <QMutex>
#include <QAbstractItemModel>
#include <QAbstractItemDelegate>
#include <QTableWidget>




SelectDebugLevelDelegate::SelectDebugLevelDelegate(QObject *parent)
: CoaItemDelegate (parent)
{
//   BEGIN;
}

SelectDebugLevelDelegate::~SelectDebugLevelDelegate()
{
//   BEGIN;
}

QWidget *SelectDebugLevelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
   //BEGIN;
   if (! index.isValid()) return 0;
   if (index.column() != 1) return CoaItemDelegate::createEditor(parent, option, index);

   CoaComboBox *editor = new CoaComboBox(parent);
   assert(editor);

   editor->insertItem(0,   ("DEFAULT"), QVariant(CoaDebug::DEFAULT));
   editor->insertItem(1,   ("OFF"), QVariant(CoaDebug::OFF));
   editor->insertItem(2,   ("ERR"), QVariant(CoaDebug::ERR));
   editor->insertItem(3,   ("WRN"), QVariant(CoaDebug::WRN));
   editor->insertItem(4,   ("INF"), QVariant(CoaDebug::INF));
   editor->insertItem(5,   ("DBG"), QVariant(CoaDebug::DBG));
   editor->installEventFilter(const_cast<SelectDebugLevelDelegate*>(this));

   connect (editor, SIGNAL(activated (int)),       editor, SLOT (emitDataChanged()) );
   connect (editor, SIGNAL(dataChanged(QWidget*)), this,   SIGNAL(commitData ( QWidget *)) );

   return editor;
}


void SelectDebugLevelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   //BEGIN;

   if (index.column() != 1) {
      CoaItemDelegate::setEditorData(editor, index);
      return;
   }

   //some checks
   assert(editor);
   if (editor == 0)      return;
   if (!index.isValid()) return;

   CoaComboBox *e = static_cast<CoaComboBox*>(editor);
   if (e == 0) return;

   int value = index.model()->data(index, Qt::EditRole).toInt();
   QString foo(index.model()->data(index, Qt::EditRole).toString());

   int i = e->findData(QVariant(value));
   e->setCurrentIndex(i);
}




void SelectDebugLevelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  // BEGIN;
   if (index.column() != 1) {
      CoaItemDelegate::setModelData(editor, model, index);
      return;
   }

   assert(editor);
   assert(model);

   if (editor == 0) return;
   if (model  == 0) return;

   CoaComboBox *e = static_cast<CoaComboBox*>(editor);
   if (e == 0) return;
   model->setData(index, e->itemData(e->currentIndex()));
}




void SelectDebugLevelDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
   //BEGIN;
   if (index.column() != 1) {
      CoaItemDelegate::updateEditorGeometry(editor, option, index);
      return;
   }

   //some checks
   assert(editor);
   if (editor == 0)      return;

   editor->setGeometry(option.rect);
}





void CoaSettingsWidgetChangeDebug::loadModel()
{
   BEGIN;

   if (actionModel != 0) {
      actionModel->remMasterWindow(this);
      delete actionModel;
      actionModel = 0;
   }

   actionModel = new CoaDebugSettingsModel( this );
   assert(actionModel);
   if (actionModel == 0) return;
   actionModel->addMasterWindow(this);

   connect (actionModel, SIGNAL(allDataChanged() ),
            this,        SLOT  (slotEnableAllPersistentEditors ( ))
           );

   CoaTableView *tableView    = qFindChild<CoaTableView*>(this, "tableView");
   tableView->setItemDelegate (new SelectDebugLevelDelegate(this));
   tableView->setModel(actionModel);

   tableView->verticalHeader()->hide();

}



CoaSettingsWidgetChangeDebug::CoaSettingsWidgetChangeDebug(QWidget * const parent , Qt::WFlags f )
: CoaSettingsWidget (parent, f)
,actionModel(0)
{
   BEGIN;

   //Create the central form
   Q_INIT_RESOURCE(tools);
   CoaFormFactory factory(this);
   factory.formBuild(":/tools/settings/coachangedebug.ui");
   setIcon(":/tools/settings/icons/debug.png");

   initMainButtons();
   initDefaultModeButtons();

   loadModel();
   assert(actionModel);

   initTableView();
   setShortName( tr("Debug") );
   setGroupName( shortName() );

}




CoaSettingsWidgetChangeDebug::~CoaSettingsWidgetChangeDebug()
{
   BEGIN;

   if (actionModel != 0) {
      actionModel->remMasterWindow(this);
      delete actionModel;
      actionModel = 0;
   }
}



void CoaSettingsWidgetChangeDebug::initDefaultModeButtons()
{
   BEGIN;

   //Get the Button Pointer
   CoaRadioButton *radioOff = qFindChild<CoaRadioButton*>(this, "radioOff");
   CoaRadioButton *radioErr = qFindChild<CoaRadioButton*>(this, "radioErr");
   CoaRadioButton *radioWrn = qFindChild<CoaRadioButton*>(this, "radioWrn");
   CoaRadioButton *radioInf = qFindChild<CoaRadioButton*>(this, "radioInf");
   CoaRadioButton *radioDbg = qFindChild<CoaRadioButton*>(this, "radioDbg");

   
   assert(radioOff);
   assert(radioErr);
   assert(radioWrn);
   assert(radioInf);
   assert(radioDbg);

   
   //Enable / Disable the Buttons
   switch(CoaDebugThread::getInstance()->getDebugLevel()){
      case CoaDebug::DEFAULT: assert(1==2); //should never happen
      case CoaDebug::OFF:     radioOff->setChecked(true); break;
      case CoaDebug::ERR:     radioErr->setChecked(true); break;
      case CoaDebug::WRN:     radioWrn->setChecked(true); break;
      case CoaDebug::INF:     radioInf->setChecked(true); break;
      case CoaDebug::DBG:     radioDbg->setChecked(true); break;
   }

   //Connect to slots
   connect (radioOff,    SIGNAL(toggled(bool)),    this, SLOT(slotSetLevelOff()) );
   connect (radioErr,    SIGNAL(toggled(bool)),    this, SLOT(slotSetLevelErr()) );
   connect (radioWrn,    SIGNAL(toggled(bool)),    this, SLOT(slotSetLevelWrn()) );
   connect (radioInf,    SIGNAL(toggled(bool)),    this, SLOT(slotSetLevelInf()) );
   connect (radioDbg,    SIGNAL(toggled(bool)),    this, SLOT(slotSetLevelDbg()) );

}

void CoaSettingsWidgetChangeDebug::initMainButtons()
{
   BEGIN;

   //Get the Button Pointer
   CoaCheckBox *checkEnabled= qFindChild<CoaCheckBox*>(this, "checkEnabled");
   CoaCheckBox *checkTime   = qFindChild<CoaCheckBox*>(this, "checkTime");

   assert(checkEnabled);
   assert(checkTime);
   
   checkEnabled->setChecked(CoaDebugThread::getInstance()->isDebuggingEnabled());
   checkTime->setChecked(CoaDebugThread::getInstance()->showTimeInOutput());

   //Connect to slots
   connect (checkEnabled, SIGNAL(toggled(bool)), this, SLOT(slotSetDebugEnabled(bool))  );
   connect (checkTime,    SIGNAL(toggled(bool)), this, SLOT(slotShowTimeInOutput(bool)) );
}



void CoaSettingsWidgetChangeDebug::initTableView()
{
   BEGIN;

   CoaTableView *tableView    = qFindChild<CoaTableView*>(this, "tableView");
   assert(tableView);
   
   QItemSelectionModel *selectionModel = tableView->selectionModel();
   tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
   tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

   connect (selectionModel, SIGNAL(selectionChanged (   const QItemSelection &, const QItemSelection & )),
            this,           SLOT(slotSelectionChanged ( const QItemSelection &, const QItemSelection & ))
           );

   slotEnableAllPersistentEditors();

}


void CoaSettingsWidgetChangeDebug::slotEnableAllPersistentEditors()
{
   BEGIN;

   //create a persistent editor
   CoaTableView *tableView    = qFindChild<CoaTableView*>(this, "tableView");
   assert(tableView);

   for (int i = 0; i < actionModel->rowCount(); ++i) {
      tableView->openPersistentEditor(actionModel->index(i, 1, QModelIndex()));
   }


}


void CoaSettingsWidgetChangeDebug::slotSetDebugEnabled(bool set)
{
   BEGIN;
   CoaDebug::getInstance()->enableDebugging(set);
}

void CoaSettingsWidgetChangeDebug::slotShowTimeInOutput(bool set)
{
   BEGIN;
   CoaDebug::getInstance()->showTimeInOutput(set);
}


void CoaSettingsWidgetChangeDebug::slotSetLevelOff()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::OFF);
}


void CoaSettingsWidgetChangeDebug::slotSetLevelErr()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::ERR);
}


void CoaSettingsWidgetChangeDebug::slotSetLevelWrn()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::WRN);
}


void CoaSettingsWidgetChangeDebug::slotSetLevelInf()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::INF);
}


void CoaSettingsWidgetChangeDebug::slotSetLevelDbg()
{
   BEGIN;
   CoaDebug::getInstance()->setDebugLevel(CoaDebug::DBG);
}





bool CoaSettingsWidgetChangeDebug::applyDefaults()
{
   BEGIN;

   assert(actionModel);

   CoaTableView *tableView    = qFindChild<CoaTableView*>(this, "tableView");
   assert(tableView);
   
   QItemSelectionModel * selection = tableView->selectionModel ();
   QModelIndexList list = selection->selectedIndexes();
   actionModel->setDefault(list);

   RETURN(true);
}


void CoaSettingsWidgetChangeDebug::slotSelectionChanged ( const QItemSelection & selected, const QItemSelection & deselected )
{
   BEGIN;
   Q_UNUSED(deselected);
   emit signalCanApplyDefaults(!selected.isEmpty());
}


bool CoaSettingsWidgetChangeDebug::applyChanges()
{
   BEGIN
   RETURN(true);
}

bool CoaSettingsWidgetChangeDebug::canApplyDefaults() const
{
   BEGIN;
   RETURN(true);
}

