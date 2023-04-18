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
    QWidget * container = new QWidget();
    ui->scrollArea->setWidget( container );
    this->layout = new QVBoxLayout(container);
    this->requests_buttons.push_back(new description_button( "1", container, 0, 2));
    this->connect(this->requests_buttons[0], &description_button::pressed, this
        , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "2", container, 1, WORK_PROOF));
    this->connect(this->requests_buttons[1], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "3", container, 2, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[2], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "4", container, 3, SALARY_PROOF));
    this->connect(this->requests_buttons[3], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "5", container, 4, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[4], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "6", container, 5, PAYMENT_PROOF));
    this->connect(this->requests_buttons[5], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "7", container, 6, WORK_PROOF));
    this->connect(this->requests_buttons[6], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "8", container, 7, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[7], &description_button::pressed, this
                  , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "9", container, 8, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[8], &description_button::pressed, this
                  , &handle_requests::show_description);
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

handle_requests::~handle_requests() {
    delete ui;
}

void handle_requests::update_scroll() {
    int length = this->requests_buttons.size();
    for(int count = 0; count < length; ++count) {
        this->layout->removeWidget(this->requests_buttons[count]);
    }
    for(int count = 0; count < length; ++count) {
        if (this->requests_buttons[count]->getValid()) {
            this->layout->addWidget(this->requests_buttons[count]);
        }
    }
}

void handle_requests::show_description(int id, int type) {
    // TODO (nosotros): Borrar y cambiar la fecha y la descripción (ahora se muere porque la descripción es local)¨
    Q_UNUSED(id)
    this->description = new request_description(9, 8, 2020, type, "Me gusta jugar Mario", nullptr, this->requests_buttons[id]);
    this->description->setModal(true);
    this->description->show();
    // this->update_scroll();
}
