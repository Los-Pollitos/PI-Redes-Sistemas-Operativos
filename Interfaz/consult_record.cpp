#include "consult_record.h"
#include "ui_consult_record.h"

consult_record::consult_record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_record)
{
    ui->setupUi(this);
    this->setWindowTitle("Consultar expediente");
}

consult_record::~consult_record()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
     }
}

void consult_record::set_client(client* local_client){
     this->local_client = local_client;
}
