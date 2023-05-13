#include "consult_requests.h"
#include "ui_consult_requests.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>


consult_requests::consult_requests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_requests) {
    ui->setupUi(this);
    this->setWindowTitle("Consultar Solicitudes");
    ui->scrollArea->setVerticalScrollBar(ui->verticalScrollBar);
    this->container = new QWidget();
    this->description = new request_description(nullptr);
    ui->scrollArea->setWidget(container);
    this->layout = new QVBoxLayout(container);
    this->requests_buttons.push_back(new description_button( "1", container, 0, 2));
    this->connect(this->requests_buttons[0], &description_button::pressed, this
                  , &consult_requests::show_description);
    this->requests_buttons.push_back(new description_button( "2", container, 1, WORK_PROOF));
    this->connect(this->requests_buttons[1], &description_button::pressed, this
                  , &consult_requests::show_description);

    this->requests_buttons.push_back(new description_button( "3", container, 2, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[2], &description_button::pressed, this
                  , &consult_requests::show_description);

    this->requests_buttons.push_back(new description_button( "4", container, 3, SALARY_PROOF));
    this->connect(this->requests_buttons[3], &description_button::pressed, this
                  , &consult_requests::show_description);

    this->requests_buttons.push_back(new description_button( "5", container, 4, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[4], &description_button::pressed, this
                  , &consult_requests::show_description);

    this->requests_buttons.push_back(new description_button( "6", container, 5, PAYMENT_PROOF));
    this->connect(this->requests_buttons[5], &description_button::pressed, this
                  , &consult_requests::show_description);

    this->requests_buttons.push_back(new description_button( "7", container, 6, WORK_PROOF));
    this->connect(this->requests_buttons[6], &description_button::pressed, this
                  , &consult_requests::show_description);

    this->requests_buttons.push_back(new description_button( "8", container, 7, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[7], &description_button::pressed, this
                  , &consult_requests::show_description);

    this->requests_buttons.push_back(new description_button( "9", container, 8, REQUEST_VACATIONS));
    this->connect(this->requests_buttons[8], &description_button::pressed, this
                  , &consult_requests::show_description);

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


void consult_requests::set_user_login(login_info * user_login) {
    this->users_login = user_login;
}


consult_requests::~consult_requests() {
    delete this->ui;
    delete this->description;
}


void consult_requests::show_description(int id, int type) {
    // TODO (nosotros): Borrar y cambiar la fecha y la descripción (se realizará cuando se tengan los datos del servidor)
    Q_UNUSED(id)
    QString newString = "Me gusta jugar";
    int new_type = type;
    this->description->set_atributes(9, 8, 2020, new_type, newString, newString, this->requests_buttons[id], this->users_login, false);
    this->description->setModal(true);
    this->description->show();
}
