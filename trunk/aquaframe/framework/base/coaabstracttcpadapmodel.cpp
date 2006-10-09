#include "coaabstracttcpadapmodel.h"
#include <CoaDebug>


CoaAbstractTcpAdapModel::CoaAbstractTcpAdapModel ( const CoaTcpSocket & socket, QObject * parent )
: CoaAbstractProxyModel(parent)
, m_socket(socket)
{
   BEGIN;
}


CoaAbstractTcpAdapModel::~CoaAbstractTcpAdapModel ()
{
   BEGIN;
}



