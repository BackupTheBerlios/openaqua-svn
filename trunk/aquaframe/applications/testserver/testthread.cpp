#include "testthread.h"
#include <CoaDebug>

#include <QDataStream>
#include <QDateTime>
#include <unistd.h>
const int SLEEP = 0; //20*1000

TestThread::TestThread(QTcpSocket* socket, QObject *parent)
    : CoaThread("testthread", parent)
    , m_socket(socket)
    , m_timer(0)
    , m_col (10)
    , m_row (50000)
{
   BEGIN;
   connect(m_socket, SIGNAL(readyRead ()), this, SLOT(handleMessage()));
   connect(&m_timer,  SIGNAL(timeout()),    this, SLOT(sendTime()));
   connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(checkSocket()));
   //m_timer.start(3000); // emit signal every 3 secs
}


TestThread::~TestThread()
{
   BEGIN;
   ERR("Delete TestThread");
   m_socket->close();
   m_socket->deleteLater();
}



void TestThread::run()
{
   BEGIN;
   if (checkSocket() != true) return;
   INF("Ready to get messages from socket");

   CoaThread::run();
}


void TestThread::handleMessage()
{
   INF("Handle Message");
   if (checkSocket() != true) return;

   if (m_socket->bytesAvailable() < 1) return;

   QDataStream in(m_socket);
   in.setVersion(QDataStream::Qt_4_0);


   quint16    msgSize = 0;
   int        msgType = ERROR;

   in >> msgSize >> msgType;
   switch(msgType) {
      case REQ_TIME:
      {
         INF("GOT: REQ_TIME");
         sendTime();
         break;
      }


      case REQ_STR:
      {
         INF("GOT: REQ_STR");
         CoaString  msgContent = "";
         in >> msgContent;
         CoaString response = "Request was: ";
         sendString(RES_STR, response + msgContent);
         break;
      }


      case REQ_TAB_SIZE:
      {
         INF("GOT: REQ_TAB_SIZE");
         sendTabSize(m_col, m_row);
         break;
      }


      case REQ_TAB_CONT:
      {
         INF("GOT: REQ_TAB_CONT");
         int colFrom, colTo, rowFrom, rowTo;
         in >> colFrom >> colTo >> rowFrom >> rowTo;
         ERR(CoaString("colFrom %1 colTo %2 rowFrom %3 rowTo %4").arg(colFrom).arg(colTo).arg(rowFrom).arg(rowTo));
         INF("GOT: REQ_TAB_CONT");
         sendTabContent(colFrom, colTo, rowFrom, rowTo);
         break;
      }

   }



}



void TestThread::sendTime()
{
   BEGIN;
   if (checkSocket() != true) return;
   sendString(RES_TIME, QDateTime::currentDateTime().toString());
}


bool TestThread::checkSocket()
{
   BEGIN;
   //do some checks
   if (!m_socket->isValid()) {

      ERR("Socket isn't valid anymore");
      switch (m_socket->error()) {
      case QAbstractSocket::RemoteHostClosedError:    ERR("RemoteHostClosedError");    break;
      case QAbstractSocket::HostNotFoundError:        ERR("HostNotFoundError");        break;
      case QAbstractSocket::ConnectionRefusedError:   ERR("ConnectionRefused");        break;
      default:                                        ERR("Other Errors");
      }

      exit(-1); //quit this thread
      deleteLater();
      return false;
   }

   return true;
}



void TestThread::sendString(const int i, const CoaString& str)
{
   BEGIN;
   if (checkSocket() != true) return;


   //prepare the string
   QByteArray block;
   QDataStream out(&block, QIODevice::WriteOnly);
   out.setVersion(QDataStream::Qt_4_0);
   out << (quint16)0 //msg size
       << i //msg type
       << str //msg content
       ;
   out.device()->seek(0);
   out << (quint16)(block.size() - sizeof(quint16));

   //send the message
   usleep(SLEEP);
   m_socket->write(block);
}



void TestThread::sendTabSize(const int col, const int row)
{
   BEGIN;
   if (checkSocket() != true) return;

   //prepare the string
   QByteArray block;
   QDataStream out(&block, QIODevice::WriteOnly);
   out.setVersion(QDataStream::Qt_4_0);
   out << (quint16)0 //msg size
       << RES_TAB_SIZE
       << col
       << row
       ;
   out.device()->seek(0);
   out << (quint16)(block.size() - sizeof(quint16));

   //send the message
   usleep(SLEEP);
   m_socket->write(block);
}


void TestThread::sendTabContent(int colFrom, int colTo, int rowFrom, int rowTo)
{
   BEGIN;
   if (checkSocket() != true) return;

   //prepare the string
   QByteArray block;
   QDataStream out(&block, QIODevice::WriteOnly);
   out.setVersion(QDataStream::Qt_4_0);
   out << (quint16)0 //msg size
       << RES_TAB_CONT
       << colTo - colFrom +1
       << rowTo - rowFrom +1
       ;
   for (int c = colFrom; c <= colTo; c++){ //iterate over cols
      for (int r = rowFrom; r <= rowTo; r++) {
         out << c << r;

         switch(c) {
            case 1: out << c+100; break;
            case 2: out << c+102; break;
            case 3: out << c+103; break;
            case 4: out << c+104; break;
            case 5: out << c+105; break;
            case 6: out << c+106; break;
            case 7: out << c+107; break;
            case 8: out << c+108; break;
            case 9: out << c+109; break;
            default: break;
         }
      }
   }

   out.device()->seek(0);
   out << (quint16)(block.size() - sizeof(quint16));

   INF(CoaString("Size: %1 bytes").arg((quint16)(block.size() - sizeof(quint16))))
   //send the message
   usleep(SLEEP);
   m_socket->write(block);

}








