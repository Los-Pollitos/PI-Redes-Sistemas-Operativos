#include "office_description.h"
#include "ui_office_description.h"

office_description::office_description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::office_description)
{
    ui->setupUi(this);
}

office_description::~office_description()
{
    delete ui;
}
