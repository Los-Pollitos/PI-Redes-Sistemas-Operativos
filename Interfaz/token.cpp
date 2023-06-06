#include "token.h"
#include "ui_token.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

/**
 * @brief Construct a new Token:: Token object
 * 
 * @param parent 
 */
Token::Token(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Token)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->cancel_button->setStyleSheet("color: #001f21;");
    this->ui->indicacion_label->setStyleSheet("color: #001f21;");
    this->ui->token_input->setStyleSheet("color: #001f21;");
    this->ui->validate_label->setStyleSheet("color: #001f21;");
    this->ui->token_input->setEchoMode(QLineEdit::Password);
    srand (time(NULL));
    this->setWindowTitle("Ingreso de token");
    this->initial_page = new initial();
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
}

/**
 * @brief Receives and stores a client
 * 
 * @param local_client Client to be stored
 */
void Token::set_client(client* local_client){
    this->local_client = local_client;
}

/**
 * @brief Destroy the Token:: Token object
 * 
 */
Token::~Token()
{
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
    if (this->initial_page) {
       delete this->initial_page;
       this->initial_page = 0;
    }
}

/**
 * @brief Receives and stores the information of a user
 * 
 * @param user_data The login information of the user
 */
void Token::setUserData(login_info * user_data) {
    this->user_data = user_data;
    this->pos = (int)(rand()%6);
    int columna = pos%3 +1;
    int fila = pos/3+1;
    this->ui->indicacion_label->setText("Fila: " + QString::number(fila) + " Columna: " + QString::number(columna));
}

/**
 * @brief Receives and stores the cancel logic button
 * 
 * @param parent_button Cancel logic button
 */
void Token::setParent_Button(logout_button * parent_button){
    this->parent_button = parent_button;
}

/**
 * @brief Checks if data is correct
 * 
 */
void Token::on_validate_label_clicked() {
    QString tok = ui->token_input->text();
    try {
        if (std::stoi(tok.toStdString()) == this->user_data->token[this->pos]) {
            this->ui->token_input->clear();
            this->hide();
            this->initial_page->set_client(this->local_client);
            this->initial_page->setUserDataLogin(this->user_data);
            this->initial_page->setParent_Button(this->parent_button);
            this->initial_page->setModal(true);
            this->initial_page->show();
        } else {
            QMessageBox::warning(this, "Error", "Token incorrecto");
        }
    } catch (const std::runtime_error& exception) {
       std::cerr << exception.what() << std::endl;
    }

}

/**
 * @brief Sends a signal to hide token window and show login window
 * 
 */
void Token::on_cancel_button_clicked() {
    emit this->parent_button->pressed();
    this->ui->token_input->clear();
    this->hide();
    this->parent_button->valid = false;
}

