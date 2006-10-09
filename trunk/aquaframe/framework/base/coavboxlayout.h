#ifndef __CoaVBoxLayout_h__
#define __CoaVBoxLayout_h__

#include <QVBoxLayout>


class CoaVBoxLayout: public QVBoxLayout {
   Q_OBJECT
   public:
      CoaVBoxLayout ();
      CoaVBoxLayout ( QWidget * parent);
      virtual ~CoaVBoxLayout ();
};


#endif //__CoaVBoxLayout_h__

