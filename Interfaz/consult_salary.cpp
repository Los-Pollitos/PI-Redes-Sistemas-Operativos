#include "consult_salary.h"
#include "ui_consult_salary.h"

consult_salary::consult_salary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_salary)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->name_label->setStyleSheet("color: #001f21;");
    this->ui->name->setStyleSheet("color: #001f21;");
    this->ui->id_label->setStyleSheet("color: #001f21;");
    this->ui->id->setStyleSheet("color: #001f21;");
    this->ui->base_salary_label->setStyleSheet("color: #001f21;");
    this->ui->base_salary->setStyleSheet("color: #001f21;");
    this->ui->salary_label->setStyleSheet("color: #001f21;");
    this->ui->salary->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Consultar Salario Bruto");
    ui->base_salary->setReadOnly(true);
    ui->salary->setReadOnly(true);
    ui->id->setReadOnly(true);
    ui->name->setReadOnly(true);
    this->user_login = new login_info();
    this->local_client = new client();
}

void consult_salary::set_client(client* local_client){
    this->local_client = local_client;
}

void consult_salary::setUserData(login_info * user_login) {
    this->user_login = user_login;
    std::cout << "Entrando... 1" << std::endl;
    std::string envio = "";
    envio += ((char)SALARY_CONSULT);
    envio += this->user_login->user;
    std::cout << "Entrando... 2" << std::endl;
    std::string result = local_client->send_and_receive(envio);
    std::cout << "Entrando... 3" << std::endl;
}

consult_salary::~consult_salary()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}
