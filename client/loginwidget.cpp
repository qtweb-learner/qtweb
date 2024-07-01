#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_loginButton_clicked()
{
    auto username = ui->usernameLineEdit->text();
    auto password = ui->passwordLineEdit->text();
    if (username.length() == 0 || password.length() == 0){
        return;
    }
    emit login(username, password);
}

