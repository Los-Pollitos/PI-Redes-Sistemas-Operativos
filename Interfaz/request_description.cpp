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
    this->uploaded_file = false;
}



void request_description::set_atributes(int day, int month, int year,
        int& type, QString user, QString& description,
        description_button *& parent_button, login_info * user_data,
        bool admin) {
    this->parent_button = parent_button;
    this->description = description;
    this->date[0]= day;
    this->date[1] = month;
    this->date[2] = year;
    this->type= type;
    this->admin = admin;
    if (!this->admin) {
       this->ui->file_button->setText("Descargar archivo");
       this->ui->buttonBox->hide();
       this->ui->password_label->hide();
       this->ui->lineEdit->hide();
       this->ui->accept_label->hide();
    } else {
        this->ui->accept_button->hide();
    }
    if (this->type == REQUEST_VACATIONS) {
        this->ui->file_button->hide();
    }
    this->user = user;
    this->description = description;
    QString date_string = QString::number(day);
    date_string += "/";
    date_string += QString::number(month);
    date_string += "/";
    date_string += QString::number(year);
    this->ui->label_descripcion->setText(description);
    this->ui->label_fecha->setText(date_string);
    QString type_string = request_type(this->type);
    this->ui->label_tipo->setText(type_string);
    this->ui->lineEdit->setEchoMode(QLineEdit::Password);
    this->user_data = user_data;
}

request_description::~request_description()
{
    delete ui;
}

void request_description::on_buttonBox_accepted() {
    QString password = ui->lineEdit->text();
    if (password.toStdString() == this->user_data->password) {
        if (this->type == REQUEST_VACATIONS || this->uploaded_file == true) {
            QMessageBox::information(this, "Correcto", "Solicitud aceptada");
            this->parent_button->valid = false;
            this->close();
            emit this->parent_button->disapear(this->parent_button->identifier);
        } else {
            QMessageBox::warning(this, "Error", "Debe incluir un archivo de constancia");
        }
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}


void request_description::on_buttonBox_rejected() {
    QString password = ui->lineEdit->text();
    if (password.toStdString() == this->user_data->password) {
        QMessageBox::information(this, "Correcto", "Solicitud denegada");
        this->close();
        this->parent_button->valid = false;
        emit this->parent_button->disapear(this->parent_button->identifier);
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecto");
    }
}


void request_description::on_file_button_clicked() {
    if (this->admin) {
        // TODO(cristopher): hacer lo de subir un archivo
        this->uploaded_file = true; // TODO (cristopher): esto hay que ponerlo true solo si sí subió el archivo
        // la idea es que el programa no deje aceptar una solicitud de constancia si no ha subido el archivo
    } else {
        // TODO(cristopher): hacer lo de descargar un archivo
    }
}

