#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <fstream>
#include <iostream>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //QPixmap pix ("C:/Users/emili/Downloads/a.png");
    //this->ui->pic_label->setPixmap(pix.scaled(ui->pic_label->width(),
    //                                          ui->pic_label->height(),Qt::KeepAspectRatio));
    this->ui->password_input->setEchoMode(QLineEdit::Password); // no muestra password
    this->tokenPage = new Token(nullptr);
    this->changePass = new change_password(this);
    this->setWindowTitle("Login");
}

login::~login()
{
    delete this->ui;
    delete this->tokenPage;
    if (this->user_data) {
        delete this->user_data;
    }
    delete this->changePass;
}

void login::set_file_system(FS* file_system) {

    // TODO(nosotros): borrar
    std::cout << "estoy setteando, me llego: " << file_system << std::endl;

    this->file_system = file_system;
}

bool login::validate_data(QString username, QString password) {

    // TODO(nosotros): borrar
    std::cout << "estoy en valid valid" << std::endl;

    bool answer = false;
    bool found = false;
    std::string buffer = " ";
    // Find the username in the file

    // TODO(nosotros): borrar
    std::cout << "voy al while" << std::endl;

    while (!found /*&& this->file_system->is_eof(username.toStdString(), "Login.txt")*/) {

        // TODO(nosotros): borrar
        std::cout << "dentro del while" << std::endl;

        buffer = this->file_system->read_until(username.toStdString(), "Login.txt", '\t');

        // TODO(nosotros): borrar
        std::cout << "buffer: " << buffer << std::endl;

        if (buffer != username.toStdString()) {
            // Read the rest of the data
            this->file_system->read_line(username.toStdString(), "Login.txt");
        } else {
            found = true;
        }
        buffer = " ";
    }
    // Compare
    if (found) {
        buffer = this->file_system->read_until(username.toStdString(), "Login.txt", '\t');
        if (buffer == password.toStdString()) {
            // The user was found and is inserted in the struct
            answer = true;
            this->user_data = new login_info();
            this->user_data->user = username.toStdString();
            this->user_data->password = password.toStdString();
            // Obtain the token
            for (int i = 0; i < TOKEN_SIZE; ++i) {
                this->user_data->token[i] =
                    std::stoi(this->file_system->read_until(username.toStdString(), "Login.txt", ' '));
            }
        }
    }
    // Success
    return answer;
}

// TODO(nosotros): borrar
bool login::validate_data_old(QString username, QString password) {
    bool correct = false;
 //   try {
        std::ifstream file ("../Etapa 2/Archivos/Login.txt");
        std::string read_data = "";
        if (file.is_open()) {
            while (read_data != username.toStdString() && file) {
               file >> read_data;
               std::cout << "Lei:" << read_data << "." << std::endl;
               if (read_data != username.toStdString()) {
                   file >> read_data;  // don't keep the password
                   std::cout << "Lei:" << read_data << "." << std::endl;
                   for (int i = 0; i < TOKEN_SIZE; ++i) {
                       file >> read_data; // don't keep token
                   }
                   read_data = "";
               }
           }
           // TODO(nosotros): borrar
           std::cout << "Found user: " << read_data << std::endl;
           if (read_data == username.toStdString()) {
               file >> read_data;
               if (password.toStdString() == read_data) {
                   correct = true;
                   this->user_data = new login_info();
                   this->user_data->user = username.toStdString();
                   this->user_data->password = password.toStdString();
                   for (int i = 0; i < TOKEN_SIZE; ++i) {
                       file >> this->user_data->token[i]; // read token
                       // std::cout << this->user_data->token[i] << std::endl;
                   }
               }
           }
           file.close();
        } else {
            std::cerr << "Archivo de login no encontrado" << std::endl;
        }
 //   } catch (_exception e) {  // TODO (nosotros): volver después
 //       std::cerr << "Archivo de login no encontrado" << std::endl;
 //   }
       return correct;
}

void login::on_login_button_clicked() {
    QString username = ui->user_input->text();  // get username
    QString password = ui->password_input->text();

    // TODO(nostros): borrar
    std::cout << "Intento de login: " << username.toStdString() << " contrseña: " << password.toStdString() << std::endl;

    if (this->validate_data(username, password)) {
        this->hide();
        this->tokenPage->setUserData(this->user_data);
        this->tokenPage->show();
    } else {
       QMessageBox::warning(this, "Error", "Datos incorrectos");
       this->ui->user_input->setText("");
       this->ui->password_input->setText("");
    }
}

void login::on_forgot_button_clicked() {
    this->changePass->setModal(true);
    this->changePass->show();
}

