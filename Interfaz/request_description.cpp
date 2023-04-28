#include "request_description.h"
#include "ui_request_description.h"

#include <iostream>  //TODO(nosotros): Borrar
#include <QMessageBox>

QString request_type(int type) {
    QString string_type = "Solicitud de Vacaciones";
    switch (type) {
    case WORK_PROOF:
        string_type = "Constancia laboral";
        break;
    case SALARY_PROOF:
        string_type = "Constancia de salario";
        break;
    case PAYMENT_PROOF:
        string_type = "Comprobante de pago";
    }
    return string_type;
}

request_description::request_description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_description) {
    ui->setupUi(this);
}



void request_description::set_atributes(int day, int month, int year,
        int& type, QString user, QString& description,
        description_button *& parent_button) {
    this->parent_button = parent_button;
    this->description = description;
    this->date[0]= day;
    this->date[1] = month;
    this->date[2] = year;
    this->type= type;
    this->user = user;
    this->description = description;
    QString date_string = QString::number(day);
    date_string += "/";
    date_string += QString::number(month);
    date_string += "/";
    date_string += QString::number(year);
    std::cout << "descr: " << description.toStdString() << std::endl;  //TODO(us) borrar
    this->ui->label_descripcion->setText(description);
    this->ui->label_fecha->setText(date_string);
    QString type_string = request_type(this->type);
    this->ui->label_tipo->setText(type_string);
    this->ui->lineEdit->setEchoMode(QLineEdit::Password);
}

request_description::~request_description()
{
    delete ui;
}

void request_description::on_buttonBox_accepted() {
    QString password = ui->lineEdit->text();
    if (password == "123") { // TODO(nosotros): password
        QMessageBox::information(this, "Correcto", "Solicitud aceptada");
        this->parent_button->valid = false;
        this->close();
        emit this->parent_button->disapear(this->parent_button->getId());
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}


void request_description::on_buttonBox_rejected() {
    QString password = ui->lineEdit->text();
    if (password == "123") { // TODO(nosotros): password
        QMessageBox::information(this, "Correcto", "Solicitud denegada");
        this->close();
        this->parent_button->valid = false;
        emit this->parent_button->disapear(this->parent_button->getId());
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecto");
    }
}

