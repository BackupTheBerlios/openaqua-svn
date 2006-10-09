#include "coadateedit.h"
#include <CoaDebug>


CoaDateEdit::CoaDateEdit ( QWidget * parent)
:QDateEdit(parent)
{
   BEGIN;
}


CoaDateEdit::CoaDateEdit ( const QDate & date, QWidget * parent )
:QDateEdit(date, parent)
{
   BEGIN;
}



CoaDateEdit::~CoaDateEdit()
{
   BEGIN;
}

