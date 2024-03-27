#include "mytcpsocket.h"

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

myTcpSocket::myTcpSocket(QObject* parent)
    :QTcpSocket(parent)
{
    connect(this,&myTcpSocket::readyRead, this,&myTcpSocket::receiveMessage);
}

myTcpSocket::~myTcpSocket()
{

}

void myTcpSocket::receiveMessage()
{
    QByteArray Data = readAll();

    QString NewData = QString::fromUtf8(Data);
    QStringList DataInfo = NewData.split(":");

    if (DataInfo.size() == 2)
   {
       QString Account = DataInfo[0];
       QString Password = DataInfo[1];

       //查询数据
       QSqlQuery Newquery("SELECT * FROM mytable");
       while (Newquery.next()) {
           QString QueryAccount = Newquery.value(0).toString();
           QString QueryPassword = Newquery.value(1).toString();

           if(Account == QueryAccount)
           {
               if (Password == QueryPassword)
               {
                   qDebug() << "Succeed to query data";
                   // 发送数据
                   write("Succeed");
               }
               else
               {
                   write("PasswordError");
               }
           }
           else
           {
                write("AccountError");
           }
       }
   }

}
