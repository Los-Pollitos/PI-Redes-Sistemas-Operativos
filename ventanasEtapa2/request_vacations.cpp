#include "request_vacations.h"
#include "ui_request_vacations.h"

request_vacations::request_vacations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_vacations)
{
    ui->setupUi(this);
}

request_vacations::~request_vacations()
{
    delete ui;
}
