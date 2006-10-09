#ifndef __CoaTcpSocket_h__
#define __CoaTcpSocket_h__

#include <QTcpSocket>


class CoaTcpSocket: public QTcpSocket {
Q_OBJECT
public:
   CoaTcpSocket(QObject *const parent=0);
   virtual ~CoaTcpSocket();
};


#endif //__CoaTcpSocket_h__

