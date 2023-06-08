#include "modify_user.h"
#include "ui_modify_user.h"

#include <fstream>
#include <iostream>
#include <QCheckBox>
#include <QMessageBox>

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->approve_changes->setStyleSheet("color: #001f21;");
    this->ui->base_salary->setStyleSheet("color: #001f21;");
    this->ui->deductions->setStyleSheet("color: #001f21;");
    this->ui->email->setStyleSheet("color: #001f21;");
    this->ui->employee->setStyleSheet("color: #001f21;");
    this->ui->id->setStyleSheet("color: #001f21;");
    this->ui->job_title->setStyleSheet("color: #001f21;");
    this->ui->label_8->setStyleSheet("color: #001f21;");
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
    this->ui->label_15->setStyleSheet("color: #001f21;");
    this->ui->net_salary->setStyleSheet("color: #001f21;");
    this->ui->office->setStyleSheet("color: #001f21;");
    this->ui->password->setStyleSheet("color: #001f21;");
    this->ui->name->setStyleSheet("color: #001f21;");
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

void modify_user::on_comboBox_activated(int index) {
    // obtain the user's data
    this->user_info.user = this->user_names[index];
    std::string to_send = "0" + this->user_names[index];
    to_send[0] = DATA_USER;
    std::string data_received = this->local_client->send_and_receive(to_send);
    // data_received tiene el formato definido en el datagrama
    this->load_user_data(data_received);

    // if the user was fired, noting can't be changed
    if(unmask_role(UNEMPLOYEED, this->user_info.role) == Qt::Unchecked) {
        ui->checkbox_active->setCheckState(unmask_role(index, UNEMPLOYEED));
        this->set_read_only();
    }

    // set the data in the ui
    int office_id = (int) this->user_info.office_id;
    ui->name->setReadOnly(true);
    ui->name->setText(QString::fromStdString(this->user_info.name));
    ui->id->setReadOnly(true);
    ui->id->setText(QString::fromStdString(this->user_info.identification));
    ui->phone->setText(QString::fromStdString(this->user_info.phone));
    ui->email->setText(QString::fromStdString(this->user_info.email));
    ui->office->setText(QString::number(office_id));
    ui->checkbox_admin_users->setCheckState((unmask_role(ADMIN_USER, this->user_info.role) == Qt::Checked) ? Qt::Unchecked : Qt::Checked);
    ui->checkbox_admin_users->setCheckState(unmask_role(ADMIN_USER, this->user_info.role));
    ui->checkbox_admin_config->setCheckState(unmask_role(ADMIN_CONFIG, this->user_info.role));
    ui->checkbox_debug->setCheckState(unmask_role(DEBUG, this->user_info.role));
    ui->checkbox_employee->setCheckState(unmask_role(EMPLOYEE, this->user_info.role));
    ui->checkbox_human_resources->setCheckState(unmask_role(HUMAN_RESOURCES, this->user_info.role));
    ui->checkbox_supervisor->setCheckState(unmask_role(SUPERVISOR, this->user_info.role));
    ui->job_title->setText(QString::fromStdString(this->user_info.job_title));
    ui->base_salary->setText(QString::number(this->user_info.salary_base));
    ui->deductions->setText(QString::number(this->user_info.deductibles));
    ui->net_salary->setReadOnly(true);
    ui->net_salary->setText(QString::number(this->user_info.salary_net));
}

void modify_user::set_read_only() {
    // read only the other roles
    ui->checkbox_admin_config->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkbox_admin_config->setFocusPolicy(Qt::NoFocus);
    ui->checkbox_admin_users->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkbox_admin_users->setFocusPolicy(Qt::NoFocus);
    ui->checkbox_employee->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkbox_employee->setFocusPolicy(Qt::NoFocus);
    ui->checkbox_debug->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkbox_debug->setFocusPolicy(Qt::NoFocus);
    ui->checkbox_human_resources->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkbox_human_resources->setFocusPolicy(Qt::NoFocus);
    ui->checkbox_supervisor->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->checkbox_supervisor->setFocusPolicy(Qt::NoFocus);

    // read only the text edits
    ui->name->setReadOnly(true);
    ui->id->setReadOnly(true);
    ui->phone->setReadOnly(true);
    ui->email->setReadOnly(true);
    ui->office->setReadOnly(true);
    ui->job_title->setReadOnly(true);
    ui->base_salary->setReadOnly(true);
    ui->deductions->setReadOnly(true);
    ui->net_salary->setReadOnly(true);
}

