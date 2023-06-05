#include "work_proof.h"
#include "ui_work_proof.h"

work_proof::work_proof(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::work_proof)
{
    ui->setupUi(this);
    this->setWindowTitle("Constancia laboral");
}

work_proof::~work_proof() {
    if (this->ui) {
        delete ui;
        this->ui = 0;
     }
}

void work_proof::set_client(client* local_client){
     this->local_client = local_client;
}

void work_proof::on_pushButton_clicked()
{
    this->close();
}
