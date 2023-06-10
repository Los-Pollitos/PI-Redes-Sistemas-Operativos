#include "manage_user.h"
#include "ui_manage_user.h"

#include <vector>
#include <fstream>
#include <string>
#include <QMessageBox>

manage_user::manage_user(QWidget *parent) :
    QDialog(parent), ui(new Ui::manage_user) {
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
    this->ui->create_username->setStyleSheet("color: #001f21;");
    this->ui->create_id->setStyleSheet("color: #001f21;");
    this->ui->create_name->setStyleSheet("color: #001f21;");
    this->ui->create_password->setStyleSheet("color: #001f21;");
    this->ui->first_rh_password->setStyleSheet("color: #001f21;");
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
    std::string inserted_password = this->ui->first_rh_password->text().toStdString();
    if (inserted_password == this->user_login->password) {
        // The password is correct, get the desired user to be created
        std::string desired_user = this->ui->create_username->text().toStdString();
        std::string desired_password = this->ui->create_password->text().toStdString();
        std::string id = this->ui->create_id->text().toStdString();
        std::string name = this->ui->create_name->text().toStdString();
        if (desired_user != this->user_login->user) {
            // Send the information to the intermediary to handle it
            std::string first_result = this->send_create(desired_user, desired_password, id, name, '1');
            std::string second_result = this->send_create(desired_user, desired_password, id, name, '2');
            if (first_result[0] == '1' && second_result[0] == '1') {
                // Success
                this->show_success("Se logró crear el usuario de manera exitosa");
            } else {
                // Error
                this->show_error("No se logró crear el usuario");
            }
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

std::string manage_user::send_create(std::string username, std::string password, std::string identification, std::string name, char server) {
    std::string to_send = "";
    to_send += ((char)CREATE_USER);
    to_send += server;
    to_send += this->user_login->user;
    to_send += ",";
    to_send += username;
    to_send += ",";
    if (server == '1') {
        // Data base
        to_send += identification;
        to_send += ",";
        to_send += name;
        to_send += ",";
    } else {
        // Login
        // Hash the password
        security hasher;
        to_send += hasher.hash_string(password);
        to_send += ",";
    }

    std::cout << "TO SEND: " << to_send << "\n";

    return this->local_client->send_and_receive(to_send);
}

std::string manage_user::send_delete(std::string username, char server) {
    std::string to_send = "";
    to_send += ((char)DELETE_USER);
    to_send += server;
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
            std::string first_result = this->send_delete(desired_user, '1');
            std::string second_result = this->send_delete(desired_user, '2');
            if (first_result[0] == '1' && second_result[0] == '1') {
                this->show_success("Se logró eliminar el usuario");
            } else {
                this->show_error("No se logró eliminar el usuario");
            }
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
