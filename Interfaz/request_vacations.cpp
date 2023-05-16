#include <QPushButton>

#include "request_vacations.h"
#include "ui_request_vacations.h"

request_vacations::request_vacations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_vacations)
{
    ui->setupUi(this);
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
