#include "modify_user.h"
#include "ui_modify_user.h"

modify_user::modify_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_user)
{
    ui->setupUi(this);
}

modify_user::~modify_user()
{
    delete ui;
}
