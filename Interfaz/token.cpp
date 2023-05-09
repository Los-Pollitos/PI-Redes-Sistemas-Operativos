#include "token.h"
#include "ui_token.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

Token::Token(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Token)
{
    ui->setupUi(this);
    this->ui->token_input->setEchoMode(QLineEdit::Password);
    srand (time(NULL));
    this->initial_page = new initial();
}

Token::~Token()
{
    delete this->ui;
    delete this->initial_page;
}

void Token::setUserData(login_info * user_data) {
    this->user_data = user_data;
    this->pos = (int)(rand()%6);
    int columna = pos%3 +1;
    int fila = pos/3+1;
    this->ui->indicacion_label->setText("Fila: " + QString::number(fila) + " Columna: " + QString::number(columna));
}

void Token::on_validate_label_clicked() {
    QString tok = ui->token_input->text();
    // TODO (hacer un try catch que haga lo mismo que el else)
    if (std::stoi(tok.toStdString()) == this->user_data->token[this->pos]) {
        this->hide();
        this->initial_page->setModal(true);
        this->initial_page->setUserData(this->user_data);
        this->initial_page->exec();
    } else {
        QMessageBox::warning(this, "Error", "Token incorrecto");
    }
}
