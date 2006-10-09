#ifndef __CoaAbstractTcpProxyModel_h__
#define __CoaAbstractTcpProxyModel_h__


#include <CoaAbstractProxyModel>



class CoaAbstractTcpProxyModel: public CoaAbstractProxyModel {
Q_OBJECT
public:
   CoaAbstractTcpProxyModel ( QObject * parent = 0 );
   virtual ~CoaAbstractTcpProxyModel ();
};


#endif //__CoaAbstractTcpProxyModel_h__

