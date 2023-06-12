#include "modify_user.h"
#include "ui_modify_user.h"

#include <fstream>
#include <iostream>
#include <QCheckBox>
#include <QMessageBox>

modify_user::modify_user(QWidget *parent) : QDialog(parent), ui(new Ui::modify_user) {
    ui->setupUi(this);
    this->correct_changes = false;
    this->changed = false;

    // colors
    this->set_colors();

    // window name
    this->setWindowTitle("Modificar usuarios");
}

modify_user::~modify_user() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void modify_user::set_colors() {
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
    this->ui->label_16->setStyleSheet("color: #001f21;");
    this->ui->label_17->setStyleSheet("color: #001f21;");
    this->ui->net_salary->setStyleSheet("color: #001f21;");
    this->ui->office->setStyleSheet("color: #001f21;");
    this->ui->password->setStyleSheet("color: #001f21;");
    this->ui->name->setStyleSheet("color: #001f21;");
    this->ui->phone->setStyleSheet("color: #001f21;");
    this->ui->password->setStyleSheet("color: #001f21;");
    this->ui->vacations->setStyleSheet("color: #001f21;");
    this->ui->record->setStyleSheet("color: #001f21;");
    this->ui->checkbox_active->setStyleSheet("color: #001f21;");
    this->ui->checkbox_admin_config->setStyleSheet("color: #001f21;");
    this->ui->checkbox_admin_users->setStyleSheet("color: #001f21;");
    this->ui->checkbox_debug->setStyleSheet("color: #001f21;");
    this->ui->checkbox_employee->setStyleSheet("color: #001f21;");
    this->ui->checkbox_human_resources->setStyleSheet("color: #001f21;");
    this->ui->checkbox_supervisor->setStyleSheet("color: #001f21;");
    this->ui->checkbox_shift->setStyleSheet("color: #001f21;");
    this->ui->comboBox->setStyleSheet("color: #001f21;");
}

void modify_user::on_comboBox_activated(int index) {
    // obtain the user's data
    this->user_info.user = this->user_names[index];
    std::string to_send = (char) DATA_USER + this->user_names[index];
    std::string data_received = this->local_client->send_and_receive(to_send);

    // data_received tiene el formato definido en el datagrama
    this->load_user_data(data_received);

    // if the user was fired, noting can't be changed
    if(unmask_role(UNEMPLOYEED, this->user_info.role) == Qt::Checked) {
        ui->checkbox_active->setCheckState(unmask_role(index, UNEMPLOYEED));
        this->set_read_only();
    }

    // set the data in the ui
    this->set_data_ui();
}

void modify_user::set_data_ui() {
    int office_id = (int) (this->user_info.office_id - 48);
    this->ui->name->setReadOnly(true);
    this->ui->name->setText(QString::fromStdString(this->user_info.name));
    this->ui->id->setReadOnly(true);
    this->ui->id->setText(QString::fromStdString(this->user_info.identification));
    this->ui->phone->setText(QString::fromStdString(this->user_info.phone));
    this->ui->email->setText(QString::fromStdString(this->user_info.email));
    this->ui->office->setText(QString::number(office_id));
    this->ui->checkbox_active->setCheckState((unmask_role(UNEMPLOYEED, this->user_info.role) == Qt::Checked) ? Qt::Unchecked : Qt::Checked);
    this->ui->checkbox_admin_users->setCheckState(unmask_role(ADMIN_USER, this->user_info.role));
    this->ui->checkbox_admin_config->setCheckState(unmask_role(ADMIN_CONFIG, this->user_info.role));
    this->ui->checkbox_debug->setCheckState(unmask_role(DEBUG, this->user_info.role));
    this->ui->checkbox_employee->setCheckState(unmask_role(EMPLOYEE, this->user_info.role));
    this->ui->checkbox_human_resources->setCheckState(unmask_role(HUMAN_RESOURCES, this->user_info.role));
    this->ui->checkbox_supervisor->setCheckState(unmask_role(SUPERVISOR, this->user_info.role));
    this->ui->vacations->setText(QString::number(this->user_info.available_vacations));
    this->ui->checkbox_shift->setCheckState(this->user_info.shift_available ? Qt::Checked : Qt::Unchecked);
    this->ui->job_title->setText(QString::fromStdString(this->user_info.job_title));
    this->ui->base_salary->setText(QString::number(this->user_info.salary_base));
    this->ui->deductions->setText(QString::number(this->user_info.deductibles));
    this->ui->net_salary->setReadOnly(true);
    this->ui->net_salary->setText(QString::number(this->user_info.salary_net));
}

