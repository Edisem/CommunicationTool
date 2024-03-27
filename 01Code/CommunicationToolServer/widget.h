#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QTcpSocket>
#include <QTcpServer>

#include "mytcpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void DealConnect();

private:
    Ui::Widget *ui;

    QTcpSocket* Socket;

    myTcpServer* Server;
};
#endif // WIDGET_H