void modify_user::load_user_data(std::string& data) {
    // clean the user_data strings
    this->user_info.name = "\0";
    this->user_info.identification  = "\0";
    this->user_info.phone  = "\0";
    this->user_info.email  = "\0";
    this->user_info.job_title  = "\0";

    size_t pos = 0;
    int commas_found = 0;
    std::string temp_salary = "\0";
    std::string temp_deductibles = "\0";
    std::string temp_vacations = "\0";

    while (pos < data.length()) {
        if (data[pos] != ','  && data[pos] != '\0') {
            switch(commas_found) {
                case 0:  // the name is
                    this->user_info.name += data[pos];
                    break;
                case 1:  // identification
                    this->user_info.identification += data[pos];
                    break;
                case 2:  // phone
                    this->user_info.phone += data[pos];
                    break;
                case 3:  // email
                    this->user_info.email += data[pos];
                    break;
                case 4:  // office
                    this->user_info.office_id = data[pos];  // only one char always
                    break;
                case 5:  // role
                    this->user_info.role = data[pos];  // only one char always
                    break;
                case 6:  // vacations
                    temp_vacations += data[pos];
                    break;
//                case 7:  // job_title
//                    this->user_info.job_title += data[pos];
//                    break;
//                case 8:  // base salary
//                    temp_salary += data[pos];
//                    break;
//                case 9:  // deductibles
//                    temp_deductibles += data[pos];
//                    break;
            }
        } else {
            ++commas_found;  // indicate a comma was found
        }
        ++pos;
    }

    // TODO(Angie): borrar
    std::cout << "temp_vacations: " << temp_vacations << std::endl;

//    this->user_info.available_vacations = stoi(temp_vacations);
//    this->user_info.salary_base = stoi(temp_salary);
//    this->user_info.deductibles = stoi(temp_deductibles);
//    this->user_info.salary_net = this->user_info.salary_base - this->user_info.deductibles;
}