void modify_user::set_read_only() {
    // read only the other roles
    this->ui->checkbox_active->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_active->setFocusPolicy(Qt::NoFocus);
    this->ui->checkbox_admin_config->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_admin_config->setFocusPolicy(Qt::NoFocus);
    this->ui->checkbox_admin_users->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_admin_users->setFocusPolicy(Qt::NoFocus);
    this->ui->checkbox_employee->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_employee->setFocusPolicy(Qt::NoFocus);
    this->ui->checkbox_debug->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_debug->setFocusPolicy(Qt::NoFocus);
    this->ui->checkbox_human_resources->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_human_resources->setFocusPolicy(Qt::NoFocus);
    this->ui->checkbox_supervisor->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_supervisor->setFocusPolicy(Qt::NoFocus);
    this->ui->checkbox_shift->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkbox_shift->setFocusPolicy(Qt::NoFocus);

    // read only the text edits
    this->ui->name->setReadOnly(true);
    this->ui->id->setReadOnly(true);
    this->ui->phone->setReadOnly(true);
    this->ui->email->setReadOnly(true);
    this->ui->office->setReadOnly(true);
    this->ui->job_title->setReadOnly(true);
    this->ui->base_salary->setReadOnly(true);
    this->ui->deductions->setReadOnly(true);
    this->ui->net_salary->setReadOnly(true);
    this->ui->vacations->setReadOnly(true);
    this->ui->record->setReadOnly(true);
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
    std::string temp_salary = "";
    std::string temp_deductibles = "\0";
    std::string temp_vacations = "\0";
    std::string temp_shift = "\0";

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
                case 7:  // shift
                    temp_shift += data[pos];
                    break;
                case 8: // base salary
                    temp_salary += data[pos];
                    break;
                case 9: // deductibles
                    temp_deductibles += data[pos];
                    break;
                case 10: // job_title
                    this->user_info.job_title += data[pos];
                    break;
            }
        } else {
            ++commas_found;  // indicate a comma was found
        }
        ++pos;
    }
    this->user_info.available_vacations = stoi(temp_vacations);
    this->decrypt_salary(temp_salary, temp_deductibles);
    this->user_info.salary_net = this->user_info.salary_base - this->user_info.deductibles;
    this->user_info.shift_available = (stoi(temp_shift) == 1 ? true : false);
}

void modify_user::encrypt_salary(std::string& salary,std::string& deductibles) {
    security security_manager;
    std::string buffer = security_manager.encrypt(std::to_string(this->user_info.salary_base));

    // salary
    for (size_t i = 0; i < buffer.length(); ++i) {
        salary += std::to_string((int)buffer[i]);
        salary += ".";
    }

    // deductibles
    buffer = security_manager.encrypt(std::to_string(this->user_info.deductibles));
    for (size_t i = 0; i < buffer.length(); ++i) {
        deductibles += std::to_string((int)buffer[i]);
        deductibles += ".";
    }
}

void modify_user::decrypt_salary(std::string salary, std::string deductibles) {
    security security_manager;
    std::string salary_temp = "\0";
    std::string deductibles_temp = "\0";

    // salary
    for (size_t i = 0; i < salary.length(); ++i) {
        if (salary[i] != '.') {
            if (salary[i+1] == '.') {
                    salary_temp += (char)(salary[i]-48);
            } else if (salary[i+2] == '.'){
                    salary_temp += (char)(((int)salary[i]) - 48)*10 +(((int)salary[i+1]) - 48);
                    ++i; // ignore i+1
            } else {
                    salary_temp += (char)(((int)salary[i] - 48)*100 + ((int)salary[i+1] -48)*10 - +(((int)salary[i+2] -48)));
                    i+=2; // ignore i+2
            }
            // next one would be a '.'
            i++;
        }
    }
    this->user_info.salary_base = stoi(security_manager.decrypt(salary_temp));
    // deductibles
    for (size_t i = 0; i < deductibles.length(); ++i) {
        if (deductibles[i] != '.') {
            if (deductibles[i+1] == '.') {
                    deductibles_temp += (char)(deductibles[i]-48);
            } else if (deductibles[i+2] == '.'){
                    deductibles_temp += (char)(((int)deductibles[i]) - 48)*10 +(((int)deductibles[i+1]) - 48);
                    ++i; // ignore i+1
            } else {
                    deductibles_temp += (char)(((int)deductibles[i] - 48)*100 + ((int)deductibles[i+1] -48)*10 - +(((int)deductibles[i+2] -48)));
                    i+=2; // ignore i+2
            }
            // next one would be a '.'
            i++;
        }
    }
    this->user_info.deductibles = stoi(security_manager.decrypt(deductibles_temp));
}

