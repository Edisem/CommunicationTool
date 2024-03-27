#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDtls>
#include <QMessageBox>

#include "mytcpserver.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // 使用SQLite数据库，也可以选择其他数据库
    db.setDatabaseName("mydatabase.db"); // 设置数据库名称
    if (!db.open()) {
        qDebug() << "Failed to open database";
        return;
    }

    //创建数据库表
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS mytable (account TEXT PRIMARY KEY, password TEXT)");

    /*
    //插入数据
    // 准备 SQL 语句，同时插入 account 和 password
    query.prepare("INSERT INTO mytable (account, password) VALUES (:account, :password)");

    // 绑定 account 和 password 的值
    query.bindValue(":account", "admin");
    query.bindValue(":password", "123");

    if (!query.exec()) {
        qDebug() << "Failed to insert data";
    }
    */

    //创建服务器
    Server = new myTcpServer(this);
    if(!Server->listen(QHostAddress::Any,5555))
       {
           QMessageBox::critical(this, "失败", "服务器启动失败");
       }else{
           QMessageBox::information(this, "成功", "服务器启动成功");
       }

    //connect(Server,&QTcpServer::newConnection,this, &Widget::DealConnect);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::DealConnect()
{

    qDebug() << "Connected to the client.";
    Socket = Server->nextPendingConnection();


    connect(Socket, &QTcpSocket::readyRead, [=](){
        if (Socket->state() == 0)
        {
             qDebug() << "UnConnected to the client.";
            return ;
        }

        QByteArray Data = Socket->readAll();

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
                       Socket->write("Succeed");
                   }
                   else
                   {
                       Socket->write("PasswordError");
                   }
               }
               else
               {
                    Socket->write("AccountError");
               }
           }
       }
    });
}
