#ifndef __basecast__
#define __basecast__
#include <OPI.h>
#include <codaba2.h>
#include <OPII.hpp>

// generic casts
// handwritten - not able to generate from database yet

// in: dbobjecthandle prx
// out: ::dbobjecthandle

::DBObjectHandle* dbocast(const ::OPI::DBObjectHandlePrx& objecthandle,const ::Ice::Current& c);

// in: databasehandle prx
// out: ::databasehandle
::DatabaseHandle* dbhcast(const ::OPI::DatabaseHandlePrx& dbhandle,const ::Ice::Current& c);
#endif
