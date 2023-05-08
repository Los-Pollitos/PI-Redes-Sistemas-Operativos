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
    ui->setupUi(this);
}

manage_user::~manage_user() {
    delete ui;
}

void manage_user::set_user_data(login_info* user_data) {
    this->user_data = user_data;
}

bool manage_user::find_user(std::string& desired_username) {
    bool answer = false;
    std::ifstream file ("../Etapa 2/Archivos/Login.txt");
    std::string read_data = "";
    if (file.is_open()) {
        while (!answer) {
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

        file.close();
    }
}

void manage_user::on_generate_button_clicked() {
    // Get password from text
    QString inserted_password = ui->first_rh_password->text();
    if (inserted_password.toStdString() == user_data->password) {
        // Store the inserted username
        std::string desired_user = ui->create_username->text().toStdString();
        std::string desired_password = ui->create_password->text().toStdString();
        // Find out if the username is new
        if(!this->find_user(desired_user)) {
            this->insert_user(desired_user, desired_password);
        } else {
            QMessageBox::warning(this, "Error", "Este usuario ya existe");
        }
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}

void manage_user::on_delete_button_clicked() {
    // Get password from text
    QString inserted_password = ui->second_rh_password->text();
    if (inserted_password.toStdString() == user_data->password) {
        std::cout << "Exitos\n";
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}

