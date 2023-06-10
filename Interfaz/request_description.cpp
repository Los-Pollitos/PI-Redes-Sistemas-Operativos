#include "request_description.h"
#include "ui_request_description.h"

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
    this->setWindowTitle("Descripción");
    this->uploaded_file = false;
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->accept_button->setStyleSheet("color: #001f21;");
    this->ui->accept_label->setStyleSheet("color: #001f21;");
    this->ui->buttonBox->setStyleSheet("color: #001f21;");
    this->ui->file_button->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->label_2->setStyleSheet("color: #001f21;");
    this->ui->label_3->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");
    this->ui->label_descripcion->setStyleSheet("color: #001f21;");
    this->ui->label_fecha->setStyleSheet("color: #001f21;");
    this->ui->label_tipo->setStyleSheet("color: #001f21;");
    this->ui->lineEdit->setStyleSheet("color: #001f21;");
    this->ui->password_label->setStyleSheet("color: #001f21;");
}

void request_description::set_client(client* local_client){
    this->local_client = local_client;
}

void request_description::set_atributes(int day, int month, int year,
        int& type, QString user, QString& description,
        description_button*& parent_button, login_info* user_login,
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
       this->ui->accept_button->show();
    } else {
        this->ui->file_button->setText("Adjuntar archivo");
        this->ui->buttonBox->show();
        this->ui->password_label->show();
        this->ui->lineEdit->show();
        this->ui->accept_label->show();
        this->ui->accept_button->hide();
    }
    if (this->type == REQUEST_VACATIONS) {
        this->ui->file_button->hide();
    } else {
        this->ui->file_button->show();
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
    this->user_login = user_login;
    this->uploaded_file = false;
}

request_description::~request_description()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void request_description::on_buttonBox_accepted() {
    QString password = this->ui->lineEdit->text();
    this->ui->lineEdit->clear();
    if (password.toStdString() == this->user_login->password) {
        if (this->type == REQUEST_VACATIONS || this->uploaded_file == true) {
            QMessageBox show_message =  QMessageBox();
            show_message.setWindowTitle("Correcto");
            show_message.setModal(true);
            show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_message.setText("Solicitud aceptada");
            show_message.exec();
            this->parent_button->valid = false;
            this->close();
            emit this->parent_button->disapear(this->parent_button->identifier);
        } else {
            QMessageBox show_message =  QMessageBox();
            show_message.setWindowTitle("Error");
            show_message.setModal(true);
            show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_message.setText("Debe incluir un archivo de constancia");
            show_message.exec();
        }
    } else {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Contraseña incorrecta");
        show_message.exec();
    }
}


void request_description::on_buttonBox_rejected() {
    QString password = this->ui->lineEdit->text();
    this->ui->lineEdit->clear();
    if (password.toStdString() == this->user_login->password) {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Correcto");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Solicitud denegada");
        show_message.exec();
        this->close();
        this->parent_button->valid = false;
        emit this->parent_button->disapear(this->parent_button->identifier);
    } else {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Contraseña incorrecta");
        show_message.exec();
    }
}


void request_description::on_file_button_clicked() {
    if (this->admin) {
        // TODO(cristopher): hacer lo de subir un archivo (no es para esta entrega)
        this->uploaded_file = true;
        // TODO (cristopher): esto hay que ponerlo true solo si sí subió el archivo
        // la idea es que el programa no deje aceptar una solicitud de constancia si
        // no ha subido el archivo (no es para esta entrega)
    } else {
        // TODO(cristopher): hacer lo de descargar un archivo (no es para esta entrega)
    }
}

