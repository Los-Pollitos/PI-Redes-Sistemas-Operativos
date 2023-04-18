#include "request_description.h"
#include "ui_request_description.h"

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

request_description::request_description(int day, int month, int year, int type, QString user, QString description, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_description)
{
    ui->setupUi(this);
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
    this->ui->label_descripcion->setText(this->description);
    this->ui->label_fecha->setText(date_string);
    QString type_string = request_type(this->type);
    this->ui->label_tipo->setText(type_string);
}

request_description::~request_description()
{
    delete ui;
}