// Método que va a agregar los usuarios al comboBox
void modify_user::add_data_to_combobox() {
    // clear the comboBox
    for (int i = this->ui->comboBox->count(); i > 0; --i) {
        this->ui->comboBox->removeItem(i-1);
    }
    this->user_names.clear();

    // empty text lines
    this->empty_text();

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

    data_received += ",";

    // store the usernames individually
    std::string new_user = "";
    for(size_t i = 0; i < data_received.length(); ++i) {
        if (data_received[i] != ',') {
            new_user += data_received[i];
        } else {  // is the end of the username
            if (new_user != this->user_login->user) {  // an user cannot modify itself
                this->user_names.push_back(new_user);
            }
            new_user = "";  // it is cleaned for next username
        }
    }

    // add the users to the comboBox
    for (size_t i = 0; i < user_names.size(); ++i) {
        ui->comboBox->addItem(QString::fromStdString(this->user_names[i]));
    }
}

void modify_user::empty_text() {
    this->ui->name->setText("");
    this->ui->id->setText("");
    this->ui->phone->setText("");
    this->ui->email->setText("");
    this->ui->office->setText("");
    this->ui->checkbox_active->setCheckState(Qt::Unchecked);
    this->ui->checkbox_admin_users->setCheckState(Qt::Unchecked);
    this->ui->checkbox_admin_config->setCheckState(Qt::Unchecked);
    this->ui->checkbox_debug->setCheckState(Qt::Unchecked);
    this->ui->checkbox_employee->setCheckState(Qt::Unchecked);
    this->ui->checkbox_human_resources->setCheckState(Qt::Unchecked);
    this->ui->checkbox_supervisor->setCheckState(Qt::Unchecked);
    this->ui->checkbox_shift->setCheckState(Qt::Unchecked);
    this->ui->vacations->setText(0);
    this->ui->job_title->setText(0);
    this->ui->base_salary->setText(0);
    this->ui->deductions->setText(0);
    this->ui->net_salary->setText(0);
    this->ui->password->setText("");
    this->ui->record->setPlainText("");
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
    QMessageBox show_message = QMessageBox();
    QString password = ui->password->text();
    if (password.toStdString() == this->user_login->password) {
        this->update_data();
        if (correct_changes) {
            show_message.setWindowTitle("Correcto");
            show_message.setModal(true);
            show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_message.setText("Cambios aplicados");
            show_message.exec();
        } else {
            show_message.setWindowTitle("Error");
            show_message.setModal(true);
            show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_message.setText("Los cambios no fueron aplicados o no había cambios");
            show_message.exec();
        }
    } else {
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Contraseña incorrecta");
        show_message.exec();
    }
    this->changed = false;
    this->correct_changes = false;
}

void modify_user::update_data() {
    // update the data in the data base
    this->update_roles();
    this->update_phone();
    this->update_email();
    this->update_office();
    this->update_vacations();
    this->update_laboral_data();
    this->add_record();

    if (this->changed) {
        // refresh the data in the window
        this->add_data_to_combobox();
    }
}

