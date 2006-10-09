#include "coacombobox.h"
#include <CoaDebug>


CoaComboBox::CoaComboBox ( QWidget * parent )
:QComboBox(parent)
{
//   BEGIN;
}



CoaComboBox::~CoaComboBox()
{
//   BEGIN;
}


void CoaComboBox::emitDataChanged ()
{
//   BEGIN;
   emit dataChanged ( this );
}

