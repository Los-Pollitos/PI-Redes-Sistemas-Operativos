#include "modify_user.h"
#include "ui_modify_user.h"
#include <fstream>

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
    ui->employee_salary->setText(QString::number(this->salary[index]));
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
            while (temp[0] < 48 && temp[0] > 58) {
                users_data[i].name.append(" ");
                users_data[i].name.append(temp);
                data >> temp;
            }
            // va a salir con la identificacion
            users_data[i].identification = stoi(temp);
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
    for (int i = 0; i < int(users_data.size()); ++i) {
        // un usuario no se puede modificar a sí mismo
        if (this->users_data[i].user != this->user_login->user) {
            ui->comboBox->addItem(QString::fromStdString(this->users_data[i].name));
            this->ids.append(this->users_data[i].identification);
            // TODO(Angie): this->job.append("Trabajo1");
            this->salary.append(QString::fromStdString(this->users_data[i].salary));
            this->vacations.append(this->users_data[i].available_vacations);
            // record no es requerido para esta entrega
        }
    }
    
}

// role indicates the role that wants to be analized if the user has
bool modify_user::mask_role(int user_index, int role) {
    bool has_role = false;
    if ((role & this->users_data[user_index].role) == role) {
        has_role = true;
    }
    return has_role;
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
    // this->job[modified_index] = ui->employee_job->text();
    this->salary[modified_index] = ui->employee_salary->text().toInt();
    this->vacations[modified_index] = ui->employee_vacations->text().toInt();
}

void modify_user::set_login_info(login_info* info) {
    this->user_login = info;
    this->add_data();
    this->read_data();
}