void modify_user::update_roles() {
    std::string to_send = " " + this->user_info.user + ",";
    to_send[0] = CHANGE_ROLES;
    int role_int = 0;

    // if something was modified, so data has to be updated
    // check if the employee was fired
    if (ui->checkbox_active->checkState() == Qt::Unchecked
            && unmask_role(UNEMPLOYEED, this->user_info.role) == Qt::Unchecked) {
        this->changed = true;

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
        to_send += "," + this->user_login->user;

        this->check_error(this->local_client->send_and_receive(to_send), "Error al despedir el empleado");

        // once fired, nothing can be changed
        this->set_read_only();
    } else {
        // if the user is Debug, it can not have more roles
        if (ui->checkbox_debug->checkState() == Qt::Checked
                && unmask_role(DEBUG, this->user_info.role) == Qt::Checked) {
            this->user_info.role = DEBUG;
            this->changed = true;

            // the debug is exclusive of other roles
            ui->checkbox_admin_users->setCheckState(Qt::Unchecked);
            ui->checkbox_admin_config->setCheckState(Qt::Unchecked);
            ui->checkbox_employee->setCheckState(Qt::Unchecked);
            ui->checkbox_human_resources->setCheckState(Qt::Unchecked);
            ui->checkbox_supervisor->setCheckState(Qt::Unchecked);

            // update the data base
            to_send += this->user_info.role;
            this->check_error(this->local_client->send_and_receive(to_send), "Error al cambiar el rol a Depurador");
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

            if (this->user_info.role != role_int) {
                this->changed = true;
                this->user_info.role = role_int;
                to_send += this->user_info.role;
                this->check_error(this->local_client->send_and_receive(to_send), "Error al cambiar los roles");
            }
        }
    }
}

void modify_user::update_phone() {
    std::string to_send = "\0";
    bool is_number = true;

    this->ui->phone->text().toInt(&is_number);

    if (this->ui->phone->text().toStdString() != this->user_info.phone
                && this->ui->phone->text().length() == 8 && is_number) {
        this->changed = true;
        this->user_info.phone = this->ui->phone->text().toStdString();
        to_send = " " + this->user_info.user + "," + this->user_info.phone
                  + "," + this->user_login->user;
        to_send[0] = CHANGE_PHONE;
        this->check_error(this->local_client->send_and_receive(to_send)
                          , "Error al cambiar el número de teléfono");
    } else if (this->ui->phone->text().length() != 8 || !is_number) {
        this->check_error("0", "Error: el número de teléfono debe ser de 8 dígitos numéricos");
    }
}

void modify_user::update_email() {
    std::string to_send = "\0";

    if (this->ui->email->text().toStdString() != this->user_info.email
                && this->ui->email->text().length() > 0
                && this->ui->email->text().length() <= 23) {
        this->changed = true;
        this->user_info.email = this->ui->email->text().toStdString();
        to_send = (char) CHANGE_EMAIL + this->user_info.user + ","
                  + this->user_info.email + "," + this->user_login->user;
        this->check_error(this->local_client->send_and_receive(to_send)
                          , "Error al cambiar el correo");
    } else if (this->ui->email->text().length() < 0
               || this->ui->email->text().length() > 23) {
        this->check_error("0", "Error: el correo debe ser de máximo 23 caracteres");
    }
}

void modify_user::update_office() {
    std::string to_send = "\0";
    bool is_number = true;

    // only saved if office is a valid number
    if (this->ui->office->text().toInt(&is_number, 10) != (int) (this->user_info.office_id - 48) && is_number) {
        this->changed = true;
        this->user_info.office_id = this->ui->office->text().toInt(&is_number, 10);
        to_send = " " + this->user_info.user + "," + std::to_string(this->user_info.office_id)
                  + "," + this->user_login->user;
        to_send[0] = CHANGE_OFFICE_ID;
        this->check_error(this->local_client->send_and_receive(to_send), "Error al cambiar la sucursal");
    } else if (!is_number) {
        this->check_error("0", "Error: sucursal inválida");
    }
}

