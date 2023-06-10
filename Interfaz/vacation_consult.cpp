#include "vacation_consult.h"
#include "ui_vacation_consult.h"

vacation_consult::vacation_consult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vacation_consult)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->available_vacations->setStyleSheet("color: #001f21;");
    this->ui->available_vacations_label->setStyleSheet("color: #001f21;");
    this->ui->id->setStyleSheet("color: #001f21;");
    this->ui->id_label->setStyleSheet("color: #001f21;");
    this->ui->name->setStyleSheet("color: #001f21;");
    this->ui->name_label->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Vacaciones disponibles");
    ui->available_vacations->setReadOnly(true);
    ui->id->setReadOnly(true);
    ui->name->setReadOnly(true);
}

std::string vacation_consult::obtain_from_server() {
    std::string to_send = "";
    // Setup the char for the intermediary
    to_send += ((char)CONSULT_VACATION);
    // Add the username to know whose vacation information is desired
    to_send += this->user_login->user;
    // Add a coma to find the end of the username
    to_send += ',';
    return this->local_client->send_and_receive(to_send);
}


void vacation_consult::set_client(client* local_client){
    this->local_client = local_client;
}

void vacation_consult::set_user_login(login_info* user_login) {
    this->user_login = user_login;
    this->show_result(this->obtain_from_server());
}

void vacation_consult::show_result(std::string result) {
    // Obtain the name
    std::string name = "";
    int i = 0;
    for (; result[i] != ','; ++i) {
        name += result[i];
    }
    ++i;
    // Obtain the identification
    std::string identification = "";
    for (; result[i] != ','; ++i) {
        identification += result[i];
    }
    ++i;
    // Obtain the vacation information
    std::string vacations = "";
    for (; result[i] != ','; ++i) {
        vacations += result[i];
    }
    ++i;
    this->ui->name->setText(QString::fromStdString(name));
    this->ui->id->setText(QString::fromStdString(identification));
    this->ui->available_vacations->setText(QString::fromStdString(vacations));
}

vacation_consult::~vacation_consult() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}
