#include "salary_proof.h"
#include "ui_salary_proof.h"

salary_proof::salary_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salary_proof)
{
    ui->setupUi(this);
}

salary_proof::~salary_proof()
{
    delete ui;
}
