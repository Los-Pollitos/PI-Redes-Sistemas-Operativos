#include "sys_config.h"
#include "ui_sys_config.h"

sys_config::sys_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sys_config) {
    this->ui->setupUi(this);
    this->encrypter = new common();

    // Set the window name and colors
    this->setWindowTitle("Modificar configuración del sistema");
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->inter_ip->setStyleSheet("color: #001f21;");
    this->ui->file_system_ip->setStyleSheet("color: black;");
    this->ui->file_system_port->setStyleSheet("color: #001f21;");
    this->ui->data_base_ip->setStyleSheet("color: #001f21;");
    this->ui->data_base_port->setStyleSheet("color: #001f21;");
    this->ui->password_insert->setStyleSheet("color: black;");
    this->ui->confirm->setStyleSheet("color: #001f21;");
    this->ui->reset->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");
    this->ui->label_5->setStyleSheet("color: #001f21;");
    this->ui->label_7->setStyleSheet("color: #001f21;");
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
    delete this->ui;
    delete this->encrypter;
}

void sys_config::set_client(client* local_client){
    this->local_client = local_client;
}

void sys_config::set_user_login(login_info* user_login) {
    this->user_login = user_login;
}

void sys_config::on_reset_clicked() {
    //Reset the window
    this->ui->inter_ip->clear();
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
            // Set the client up
            this->set_up_client();

            // Encrypt and prepare the datagram for intermediary
            std::string to_send = " 1";
            to_send[0] = ((char)MODIFY_NETWORK);
            std::string encrypted = "";
            std::string to_encrypt = "";
            for (size_t i = 2; i < this->current_text.size() - 1; ++i) {
                to_encrypt = this->current_text[i];
                this->encrypter->encrypt(to_encrypt, encrypted);
                to_send += encrypted + ":";
            }
            std::string first_answer = this->local_client->send_and_receive(to_send);

            // Encrypt and prepare the datagram for file system
            to_encrypt = this->current_text[3];
            this->encrypter->encrypt(to_encrypt, encrypted);
            to_send = " 2" + encrypted + ":";
            to_send[0] = ((char)MODIFY_NETWORK);
            std::string second_answer = this->local_client->send_and_receive(to_send);

            // Encrypt and prepare the datagram for data base
            to_encrypt = this->current_text[5];
            this->encrypter->encrypt(to_encrypt, encrypted);
            to_send = " 3" + encrypted + ":";
            to_send[0] = ((char)MODIFY_NETWORK);
            std::string third_answer = this->local_client->send_and_receive(to_send);

            // Encrypt and prepare the datagram for the auditors
            // Intermediary auditor
            to_send = " 4";
            to_send[0] = ((char)MODIFY_NETWORK);
            to_encrypt = current_text[0];
            this->encrypter->encrypt(to_encrypt, encrypted);
            to_send += encrypted + ":";
            to_encrypt = current_text[1];
            this->encrypter->encrypt(to_encrypt, encrypted);
            to_send += encrypted + ":";
            std::string fourth_answer = this->local_client->send_and_receive(to_send);
            // File system auditor
            to_send[1] = '5';
            std::string fifth_answer = this->local_client->send_and_receive(to_send);
            // Data base auditor
            to_send[1] = '6';
            std::string final_answer = this->local_client->send_and_receive(to_send);
            // Setup the joint answer
            std::string joint_answer = "";
            joint_answer += first_answer[0];
            joint_answer += second_answer[0];
            joint_answer += third_answer[0];
            joint_answer += fourth_answer[0];
            joint_answer += fifth_answer[0];
            joint_answer += final_answer[0];

            if (joint_answer == "111111") {
              this->show_success("Los cambios fueron aplicados");
            } else {
              this->show_error("Error: no se pudieron aplicar los cambios");
            }
        } else {
            // Show error
            this->show_error("Por favor inserte su contraseña");
        }
    } else {
        // Show error
        this->show_error("Por favor rellene todas las opciones");
    }
    //Reset the window
    this->ui->inter_ip->clear();
    this->ui->file_system_ip->clear();
    this->ui->file_system_port->clear();
    this->ui->data_base_ip->clear();
    this->ui->data_base_port->clear();
    this->ui->password_insert->clear();
}

void sys_config::set_up_client() {
    std::string intermediary_ip;
    this->encrypter->encrypt(this->current_text[0], intermediary_ip);
    std::string port;
    this->encrypter->encrypt(this->current_text[1], port);
    std::ofstream config_file("../client.config", std::fstream::trunc);
    if (config_file.is_open()) {
        config_file << intermediary_ip;
        config_file << "\n";
        config_file << port;
        config_file.close();
    }
}

bool sys_config::check_if_empty() {
    // Assume the answer as true
    bool answer = false;
    // Clear the current_text vector
    this->current_text.clear();
    // Append to current text vector
    this->current_text.push_back(this->ui->inter_ip->toPlainText().toStdString());
    this->current_text.push_back("9090");
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
