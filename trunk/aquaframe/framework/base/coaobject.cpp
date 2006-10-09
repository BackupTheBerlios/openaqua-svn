#include "coaobject.h"
#include <CoaDebug>

CoaObject::CoaObject( CoaObject * parent)
:QObject(parent)
{
   BEGIN;
}


CoaObject::~CoaObject()
{
   BEGIN;
}
