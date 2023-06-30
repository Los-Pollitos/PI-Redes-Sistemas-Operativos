#include "sys_config.h"
#include "ui_sys_config.h"

sys_config::sys_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sys_config) {
    ui->setupUi(this);
    // Set the window name and colors
    this->setWindowTitle("Modificar configuración del sistema");
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->client_port->setStyleSheet("color: #001f21;");
    this->ui->inter_ip->setStyleSheet("color: #001f21;");
    this->ui->inter_port->setStyleSheet("color: #001f21;");
    this->ui->file_system_ip->setStyleSheet("color: black;");
    this->ui->file_system_port->setStyleSheet("color: #001f21;");
    this->ui->data_base_ip->setStyleSheet("color: #001f21;");
    this->ui->data_base_port->setStyleSheet("color: #001f21;");
    this->ui->password_insert->setStyleSheet("color: black;");
    this->ui->confirm->setStyleSheet("color: #001f21;");
    this->ui->reset->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->label_2->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");
    this->ui->label_5->setStyleSheet("color: #001f21;");
    this->ui->label_6->setStyleSheet("color: #001f21;");
    this->ui->label_7->setStyleSheet("color: #001f21;");
    this->ui->label_8->setStyleSheet("color: #001f21;");
    this->ui->label_9->setStyleSheet("color: #001f21;");
    this->ui->label_10->setStyleSheet("color: #001f21;");
    this->ui->label_11->setStyleSheet("color: #001f21;");
    this->ui->label_12->setStyleSheet("color: #001f21;");
    this->ui->label_13->setStyleSheet("color: #001f21;");
    this->ui->label_14->setStyleSheet("color: #001f21;");
    // Set the password mode for password_insert
    this->ui->password_insert->setEchoMode(QLineEdit::Password);
}

sys_config::~sys_config() {
    delete ui;
}

void sys_config::set_client(client* local_client){
    this->local_client = local_client;
}

void sys_config::set_user_login(login_info* user_login) {
    this->user_login = user_login;
}

void sys_config::on_reset_clicked() {
    //Reset the window
    this->ui->client_port->clear();
    this->ui->inter_ip->clear();
    this->ui->inter_port->clear();
    this->ui->file_system_ip->clear();
    this->ui->file_system_port->clear();
    this->ui->data_base_ip->clear();
    this->ui->data_base_port->clear();
    this->ui->password_insert->clear();
}


void sys_config::on_confirm_clicked() {
    // Check if all boxes are complete
    if (this->check_if_empty() == false) {
        // Check the password
        if (this->check_password() == true) {
            // Encrypt and prepare the datagram
            for (size_t i = 0; i < this->current_text.size(); ++i) {            }
            // Prepare string

            std::string to_send = "A";
            // TODO(Luis): descomentar
            // this->prepare_string(to_send);
            for (size_t i = 0; i < this->current_text.size() - 1; ++i) {
                qDebug() << this->current_text[i];
                to_send += this->current_text[i];
                to_send += ":";
            }

            qDebug() << "TO_SEND" << to_send;

            // Send
            this->show_success("FULVO");

        } else {
            // Show error
            this->show_error("Por favor inserte su contraseña");
        }
    } else {
        // Show error
        this->show_error("Por favor rellene todas las opciones");
    }
}

void decrypt_salary(std::string salary) {
    security security_manager;
    std::string salary_temp = "";

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
    salary_temp = security_manager.decrypt(salary_temp);
    qDebug() << salary_temp.size();
    qDebug() << "desde DECRYPT";
    qDebug() << salary_temp;

    for (int j = 0; j < salary_temp.size(); ++j) {
        qDebug() << (int)salary_temp[j];
        qDebug() << salary_temp[j];
    }

    qDebug() << (int)("1:2:3:4:5:6:7:8:" == salary_temp);
}

void sys_config::prepare_string(std::string& to_send) {
    security encrypter;
    std::string to_encrypt = "";
    for (size_t i = 0; i < this->current_text.size() - 1; ++i) {
        qDebug() << this->current_text[i];
        to_encrypt += this->current_text[i];
        to_encrypt += ":";
    }

    qDebug() << "PREPARE STRING" << to_encrypt;

    std::string result = encrypter.encrypt(to_encrypt);
    to_send = 'A';
    for (size_t i = 0; i < result.size(); ++i) {
        to_send += ((int)result[i]);
        to_send += ".";
    }

    qDebug() << "SIZE" << to_send.size();
    qDebug() << to_send;
    decrypt_salary(to_send);
}

bool sys_config::check_if_empty() {
    // Assume the answer as true
    bool answer = false;
    // Clear the current_text vector
    this->current_text.clear();
    // Append to current text vector
    this->current_text.push_back(this->ui->client_port->toPlainText().toStdString());
    this->current_text.push_back(this->ui->inter_ip->toPlainText().toStdString());
    this->current_text.push_back(this->ui->inter_port->toPlainText().toStdString());
    this->current_text.push_back(this->ui->file_system_ip->toPlainText().toStdString());
    this->current_text.push_back(this->ui->file_system_port->toPlainText().toStdString());
    this->current_text.push_back(this->ui->data_base_ip->toPlainText().toStdString());
    this->current_text.push_back(this->ui->data_base_port->toPlainText().toStdString());
    this->current_text.push_back(this->ui->password_insert->text().toStdString());

    // Check the condition
    for (size_t i = 0; i < this->current_text.size(); ++i) {
        if (this->current_text[i].size() == 0) {
            answer = true;
            break;
        }
    }
    return answer;
}

bool sys_config::check_password() {
    bool answer = false;
    std::string password = this->ui->password_insert->text().toStdString();
    if (password == this->user_login->password) {
        answer = true;
    }
    return answer;
}

void sys_config::show_error(std::string error) {
    QMessageBox error_message;
    error_message.setText(QString::fromStdString(error));
    error_message.setWindowTitle("Error");
    error_message.setModal(true);
    error_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
    error_message.exec();
}

void sys_config::show_success(std::string success) {
    QMessageBox success_box;
    success_box.setText(QString::fromStdString(success));
    success_box.setWindowTitle("Información");
    success_box.setModal(true);
    success_box.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
    success_box.exec();
}
