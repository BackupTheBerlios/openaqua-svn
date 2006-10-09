#include "coapushbutton.h"
#include <CoaDebug>

CoaPushButton::CoaPushButton(QWidget *parent)
:QPushButton(parent)
{
   BEGIN;
}


CoaPushButton::CoaPushButton ( const QString & text, QWidget * parent)
:QPushButton(text, parent)
{
   BEGIN;
}


CoaPushButton::CoaPushButton ( const QIcon & icon, const QString & text, QWidget * parent)
:QPushButton(icon, text, parent)
{
   BEGIN;
}


CoaPushButton::~CoaPushButton()
{
   BEGIN;
}


