#include "testserver.h"
#include "testthread.h"


#include <QTcpSocket>

TestServer::TestServer(QObject *parent)
    : CoaTcpServer(parent)
{
   BEGIN;
   connect(this, SIGNAL(newConnection()), this, SLOT(openConnection()));
}



void TestServer::openConnection()
{
   BEGIN;
   QTcpSocket * socket = nextPendingConnection();
   const CoaString peerAdd = socket->peerAddress().toString();
   const CoaString peerNam = socket->peerName ();
   const quint16 peerPor   = socket->peerPort();


   INF(QString("Got Connection from %1:%2 (%3)").arg(peerAdd).arg(peerNam).arg(peerPor));
   new TestThread(socket, this);
}

