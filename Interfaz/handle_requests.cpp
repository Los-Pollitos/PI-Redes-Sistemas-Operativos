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
    std::cout << "Volvi de uptate" << std::endl;
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
    std::cout << "vamos a update scroll" <<std::endl;
    size_t length = this->requests_buttons.size();
    for(size_t count = 0; count < length; ++count) {
       this->layout->removeWidget(this->requests_buttons[count]);
       this->requests_buttons[count]->hide();
       this->requests_buttons.erase(this->requests_buttons.begin()+(count));
    }

    std::cout << "vamos a pedirle al server" <<std::endl;

    std::string to_server = "";
    to_server += (char)SEE_PROCESS_REQUESTS;
    to_server += this->user_login->user;
    to_server += ",";
    std::string from_server = "";
    from_server = this->local_client->send_and_receive(to_server);
    from_server += ",";
    std::cout << "Para see process requests, recibi: " << from_server << std::endl;

    std::string temp_user = "";
    std::string temp_id = "";
    std::string temp_type = "";
    int id = 0;
    int type = 0;
    std::string temp_to_show = "";
    for (int i = 0; i < from_server.length(); ++i) {
       std::cout << "procesando: " << from_server[i] << std::endl;
       if (from_server[i] != ',') {
           while (from_server[i] != ':') {
               temp_user += from_server[i];
               ++i;
           }
           ++i; // skip :
           while (from_server[i] != ':') {
               temp_id += from_server[i];
               ++i;
           }
           ++i; // skip :
           while (from_server[i] != ':') {
               std::cout << "while " << from_server[i] << std::endl;
               temp_type += from_server[i];
               ++i;
           }
       } else {
           type = (int)(temp_type[0] -48);
           id = (int)(temp_id[0] -48);
           temp_to_show = temp_user;
           temp_to_show += " : ";
           switch (type) {
               case VACATION:
                    temp_to_show += "Vacaciones";
                    break;
               case PROOF:
                    temp_to_show += "Constancia";
                    break;
           }
           std::cout << "Voy a poner un boton con " << temp_to_show << std::endl;
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

void handle_requests::show_description(int id, int type) {
    // TODO (nosotros): Borrar y cambiar la fecha y la descripción (se realizará cuando se tengan los datos del servidor)
    Q_UNUSED(id)
    QString newString = "Me gusta jugar";
    int new_type = type;
    this->description->set_client(this->local_client);
    this->description->set_atributes(9, 8, 2020, new_type, newString, newString, this->requests_buttons[id], this->user_login, true);
    this->description->setModal(true);
    this->description->show();
}
