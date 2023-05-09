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

    this->requests_buttons.push_back(new description_button( "Constancia Laboral", container, WORK_PAGE, 0));
    this->connect(this->requests_buttons[0], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Constancia de pago", container, PAYMENT_PAGE, 0));
    this->connect(this->requests_buttons[1], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Constancia salarial", container, SALARY_PAGE, 0));
    this->connect(this->requests_buttons[2], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Consultar salario", container, SEE_SALARY, 0));
    this->connect(this->requests_buttons[3], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Ver solicitudes", container, PENDING_REQUESTS, 0));
    this->connect(this->requests_buttons[4], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Solicitar vacaciones", container, VACATION_MANGER, 0));
    this->connect(this->requests_buttons[5], &description_button::pressed, this
           , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Saldo de vacaciones", container, SEE_VACATIONS, 0));
    this->connect(this->requests_buttons[6], &description_button::pressed, this
           , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Ver anotaciones al expediente", container, SEE_RECORD, 0));
    this->connect(this->requests_buttons[7], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Procesar solicitudes", container, REQUEST_HANDLER, 0));
    this->connect(this->requests_buttons[8], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Crear y borrar usuarios", container, USER_MANAGER, 0));
    this->connect(this->requests_buttons[9], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Modificar usuarios", container, USER_MOD, 0));
    this->connect(this->requests_buttons[10], &description_button::pressed, this
        , &initial::create_windows);

    this->update_scrollbar();

}


void initial::setUserData(login_info * user_data) {
    this->user_data = user_data;
}


void initial::update_scrollbar() {
    // TODO (nosotros): poner ifs
    layout->addWidget(this->requests_buttons[WORK_PAGE]);
    layout->addWidget(this->requests_buttons[PAYMENT_PAGE]);
    layout->addWidget(this->requests_buttons[SALARY_PAGE]);
    layout->addWidget(this->requests_buttons[SEE_SALARY]);
    layout->addWidget(this->requests_buttons[PENDING_REQUESTS]);
    layout->addWidget(this->requests_buttons[VACATION_MANGER]);
    layout->addWidget(this->requests_buttons[SEE_VACATIONS]);
    layout->addWidget(this->requests_buttons[SEE_RECORD]);
    layout->addWidget(this->requests_buttons[REQUEST_HANDLER]);
    layout->addWidget(this->requests_buttons[USER_MANAGER]);
    layout->addWidget(this->requests_buttons[USER_MOD]);
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

void initial::create_windows(int id, int type) {
   std::cout << id << " " << type << std::endl;
}

