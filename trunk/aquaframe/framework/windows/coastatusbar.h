#ifndef __CoaStatusBar_h__
#define __CoaStatusBar_h__

#include <QStatusBar>

class CoaStatusBar : public QStatusBar {
Q_OBJECT
public:
   CoaStatusBar ( QWidget * parent = 0 );
   virtual ~CoaStatusBar ( );
};

#endif

