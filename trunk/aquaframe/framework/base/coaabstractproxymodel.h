#ifndef __CoaAbstractProxyModel_h__
#define __CoaAbstractProxyModel_h__


#include <QAbstractProxyModel>



class CoaAbstractProxyModel: public QAbstractProxyModel {
   Q_OBJECT
   public:
   CoaAbstractProxyModel ( QObject * parent = 0 );
   virtual ~CoaAbstractProxyModel ();
};


#endif //__CoaAbstractProxyModel_h__

