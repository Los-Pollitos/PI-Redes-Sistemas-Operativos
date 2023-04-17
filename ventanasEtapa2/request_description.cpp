#include "request_description.h"
#include "ui_request_description.h"

request_description::request_description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::request_description)
{
    ui->setupUi(this);
}

request_description::~request_description()
{
    delete ui;
}
