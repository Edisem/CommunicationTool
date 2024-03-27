#include "userwidget.h"

#include "ui_second.h"

UserWidget::UserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserWidget)
{
    ui->setupUi(this);

}

UserWidget::~UserWidget()
{
    delete ui;
}

void UserWidget::ShowWidget()
{
    this->show();
}