void modify_user::update_vacations() {
    std::string to_send = "\0";
    bool is_number = true;

    if (this->ui->vacations->text().toInt(&is_number, 10) != this->user_info.available_vacations
                && is_number) {
        this->changed = true;
        this->user_info.available_vacations = this->ui->vacations->text().toInt(&is_number, 10);
        to_send = " " + this->user_info.user;
        to_send[0] = CHANGE_VACATIONS;
        to_send += "," + std::to_string(this->user_info.available_vacations);
        to_send += "," + this->user_login->user;
        this->check_error(this->local_client->send_and_receive(to_send)
                          , "Error al cambiar las vacaciones disponibles");
    } else if (!is_number) {
        this->check_error("0", "Error: cantidad de vacaciones inválida");
    }

    if ((ui->checkbox_shift->checkState() == Qt::Checked && this->user_info.shift_available == false)
            || (ui->checkbox_shift->checkState() == Qt::Unchecked && this->user_info.shift_available == true)) {

        std::cout << "cambiando shift" << std::endl;

        this->changed = true;
        this->user_info.shift_available = !this->user_info.shift_available;  // set to the contrary
        to_send = (char) CHANGE_SHIFT + this->user_info.user;
        to_send += "," + std::to_string(this->user_info.shift_available ? 1 : 0);
        to_send += "," + this->user_login->user;
        this->check_error(this->local_client->send_and_receive(to_send), "Error al cambiar el turno disponible");
    }
}

void modify_user::update_laboral_data() {
    std::string to_send = "\0";
    bool salary_is_number = true;
    bool deductible_is_number = true;

    if ((this->ui->base_salary->text().toInt(&salary_is_number, 10)
            != this->user_info.salary_base && salary_is_number)
            || (this->ui->deductions->text().toInt(&deductible_is_number, 10)
            != this->user_info.deductibles && deductible_is_number)
            || (this->ui->job_title->text().toStdString()
            != this->user_info.job_title && this->ui->job_title->text().length() > 0)) {
        this->changed = true;
        // update user info
        this->user_info.job_title = this->ui->job_title->text().toStdString();
        this->user_info.salary_base = this->ui->base_salary->text().toInt(&salary_is_number, 10);
        this->user_info.deductibles = this->ui->deductions->text().toInt(&deductible_is_number, 10);
        this->user_info.salary_net = this->user_info.salary_base-this->user_info.deductibles;
        this->ui->net_salary->setText(QString::number(this->user_info.salary_net));

        // send changes to data_base
        to_send = (char) CHANGE_LABORAL_DATA + this->user_info.user;
        // set the date
        QDate date = QDate::currentDate();
        int day = 0;
        int month = 0;
        int year = 0;
        date.getDate(&year, &month, &day);
        to_send += "," + std::to_string(day) + "," + std::to_string(month) + "," + std::to_string(year);

        // encrypt salary and deductibles
        std::string salary_encripted = "\0";
        std::string deductibles_encripted = "\0";
        this->encrypt_salary(salary_encripted, deductibles_encripted);

        // add laboral data info
        to_send += "," + this->user_info.job_title;
        to_send += "," + salary_encripted;
        to_send += "," + deductibles_encripted;
        to_send += "," + this->user_login->user;

        this->check_error(this->local_client->send_and_receive(to_send), "Error al cambiar el puesto, salario y/o deducciones");
    } else if (!salary_is_number || !deductible_is_number || this->ui->job_title->text().length() <= 0) {
        this->check_error("0", "Error: el salario y las deducciones deben ser números y el puesto debe ser mayor a 0 caracteres");
    }
}

void modify_user::add_record() {
    std::string to_send = "\0";

    if (this->ui->record->toPlainText().toStdString().length() > 0
                && this->ui->record->toPlainText().toStdString().length() <= 227) {  // new annotation
        this->changed = true;
        to_send = " " + this->user_info.user;
        to_send[0] = ADD_RECORD;
        QDate date = QDate::currentDate();
        int day = 0;
        int month = 0;
        int year = 0;
        date.getDate(&year, &month, &day);
        to_send += "," + std::to_string(day) + "," + std::to_string(month) + "," + std::to_string(year);
        to_send += "," + this->ui->record->toPlainText().toStdString();
        to_send += "," + this->user_login->user;
        this->check_error(this->local_client->send_and_receive(to_send), "Error al agregar una anotación");
    } else if (this->ui->record->toPlainText().toStdString().length() > 237) {
        this->check_error("0", "Error: la anotación es de máximo 237 caracteres");
    }
}

void modify_user::check_error(std::string received, QString error) {
    if (received[0] == '0') {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText(error);
        show_message.exec();
    } else {
        this->correct_changes = true;
    }
}

void modify_user::set_login_info(login_info* info) {
    this->user_login = info;
}

void modify_user::set_client(client* local_client) {
    this->local_client = local_client;
}
