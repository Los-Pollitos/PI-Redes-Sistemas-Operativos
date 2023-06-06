#include "vacation_consult.h"
#include "ui_vacation_consult.h"

vacation_consult::vacation_consult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vacation_consult)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->setWindowTitle("Vacaciones disponibles");
    ui->available_vacations->setReadOnly(true);
    ui->vacations->setReadOnly(true);
    ui->id->setReadOnly(true);
    ui->name->setReadOnly(true);
}

void vacation_consult::set_client(client* local_client){
    this->local_client = local_client;
}

vacation_consult::~vacation_consult() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}
