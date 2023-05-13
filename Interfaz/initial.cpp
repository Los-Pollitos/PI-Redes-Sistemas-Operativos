#include "initial.h"
#include "ui_initial.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <iostream>
#include <fstream>


initial::initial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initial) {
    ui->setupUi(this);
    this->setWindowTitle("Inicio");
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
    this->users_data = new user_data();

    this->update_buttons =  new description_button("Manejador de botones", nullptr, -1, 0);
    this->connect(this->update_buttons, &description_button::update_all, this
       , &initial::update_scrollbar);
    this->update_buttons->hide();

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

    layout->addWidget(this->requests_buttons[WORK_PAGE]);
    layout->addWidget(this->requests_buttons[PAYMENT_PAGE]);
    layout->addWidget(this->requests_buttons[SALARY_PAGE]);
    layout->addWidget(this->requests_buttons[SEE_SALARY]);
    layout->addWidget(this->requests_buttons[PENDING_REQUESTS]);
    layout->addWidget(this->requests_buttons[VACATION_MANGER]);
    layout->addWidget(this->requests_buttons[SEE_VACATIONS]);
    layout->addWidget(this->requests_buttons[SEE_RECORD]);
    layout->addWidget(this->requests_buttons[REQUEST_HANDLER]);
    layout->addWidget(this->requests_buttons[REQUEST_HANDLER]);
    layout->addWidget(this->requests_buttons[USER_MANAGER]);
    layout->addWidget(this->requests_buttons[USER_MOD]);

}


void initial::setUserDataLogin(login_info * user_login) {
    this->users_login = user_login;
    this->read_data();
    emit this->update_buttons->update_all();
}

void initial::setParent_Button(logout_button * parent_button){
    this->parent_button = parent_button;
    emit this->update_buttons->update_all();
}


void initial::update_scrollbar() {
    if ((this->users_data->role & EMPLOYEE) == EMPLOYEE) {
        layout->addWidget(this->requests_buttons[WORK_PAGE]);
        layout->addWidget(this->requests_buttons[PAYMENT_PAGE]);
        layout->addWidget(this->requests_buttons[SALARY_PAGE]);
        layout->addWidget(this->requests_buttons[SEE_SALARY]);
        layout->addWidget(this->requests_buttons[PENDING_REQUESTS]);
        layout->addWidget(this->requests_buttons[VACATION_MANGER]);
        layout->addWidget(this->requests_buttons[SEE_VACATIONS]);
        layout->addWidget(this->requests_buttons[SEE_RECORD]);
        this->requests_buttons[WORK_PAGE]->show();
        this->requests_buttons[PAYMENT_PAGE]->show();
        this->requests_buttons[SALARY_PAGE]->show();
        this->requests_buttons[SEE_SALARY]->show();
        this->requests_buttons[PENDING_REQUESTS]->show();
        this->requests_buttons[VACATION_MANGER]->show();
        this->requests_buttons[SEE_VACATIONS]->show();
        this->requests_buttons[SEE_RECORD]->show();
    } else {
        this->layout->removeWidget(this->requests_buttons[WORK_PAGE]);
        this->requests_buttons[WORK_PAGE]->hide();
        this->layout->removeWidget(this->requests_buttons[PAYMENT_PAGE]);
        this->requests_buttons[PAYMENT_PAGE]->hide();
        this->layout->removeWidget(this->requests_buttons[SALARY_PAGE]);
        this->requests_buttons[SALARY_PAGE]->hide();
        this->layout->removeWidget(this->requests_buttons[SEE_SALARY]);
        this->requests_buttons[SEE_SALARY]->hide();
        this->layout->removeWidget(this->requests_buttons[PENDING_REQUESTS]);
        this->requests_buttons[PENDING_REQUESTS]->hide();
        this->layout->removeWidget(this->requests_buttons[VACATION_MANGER]);
        this->requests_buttons[VACATION_MANGER]->hide();
        this->layout->removeWidget(this->requests_buttons[SEE_VACATIONS]);
        this->requests_buttons[SEE_VACATIONS]->hide();
        this->layout->removeWidget(this->requests_buttons[SEE_RECORD]);
        this->requests_buttons[SEE_RECORD]->hide();
    }
    if (((this->users_data->role & SUPERVISOR) == SUPERVISOR) || ((this->users_data->role & HUMAN_RESOURCES) == HUMAN_RESOURCES)) {
         layout->addWidget(this->requests_buttons[REQUEST_HANDLER]);
         this->requests_buttons[REQUEST_HANDLER]->show();
    } else {
        this->layout->removeWidget(this->requests_buttons[REQUEST_HANDLER]);
        this->requests_buttons[REQUEST_HANDLER]->hide();
    }
    if (((this->users_data->role & HUMAN_RESOURCES) == HUMAN_RESOURCES) || ((this->users_data->role & ADMIN_USER) == ADMIN_USER)) {
        layout->addWidget(this->requests_buttons[USER_MANAGER]);
        layout->addWidget(this->requests_buttons[USER_MOD]);
        this->requests_buttons[USER_MANAGER]->show();
        this->requests_buttons[USER_MOD]->show();
    } else {
        this->layout->removeWidget(this->requests_buttons[USER_MANAGER]);
        this->requests_buttons[USER_MANAGER]->hide();
        this->layout->removeWidget(this->requests_buttons[USER_MOD]);
        this->requests_buttons[USER_MOD]->hide();
    }
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
    delete this->users_data;
    delete this->update_buttons;
}


