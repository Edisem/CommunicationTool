#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class myTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    myTcpServer(QObject* parent = nullptr);
    ~myTcpServer();

    void incomingConnection(qintptr handle) override;
};

#endif // MYTCPSERVER_H
