#include "token.h"
#include "ui_token.h"

Token::Token(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Token)
{
    ui->setupUi(this);
    this->ui->token_input->setEchoMode(QLineEdit::Password);
}

Token::~Token()
{
    delete ui;
}

void Token::on_validate_label_clicked() {
    QString tok = ui->token_input->text();
    if (tok == "4") {
        this->hide();
        this->initial_page = new initial();
        this->initial_page->setModal(true);
        this->initial_page->exec();
    } else {
        QMessageBox::warning(this, "Error", "Token incorrecto");
    }
}

