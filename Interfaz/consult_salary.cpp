#include "consult_salary.h"
#include "ui_consult_salary.h"

consult_salary::consult_salary(QWidget *parent) :
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
    // Nota: se lo comenté porque con esto crasheaba
//    std::string envio = "";
//    envio += ((char)PAYMENT_PROOF);
//    envio += this->users_data->user;
//    std::string result = local_client->send_and_receive(envio);
}

void consult_salary::setUserData(login_info * user_login, user_data* users_data) {
    this->users_data = users_data;
    this->user_login = user_login;
}

consult_salary::~consult_salary()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}
