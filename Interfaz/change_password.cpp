#include "change_password.h"
#include "ui_change_password.h"

change_password::change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password); // no muestra password
    this->ui->lineEdit_3->setEchoMode(QLineEdit::Password); // no muestra token
}

change_password::~change_password()
{
    delete ui;
}
