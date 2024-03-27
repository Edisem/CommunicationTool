#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class UserWidget; }
QT_END_NAMESPACE

class UserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();

    void ShowWidget();
signals:

private:
    Ui::UserWidget *ui;
};

#endif // USERWIDGET_H
