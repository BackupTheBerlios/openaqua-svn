#ifndef __CoaAbstractTcpAdapModel_h__
#define __CoaAbstractTcpAdapModel_h__


#include <CoaAbstractProxyModel>
#include <CoaTcpSocket>



class CoaAbstractTcpAdapModel: public CoaAbstractProxyModel {
Q_OBJECT

public:

   CoaAbstractTcpAdapModel ( const CoaTcpSocket & socket, QObject * parent = 0 );
   virtual ~CoaAbstractTcpAdapModel ();

private:
   const CoaTcpSocket & m_socket;
};


#endif //__CoaAbstractTcpAdapModel_h__