// Método que va a agregar los usuarios al comboBox
void modify_user::add_data_to_combobox() {
    // clear the comboBox
    this->ui->comboBox->clear();

    int i = 0;
    // find the user's office id
    std::string to_send = "0" + this->user_login->user;
    to_send[0] = USER_OFFICE;
    std::string data_received = this->local_client->send_and_receive(to_send);

    // find all the users of an office
    to_send = "0";
    to_send[0] = ALL_USERS_OFFICE;

    // find the office id
    while (data_received[i] != '\0') {
        to_send += data_received[i++];
    }
    data_received = this->local_client->send_and_receive(to_send);

    // store the usernames individually
    std::string new_user = "\0";
    for(size_t i = 0; i < data_received.length(); ++i) {
        if (data_received[i] != ',') {
            new_user += data_received[i];
        } else {  // is the end of the username
            if (new_user != this->user_login->user) {  // an user cannot modify itself
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
Qt::CheckState modify_user::unmask_role(int role_id, char role) {
    Qt::CheckState state = Qt::Unchecked;
    int role_int = (int) role;
    if ((role_int & role_id) == role_id) {
        state = Qt::Checked;
    }
    return state;
}

void modify_user::on_approve_changes_clicked() {
    QString password = ui->password->text();
    if (password.toStdString() == this->user_login->password) {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Correcto");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Cambios aplicados");
        show_message.exec();
        this->update_data();
    } else {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Contraseña incorrecta");
        show_message.exec();
    }
}

void modify_user::update_data() {
    std::string to_send = " " + this->user_info.user;
    bool is_number = true;

    // update roles
    this->update_roles();

    if (this->ui->phone->text().toStdString() != this->user_info.phone && this->ui->phone->text().length() == 8) {
        this->user_info.phone = this->ui->phone->text().toStdString();
        to_send = " " + this->user_info.phone;
        to_send[0] = CHANGE_PHONE;
        this->local_client->send_and_receive(to_send);
    }
    if (this->ui->email->text().toStdString() != this->user_info.email && this->ui->email->text().length() > 0
                && this->ui->email->text().length() <= 23) {
        this->user_info.email = this->ui->email->text().toStdString();
        to_send += "," + this->user_info.email;
        to_send[0] = CHANGE_EMAIL;
        this->local_client->send_and_receive(to_send);
    }
    if (this->ui->office->text().toInt(&is_number, 10) != this->user_info.office_id && is_number) {  // only saved if office is a valid number
        this->user_info.office_id = this->ui->office->text().toInt(&is_number, 10);
        to_send[0] = CHANGE_OFFICE_ID;
        to_send += "," + std::to_string(this->user_info.office_id);
        this->local_client->send_and_receive(to_send);
    }
    if (this->ui->vacations->text().toInt(&is_number, 10) != this->user_info.available_vacations && is_number) {
        this->user_info.available_vacations = this->ui->vacations->text().toInt(&is_number, 10);
        to_send = "  ";
        to_send[0] = CHANGE_VACATIONS;
        to_send += "," + std::to_string(this->user_info.available_vacations);
        this->local_client->send_and_receive(to_send);
    }
    if ((this->ui->base_salary->text().toInt(&is_number, 10) != this->user_info.salary_base && is_number)
            || (this->ui->deductions->text().toInt(&is_number, 10) != this->user_info.deductibles && is_number)
            || (this->ui->job_title->text().toStdString() != this->user_info.job_title && this->ui->job_title->text().length() > 0)) {
        // update user info
        this->user_info.job_title = this->ui->job_title->text().toStdString();
        this->user_info.salary_base = this->ui->base_salary->text().toInt(&is_number, 10);
        this->user_info.deductibles = this->ui->net_salary->text().toInt(&is_number, 10);
        this->user_info.salary_net = this->user_info.salary_base-this->user_info.deductibles;
        this->ui->net_salary->setText(QString::number(this->user_info.salary_net));

        // send changes to data_base
        to_send[0] = CHANGE_LABORAL_DATA;
        // set the date
        QDate date = QDate::currentDate();
        int day = 0;
        int month = 0;
        int year = 0;
        date.getDate(&year, &month, &day);
        to_send += "," + std::to_string(day) + "," + std::to_string(month) + "," + std::to_string(year);
        // add laboral data info
        to_send += "," + this->user_info.job_title;
        to_send += "," + std::to_string(this->user_info.salary_base);
        to_send += "," + std::to_string(this->user_info.deductibles);
    }
    if (this->ui->record->toPlainText().toStdString().length() > 0 && this->ui->record->toPlainText().toStdString().length() < 237) {  // new annotation
        to_send[0] = ADD_RECORD;
        QDate date = QDate::currentDate();
        int day = 0;
        int month = 0;
        int year = 0;
        date.getDate(&year, &month, &day);
        to_send += "," + std::to_string(day) + "," + std::to_string(month) + "," + std::to_string(year);
        to_send += "," + this->ui->record->toPlainText().toStdString();
        // TODO(Angie): ver si data base puede recibir '&' para mandar anotaciones largas
    }
}

void modify_user::update_roles() {
    std::string to_send = " " + this->user_info.user + ",";
    to_send[0] = CHANGE_ROLES;
    int role_int = 0;

    // if something was modified, so data has to be updated
    // check if the employee was fired
    if (ui->checkbox_active->checkState() == Qt::Unchecked
            && unmask_role(UNEMPLOYEED, this->user_info.role) == Qt::Checked) {
        // the new role is fired
        this->user_info.role = UNEMPLOYEED | this->user_info.role;
        to_send[0] = FIRE_EMPLOYEE;
        to_send += this->user_info.role;

        // set the date
        QDate date = QDate::currentDate();
        int day = 0;
        int month = 0;
        int year = 0;
        date.getDate(&year, &month, &day);
        to_send += "," + std::to_string(day) + "," + std::to_string(month) + "," + std::to_string(year);

        this->local_client->send_and_receive(to_send);
        // TODO(Angie):mostrar pop up si hubo error

        // once fired, nothing can be changed
        this->set_read_only();
    } else {
        // if the user is Debug, it can not have more roles
        if (ui->checkbox_debug->checkState() == Qt::Checked
                && unmask_role(DEBUG, this->user_info.role) == Qt::Checked) {
            this->user_info.role = DEBUG;

            // the debug is exclusive of other roles
            ui->checkbox_admin_users->setCheckState(Qt::Unchecked);
            ui->checkbox_admin_config->setCheckState(Qt::Unchecked);
            ui->checkbox_employee->setCheckState(Qt::Unchecked);
            ui->checkbox_human_resources->setCheckState(Qt::Unchecked);
            ui->checkbox_supervisor->setCheckState(Qt::Unchecked);

            // update the data base
            to_send += this->user_info.role;
            this->local_client->send_and_receive(to_send);
        } else {  // see if any role changed
            if (ui->checkbox_admin_config->checkState() == Qt::Checked) {
                role_int |= ADMIN_CONFIG;
            }
            if (ui->checkbox_admin_users->checkState() == Qt::Checked) {
                role_int |= ADMIN_USER;
            }
            if (ui->checkbox_employee->checkState() == Qt::Checked) {
                role_int |= EMPLOYEE;
            }
            if (ui->checkbox_human_resources->checkState() == Qt::Checked) {
                role_int |= HUMAN_RESOURCES;
            }
            if (ui->checkbox_supervisor->checkState() == Qt::Checked) {
                role_int |= SUPERVISOR;
            }

            this->user_info.role = role_int;
            to_send += this->user_info.role;
            this->local_client->send_and_receive(to_send);
        }
    }
}

void modify_user::set_login_info(login_info* info) {
    this->user_login = info;
}

void modify_user::set_client(client* local_client) {
    this->local_client = local_client;
}
