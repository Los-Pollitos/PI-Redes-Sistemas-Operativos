#include "request_vacations.h"
#include "ui_request_vacations.h"

request_vacations::request_vacations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_vacations)
{
    ui->setupUi(this);
    this->setWindowTitle("Solicitud de vacaciones");
}

request_vacations::~request_vacations()
{
    delete ui;
}
