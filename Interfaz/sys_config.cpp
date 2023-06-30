#include "sys_config.h"
#include "ui_sys_config.h"

sys_config::sys_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sys_config) {
    ui->setupUi(this);
    // Set the window name and colors
    this->setWindowTitle("Modificar configuración del sistema");
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->client_ip->setStyleSheet("color: #001f21;");
    this->ui->client_port->setStyleSheet("color: #001f21;");
    this->ui->inter_ip->setStyleSheet("color: #001f21;");
    this->ui->inter_port->setStyleSheet("color: #001f21;");
    this->ui->file_system_ip->setStyleSheet("color: #001f21;");
    this->ui->file_system_port->setStyleSheet("color: #001f21;");
    this->ui->data_base_ip->setStyleSheet("color: #001f21;");
    this->ui->data_base_port->setStyleSheet("color: #001f21;");
    this->ui->password_insert->setStyleSheet("color: #001f21;");
    // Set the password mode for password_insert
    this->ui->password_insert->setEchoMode(QLineEdit::Password);
}

sys_config::~sys_config() {
    delete ui;
}

void sys_config::set_client(client* local_client){
    this->local_client = local_client;
}

void sys_config::set_user_login(login_info* user_login) {
    this->user_login = user_login;
}
