#include "manage_user.h"
#include "ui_manage_user.h"

#include <vector>
#include <fstream>
#include <string>
#include <QMessageBox>

manage_user::manage_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manage_user) {
    this->ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->label_2->setStyleSheet("color: #001f21;");
    this->ui->label_3->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");
    this->ui->label_5->setStyleSheet("color: #001f21;");
    this->ui->user_name_text->setStyleSheet("color: #001f21;");
    this->ui->user_name_text_2->setStyleSheet("color: #001f21;");
    this->ui->user_name_text_3->setStyleSheet("color: #001f21;");
    this->ui->create_id->setStyleSheet("color: #001f21;");
    this->ui->create_name->setStyleSheet("color: #001f21;");
    this->ui->create_password->setStyleSheet("color: #001f21;");
    this->ui->second_rh_password->setStyleSheet("color: #001f21;");
    this->ui->delete_username->setStyleSheet("color: #001f21;");
    this->ui->user_password_text->setStyleSheet("color: #001f21;");
    this->ui->generate_button->setStyleSheet("color: #001f21;");
    this->ui->delete_button->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Administrar usuarios");
    // Hide passwords
    this->ui->first_rh_password->setEchoMode(QLineEdit::Password);
    this->ui->second_rh_password->setEchoMode(QLineEdit::Password);
    this->ui->create_password->setEchoMode(QLineEdit::Password);
}

void manage_user::set_client(client* local_client){
    this->local_client = local_client;
}

void manage_user::set_user_login(login_info* user_login) {
    this->user_login = user_login;
}

manage_user::~manage_user() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void manage_user::on_generate_button_clicked() {

}

void manage_user::on_delete_button_clicked() {

}
