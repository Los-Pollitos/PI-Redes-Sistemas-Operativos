#include "consult_requests.h"
#include "ui_consult_requests.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>


consult_requests::consult_requests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_requests) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Consultar Solicitudes");
    ui->scrollArea->setVerticalScrollBar(ui->verticalScrollBar);
    this->container = new QWidget();
    this->description = new request_description(nullptr);
    ui->scrollArea->setWidget(container);
    this->layout = new QVBoxLayout(container);
}

consult_requests::~consult_requests() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
    if (this->description) {
        delete this->description;
        this->description = 0;
    }
}

void consult_requests::set_client(client* local_client){
    this->local_client = local_client;
}

void consult_requests::set_user_login(login_info * user_login) {
    this->user_login = user_login;
    this->update_scroll();
}

void consult_requests::update_scroll() {
    // Remove all buttons
    size_t length = this->requests_buttons.size();
    for(size_t count = 0; count < length; ++count) {
        this->layout->removeWidget(this->requests_buttons[count]);
        this->requests_buttons[count]->hide();
    }
    this->requests_buttons.clear();

    // Ask for information from server
    std::string to_send = " " + this->user_login->user;
    to_send[0] = SEE_CONSULT_REQUESTS;
    to_send =  this->local_client->send_and_receive(to_send);

    // Separate the data received
    std::string id_temp = "\0";
    std::string type_temp = "\0";
    std::string button_content = "\0";
    int id = 0;
    int type = 0;

    for (size_t i = 0; i < to_send.length(); ++i) {
        id_temp = "\0";
        type_temp = "\0";
        button_content = "\0";

        while(to_send[i] != '-') {  // id
            id_temp += to_send[i++];
        }

        // TODO(nosotros): borrar
        qDebug() << id_temp;

        id = stoi(id_temp);
        ++i;

        while(to_send[i] != '-') {  // type
            type_temp += to_send[i++];
        }
        type = stoi(type_temp);
        ++i;

        while(to_send[i] != ',' && to_send[i] != '\0') {
            button_content += to_send[i++];
        }

        this->requests_buttons.push_back(new description_button(QString::fromStdString(button_content), container, requests_buttons.size()-1, type, id));
        this->connect(this->requests_buttons[requests_buttons.size()-1], &description_button::disapear, this
                      , &consult_requests::update_scroll);
        this->connect(this->requests_buttons[requests_buttons.size()-1], &description_button::pressed, this
                      , &consult_requests::show_description);
        layout->addWidget(this->requests_buttons[requests_buttons.size()-1]);
    }
}

void consult_requests::show_description(int vector_pos, int type) {
    std::string to_send = " " + std::to_string(this->requests_buttons[vector_pos + 1]->get_id_requests()) + "," + std::to_string(type);
    to_send[0] = CONSULT_REQUESTS;
    to_send = this->local_client->send_and_receive(to_send);  // day, month, year, content

    int pos = 0;
    std::string temp = "\0";
    int day = 0;
    int month = 0;
    int year = 0;
    QString content = "\0";

    // day
    while(to_send[pos] != ',') {
        temp += to_send[pos++];
    }
    day = stoi(temp);
    temp = "\0";
    ++pos;

    // month
    while(to_send[pos] != ',') {
        temp += to_send[pos++];
    }
    month = stoi(temp);
    temp = "\0";
    ++pos;

    // year
    while(to_send[pos] != ',') {
        temp += to_send[pos++];
    }
    year = stoi(temp);
    ++pos;

    // content
    while(to_send[pos] != '\0') {
        content += to_send[pos++];
    }
    content += '\0';

    this->description->set_client(this->local_client);
    this->description->set_atributes(day, month, year, type, QString::fromStdString(this->user_login->user)
                                     , content, this->requests_buttons[vector_pos + 1], this->user_login, false);
    this->description->setModal(true);
    this->description->show();
}
