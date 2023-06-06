#include "payment_proof.h"
#include "ui_payment_proof.h"

payment_proof::payment_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment_proof)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->pushButton->setStyleSheet("color: #001f21;");
    this->ui->textBrowser->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Comprobante de pago");
}

payment_proof::~payment_proof()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void payment_proof::set_client(client* local_client){
    this->local_client = local_client;
}

void payment_proof::on_pushButton_clicked()
{
    this->close();
}
