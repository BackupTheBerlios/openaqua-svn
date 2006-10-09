#ifndef __CoaTcpServer_h__
#define __CoaTcpServer_h__

#include <CoaTcpSocket>

#include <QTcpServer>

class CoaTcpServer: public QTcpServer {
public:
   CoaTcpServer ( QObject * parent = 0 );
   virtual ~CoaTcpServer ();
};

#endif //__CoaTcpServer_h__

