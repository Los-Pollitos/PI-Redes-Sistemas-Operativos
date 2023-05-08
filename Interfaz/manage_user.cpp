#include "manage_user.h"
#include "ui_manage_user.h"

//TODO(Luis): borrar
#include <iostream>
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

void manage_user::on_generate_button_clicked() {
    // Get password from text
    QString inserted_password = ui->first_rh_password->text();
    if (inserted_password.toStdString() == user_data->password) {
        std::cout << "Exitos\n";
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}

void manage_user::on_delete_button_clicked() {
    // Get password from text
    QString inserted_password = ui->first_rh_password->text();
    if (inserted_password.toStdString() == user_data->password) {
        std::cout << "Exitos\n";
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}

