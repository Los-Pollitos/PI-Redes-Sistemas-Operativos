#include "consult_record.h"
#include "ui_consult_record.h"

consult_record::consult_record(QWidget *parent) : QDialog(parent), ui(new Ui::consult_record) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->setWindowTitle("Consultar expediente");
    this->ui->title->setStyleSheet("color: #001f21;");
    this->local_client = 0;
    this->user_login = 0;
}

consult_record::~consult_record() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void consult_record::set_client(client* local_client){
    this->local_client = local_client;
}

void consult_record::set_user_login(login_info* user_login) {
    this->user_login = user_login;
}

void consult_record::show_record() {
    std::string to_send = " " + this->user_login->user;
    this->ui->plainTextEdit->setPlainText(QString::fromStdString(this->local_client->send_and_receive(to_send)));
    this->ui->plainTextEdit->setReadOnly(true);
}
