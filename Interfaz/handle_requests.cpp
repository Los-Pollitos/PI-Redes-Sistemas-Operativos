#include "handle_requests.h"
#include "ui_handle_requests.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>


handle_requests::handle_requests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::handle_requests) {
    ui->setupUi(this);
    ui->scrollArea->setVerticalScrollBar(ui->verticalScrollBar);
    this->container = new QWidget();
    ui->scrollArea->setWidget(container);
    this->layout = new QVBoxLayout(container);
    this->requests_buttons.push_back(new description_button( "1", container, 0, 2));
    this->connect(this->requests_buttons[0], &description_button::disapear, this
        , &handle_requests::update_scroll);
    this->connect(this->requests_buttons[0], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "2", container, 1, WORK_PROOF));
    this->connect(this->requests_buttons[1], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[1], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    this->requests_buttons.push_back(new description_button( "3", container, 2, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[2], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[2], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    this->requests_buttons.push_back(new description_button( "4", container, 3, SALARY_PROOF));
    this->connect(this->requests_buttons[3], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[3], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    this->requests_buttons.push_back(new description_button( "5", container, 4, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[4], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[4], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    this->requests_buttons.push_back(new description_button( "6", container, 5, PAYMENT_PROOF));
    this->connect(this->requests_buttons[5], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[5], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    this->requests_buttons.push_back(new description_button( "7", container, 6, WORK_PROOF));
    this->connect(this->requests_buttons[6], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[6], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    this->requests_buttons.push_back(new description_button( "8", container, 7, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[7], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[7], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    this->requests_buttons.push_back(new description_button( "9", container, 8, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[8], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->connect(this->requests_buttons[8], &description_button::disapear, this
                  , &handle_requests::update_scroll);
    layout->addWidget(this->requests_buttons[0]);
    layout->addWidget(this->requests_buttons[1]);
    layout->addWidget(this->requests_buttons[2]);
    layout->addWidget(this->requests_buttons[3]);
    layout->addWidget(this->requests_buttons[4]);
    layout->addWidget(this->requests_buttons[5]);
    layout->addWidget(this->requests_buttons[6]);
    layout->addWidget(this->requests_buttons[7]);
    layout->addWidget(this->requests_buttons[8]);

}


void handle_requests::set_user_data(login_info * user_data) {
    this->user_data = user_data;
}


handle_requests::~handle_requests() {
    delete ui;
}

void handle_requests::update_scroll() {
    int length = this->requests_buttons.size();
    for(int count = 0; count < length; ++count) {
        this->layout->removeWidget(this->requests_buttons[count]);
        this->requests_buttons[count]->hide();
    }
    int index = 0;
    for(int count = 0; count < length; ++count) {
        if (this->requests_buttons[index]->valid) {
            this->layout->addWidget(this->requests_buttons[index]);
            this->requests_buttons[index]->show();
            ++index;
        } else {
            std::cout << "Mando a borrar a  " << this->requests_buttons[index]->getId() << " en la pos " << index << std::endl;
            // this->layout->removeWidget(this->requests_buttons[index]);
            //description_button * victim =  requests_buttons[index];
            this->requests_buttons.erase(this->requests_buttons.begin()+(index-1));
            //delete victim;
        }
    }
}

void handle_requests::remove_request(int index) {
    std::cout << "Voy a borrar widget\n";
    this->layout->removeWidget(this->requests_buttons[index]);
    std::cout << "Borre widget y voy con boton\n";
    description_button * victim =  requests_buttons[index];
    delete victim;
    this->requests_buttons[index] = 0;
    std::cout << "Borre boton \n";
    if (this->requests_buttons.size() > 1) {
        for (int element = index; element < this->requests_buttons.size()-1; ++element) {
            this->requests_buttons[element] = this->requests_buttons[element+1];
            // this->requests_buttons[element+1] = 0;
            std::cout << "Movi boton \n";
        }
    }
    if (this->requests_buttons.size() > 0) {
        this->requests_buttons[this->requests_buttons.size() - 1] = 0;
        this->requests_buttons.pop_back();
        std::cout <<"Me quedan: " << this->requests_buttons.size() << " botones\n";
    }
}

void handle_requests::show_description(int id, int type) {
    // TODO (nosotros): Borrar y cambiar la fecha y la descripción
    Q_UNUSED(id)
    QString newString = "Me gusta jugar";
    int new_type = type;
    this->description = new request_description(nullptr);
    this->description->set_atributes(9, 8, 2020, new_type, newString, newString, this->requests_buttons[id], this->user_data);
    this->description->setModal(true);
    this->description->show();
}
