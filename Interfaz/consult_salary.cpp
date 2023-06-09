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
    this->setWindowTitle("Consultar Salario");
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
    std::string gross = "";
    std::string net = "";

    gross_salary += ";";
    for (int i = 0; i < gross_salary.length() && gross_salary[i] != ';'; ++i) {
        if (gross_salary[i] != ',') {
            if (gross_salary[i+1] == ',') {
                gross += (char)(gross_salary[i]-48);
            } else if (gross_salary[i+2] == ','){
                gross += (char)(((int)gross_salary[i]) - 48)*10 +(((int)gross_salary[i+1]) - 48);
                ++i; // ignore i+1
            } else {
                gross += (char)(((int)gross_salary[i] - 48)*100 + ((int)gross_salary[i+1] -48)*10 - +(((int)gross_salary[i+2] -48)));
                i+=2; // ignore i+2
            }
            // next one would be a ,
            i++;
        }
    }

    std::cout << gross << std::endl;
    gross_salary = security_manager.decrypt(gross);

    net_salary += ";";
    std::cout << " net antes del for " << net_salary << std::endl;
    for (int i = 0; i < net_salary.length() && net_salary[i] != ';'; ++i) {
        if (net_salary[i] != ',') {
            if (net_salary[i+1] == ',') {
                net += (char)(net_salary[i]-48);
            } else if (net_salary[i+2] == ','){
                net += (char)(((int)net_salary[i]) - 48)*10 +(((int)net_salary[i+1]) - 48);
                ++i; // ignore i+1
            } else {
                net += (char)(((int)net_salary[i] - 48)*100 + ((int)net_salary[i+1] -48)*10 - +(((int)net_salary[i+2] -48)));
                i+=2; // ignore i+2
            }
            // next one would be a ,
            i++;
        }
    }

    std::cout << net << std::endl;

    net_salary = security_manager.decrypt(net);

    std::cout << gross_salary << std::endl;
    std::cout << net_salary << std::endl;

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
