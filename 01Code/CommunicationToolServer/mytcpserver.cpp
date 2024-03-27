#include "mytcpserver.h"

#include "mytcpsocket.h"

myTcpServer::myTcpServer(QObject* parent)
    :QTcpServer(parent)
{

}

myTcpServer::~myTcpServer()
{

}

void myTcpServer::incomingConnection(qintptr handle)
{
    myTcpSocket* Socket = new myTcpSocket(this);
    Socket->setSocketDescriptor(handle);
}
