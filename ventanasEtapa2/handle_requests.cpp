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
    QVBoxLayout * layout = new QVBoxLayout(container);
    this->requests_buttons.push_back(new description_button( "1", container, 1, 2));
    this->connect(this->requests_buttons[0], &description_button::pressed, this
        , &handle_requests::show_description);
    this->requests_buttons.push_back(new description_button( "2", container, 2, 3));
    this->requests_buttons.push_back(new description_button( "3", container, 3, 1));
    this->requests_buttons.push_back(new description_button( "4", container, 4, 1));
    this->requests_buttons.push_back(new description_button( "5", container, 5, 1));
    this->requests_buttons.push_back(new description_button( "6", container, 6, 1));
    this->requests_buttons.push_back(new description_button( "7", container, 7, 1));
    this->requests_buttons.push_back(new description_button( "8", container, 8, 1));
    this->requests_buttons.push_back(new description_button( "9", container, 9, 1));
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

void handle_requests::show_description(int id, int type) {
    // lo que va a pasar
    std::cout << "He llegado con " << id << " y " << type << std::endl;
}
