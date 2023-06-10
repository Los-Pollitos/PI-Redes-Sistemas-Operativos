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
    // Remove all buttos
    size_t length = this->requests_buttons.size();
    for(size_t count = 0; count < length; ++count) {
        this->layout->removeWidget(this->requests_buttons[count]);
        this->requests_buttons[count]->hide();
        this->requests_buttons.erase(this->requests_buttons.begin()+(count));
    }

    // Ask for information from server
    std::string to_send = " " + this->user_login->user + ",";
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
        id = stoi(id_temp);

        while(to_send[i] != '-') {  // type
            type_temp += to_send[i++];
        }
        type = stoi(type_temp);

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

void consult_requests::show_description(int id, int type) {
//    Q_UNUSED(id)
//    QString newString = "Me gusta jugar";
//    int new_type = type;
//    this->description->set_client(this->local_client);
//    this->description->set_atributes(9, 8, 2020, new_type, newString, newString, this->requests_buttons[id], this->user_login, true);
//    this->description->setModal(true);
//    this->description->show();
}
