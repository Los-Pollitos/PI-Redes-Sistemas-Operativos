#include "consult_salary.h"
#include "ui_consult_salary.h"

consult_salary::consult_salary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_salary)
{
    ui->setupUi(this);
    this->setWindowTitle("Consultar Salario Base");
    ui->base_salary->setReadOnly(true);
    ui->salary->setReadOnly(true);
    ui->id->setReadOnly(true);
    ui->name->setReadOnly(true);
}

consult_salary::~consult_salary()
{
    delete ui;
}
