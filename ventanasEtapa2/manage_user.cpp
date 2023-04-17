#include "manage_user.h"
#include "ui_manage_user.h"

manage_user::manage_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manage_user)
{
    ui->setupUi(this);
}

manage_user::~manage_user()
{
    delete ui;
}
