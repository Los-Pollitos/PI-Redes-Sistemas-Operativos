#include "payment_proof.h"
#include "ui_payment_proof.h"

payment_proof::payment_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment_proof)
{
    ui->setupUi(this);
}

payment_proof::~payment_proof()
{
    delete ui;
}

void payment_proof::on_pushButton_clicked()
{
    this->close();
}
