#include "payment_proof.h"
#include "ui_payment_proof.h"

payment_proof::payment_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment_proof)
{
    ui->setupUi(this);
    this->setWindowTitle("Comprobante de pago");
}

payment_proof::~payment_proof()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void payment_proof::on_pushButton_clicked()
{
    this->close();
}
