#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QPainter>
#include <QTcpSocket>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("Communicate"));
    //固定登陆界面
    this->setFixedSize(428,325);



    QTcpSocket* Socket = new QTcpSocket(this);
    Socket->connectToHost("127.0.0.1", 5555); // 连接到服务器端

    // 连接成功时的处理
    connect(Socket, &QTcpSocket::connected, [](){
        qDebug() << "Connected to the server.";
    });

    // 连接出错时的处理
    connect(Socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), [=](QAbstractSocket::SocketError socketError){
        qDebug() << "Socket error: " << socketError;
    });

    //点击登陆按钮触发账号，密码数据库查询检测操作
    connect(ui->btn_Land, &QPushButton::pressed, [=](){

        QString Account = ui->lineEditAccound->text();       
        QString Password = ui->lineEditPassword->text();


        QString TransforData = Account + ":" + Password;
        QAbstractSocket::SocketState socketState = Socket->state();
        if (socketState != 0)
        {
             Socket->write(TransforData.toUtf8());
        }
    });

    //读取到服务器的返回数据
    connect(Socket, &QTcpSocket::readyRead,[=](){
        QByteArray Data = Socket->readAll();
        QString AcceptData = QString::fromUtf8(Data);
        if (AcceptData == "Succeed")
        {
             this->hide();
        }
        else if(AcceptData == "PasswordError")
        {
            //出现警告窗口
            QMessageBox::critical(this, "错误", "密码输入有误，请重新输入");
        }
        else if(AcceptData == "AccountError")
        {
            //出现警告窗口
            QMessageBox::critical(this, "错误", "账号输入有误，请重新输入");
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    //绘制登陆界面的背景图片
    QPainter Painter(this);
    QPixmap PixMap(":/1689943712391.png");
    Painter.drawPixmap(0,0,PixMap);
}
