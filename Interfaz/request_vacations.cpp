#include <QPushButton>

#include "request_vacations.h"
#include "ui_request_vacations.h"

request_vacations::request_vacations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_vacations)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->confirm->setStyleSheet("color: #001f21;");
    this->ui->label_start->setStyleSheet("color: #001f21;");
    this->ui->reset->setStyleSheet("color: #001f21;");
    this->ui->start_date->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Solicitud de vacaciones");
    ui->reset->setStyleSheet("background-color: red");
    ui->confirm->setStyleSheet("background-color: green");
}

request_vacations::~request_vacations()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}


void request_vacations::set_client(client* local_client){
    this->local_client = local_client;
}
