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
    // Get password from textbox
    std::string inserted_password = this->ui->second_rh_password->text().toStdString();
    if (inserted_password == this->user_login->password) {
        // The password is correct, get the desired user to be created
        std::string desired_user = this->ui->create_username->text().toStdString();
        std::string desired_password = this->ui->create_password->text().toStdString();
        if (desired_user != this->user_login->user) {
            // Send the information to the intermediary to handle it
            this->send_create(desired_user, desired_password, "", "");
        } else {
            // Show the user the error
            this->show_error("No se puede crear su propio usuario");
        }
    } else {
        // Show the user the error
        this->show_error("Por favor inserte su contraseña de manera correcta");
    }
    // Clear the text boxes
    this->ui->first_rh_password->clear();
    this->ui->create_username->clear();
    this->ui->create_password->clear();
    this->ui->create_id->clear();
    this->ui->create_name->clear();
}

std::string manage_user::send_create(std::string username, std::string password, std::string identification, std::string name) {
    security hasher;
    std::string to_send = "\0";
    to_send[0] = ((char)CREATE_USER);
    to_send += username;
    to_send += ",";
    // Hash the password
    to_send += hasher.hash_string(password);
    to_send += ",";
    to_send += identification;
    to_send += ",";
    to_send += name;
    to_send += ",";
    return this->local_client->send_and_receive(to_send);
}

std::string manage_user::send_delete(std::string username) {
    std::string to_send = "\0";
    to_send[0] = ((char)DELETE_USER);
    to_send += username;
    to_send += ",";
    return this->local_client->send_and_receive(to_send);
}

void manage_user::on_delete_button_clicked() {
    // Get password from textbox
    std::string inserted_password = this->ui->second_rh_password->text().toStdString();
    if (inserted_password == this->user_login->password) {
        // The password is correct, get the desired user to delete
        std::string desired_user = this->ui->delete_username->text().toStdString();
        if (desired_user != this->user_login->user) {
            // Send the information to the intermediary to handle it
            this->send_delete(desired_user);
        } else {
            // Show the user the error
            this->show_error("No se puede eliminar su propio usuario");
        }
    } else {
        // Show the user the error
        this->show_error("Por favor inserte su contraseña de manera correcta");
    }
    // Clear the text boxes
    this->ui->second_rh_password->clear();
    this->ui->delete_username->clear();
}

void manage_user::show_error(std::string error) {
    QMessageBox error_message;
    error_message.setText(QString::fromStdString(error));
    error_message.setWindowTitle("Error");
    error_message.setModal(true);
    error_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
    error_message.exec();
}

void manage_user::show_success(std::string success) {
    QMessageBox success_box;
    success_box.setText(QString::fromStdString(success));
    success_box.setWindowTitle("Información");
    success_box.setModal(true);
    success_box.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
    success_box.exec();
}
