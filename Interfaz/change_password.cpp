#include "change_password.h"
#include "ui_change_password.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <QMessageBox>

/**
 * @brief Construct a new change password::change password object
 * 
 * @param parent Parent window
 */
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
    this->ui->groupBox->setStyleSheet("color: #001f21;");
    this->ui->pushButton_reinicarContra->setStyleSheet("color: #001f21;");
    this->ui->indicacion_label->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Cambiar contraseña");
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password); // no muestra password
    this->ui->lineEdit_3->setEchoMode(QLineEdit::Password); // no muestra token
    this->ui->lineEdit_4->setEchoMode(QLineEdit::Password); // no muestra confirmacion
    this->pos = (int)(rand()%6);
    int columna = pos%3 +1;
    int fila = pos/3+1;
    this->ui->indicacion_label->setText("Fila: " + QString::number(fila) + " Columna: " + QString::number(columna));
}

/**
 * @brief Destroy the change password::change password object
 * 
 */
change_password::~change_password()
{
    if (this->ui) {
        delete ui;
        this->ui = 0;
    }
}

/**
 * @brief Receives local client from previous window and uses it
 * 
 * @param local_client 
 */
void change_password::set_client(client* local_client){
    this->local_client = local_client;
}

/**
 * @brief Comunicates with client to change password
 * 
 * @param username Username that wants to change password
 * @param password New password
 * @param token Token asked for validation
 * @return true if it was succesful
 * @return false if data was incorrect
 */
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


/**
 * @brief Indicates that password must be changed
 * 
 */
void change_password::on_pushButton_reinicarContra_clicked()
{
    if (this->ui->lineEdit->text() == "" || this->ui->lineEdit_2->text() == "" ||
            this->ui->lineEdit_3->text() == "" || this->ui->lineEdit_4->text() == ""){
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Datos incompletos");
        show_message.exec();

    } else if(this->ui->lineEdit_2->text() != this->ui->lineEdit_4->text()) {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Las contraseñas no son iguales");
        show_message.exec();

    } else {
        if (this->change_data(this->ui->lineEdit->text(), this->ui->lineEdit_2->text(), std::stoi(this->ui->lineEdit_3->text().toStdString()))) {
            this->hide();
        } else {
            QMessageBox show_message =  QMessageBox();
            show_message.setWindowTitle("Error");
            show_message.setModal(true);
            show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_message.setText("Datos incompletos");
            this->ui->lineEdit->setText("");
            this->ui->lineEdit_2->setText("");
            this->ui->lineEdit_3->setText("");
            this->ui->lineEdit_4->setText("");
        }
    }
}

