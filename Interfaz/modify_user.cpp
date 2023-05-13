#include "modify_user.h"
#include "ui_modify_user.h"

#include <fstream>
#include <iostream>
#include <QCheckBox>
#include <QMessageBox>

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    this->modified_index = -1;
    ui->setupUi(this);
}

modify_user::~modify_user() {
    delete ui;
}

void modify_user::on_comboBox_activated(int index) {
    this->modified_index = index;
    ui->employee_id->setReadOnly(true);
    ui->employee_id->setText(QString::number(this->users_data[index].identification));
    ui->employee_salary->setText(QString::fromStdString(this->users_data[index].salary));
    ui->checkbox_admin_users->setCheckState(unmask_role(index, ADMIN_USER));
    ui->checkbox_admin_config->setCheckState(unmask_role(index, ADMIN_CONFIG));
    ui->checkbox_debug->setCheckState(unmask_role(index, DEBUG));
    ui->checkbox_employee->setCheckState(unmask_role(index, EMPLOYEE));
    ui->checkbox_human_resources->setCheckState(unmask_role(index, HUMAN_RESOURCES));
    ui->checkbox_supervisor->setCheckState(unmask_role(index, SUPERVISOR));
    ui->employee_vacations->setText(QString::number(this->users_data[index].available_vacations));
}


void modify_user::write_data() {
    std::ofstream file("../Etapa2/Archivos/Data.txt", std::ofstream::out);
    if (file.is_open()) {
        for (size_t i = 0; i < users_data.size(); ++i) {
            file << this->users_data[i].user << "\t";
            file << this->users_data[i].name << "\t";
            file << this->users_data[i].identification << "\t";
            file << this->users_data[i].salary << "\t";
            file << this->users_data[i].role << "\t";
            file << this->users_data[i].assigned_vacations << "\t";
            file << this->users_data[i].available_vacations << "\n";
        }
        file.close();
    }
}

void modify_user::add_data() {
    for (size_t i = 0; i < users_data.size(); ++i) {
        // un usuario no se puede modificar a sí mismo
        if (this->users_data[i].user != this->user_login->user) {
            ui->comboBox->addItem(QString::fromStdString(this->users_data[i].name));
        }
    }
}

// role indicates the role that wants to be analized if the user has
Qt::CheckState modify_user::unmask_role(int user_index, int role) {
    Qt::CheckState state = Qt::Unchecked;
    if ((role & this->users_data[user_index].role) == role) {
        state = Qt::Checked;
    }
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
    users_data[modified_index].role = 0;
    // si el usuario es Debug, no puede tener más roles
    if (ui->checkbox_debug->checkState() == 2) {
        users_data[modified_index].role = DEBUG;
        ui->checkbox_admin_users->setCheckState(unmask_role(modified_index, ADMIN_USER));
        ui->checkbox_admin_config->setCheckState(unmask_role(modified_index, ADMIN_CONFIG));
        ui->checkbox_employee->setCheckState(unmask_role(modified_index, EMPLOYEE));
        ui->checkbox_human_resources->setCheckState(unmask_role(modified_index, HUMAN_RESOURCES));
        ui->checkbox_supervisor->setCheckState(unmask_role(modified_index, SUPERVISOR));
    } else {
        if (ui->checkbox_admin_config->checkState() == 2) {  // significa que tiene ese rol
            users_data[modified_index].role |= ADMIN_CONFIG;
        }
        if (ui->checkbox_admin_users->checkState() == 2) {
            users_data[modified_index].role |= ADMIN_USER;
        }
        if (ui->checkbox_employee->checkState() == 2) {
            users_data[modified_index].role |= EMPLOYEE;
        }
        if (ui->checkbox_human_resources->checkState() == 2) {
            users_data[modified_index].role |= HUMAN_RESOURCES;
        }
        if (ui->checkbox_supervisor->checkState() == 2) {
            users_data[modified_index].role |= SUPERVISOR;
        }
        if (ui->checkbox_debug->checkState() == 2) {
            users_data[modified_index].role |= DEBUG;
        }
    }

    this->users_data[modified_index].salary = ui->employee_salary->text().toStdString();
    this->users_data[modified_index].available_vacations = ui->employee_vacations->text().toInt();
    // TODO(nosotros): record (no es requerido para esta entrega)

    this->write_data();
}

void modify_user::set_login_info(login_info* info) {
    this->user_login = info;
    this->read_data();
    this->add_data();
}

void modify_user::read_data() {
    std::ifstream data ("../Etapa2/Archivos/Data.txt");
    try {
        int i = 0;
        std::string temp = " ";
        if (data.is_open()) {
            while(data >> temp) {
                users_data.push_back(user_data());
                users_data[i].user = temp;
                users_data[i].name = "";  // se limpia
                data >> temp;

                while (temp[0] < 48 || temp[0] > 58) {  // no es un número
                    users_data[i].name.append(temp);
                    users_data[i].name.append(" ");
                    data >> temp;
                }

                // va a salir con la identificacion
                users_data[i].identification = std::stoi(temp);
                data >> users_data[i].salary;
                data >> users_data[i].role;
                data >> users_data[i].assigned_vacations;
                data >> users_data[i].available_vacations;
                ++i;
                temp = " ";  // reinicia el valor
            }
            data.close();
        }
    } catch (const std::runtime_error& exception) {
      std::cerr << exception.what() << std::endl;
    }

}
