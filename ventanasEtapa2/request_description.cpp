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

request_description::request_description(int day, int month, int year,
        int& type, QString user, QString& description,
        description_button *& parent_button, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_description),
    parent_button(parent_button),
    description(description)
{
    ui->setupUi(this);
    // this->parent_button = parent_button;
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
        std::cout << "Button " << this->parent_button;
        std::cout << "\n" << this->parent_button->valid << std::endl;
        this->parent_button->valid = false;
        this->close();
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
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecto");
    }
}

