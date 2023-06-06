#include "consult_salary.h"
#include "ui_consult_salary.h"

consult_salary::consult_salary(QWidget *parent, user_data* users_data) :
    QDialog(parent),
    ui(new Ui::consult_salary)
{
    ui->setupUi(this);
    this->setWindowTitle("Consultar Salario Base");
    ui->base_salary->setReadOnly(true);
    ui->salary->setReadOnly(true);
    ui->id->setReadOnly(true);
    ui->name->setReadOnly(true);
    this->users_data = users_data;
}

void consult_salary::set_client(client* local_client){
    this->local_client = local_client;
    std::string envio = ((char)PAYMENT_PROOF);
    envio += this->users_data->user;
    std::string result = local_client->send_and_receive(envio);
}

consult_salary::~consult_salary()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}
