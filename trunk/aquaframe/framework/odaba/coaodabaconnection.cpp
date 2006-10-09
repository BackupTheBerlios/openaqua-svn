#include "coaodabasconnection.h"
#include <CoaDebug>
#include <QWriteLocker>
#include <QReadLocker>

CoaOdabasConnection::CoaOdabasConnection(const QString& threadName, QObject * parent)
: CoaThread(threadName, parent)
, m_client(0)
, m_jobId(0)
, m_servername("")
, m_serverport(0)
{
   BEGIN;
}

CoaOdabasConnection::~CoaOdabasConnection()
{
   BEGIN;
   delete m_client;
}


unsigned int CoaOdabasConnection::getNextJobId()
{
   BEGIN;
   QWriteLocker locker(&m_Lock);
   return (++m_jobId); 
}

unsigned int CoaOdabasConnection::openConnection(const QString& server, const int port)
{
   BEGIN;
   unsigned int result = getNextJobId();
   QWriteLocker locker(&m_Lock);
   
   
   if (m_client != 0) {
      //allready connected?
      //do nothing
   } else {
      //otherwise connect;
      
      //make char array from servername;
      char s[255];
      strncpy(s, server.toLocal8Bit().constData(), 254);
      s[255]='\0';

      //connect
      m_client = new ODABAClient();
      logical i = m_client -> Connect(s, port); //might change server!

      if (i != TRUE){
         emit connectionError(result, "Connection Error");
         m_servername=s;
         m_serverport=port;
         delete m_client;
         m_client = 0;
         return result;
      }
   }

   emit connectionOpened(result);
   return result;
}



unsigned int CoaOdabasConnection::closeConnection()
{
   BEGIN;
   unsigned int result = getNextJobId();
   QWriteLocker locker(&m_Lock);
   
   if (m_client == 0) {
      //no connection there?
      //do nothing
   } else {
      //otherwise close connection
      m_client->Disconnect ( );
      delete m_client;
   }
   
   emit connectionClosed(result);
   return result;
 
}

const QString CoaOdabasConnection::serverName() 
{
   BEGIN;
   QReadLocker locker(&m_Lock);
   return m_servername;
}


const int CoaOdabasConnection::serverPort() 
{
   BEGIN;
   QReadLocker locker(&m_Lock);
   return m_serverport;
}

