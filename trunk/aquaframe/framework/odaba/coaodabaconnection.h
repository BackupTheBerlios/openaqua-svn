#ifndef __CoaOdabasConnection_h__
#define __CoaOdabasConnection_h__

#include <CoaThread>
#include <CoaMakros>


//for the ODABAClient
#include  <csos4mac.h>
#include  <igvtx.h>
#include  <igvts.h>
#include  <sODABAClient.hpp>



class CoaOdabasConnection: public CoaThread
{
   Q_OBJECT;
public:
   CoaOdabasConnection( const QString& threadName, QObject * parent = 0);
	virtual ~CoaOdabasConnection();
   
   //connection stuff
public slots:   
   unsigned int openConnection(const QString& server, const int port);
   unsigned int closeConnection();
   const QString serverName() ;
   const int serverPort() ;
   
signals:
   void connectionOpened( unsigned int );   
   void connectionClosed( unsigned int );
   void connectionError( unsigned int, const QString& );
   
   
   
protected:
   unsigned int getNextJobId();
   
private:
   bool m_isConntected;
   ODABAClient *m_client;
   unsigned int m_jobId;  //
   QReadWriteLock  m_Lock; //mutex
   QString m_servername;
   int m_serverport;
   
   //not implemented
   CoaOdabasConnection( QObject * parent = 0 );

   //not implemented
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaOdabasConnection);
   COAMAKRO_NO_COMPARE(CoaOdabasConnection);
   
};


#endif //__CoaOdabasConnection_h__
