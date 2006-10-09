#ifndef __CoaPrintDialog_h__
#define __CoaPrintDialog_h__

#include <QPrintDialog>

class QPrinter;

class CoaPrintDialog: public QPrintDialog {
Q_OBJECT

public:

   CoaPrintDialog ( QPrinter * printer, QWidget * parent = 0 );
   virtual ~CoaPrintDialog ();


};

#endif //__CoaPrintDialog_h__

