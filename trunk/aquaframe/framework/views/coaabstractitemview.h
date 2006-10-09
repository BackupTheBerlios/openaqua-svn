#ifndef __CoaAbstractItemView_h__
#define __CoaAbstractItemView_h__

#include <QAbstractItemView>

class CoaAbstractItemView: public QAbstractItemView {
Q_OBJECT

public:

   CoaAbstractItemView ( QWidget * parent = 0 );
   virtual ~CoaAbstractItemView ();

};


#endif //__CoaAbstractItemView_h__

