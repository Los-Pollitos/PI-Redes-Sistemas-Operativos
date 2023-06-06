#include "change_password.h"
#include "ui_change_password.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <QMessageBox>

change_password::change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->label_2->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->label_4->setStyleSheet("color: #001f21;");
    this->ui->lineEdit->setStyleSheet("color: #001f21;");
    this->ui->lineEdit_2->setStyleSheet("color: #001f21;");
    this->ui->lineEdit_3->setStyleSheet("color: #001f21;");
    this->ui->lineEdit_4->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Cambiar contraseña");
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password); // no muestra password
    this->ui->lineEdit_3->setEchoMode(QLineEdit::Password); // no muestra token
    this->ui->lineEdit_4->setEchoMode(QLineEdit::Password); // no muestra confirmacion
    this->pos = (int)(rand()%6);
    int columna = pos%3 +1;
    int fila = pos/3+1;
    this->ui->indicacion_label->setText("Fila: " + QString::number(fila) + " Columna: " + QString::number(columna));
}

change_password::~change_password()
{
    if (this->ui) {
        delete ui;
        this->ui = 0;
    }
}

void change_password::set_client(client* local_client){
    this->local_client = local_client;
}

bool change_password::change_data(QString username, QString password, int token) {
    std::string to_send = "";
    to_send += ((char)GET_TOKEN);
    to_send += username.toStdString();
    to_send += ",";
    std::string result = "\0";
    bool return_value = true;
    result = this->local_client->send_and_receive(to_send);
    if (result[0] != 'e') {
        int user_token[6];
        int token_count = 0;
        for (int i = 0; i < TOKEN_SIZE*2; i+=2) {
            user_token[token_count] = (((int)result[i]) - 48)*10 +(((int)result[i+1]) - 48) ;
            ++token_count;
        }
        if (token == user_token[pos]) {
            to_send = "";
            to_send += ((char)GET_CHANGE_PASSWORD);
            to_send += username.toStdString();
            to_send += ",";
            to_send += password.toStdString();
            result = this->local_client->send_and_receive(to_send);
            return_value = ((int)result[0]) - 48;
            std::cout << "el cambio fue correcto?  " << return_value << std::endl;
        } else { // invalid token
            return_value = false;
        }
    } else {
        return_value = false;
    }
    return return_value;
}



void change_password::on_pushButton_reinicarContra_clicked()
{
    if (this->ui->lineEdit->text() == "" || this->ui->lineEdit_2->text() == "" ||
            this->ui->lineEdit_3->text() == "" || this->ui->lineEdit_4->text() == ""){
        QMessageBox::warning(this, "Error", "Datos incompletos");

    } else if(this->ui->lineEdit_2->text() != this->ui->lineEdit_4->text()) {
        QMessageBox::warning(this, "Error", "Las contraseñas no son iguales");

    } else {
        if (this->change_data(this->ui->lineEdit->text(), this->ui->lineEdit_2->text(), std::stoi(this->ui->lineEdit_3->text().toStdString()))) {
            this->hide();
        } else {
            QMessageBox::warning(this, "Error", "Datos incorrectos");
            this->ui->lineEdit->setText("");
            this->ui->lineEdit_2->setText("");
            this->ui->lineEdit_3->setText("");
            this->ui->lineEdit_4->setText("");
        }
    }
}

