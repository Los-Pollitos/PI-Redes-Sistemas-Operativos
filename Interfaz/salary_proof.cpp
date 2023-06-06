#include "salary_proof.h"
#include "ui_salary_proof.h"

salary_proof::salary_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salary_proof)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->pushButton->setStyleSheet("color: #001f21;");
    this->ui->textBrowser->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Constancia salarial");
}

salary_proof::~salary_proof()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void salary_proof::on_pushButton_clicked()
{
    this->close();
}


void salary_proof::set_client(client* local_client){
    this->local_client = local_client;
}
