#ifndef FORTUNETHREAD_H
#define FORTUNETHREAD_H

#include <CoaThread>
#include <CoaTcpSocket>
#include <CoaString>
#include <QTimer>

class TestThread : public CoaThread
{
    Q_OBJECT

public:
    TestThread(QTcpSocket* socket, QObject *parent);
    virtual ~TestThread();
    void run();

protected slots:
   void handleMessage();
   void sendTime();
   bool checkSocket();

protected:
   void sendString(const int i, const CoaString& str);
   void sendTabSize(const int col, const int row);
   void sendTabContent(int colFrom, int colTo, int rowFrom, int rowTo);

signals:
    void error(CoaTcpSocket::SocketError socketError);


private:
    QTcpSocket* m_socket;

   enum MSG {
      REQ_TIME = 0,
      REQ_STR  = 1,
      REQ_TAB_SIZE = 2,
      REQ_TAB_CONT = 3,

      RES_TIME = 100,
      RES_STR  = 101,
      RES_TAB_SIZE = 102,
      RES_TAB_CONT = 103,

      ERROR = 200
   };

   QTimer   m_timer;

   int   m_col;
   int   m_row;

};

#endif
