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
    std::string envio = "";
    envio += ((char)SALARY_CONSULT);
    envio += this->user_login->user;
    envio += ",";
    std::string result = local_client->send_and_receive(envio);
    std::string name = "";
    std::string id = "";
    std::string gross_salary = "";
    std::string net_salary = "";
    int temp = 0;
    for (int i = 1; i < result.length(); ++i){
        if (result[i] == ';') {
            ++temp;
        } else {
            switch (temp) {
                case 0:
                    name += result[i];
                    break;
                case 1:
                    id += result[i];
                    break;
                case 2:
                    gross_salary += result[i];
                    break;
                case 3:
                    net_salary += result[i];
                    break;
            }

        }
    }
    security security_manager;

    std::cout << gross_salary << std::endl;
    std::cout << net_salary << std::endl;

    gross_salary = security_manager.decrypt(gross_salary);
    net_salary = security_manager.decrypt(net_salary);
    this->ui->name->setText(QString::fromStdString(name));
    this->ui->id->setText(QString::fromStdString(id));
    this->ui->base_salary->setText("₡" + QString::fromStdString(gross_salary));
    this->ui->salary->setText("₡" + QString::fromStdString(net_salary));
}

consult_salary::~consult_salary()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}
