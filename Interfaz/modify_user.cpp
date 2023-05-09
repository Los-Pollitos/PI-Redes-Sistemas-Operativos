#include "modify_user.h"
#include "ui_modify_user.h"
#include <fstream>

#include <iostream>  // TODO(Angie): borrar

#include <QCheckBox>
#include <QMessageBox>

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    modified_index = -1;
    ui->setupUi(this);
}

modify_user::~modify_user() {
    delete ui;
}

void modify_user::on_comboBox_activated(int index) {
    modified_index = index;
    // TODO(nosotros): rellenar info de usuarios con cantidad de usuarios real
    ui->employee_id->setReadOnly(true);
    ui->employee_id->setText(QString::number(this->ids[index]));
   //  ui->employee_job->setText(this->job[index]);
    ui->employee_salary->setText(this->salary[index]);
    ui->employee_vacations->setText(QString::number(this->vacations[index]));
    ui->record->setPlainText(this->record[index]);
}

void modify_user::read_data() {
    std::ifstream data ("../Etapa 2/Archivos/Data.txt");
    // TODO(nosotros): try catch
    int i = 0;
    std::string temp = " ";
    if (data.is_open()) {
        while(data) {
            users_data.push_back(user_data());
            data >> users_data[i].user;
            data >> temp;

            while (temp[0] < 48 || temp[0] > 58) {
                users_data[i].name.append(" ");
                users_data[i].name.append(temp);
                data >> temp;
            }

            // va a salir con la identificacion
            users_data[i].identification = std::stoi(temp);
            data >> users_data[i].salary;
            data >> users_data[i].role;
            data >> temp; // son las vacaciones asignadas, no se necesitan
            data >> users_data[i].available_vacations;
            ++i;
            temp = " ";  // reinicia el valor
        }
        data.close();
    }
}

void modify_user::add_data() {
    for (size_t i = 0; i < users_data.size(); ++i) {
        // un usuario no se puede modificar a sí mismo
        if (this->users_data[i].user != this->user_login->user) {

            // TODO(Angie): borrar
            std::cout << "estoy en el for, i = " << i << std::endl;

            ui->comboBox->addItem(QString::fromStdString(this->users_data[i].name));
            this->ids.append(this->users_data[i].identification);
            ui->checkbox_admin_users->setCheckState(unmask_role(i, ADMIN_USER));
            ui->checkbox_admin_config->setCheckState(unmask_role(i, ADMIN_CONFIG));
            ui->checkbox_debug->setCheckState(unmask_role(i, DEBUG));
            ui->checkbox_employee->setCheckState(unmask_role(i, EMPLOYEE));
            ui->checkbox_human_resources->setCheckState(unmask_role(i, HUMAN_RESOURCES));
            ui->checkbox_supervisor->setCheckState(unmask_role(i, SUPERVISOR));
            this->salary.append(QString::fromStdString(this->users_data[i].salary));
            this->vacations.append(this->users_data[i].available_vacations);
            // TODO(nosotros): record (no es requerido para esta entrega)
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
    this->role_admin_config[modified_index] = ui->checkbox_admin_config->checkState();
    this->role_admin_users[modified_index] = ui->checkbox_admin_users->checkState();
    this->role_employee[modified_index] = ui->checkbox_employee->checkState();
    this->role_human_resources[modified_index] = ui->checkbox_human_resources->checkState();
    this->role_debug[modified_index] = ui->checkbox_debug->checkState();
    this->supervisor[modified_index] = ui->checkbox_supervisor->checkState();
    this->salary[modified_index] = ui->employee_salary->text();
    this->vacations[modified_index] = ui->employee_vacations->text().toInt();
    // TODO(nosotros): record (no es requerido para esta entrega)
}

void modify_user::set_login_info(login_info* info) {
    this->user_login = info;
    this->read_data();
    this->add_data();
}
