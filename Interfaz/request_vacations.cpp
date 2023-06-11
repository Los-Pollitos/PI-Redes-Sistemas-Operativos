#include <QPushButton>

#include "request_vacations.h"
#include "ui_request_vacations.h"

request_vacations::request_vacations(QWidget *parent) :
        QDialog(parent), ui(new Ui::request_vacations) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->confirm->setStyleSheet("color: #001f21;");
    this->ui->label_start->setStyleSheet("color: #001f21;");
    this->ui->add_day->setStyleSheet("color: #001f21;");
    this->ui->start_date->setStyleSheet("color: #001f21;");
    this->ui->turn_lable->setStyleSheet("color: #001f21;");
    this->ui->comboBox->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Solicitud de vacaciones");
    ui->add_day->setStyleSheet("background-color: gray");
    ui->confirm->setStyleSheet("background-color: green");
    // Set the display format
    this->ui->start_date->setDisplayFormat("dd.MM.yyyy");
}

request_vacations::~request_vacations() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
}

void request_vacations::set_client(client* local_client) {
    this->local_client = local_client;
}

void request_vacations::reset_window() {
    // Reset the to_send string to it's base
    this->to_send = ((char)VACATION_REQUEST);
    this->ui->start_date->setDate(QDate::currentDate());
    this->ui->start_date->setMinimumDate(QDate::currentDate());
}

void request_vacations::set_current_user(std::string user) {
    // Used for datagram
    this->user = user;
    // Add the user to to_send
    this->to_send += user;
    this->to_send += ',';
}

void request_vacations::on_add_day_clicked() {
    // Get the selected date
    QDate date = this->ui->start_date->date();
    std::string selected_date = date.toString("dd.MM.yyyy").toStdString();

    std::cout << "TENGO " << selected_date <<std::endl;

    // Get the turn from the combobox
    std::string selected_turn = this->ui->comboBox->currentText().toStdString();

    std::cout << "TENGO " << selected_turn <<std::endl;

    // Format them into to_send
    this->to_send += selected_date + " - " + selected_turn + "\n";

    std::cout << "TO SEND " << to_send << std::endl;
}

void request_vacations::on_confirm_clicked() {

}

