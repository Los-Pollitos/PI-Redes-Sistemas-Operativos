#include "modify_user.h"
#include "ui_modify_user.h"

modify_user::modify_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_user)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Empleado 1");
    ui->comboBox->addItem("Empleado 2");
    ui->comboBox->addItem("Empleado 3");
}

modify_user::~modify_user()
{
    delete ui;
}
