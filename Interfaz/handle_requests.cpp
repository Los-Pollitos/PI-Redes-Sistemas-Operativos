#include "handle_requests.h"
#include "ui_handle_requests.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>


handle_requests::handle_requests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::handle_requests) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->setWindowTitle("Procesar Solicitudes");
    this->description = new request_description(nullptr);
    ui->scrollArea->setVerticalScrollBar(ui->verticalScrollBar);
    this->container = new QWidget();
    ui->scrollArea->setWidget(container);
    this->layout = new QVBoxLayout(container);
}


void handle_requests::set_user_login(login_info * user_login) {
    this->user_login = user_login;
    this->update_scroll();
}


void handle_requests::set_client(client* local_client){
    this->local_client = local_client;
}

handle_requests::~handle_requests() {
    if (this->ui) {
        delete this->ui;
        this->ui = 0;
    }
    if (this->description) {
       delete this->description;
       this->description = 0;
    }
}

void handle_requests::update_scroll() {
    // Remove all buttons
    size_t length = this->requests_buttons.size();
    for(size_t count = 0; count < length; ++count) {
       this->layout->removeWidget(this->requests_buttons[count]);
       this->requests_buttons[count]->hide();
    }
    this->requests_buttons.clear();

    // Ask for information from server
    std::string to_server = "";
    to_server += (char)SEE_PROCESS_REQUESTS;
    to_server += this->user_login->user;
    to_server += ",";
    std::string from_server = "";
    from_server = this->local_client->send_and_receive(to_server);
    if (from_server[0] != '0') {  // there is a button to create
       from_server += ",";

       // Start separating data
       std::string temp_user = "";
       std::string temp_id = "";
       std::string temp_type = "";
       int id = 0;
       int type = 0;
       std::string temp_to_show = "";
       for (size_t i = 0; i < from_server.length(); ++i) {
           if (from_server[i] != ',') { // get username
               while (from_server[i] != ':') {
                   temp_user += from_server[i];
                   ++i;
               }
               ++i; // skip :
               while (from_server[i] != ':') { // get id
                   temp_id += from_server[i];
                   ++i;
               }
               ++i; // skip :
               while (from_server[i] != ':') { // get type
                   temp_type += from_server[i];
                   ++i;
               }
           } else {
               type = (int)(temp_type[0] -48);
               id = (int)(temp_id[0] -48);
               temp_to_show = temp_user;
               temp_to_show += ": ";
               switch (type) {
               case VACATION:
                   temp_to_show += "Vacaciones";
                   break;
               case PROOF:
                   temp_to_show += "Constancia";
                   break;
               }
               this->requests_buttons.push_back(new description_button(QString::fromStdString(temp_to_show), container, requests_buttons.size()-1, type, id));
               this->connect(this->requests_buttons[requests_buttons.size()-1], &description_button::disapear, this
                             , &handle_requests::update_scroll);
               this->connect(this->requests_buttons[requests_buttons.size()-1], &description_button::pressed, this
                             , &handle_requests::show_description);
               layout->addWidget(this->requests_buttons[requests_buttons.size()-1]);
               temp_user = "";
               temp_id = "";
               temp_type = "";
               temp_to_show = "";
           }
       }
    }
}

void handle_requests::show_description(int vector_pos, int type) {
    std::string to_send = " " + std::to_string(this->requests_buttons[vector_pos + 1]->get_id_requests()) + "," + std::to_string(type);
    to_send[0] = CONSULT_REQUESTS;
    to_send = this->local_client->send_and_receive(to_send);  // day, month, year, content
//    if (type == VACATION) {
//       to_send = to_send.substr(0, to_send.find("&"));
//    }

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
    while(to_send[pos] != ',' && to_send[pos] != '\0' && to_send[pos] != '&') {
       content += to_send[pos++];
    }
    content += '\0';

    this->description->set_client(this->local_client);
    this->description->set_atributes(day, month, year, type, QString::fromStdString(this->user_login->user)
                                     , content, this->requests_buttons[vector_pos + 1], this->user_login, true);
    this->description->setModal(true);
    this->description->show();
}
