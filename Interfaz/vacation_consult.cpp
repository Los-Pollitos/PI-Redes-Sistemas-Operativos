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
    // Setup the window
    // Obtain information from server
}

void vacation_consult::setup_window() {

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
    this->obtain_from_server();
}

vacation_consult::~vacation_consult() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}