void initial::create_windows(int id, int type) {
   (void) type;
   switch (id) {
    case WORK_PAGE:
      this->work_page->setModal(true);
      this->work_page->show();
      break;
    case PAYMENT_PAGE:
      this->payment_page->setModal(true);
      this->payment_page->show();
      break;
   case SALARY_PAGE:
     this->salary_page->setModal(true);
     this->salary_page->show();
     break;
   case SEE_SALARY:
     this->see_salary->setModal(true);
     this->see_salary->show();
     break;
   case PENDING_REQUESTS:
     this->pending_requests->setModal(true);
     this->pending_requests->set_user_login(this->users_login);
     this->pending_requests->show();
     break;
   case VACATION_MANGER:
     this->vacation_manager->setModal(true);
     this->vacation_manager->show();
     break;
   case SEE_VACATIONS:
     this->see_vacations->setModal(true);
     this->see_vacations->show();
     break;
   case SEE_RECORD:
     this->see_record->setModal(true);
     this->see_record->show();
     break;
   case REQUEST_HANDLER:
     this->request_handler->set_user_login(this->users_login);
     this->request_handler->setModal(true);
     this->request_handler->show();
     break;
   case USER_MANAGER:  
     this->user_manager->set_user_login(this->users_login);
     this->user_manager->setModal(true);
     this->user_manager->show();
     break;
   case USER_MOD:
     this->user_mod->set_login_info(this->users_login);
     this->user_mod->setModal(true);
     this->user_mod->show();
     break;
   }
}

void initial::read_data() {
    std::ifstream data ("../Etapa2/Archivos/Data.txt");
    try {
        std::string temp = " ";
        if (data.is_open()) {
            while(data >> temp && temp != this->users_login->user) { /* Read until user is found*/}
            this->users_data->user = temp;
            this->users_data->name = "";  // se limpia
            data >> temp;
            while (temp[0] < 48 || temp[0] > 58) {  // no es un número
                this->users_data->name.append(temp);
                this->users_data->name.append(" ");
                data >> temp;
            }
            users_data->identification = std::stoi(temp);
            data >> users_data->salary;
            data >> users_data->role;
            data >> users_data->assigned_vacations;
            data >> users_data->available_vacations;
            temp = " ";
            data.close();
        }
    } catch (const std::runtime_error& exception) {
      std::cerr << exception.what() << std::endl;
    }
}


// Logout
void initial::on_pushButton_clicked() {
    emit this->parent_button->pressed();
    // Clean user data
    this->users_data->user = "\0";
    this->users_data->name = "\0";
    this->users_data->identification = 0;
    this->users_data->salary = "\0";
    this->users_data->role = 0;
    this->users_data->assigned_vacations = 0;
    this->users_data->available_vacations = 0;
    // Hide initial window
    this->hide();
    this->parent_button->valid = false;
}

