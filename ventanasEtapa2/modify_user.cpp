#include "modify_user.h"
#include "ui_modify_user.h"

#include <QMessageBox>

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    ui->setupUi(this);
    this->add_data();
}

modify_user::~modify_user() {
    delete ui;
}

void modify_user::on_comboBox_activated(int index) {
    // TODO(nosotros): rellenar info de usuarios con cantidad de usuarios real
    ui->employee_name->setText(this->names[index]);
    ui->employee_id->setReadOnly(true);
    ui->employee_id->setText(QString::number(this->ids[index]));
    ui->employee_job->setText(this->job[index]);
    ui->employee_subordinate->setText(this->subordinate[index]);
    ui->employee_salary->setText(QString::number(this->salary[index]));
    ui->employee_vacations->setText(QString::number(this->vacations[index]));
}

void modify_user::add_data() {
    // TODO(nosotros): leer de una base de datos
    ui->comboBox->addItem("Empleado 1");
    ui->comboBox->addItem("Empleado 2");

    this->names.append("Nombre1 Apellido1");
    this->names.append("Nombre2 Apellido2");

    this->ids.append(12345678);
    this->ids.append(87654321);

    this->job.append("Trabajo1");
    this->job.append("Trabajo2");

    this->subordinate.append("Yo1");
    this->subordinate.append("Yo2");

    this->salary.append(123);
    this->salary.append(321);

    this->vacations.append(1);
    this->vacations.append(2);
}

void modify_user::on_approve_changes_clicked() {
    QString password = ui->password->text();
    if (password == "123") { // TODO(nosotros): password
        QMessageBox::information(this, "Correcto", "Cambios aplicados");
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}

