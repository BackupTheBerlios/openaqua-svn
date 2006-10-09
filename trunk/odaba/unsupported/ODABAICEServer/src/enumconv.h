#ifndef __enumconv__
#define __enumconv__
#include <OPI.h>
#include <codaba2.h>

// handwritten - not able to generate from database yet

::OPI::PIACC enumcpp2ice(::PIACC c);
::PIACC        enumice2cpp(::OPI::PIACC c);

::OPI::PIREPL enumcpp2ice(::PIREPL c);
::PIREPL        enumice2cpp(::OPI::PIREPL  c);

::OPI::PIADEF enumcpp2ice(::PIADEF c);
::PIADEF        enumice2cpp(::OPI::PIADEF c);

::ResourceTypes        enumice2cpp(::OPI::ResourceTypes c);
::OPI::ResourceTypes enumcpp2ice(::ResourceTypes c);

::ApplicationTypes        enumice2cpp(::OPI::ApplicationTypes c);
::OPI::ApplicationTypes enumcpp2ice(::ApplicationTypes c);
#endif
