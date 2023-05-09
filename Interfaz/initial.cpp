#include "initial.h"
#include "ui_initial.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>


initial::initial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initial) {
    ui->setupUi(this);
    ui->scrollArea->setVerticalScrollBar(ui->verticalScrollBar);
    this->container = new QWidget();
    ui->scrollArea->setWidget(container);
    this->layout = new QVBoxLayout(container);
    this->work_page = new work_proof();
    this->payment_page = new payment_proof();
    this->salary_page = new salary_proof();
    this->see_salary = new consult_salary();
    this->pending_requests = new consult_requests();
    this->see_record =  new consult_record();
    this->request_handler =  new handle_requests();
    this->user_manager =  new manage_user();
    this->user_mod = new modify_user();
    this->vacation_manager = new request_vacations();
    this->see_vacations = new vacation_consult();

    //this->requests_buttons.push_back(new description_button( "", container, 0, 2));
    // this->connect(this->requests_buttons[0], &description_button::disapear, this
    //    , &handle_requests::update_scroll);
    //this->connect(this->requests_buttons[0], &description_button::pressed, this
     //             , &handle_requests::show_description);

}


void initial::setUserData(login_info * user_data) {
    this->user_data = user_data;
}


void initial::update_scrollbar() {
    //layout->addWidget(this->requests_buttons[0]);
}

initial::~initial() {
    delete ui;
    delete this->work_page;
    delete this->payment_page;
    delete this->salary_page;
    delete this->see_salary;
    delete this->pending_requests;
    delete this->see_record;
    delete this->request_handler;
    delete this->user_manager;
    delete this->vacation_manager;
    delete this->see_vacations;
    delete this->user_mod;
}


