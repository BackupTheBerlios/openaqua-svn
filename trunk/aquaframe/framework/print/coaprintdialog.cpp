#include "coaprintdialog.h"
#include <CoaPrinter>
#include <CoaDebug>



CoaPrintDialog::CoaPrintDialog ( QPrinter * printer, QWidget * parent)
:QPrintDialog(printer, parent)
{
   BEGIN;
}



CoaPrintDialog::~CoaPrintDialog ()
{
   BEGIN;
}



