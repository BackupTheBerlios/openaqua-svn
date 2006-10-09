#include "contactwindow.h"

#include <CoaDebug>
#include <CoaWorkbench>
#include <CoaFormFactory>
#include <CoaApplication>
#include <CoaString>


#include <QCloseEvent>
//#include <qsinterpreter.h>


ContactWindow::ContactWindow(const CoaString& objectName,  CoaWorkbench *const parent, Qt::WFlags flags)
: CoaApplicationWindow(objectName, parent, flags)
{
   BEGIN;
//   m_interpreter = new QSInterpreter(this);
//   m_interpreter->setErrorMode(QSInterpreter::Nothing);
}




ContactWindow::~ContactWindow()
{
   BEGIN;
   writeSettings();
//   m_interpreter = 0;
}


void ContactWindow::slotFileClose()
{
   BEGIN;
}



void ContactWindow::slotFileOpen()
{
   BEGIN;
}



void ContactWindow::initialize()
{
   BEGIN;

   //Build the Window itself
   Q_INIT_RESOURCE(contact);
   CoaFormFactory factory(this);
   factory.formBuild(":/contact/contact.ui");

   readSettings();

}


bool ContactWindow::slotFileSave()
{
   BEGIN;
   RETURN(false);

}




/**
@brief create a new window and a new memory based database

*/
bool ContactWindow::slotFileNew()
{
   BEGIN;
   RETURN(true);
}



void ContactWindow::closeDatabaseModel()
{
   BEGIN;

}



void ContactWindow::initDatabaseModel()
{
   BEGIN;

}




void ContactWindow::saveChanges()
{
   BEGIN;
}


void ContactWindow::saveChangesAs()
{
   BEGIN;
}

#if 0
void ContactWindow::closeEvent(QCloseEvent *ev)
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
            getWorkbench()->remWindow(this);
            ev->accept();
            break;
         }
         case QMessageBox::No: {
            setWindowModified(false);// Not really necessary, but stops problems if we get close again.
            getWorkbench()->remWindow(this);
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

#endif
