#ifndef TestServer_H
#define TestServer_H

#include <CoaTcpServer>

class TestServer : public CoaTcpServer
{
    Q_OBJECT

public:
    TestServer(QObject *parent = 0);

protected slots:
    void openConnection();

private:
};

#endif
