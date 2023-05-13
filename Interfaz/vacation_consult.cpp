#include "vacation_consult.h"
#include "ui_vacation_consult.h"

vacation_consult::vacation_consult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vacation_consult)
{
    ui->setupUi(this);
    this->setWindowTitle("Vacaciones disponibles");
}

vacation_consult::~vacation_consult()
{
    delete ui;
}
