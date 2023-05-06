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
    this->label = new QLabel("Datos incorrectos", this);   // el label es de esta ventana
    this->label->setStyleSheet("color:red");  // color del texto
    this-> label->hide();  // inicia escondido
    this->ui->password_input->setEchoMode(QLineEdit::Password); // no muestra password
    this->tokenPage = new Token(this);
    this->changePass = new change_password(this);
}

login::~login()
{
    delete ui;
    delete label;
    delete tokenPage;
}



bool login::validate_data(QString username, QString password) {
    bool correct = false;
 //   try {
        std::ifstream file ("../Etapa2/Archivos/Login.txt");
        std::string read_data = "";
        if (file.is_open()) {
           while (read_data != username.toStdString()) {
               file >> read_data;
               if (read_data != username.toStdString()) {
                   file >> read_data;  // don't keep the password
                   file >> read_data; // don't keep token
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
                   }
               }
           }

        }
 //   } catch (_exception e) {  // TODO (nosotros): volver después
 //       std::cerr << "Archivo de login no encontrado" << std::endl;
 //   }
       return correct;
}

void login::on_login_button_clicked() {
    QString username = ui->user_input->text();  // get username
    QString password = ui->password_input->text();
    this->label->hide();   
    if (validate_data(username, password)) {
        this->hide();
        this->tokenPage->setUserData(this->user_data);
        this->tokenPage->show();
    } else {
        this->label->resize(200, 200); // size of label
        this->label->setGeometry(QRect(95, 230, 100, 20)); // position of label
        this->label->show(); // se muestra label
    }
}

void login::on_forgot_button_clicked()
{
    this->hide();
    this->changePass->show();
}

