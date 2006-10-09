#include "tcpproxy.h"
#include <CoaDebug>


TcpProxy::TcpProxy(QObject* const parent)
: CoaAbstractTcpProxyModel(parent)
, m_socket(this)
{
   BEGIN;
   m_actionModel = new ActionModel(parent);
   //m_socket
   m_socket.connectToHost("localhost", 32000);
   if (! m_socket.waitForConnected(3000)) {
      ERR("No Socket Connection");
   }
}



TcpProxy::~TcpProxy()
{
   BEGIN;
   m_socket.disconnect();
   if (!m_socket.waitForDisconnected(3000)){
      ERR("Cannot get disconnected");
   }
   delete m_actionModel;
}


QModelIndex TcpProxy::mapFromSource ( const QModelIndex & sourceIndex ) const
{
   BEGIN;
}



QModelIndex TcpProxy::mapToSource ( const QModelIndex & proxyIndex ) const
{
   BEGIN;
}





QModelIndex TcpProxy::index(int row, int column, const QModelIndex &parent) const
{
   BEGIN;
   return m_actionModel->index(row, column, parent);
}



QModelIndex TcpProxy::parent(const QModelIndex &child) const
{
   BEGIN;
   return m_actionModel->parent(child);
}





   //Reading
QVariant TcpProxy::data ( const QModelIndex & index, int role ) const
{
   BEGIN;
   return m_actionModel->data(index, role);
}



QVariant TcpProxy::headerData(int section, Qt::Orientation orientation, int role) const
{
   BEGIN;
   return m_actionModel->headerData(section, orientation, role);
}



int TcpProxy::rowCount ( const QModelIndex & parent ) const
{
   BEGIN;
   return m_actionModel->rowCount(parent);
}



int TcpProxy::columnCount ( const QModelIndex & parent ) const
{
   BEGIN;
   return m_actionModel->columnCount(parent);
}






bool TcpProxy::loadXmlData (CoaIODevice * const device)
{
   BEGIN;
   return m_actionModel->loadXmlData(device);
}




bool TcpProxy::saveXmlData (CoaIODevice * const device)
{
   BEGIN;
   return m_actionModel->saveXmlData(device);
}





const CoaString TcpProxy::lastError() const
{
   BEGIN;
   return m_actionModel->lastError();
}
