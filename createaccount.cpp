#include "createAccount.h"
#include "ui_createaccount.h"
#include <QtGui>
#include <QtCore>

createAccount::createAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createAccount)
{
    ui->setupUi(this);
}

createAccount::~createAccount()
{
    delete ui;
}

void createAccount::on_create_acc_btn_clicked()
{
    this->close();
}

void createAccount::on_cancel_btn_clicked()
{
    this->close();
}
