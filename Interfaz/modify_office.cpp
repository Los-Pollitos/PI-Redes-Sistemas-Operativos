#include "modify_office.h"
#include "ui_modify_office.h"
#include <QMessageBox>

modify_office::modify_office(QWidget *parent) : QDialog(parent), ui(new Ui::modify_office) {
    ui->setupUi(this);

    // window name
    this->setWindowTitle("Modificar sucursales");
}

modify_office::~modify_office() {
    delete ui;
}

void modify_office::set_colors() {
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->name->setStyleSheet("color: #001f21;");
    this->ui->id->setStyleSheet("color: #001f21;");
    this->ui->password->setStyleSheet("color: #001f21;");
    this->ui->label2->setStyleSheet("color: #001f21;");
    this->ui->label1->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->change_name->setStyleSheet("color: #001f21;");
    this->ui->delete_2->setStyleSheet("color: #001f21;");
    this->ui->create->setStyleSheet("color: #001f21;");
}

void modify_office::on_change_name_clicked() {
    std::string to_send = "\0";
    bool is_number = true;

    this->ui->id->text().toInt(&is_number);

    if (is_number && this->ui->name->text().length() > 0) {
        to_send = " " + this->ui->id->text().toStdString() + "," + this->ui->name->text().toStdString()
                  + "," + this->user_login->user;
        to_send[0] = MODIFY_OFFICE_NAME;
        this->check_error(this->local_client->send_and_receive(to_send)
                          , "Error al cambiar el nombre de la sucursal. Recuerde que la sucursal debe ser válida");
    } else if (!is_number) {
        this->check_error("0", "Error: el idnetificador de la sucursal debe ser un número");
    }
}


void modify_office::on_delete_2_clicked() {

}


void modify_office::on_create_clicked() {

}

void modify_office::set_client(client* local_client) {
    this->local_client = local_client;
}

void modify_office::set_user_login(login_info* user_login) {
    this->user_login = user_login;
}

void modify_office::check_error(std::string received, QString error) {
    QMessageBox show_message =  QMessageBox();
    if (received[0] == '0') {
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText(error);
        show_message.exec();
    } else {
        show_message.setWindowTitle("Correcto");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Cambios aplicados");
        show_message.exec();
    }
}
