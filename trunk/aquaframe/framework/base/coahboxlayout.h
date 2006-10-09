#ifndef __CoaHBoxLayout_h__
#define __CoaHBoxLayout_h__

#include <QHBoxLayout>


class CoaHBoxLayout: public QHBoxLayout {
   Q_OBJECT
   public:
      CoaHBoxLayout ();
      CoaHBoxLayout ( QWidget * parent);
      virtual ~CoaHBoxLayout ();
};


#endif //__CoaHBoxLayout_h__

