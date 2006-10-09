#include "coacheckbox.h"
#include <CoaDebug>

CoaCheckBox::CoaCheckBox(QWidget *parent)
:QCheckBox(parent)
{
   BEGIN;
}


CoaCheckBox::CoaCheckBox ( const QString & text, QWidget * parent)
:QCheckBox(text, parent)
{
   BEGIN;
}


CoaCheckBox::~CoaCheckBox()
{
   BEGIN;
}


