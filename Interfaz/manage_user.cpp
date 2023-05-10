#include "manage_user.h"
#include "ui_manage_user.h"

#include <fstream>
#include <string>
//TODO(Luis): borrar
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <QMessageBox>

manage_user::manage_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manage_user) {
    this->ui->setupUi(this);
    // Hide passwords
    this->ui->first_rh_password->setEchoMode(QLineEdit::Password);
    this->ui->second_rh_password->setEchoMode(QLineEdit::Password);
    this->ui->create_password->setEchoMode(QLineEdit::Password);
}

manage_user::~manage_user() {
    delete this->ui;
}

void manage_user::set_user_login(login_info* user_login) {
    this->user_login = user_login;
}

bool manage_user::find_user(std::string& desired_username) {
    bool answer = false;
    std::ifstream file ("../Etapa 2/Archivos/Login.txt");
    std::string read_data = "";
    if (file.is_open()) {
        // While there is something to read and not an answer
        while (!file.eof() && !answer) {
            file >> read_data;
            if (read_data == desired_username) {
                answer = true;
            }
        }
        file.close();
    }
    return answer;
}

void manage_user::insert_user(std::string& desired_username, std::string& desired_password) {
    // Open file to append to it;
    std::ofstream file("../Etapa 2/Archivos/Login.txt", std::ofstream::app);
    if (file.is_open()) {
        // Insert username and password
        file << desired_username << '\t' << desired_password << '\t';
        // Generate token
        int number = 0;
        for (int i = 0; i < TOKEN_SIZE - 2; ++i) {
            number = (int)(rand()%100);
            file << std::to_string(number) << " ";
        }
        // Last token position
        number = (int)(rand()%100);
        file << std::to_string(number) << "\n";
        file.close();
    }
}

void manage_user::on_generate_button_clicked() {
    // Get password from text
    QString inserted_password = this->ui->first_rh_password->text();
    if (inserted_password.toStdString() == user_login->password) {
        // Store the inserted username
        std::string desired_user = this->ui->create_username->text().toStdString();
        std::string desired_password = this->ui->create_password->text().toStdString();
        // Find out if the username is new
        if(!this->find_user(desired_user)) {
            this->insert_user(desired_user, desired_password);
            QMessageBox success;
            success.setText("Usuario creado de manera exitosa");
            success.exec();
        } else {
            QMessageBox::warning(this, "Error", "Este usuario ya existe");
        }
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
    // Clear the text boxes
    this->ui->first_rh_password->clear();
    this->ui->create_username->clear();
    this->ui->create_password->clear();
}

void manage_user::reinsert_file() {
    std::ifstream aux_file("../Etapa 2/Archivos/file.aux");
    // Truncate the file
    std::ofstream main_file("../Etapa 2/Archivos/Login.txt", std::fstream::trunc);
    std::string buffer = "";
    // Store aux file in main file
    while (getline(aux_file, buffer)) {
        buffer.append("\n");
        main_file << buffer;
    }
    aux_file.close();
    main_file.close();
}

void manage_user::delete_user(std::string& desired_username) {
    std::ofstream aux_file("../Etapa 2/Archivos/file.aux");
    std::ifstream main_file("../Etapa 2/Archivos/Login.txt");
    std::string buffer = "";
    // Store file in aux file
    int pos = 0;
    while (getline(main_file, buffer)) {
        pos = buffer.find(desired_username);
        // Store the information avoiding the desired line
        if (pos == -1 || pos != 0) {
            buffer.append("\n");
            aux_file << buffer;
        }
    }
    aux_file.close();
    main_file.close();
    // Reinsert the contents of the file without the deleted user
    this->reinsert_file();
}

void manage_user::on_delete_button_clicked() {
    // Get password from text
    QString inserted_password = this->ui->second_rh_password->text();
    if (inserted_password.toStdString() == this->user_login->password) {
        std::string desired_user = this->ui->delete_username->text().toStdString();
        if (desired_user != this->user_login->user) {
            this->delete_user(desired_user);
            QMessageBox success;
            success.setText("Usuario eliminado de manera exitosa");
            success.exec();
        } else {
            QMessageBox::warning(this, "Error", "No se puede eliminar su propio usuario");
        }
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
    this->ui->second_rh_password->clear();
    this->ui->delete_username->clear();
}

