#include "coadialog.h"
#include <CoaDebug>
#include <CoaSettings>


#include <QSize>




CoaDialog::CoaDialog ( const QString& objectName, QWidget * parent, Qt::WFlags flags)
:QDialog(parent, flags)
{
   BEGIN;
   setObjectName(objectName);
}





CoaDialog::~CoaDialog()
{
   BEGIN;
}




void CoaDialog::readSettings()
{
   BEGIN;
   CoaSettings settings;
   settings.beginGroup(objectName());

   resize(settings.value("size", sizeHint()).toSize());

   settings.endGroup();
}


void CoaDialog::writeSettings()
{
   BEGIN;
   CoaSettings settings;
   settings.beginGroup(objectName());

   settings.setValue("size", size());

   settings.endGroup();
}
