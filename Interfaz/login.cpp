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
    this->tokenPage = new Token(this);
    this->changePass = new change_password(this);
    this->setWindowTitle("Login");
}

login::~login()
{
    delete ui;
    delete tokenPage;
}



bool login::validate_data(QString username, QString password) {
    bool correct = false;
 //   try {
        std::ifstream file ("../Etapa 2/Archivos/Login.txt");
        std::string read_data = "";
        if (file.is_open()) {
           while (read_data != username.toStdString()) {
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
    std::cout << "Intento de login: " << username.toStdString() << " usuario: " << password.toStdString() << std::endl;
    if (this->validate_data(username, password)) {
        this->hide();
        this->tokenPage->setUserData(this->user_data);
        this->tokenPage->show();
    } else {
       QMessageBox::warning(this, "Error", "Datos incorrectos");
    }
}

void login::on_forgot_button_clicked()
{
    this->hide();
    this->changePass->show();
}

