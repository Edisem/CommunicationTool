#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QTcpSocket>

class myTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    myTcpSocket(QObject* parent = nullptr);
    ~myTcpSocket();

    void receiveMessage();
};

#endif // MYTCPSOCKET_H
