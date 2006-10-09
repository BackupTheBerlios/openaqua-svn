#include "mainwindow.h"
#include "actionmodel.h"

#include <CoaDebug>
#include <CoaWorkbench>
#include <CoaFormFactory>
#include <CoaTableView>
#include <CoaApplication>
#include <CoaString>
#include <CoaTreeView>
#include <CoaTableView>
#include <CoaToolButton>
#include <CoaFileDialog>
#include <CoaWorkspace>
#include <CoaFile>

#include <QMessageBox>
#include <QCloseEvent>
#include <QHeaderView>
#include <CoaLineEditView>

//öäü

MainWindow::MainWindow(const CoaString& objectName,  CoaWorkspace *const parent, Qt::WFlags flags)
: CoaApplicationWindow(objectName, parent, flags)
, m_btnRemAction(0)
, m_btnAddAction(0)
, m_actionModel(0)
, m_listActions(0)
, m_textWhatsThis(0)
, m_lineShortCut(0)
, m_lineToolTip(0)
, m_lineText(0)
{
   BEGIN;
}





MainWindow::~MainWindow()
{
   BEGIN;
   writeSettings();
}

void MainWindow::slotFileClose()
{
   BEGIN;
}



bool MainWindow::slotFileOpen(const CoaString& filename)
{
   BEGIN;
   bool result = false;

   //some checks
   assert(m_actionModel);
   if (m_actionModel == 0){
      ERR ("No ActionModel defined");
      RETURN (result);
   }
   if (filename.length() == 0){
      ERR ("filename is empty");
      RETURN (result);
   }

   //INFO
   INF(CoaString ("Open file %1").arg(filename));

   CoaFile file(filename);
   result = m_actionModel->loadXmlData(&file);
   if (result != true){
      ERR(m_actionModel->lastError());
   }

   RETURN(result);
}



void MainWindow::initialize()
{
   BEGIN;

   //Build the Window itself
   Q_INIT_RESOURCE(actioneditor);
   CoaFormFactory factory(this);
   factory.formBuild(":/form/mainwindow.ui");
   readSettings();

   m_actionModel = new ActionModel(this);

   m_listActions = qFindChild<CoaTreeView*>(this, "listActions");
   CoaTableView *table  = qFindChild<CoaTableView*>(this, "tableView");
   m_btnRemAction = qFindChild<CoaToolButton*>(this, "btnRemAction");
   m_btnAddAction = qFindChild<CoaToolButton*>(this, "btnAddAction");

   assert(m_listActions);
   assert(table);
   assert(m_btnRemAction);
   assert(m_btnAddAction);

   m_textWhatsThis = qFindChild<CoaTextEdit*>(this, "textWhatsThis");
   m_lineShortCut = qFindChild< CoaLineEditView*>(this, "lineShortCut");
   m_lineToolTip = qFindChild< CoaLineEditView*>(this, "lineToolTip");
   m_lineText = qFindChild<CoaLineEditView*>(this, "lineText");

   //check the variables
   assert(m_textWhatsThis);
   assert(m_lineText);
   assert(m_lineToolTip);
   assert(m_lineShortCut);

   //set the data model
   m_listActions->setModel(m_actionModel);
   table->setModel(m_actionModel);
   m_lineText->setModel(m_actionModel);
   m_lineToolTip->setModel(m_actionModel);
   m_lineShortCut->setModel(m_actionModel);

   //set certain viewers to a fix column
   m_lineText->setFixColumn(3);
   m_lineToolTip->setFixColumn(4);
   m_lineShortCut->setFixColumn(5);


   //set the selectionModel
   QItemSelectionModel *selectionModel = new QItemSelectionModel(m_actionModel);
   m_listActions->setSelectionModel(selectionModel);
   m_lineText->setSelectionModel(selectionModel);
   m_lineToolTip->setSelectionModel(selectionModel);
   m_lineShortCut->setSelectionModel(selectionModel);

   //connect()
   //table->setSelectionModel(selectionModel);

   //connection objects to their slots
   connect(m_btnRemAction, SIGNAL(clicked ( bool )), this, SLOT(remAction()));
   connect(m_btnAddAction, SIGNAL(clicked ( bool )), this, SLOT(addAction()));

}



bool MainWindow::slotFileSave()
{
   BEGIN;
   CoaString fileName = CoaFileDialog::getSaveFileName(
                    this,
                    tr("Choose a filename to save under"),
                    "",
                    tr("Oa Travel Files (*.oat)"));

      if (fileName.isEmpty()) {
         INF("No file choosen");
         return false;
      }

      CoaFile file(fileName);
      bool result = m_actionModel->saveXmlData(&file);
      if (result != true){
         ERR(m_actionModel->lastError());
      }

      setWindowModified(false);
      return true;

}


bool MainWindow::slotFileSaveAs()
{
   BEGIN;
   CoaString fileName = CoaFileDialog::getSaveFileName(
                    this,
                    tr("Choose a filename to save under"),
                    "",
                    tr("ActionEditor Files (*.xml)"));

   if (fileName.isEmpty()) {
      INF("No file choosen");
      return false;
   }

   CoaFile file(fileName);
   bool result = m_actionModel->saveXmlData(&file);
   if (result != true){
      ERR(m_actionModel->lastError());
   }

   setWindowModified(false);
   return true;
}


/**
*/
bool MainWindow::slotFileNew()
{
   BEGIN;
   setWindowTitle("<unknown>[*] - oatravel");
   //setWindowModified(true);
   RETURN(true);
}








void MainWindow::saveChanges()
{
   BEGIN;
}


void MainWindow::saveChangesAs()
{
   BEGIN;
}


void MainWindow::closeEvent(QCloseEvent *ev)
{
   BEGIN;

   if (isWindowModified() == true) {
      raise();

      QMessageBox box(tr("Save Changes?"),
                tr("Do you want to save the changes you made before closing?"),
                QMessageBox::Question,
                QMessageBox::Yes    | QMessageBox::Default,
                QMessageBox::No,
                QMessageBox::Cancel | QMessageBox::Escape,
                this, Qt::Sheet);
       box.setButtonText(QMessageBox::Yes,tr("Save"));
       box.setButtonText(QMessageBox::No, tr("Don't Save"));

       switch (box.exec()) {
         case QMessageBox::Yes: {
            saveChanges();
            setWindowModified(false);// Not really necessary, but stops problems if we get close again.
            //getWorkbench()->remWindow(this);
            ev->accept();
            break;
         }
         case QMessageBox::No: {
            setWindowModified(false);// Not really necessary, but stops problems if we get close again.
            //getWorkbench()->remWindow(this);
            ev->accept();
            break;
         }
         default: {
            ev->ignore();
            break;
         }
      }
   }
}



bool MainWindow::addAction()
{
   BEGIN;
   //const bool result = m_actionModel->insertAction( m_actionModel->rowCount( QModelIndex() ), 1, QModelIndex() );
   const bool result = false;
   RETURN(result);
}


bool MainWindow::remAction()
{
   BEGIN;
   //const bool result = m_actionModel->removeAction( m_listActions->currentIndex().row(), 1, QModelIndex() );
   const bool result = false;
   RETURN(result);
}

bool MainWindow::addFolder()
{
   BEGIN;
   const bool result = false;
   RETURN(result);
}

bool MainWindow::remFolder()
{
   BEGIN;
   const bool result = false;
   RETURN(result);
}



