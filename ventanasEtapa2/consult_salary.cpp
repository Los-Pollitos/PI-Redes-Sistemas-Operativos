#include "consult_salary.h"
#include "ui_consult_salary.h"

consult_salary::consult_salary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_salary)
{
    ui->setupUi(this);
}

consult_salary::~consult_salary()
{
    delete ui;
}
