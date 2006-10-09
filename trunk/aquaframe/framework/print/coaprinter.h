#ifndef __CoaPrinter_h__
#define __CoaPrinter_h__

#include <QPrinter>

class CoaPrinter: public QPrinter
{

public:
   CoaPrinter ( PrinterMode mode = ScreenResolution );
   virtual ~CoaPrinter ();

};


#endif //__CoaPrinter_h__

