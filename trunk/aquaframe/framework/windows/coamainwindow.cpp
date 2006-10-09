#include "coamainwindow.h"
#include <CoaDebug>
#include <CoaSettings>
#include <CoaAction>
#include <CoaApplication>
#include <CoaWorkbench>

#include <cassert>

#include <QSize>
#include <QMessageBox>
#include <QCloseEvent>

CoaMainWindow::CoaMainWindow ( const QString& objectName,  QWidget * parent, Qt::WFlags flags)
: QMainWindow(parent, flags)
{
   BEGIN;
   setObjectName(objectName);
   setWindowTitle(COAAPP->applicationName ());


   //all toolwindows will be deleted after close!
   setAttribute(Qt::WA_DeleteOnClose);

}







CoaMainWindow::~CoaMainWindow()
{
   BEGIN;
   writeSettings();
}


void CoaMainWindow::readSettings()
{
   BEGIN;
   CoaSettings settings;
   settings.beginGroup(objectName());

   resize(settings.value("size", sizeHint()).toSize());
   move(settings.value("pos", pos()).toPoint());

   settings.endGroup();
}


void CoaMainWindow::writeSettings()
{
   BEGIN;
   CoaSettings settings;
   settings.beginGroup(objectName());

   settings.setValue("size", size());
   settings.setValue("pos",  pos());

   settings.endGroup();
}



void CoaMainWindow::saveChanges()
{
   BEGIN;
   ERR("Called a empty saveChanges method");
}

void CoaMainWindow::closeEvent(QCloseEvent *ev)
{
   BEGIN;

   if (isWindowModified() == true) {
      INF("window is modified");
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
            ev->accept();
            break;
         }
         case QMessageBox::No: {
            setWindowModified(false);// Not really necessary, but stops problems if we get close again.
            ev->accept();
            break;
         }
         default: {
            ev->ignore();
            break;
         }
      }
   }  else {
      INF("window is clean");
   }


}


QSize CoaMainWindow::sizeHint () const
{
   BEGIN
   QSize hint = QMainWindow::sizeHint();
   if (!hint.isValid()) {
      ERR("sizeHint is not valid");
      hint = m_sizeHint;
   }
   RETURN(hint);
}

void CoaMainWindow::setSizeHint(const QSize& sizeHint)
{
   BEGIN;
   m_sizeHint = sizeHint;
}
