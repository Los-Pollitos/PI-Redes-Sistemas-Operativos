#include "sys_config.h"
#include "ui_sys_config.h"

sys_config::sys_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sys_config) {
    ui->setupUi(this);
    // Set the window name and colors
    this->setWindowTitle("Modificar configuración del sistema");
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->client_ip->setStyleSheet("color: #001f21;");
    this->ui->client_port->setStyleSheet("color: #001f21;");
    this->ui->inter_ip->setStyleSheet("color: #001f21;");
    this->ui->inter_port->setStyleSheet("color: #001f21;");
    this->ui->file_system_ip->setStyleSheet("color: #001f21;");
    this->ui->file_system_port->setStyleSheet("color: #001f21;");
    this->ui->data_base_ip->setStyleSheet("color: #001f21;");
    this->ui->data_base_port->setStyleSheet("color: #001f21;");
    this->ui->password_insert->setStyleSheet("color: #001f21;");
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
    this->ui->client_ip->clear();
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

        qDebug() << "Antes de check_password";

        if (this->check_password() == true) {
            qDebug() << "estoy dentro";
            // Encrypt and prepare the datagram

            for (size_t i = 0; i < this->current_text.size(); ++i) {
                std::cout << "Tengo" << current_text[i] << "\n";
            }

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

bool sys_config::check_if_empty() {
    // Assume the answer as true
    bool answer = false;
    // Clear the current_text vector

    qDebug() << "antes de crash ?? \n";

    this->current_text.clear();

    qDebug() << "despues de crash ?? \n";

    // Append to current text vector
    this->current_text.push_back(this->ui->client_ip->toPlainText().toStdString());
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

        qDebug() << i;
        qDebug() << " " << current_text[i] << "\n";

        qDebug() << "antes de if ?? \n";

        if (this->current_text[i].size() == 0) {
            answer = true;
            break;
        }

        qDebug() << "fin ?? \n";

    }
    return answer;
}

bool sys_config::check_password() {
    bool answer = false;
    std::string password = this->ui->password_insert->text().toStdString();

    qDebug() << "uy " << password;
    qDebug() << "tiene el otro: " << this->user_login->password;

    if (password == this->user_login->password) {
        answer = true;
    }

    qDebug() << "despues de eso";

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
