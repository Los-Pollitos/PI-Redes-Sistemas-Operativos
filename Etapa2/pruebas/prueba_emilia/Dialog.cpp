#include "Dialog.h"
#include "ui_Dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->ui->token_input->setEchoMode(QLineEdit::Password);
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_validate_label_clicked() {
    QString tok = ui->token_input->text();
    if (tok == "4") {
         QMessageBox::information(this, "Bienvenido", "Datos correctos"); // alternativa al label
         hide();
    } else {
        QMessageBox::warning(this, "Error", "Token incorrecto");
    }
}

