#include "modify_user.h"
#include "ui_modify_user.h"

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    ui->setupUi(this);
    ui->comboBox->addItem("Empleado 1");
    ui->comboBox->addItem("Empleado 2");
    ui->comboBox->addItem("Empleado 3");
}

modify_user::~modify_user() {
    delete ui;
}

void modify_user::on_comboBox_activated(int index) {
    // TODO(nosotros): rellenar info de usuarios con cantidad de usuarios real
    if (index == 1) {
        ui->employee_name->setText("Nombre empleado 1");
    } else {
        if (index == 2) {
            ui->employee_name->setText("Nombre empleado 2");
        }
        else {
            ui->employee_name->setText("Nombre empleado 3");
        }
    }

}
