#include "coasqldriver.h"
#include <CoaDebug>
#include <cassert>


CoaSqlDriver::CoaSqlDriver ( QObject * parent)
: QSqlDriver(parent)
{
   BEGIN;
}


CoaSqlDriver::~CoaSqlDriver ()
{
   BEGIN;
}


