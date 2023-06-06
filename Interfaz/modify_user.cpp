#include "modify_user.h"
#include "ui_modify_user.h"

#include <fstream>
#include <iostream>
#include <QCheckBox>
#include <QMessageBox>

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    this->modified_index = -1;
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->approve_changes->setStyleSheet("color: #001f21;");
    this->ui->base_salary->setStyleSheet("color: #001f21;");
    this->ui->duductions->setStyleSheet("color: #001f21;");
    this->ui->email->setStyleSheet("color: #001f21;");
    this->ui->employee->setStyleSheet("color: #001f21;");
    this->ui->id->setStyleSheet("color: #001f21;");
    this->ui->job_title->setStyleSheet("color: #001f21;");
    this->ui->label_10->setStyleSheet("color: #001f21;");
    this->ui->label_11->setStyleSheet("color: #001f21;");
    this->ui->label_12->setStyleSheet("color: #001f21;");
    this->ui->label_13->setStyleSheet("color: #001f21;");
    this->ui->label_14->setStyleSheet("color: #001f21;");
    this->ui->label_3->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");
    this->ui->label_5->setStyleSheet("color: #001f21;");
    this->ui->label_6->setStyleSheet("color: #001f21;");
    this->ui->label_7->setStyleSheet("color: #001f21;");
    this->ui->label_9->setStyleSheet("color: #001f21;");
    this->ui->net_salary->setStyleSheet("color: #001f21;");
    this->ui->office->setStyleSheet("color: #001f21;");
    this->ui->password->setStyleSheet("color: #001f21;");
    this->ui->phone->setStyleSheet("color: #001f21;");
    this->ui->password->setStyleSheet("color: #001f21;");
    this->ui->record->setStyleSheet("color: #001f21;");
    this->ui->checkbox_active->setStyleSheet("color: #001f21;");
    this->ui->checkbox_admin_config->setStyleSheet("color: #001f21;");
    this->ui->checkbox_admin_users->setStyleSheet("color: #001f21;");
    this->ui->checkbox_debug->setStyleSheet("color: #001f21;");
    this->ui->checkbox_employee->setStyleSheet("color: #001f21;");
    this->ui->checkbox_human_resources->setStyleSheet("color: #001f21;");
    this->ui->checkbox_supervisor->setStyleSheet("color: #001f21;");
    this->ui->comboBox->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Modificar usuarios");
}

modify_user::~modify_user() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

// TODO(Angie): modificar
void modify_user::on_comboBox_activated(int index) {
//    this->modified_index = index;
//    ui->id->setReadOnly(true);
//    ui->id->setText(QString::number(this->users_data[index].identification));
//    ui->salary->setText(QString::fromStdString(this->users_data[index].salary));
//    ui->checkbox_admin_users->setCheckState(unmask_role(index, ADMIN_USER));
//    ui->checkbox_admin_config->setCheckState(unmask_role(index, ADMIN_CONFIG));
//    ui->checkbox_debug->setCheckState(unmask_role(index, DEBUG));
//    ui->checkbox_employee->setCheckState(unmask_role(index, EMPLOYEE));
//    ui->checkbox_human_resources->setCheckState(unmask_role(index, HUMAN_RESOURCES));
//    ui->checkbox_supervisor->setCheckState(unmask_role(index, SUPERVISOR));
//    ui->vacations->setText(QString::number(this->users_data[index].available_vacations));
}

// TODO(Angie): ver si dejar igual
// Método que va a agregar los usuarios al comboBox
void modify_user::add_data_to_combobox() {
    // find the user's office id
    std::string to_send = "0" + this->user_info.user;
    to_send[0] = USER_OFFICE;
    std::string data_received = this->local_client->send_and_receive(to_send);

    // find all the users of an office
    to_send = "01";
    to_send[0] = ALL_USERS_OFFICE;
    to_send[1] = data_received[0];  // data_received[0] is a char that represents the office_id
    data_received = this->local_client->send_and_receive(to_send);

    // store the usernames individually
    std::string new_user = "\0";
    for(size_t i = 0; i < data_received.length(); ++i) {
        if (data_received[i] != ',') {
            new_user += data_received[i];
        } else {  // is the end of the username
            if (new_user != this->user_info.user) {  // an user cannot modify itself
                this->user_names.push_back(new_user);
            }
            new_user = "\0";  // it is cleaned for next username
        }
    }

    // add the users to the comboBox
    for (size_t i = 0; i < user_names.size(); ++i) {
        ui->comboBox->addItem(QString::fromStdString(this->user_names[i]));
    }
}

// role indicates the role that wants to be analized if the user has
Qt::CheckState modify_user::unmask_role(int user_index, char role) {
    Qt::CheckState state = Qt::Unchecked;

    // TODO(Angie): actualizar
//    if ((role & this->users_data[user_index].role) == role) {
//        state = Qt::Checked;
//    }

    return state;
}

void modify_user::on_approve_changes_clicked() {
    QString password = ui->password->text();
    if (password.toStdString() == this->user_login->password) {
        QMessageBox::information(this, "Correcto", "Cambios aplicados");
        this->update_data();
    } else {
        QMessageBox::warning(this, "Error", "Contraseña incorrecta");
    }
}

void modify_user::update_data() {
    // TODO(Angie): modificar
//    users_data[modified_index].role = 0;
//    // if the user is Debug, it can not have more roles
//    if (ui->checkbox_debug->checkState() == 2) {  // the 2 indicates the user has that role
//        users_data[modified_index].role = DEBUG;
//        ui->checkbox_admin_users->setCheckState(unmask_role(modified_index, ADMIN_USER));
//        ui->checkbox_admin_config->setCheckState(unmask_role(modified_index, ADMIN_CONFIG));
//        ui->checkbox_employee->setCheckState(unmask_role(modified_index, EMPLOYEE));
//        ui->checkbox_human_resources->setCheckState(unmask_role(modified_index, HUMAN_RESOURCES));
//        ui->checkbox_supervisor->setCheckState(unmask_role(modified_index, SUPERVISOR));
//    } else {
//        if (ui->checkbox_admin_config->checkState() == 2) {
//            users_data[modified_index].role |= ADMIN_CONFIG;
//        }
//        if (ui->checkbox_admin_users->checkState() == 2) {
//            users_data[modified_index].role |= ADMIN_USER;
//        }
//        if (ui->checkbox_employee->checkState() == 2) {
//            users_data[modified_index].role |= EMPLOYEE;
//        }
//        if (ui->checkbox_human_resources->checkState() == 2) {
//            users_data[modified_index].role |= HUMAN_RESOURCES;
//        }
//        if (ui->checkbox_supervisor->checkState() == 2) {
//            users_data[modified_index].role |= SUPERVISOR;
//        }
//        if (ui->checkbox_debug->checkState() == 2) {
//            users_data[modified_index].role |= DEBUG;
//        }
//    }

//    this->users_data[modified_index].salary = ui->salary->text().toStdString();
//    this->users_data[modified_index].available_vacations = ui->vacations->text().toInt();
//    // TODO(nosotros): record (no es requerido para esta entrega)

//    this->write_data();
}

void modify_user::set_login_info(login_info* info) {
    this->user_login = info;
}

void modify_user::set_client(client* local_client) {
    this->local_client = local_client;
}
