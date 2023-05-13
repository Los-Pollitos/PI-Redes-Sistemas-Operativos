#include "work_proof.h"
#include "ui_work_proof.h"

work_proof::work_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::work_proof)
{
    ui->setupUi(this);
    this->setWindowTitle("Constancia laboral");
}

work_proof::~work_proof()
{
    delete ui;
}

void work_proof::on_pushButton_clicked()
{
    this->close();
}
