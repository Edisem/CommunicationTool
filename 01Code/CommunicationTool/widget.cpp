#include "widget.h"
#include "ui_widget.h"

#include <QMessageBox>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("Communicate"));
    //固定登陆界面
    this->setFixedSize(428,325);

    //点击登陆按钮触发账号，密码数据库查询检测操作
    connect(ui->btn_Land, &QPushButton::pressed, [=](){

        QString Account = ui->lineEditAccound->text();
        if(Account == "admin")
        {
            QString Password = ui->lineEditPassword->text();
            if (Password == "123")
            {
                this->hide();
            }
            else
            {
                //出现警告窗口
                QMessageBox::critical(this, "错误", "密码输入有误，请重新输入");
            }
        }
        else
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
