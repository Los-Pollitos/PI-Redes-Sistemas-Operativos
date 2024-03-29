#include "initial.h"
#include "ui_initial.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <iostream>
#include <fstream>


/**
 * @brief Construct a new initial::initial object
 * 
 * @param parent Parent window
 */
initial::initial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initial) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->setWindowTitle("Inicio");
    ui->scrollArea->setVerticalScrollBar(ui->verticalScrollBar);
    this->container = new QWidget();
    ui->scrollArea->setWidget(container);
    this->layout = new QVBoxLayout(container);
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->pushButton->setStyleSheet("color: #001f21;");

    this->work_page = new work_proof();
    this->payment_page = new payment_proof();
    this->salary_page = new salary_proof();
    this->see_salary = new consult_salary();
    this->pending_requests = new consult_requests();
    this->see_record =  new consult_record();
    this->request_handler =  new handle_requests();
    this->user_manager =  new manage_user();
    this->user_mod = new modify_user();
    this->new_token = new generate_new_token();
    this->vacation_manager = new request_vacations();
    this->see_vacations = new vacation_consult();
    this->local_client = new client();
    this->office_mod = new modify_office();
    this->see_office = new office_description();
    this->auditor_page = new auditor();
    this->sys_config_page = new sys_config();


    this->update_buttons =  new description_button("Manejador de botones", nullptr, -1, 0);
    this->connect(this->update_buttons, &description_button::update_all, this
       , &initial::update_scrollbar);
    this->update_buttons->hide();

    this->requests_buttons.push_back(new description_button( "Funciones de empleado:", container, EMPLOYEE_SEP, 0));

    this->requests_buttons.push_back(new description_button( "Constancia laboral", container, WORK_PAGE, 0));
    this->connect(this->requests_buttons[WORK_PAGE], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Constancia de pago", container, PAYMENT_PAGE, 0));
    this->connect(this->requests_buttons[PAYMENT_PAGE], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Constancia salarial", container, SALARY_PAGE, 0));
    this->connect(this->requests_buttons[SALARY_PAGE], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Consultar salario", container, SEE_SALARY, 0));
    this->connect(this->requests_buttons[SEE_SALARY], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Ver solicitudes", container, PENDING_REQUESTS, 0));
    this->connect(this->requests_buttons[PENDING_REQUESTS], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Solicitar vacaciones", container, VACATION_MANAGER, 0));
    this->connect(this->requests_buttons[VACATION_MANAGER], &description_button::pressed, this
           , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Saldo de vacaciones", container, SEE_VACATIONS, 0));
    this->connect(this->requests_buttons[SEE_VACATIONS], &description_button::pressed, this
           , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Ver anotaciones al expediente", container, SEE_RECORD, 0));
    this->connect(this->requests_buttons[SEE_RECORD], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Funciones de supervisor:", container, SUPERVISOR_SEP, 0));


    this->requests_buttons.push_back(new description_button( "Procesar solicitudes", container, REQUEST_HANDLER, 0));
    this->connect(this->requests_buttons[REQUEST_HANDLER], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Manejo de usuarios:", container, USER_SEP, 0));

    this->requests_buttons.push_back(new description_button( "Crear y borrar usuarios", container, USER_MANAGER, 0));
    this->connect(this->requests_buttons[USER_MANAGER], &description_button::pressed, this
       , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Modificar usuarios", container, USER_MOD, 0));
    this->connect(this->requests_buttons[USER_MOD], &description_button::pressed, this
        , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Generar token usuario", container, CHANGE_TOKEN, 0));
    this->connect(this->requests_buttons[CHANGE_TOKEN], &description_button::pressed, this
                  , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Ver sucursales", container, SEE_OFFICE, 0));
    this->connect(this->requests_buttons[SEE_OFFICE], &description_button::pressed, this
                  , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Modificar sucursales", container, OFFICE_MOD, 0));
    this->connect(this->requests_buttons[OFFICE_MOD], &description_button::pressed, this
                  , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Auditoría en Interfaz:", container, AUDITOR_SEP, 0));

    this->requests_buttons.push_back(new description_button( "Ver archivo de auditoría", container, AUDITOR_PAGE, 0));
    this->connect(this->requests_buttons[AUDITOR_PAGE], &description_button::pressed, this
                  , &initial::create_windows);

    this->requests_buttons.push_back(new description_button( "Configuración de sistema en Interfaz:", container, SYS_SEP, 0));

    this->requests_buttons.push_back(new description_button( "Modificar configuración del sistema", container, SYS_PAGE, 0));
    this->connect(this->requests_buttons[SYS_PAGE], &description_button::pressed, this
                  , &initial::create_windows);


    for (size_t i = 0; i < this->requests_buttons.size(); ++i) {
        layout->addWidget(this->requests_buttons[i]);
        this->requests_buttons[i]->setStyleSheet("color: #001f21;");
    }
    this->requests_buttons[SUPERVISOR_SEP]->setEnabled(false);
    this->requests_buttons[SUPERVISOR_SEP]->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->requests_buttons[EMPLOYEE_SEP]->setEnabled(false);
    this->requests_buttons[EMPLOYEE_SEP]->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->requests_buttons[USER_SEP]->setEnabled(false);
    this->requests_buttons[USER_SEP]->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->requests_buttons[AUDITOR_SEP]->setEnabled(false);
    this->requests_buttons[AUDITOR_SEP]->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));
    this->requests_buttons[SYS_SEP]->setEnabled(false);
    this->requests_buttons[SYS_SEP]->setStyleSheet(QString("QPushButton {border: 0px;color: #001f21;}"));

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);

}

/**
 * @brief Receives client from parent window, stores it and gives it to other windows
 * 
 * @param local_client Client that will be stored and passed down
 */
void initial::set_client(client* local_client){
    this->local_client = local_client;
    this->work_page->set_client(this->local_client);
    this->payment_page->set_client(this->local_client);
    this->salary_page->set_client(this->local_client);
    this->see_salary->set_client(this->local_client);
    this->pending_requests->set_client(this->local_client);
    this->see_record->set_client(this->local_client);
    this->request_handler->set_client(this->local_client);
    this->user_manager->set_client(this->local_client);
    this->user_mod->set_client(this->local_client);
    this->new_token->set_client(this->local_client);
    this->vacation_manager->set_client(this->local_client);
    this->see_vacations->set_client(this->local_client);
    this->see_office->set_client(this->local_client);
    this->office_mod->set_client(this->local_client);
    this->sys_config_page->set_client(this->local_client);
}

/**
 * @brief Receives login information and stores it
 * 
 * @param user_login login information
 */
void initial::setUserDataLogin(login_info * user_login) {
    this->users_login = user_login;
    int correct = -1;
    this->role = this->ask_for_role(correct);
    emit this->update_buttons->update_all();
    if (correct != 1) {
        // Logout signal
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Error procesando su usuario, por favor intente de nuevo o consulte a su supervisor");
        show_message.exec();
        emit this->parent_button->pressed();
    }
}

/**
 * @brief Receives logout logic button and stores it
 * 
 * @param parent_button Logout logic button
 */
void initial::setParent_Button(logout_button * parent_button){
    this->parent_button = parent_button;
    emit this->update_buttons->update_all();
}

/**
 * @brief Removes and adds necesary buttons acording to user's role
 * 
 */
void initial::update_scrollbar() {
    if ((this->role & UNEMPLOYEED) == UNEMPLOYEED) {
        // show the neccesary buttons
        this->layout->addWidget(this->requests_buttons[WORK_PAGE]);
        this->layout->addWidget(this->requests_buttons[PAYMENT_PAGE]);
        this->layout->addWidget(this->requests_buttons[SALARY_PAGE]);
        this->layout->addWidget(this->requests_buttons[PENDING_REQUESTS]);
        this->layout->addWidget(this->requests_buttons[SEE_RECORD]);
        this->requests_buttons[WORK_PAGE]->show();
        this->requests_buttons[PAYMENT_PAGE]->show();
        this->requests_buttons[SALARY_PAGE]->show();
        this->requests_buttons[PENDING_REQUESTS]->show();
        this->requests_buttons[SEE_RECORD]->show();

        // remove and hide the others
        this->layout->removeWidget(this->requests_buttons[EMPLOYEE_SEP]);
        this->layout->removeWidget(this->requests_buttons[SEE_SALARY]);
        this->layout->removeWidget(this->requests_buttons[VACATION_MANAGER]);
        this->layout->removeWidget(this->requests_buttons[SEE_VACATIONS]);
        this->layout->removeWidget(this->requests_buttons[SUPERVISOR_SEP]);
        this->layout->removeWidget(this->requests_buttons[REQUEST_HANDLER]);
        this->layout->removeWidget(this->requests_buttons[USER_SEP]);
        this->layout->removeWidget(this->requests_buttons[USER_MANAGER]);
        this->layout->removeWidget(this->requests_buttons[USER_MOD]);
        this->layout->removeWidget(this->requests_buttons[CHANGE_TOKEN]);
        this->layout->removeWidget(this->requests_buttons[SEE_OFFICE]);
        this->layout->removeWidget(this->requests_buttons[OFFICE_MOD]);
        this->layout->removeWidget(this->requests_buttons[AUDITOR_SEP]);
        this->layout->removeWidget(this->requests_buttons[AUDITOR_PAGE]);
        this->layout->removeWidget(this->requests_buttons[SYS_SEP]);
        this->layout->removeWidget(this->requests_buttons[SYS_PAGE]);

        this->requests_buttons[EMPLOYEE_SEP]->hide();
        this->requests_buttons[SEE_SALARY]->hide();
        this->requests_buttons[VACATION_MANAGER]->hide();
        this->requests_buttons[SEE_VACATIONS]->hide();
        this->requests_buttons[SUPERVISOR_SEP]->hide();
        this->requests_buttons[REQUEST_HANDLER]->hide();
        this->requests_buttons[USER_SEP]->hide();
        this->requests_buttons[USER_MANAGER]->hide();
        this->requests_buttons[USER_MOD]->hide();
        this->requests_buttons[CHANGE_TOKEN]->hide();
        this->requests_buttons[SEE_OFFICE]->hide();
        this->requests_buttons[OFFICE_MOD]->hide();
        this->requests_buttons[AUDITOR_SEP]->hide();
        this->requests_buttons[AUDITOR_PAGE]->hide();
        this->requests_buttons[SYS_SEP]->hide();
        this->requests_buttons[SYS_PAGE]->hide();
    } else {
        if (this->role == SUPERUSER) {
            // a superuser can do everything
            this->layout->addWidget(this->requests_buttons[EMPLOYEE_SEP]);
            this->layout->addWidget(this->requests_buttons[WORK_PAGE]);
            this->layout->addWidget(this->requests_buttons[PAYMENT_PAGE]);
            this->layout->addWidget(this->requests_buttons[SALARY_PAGE]);
            this->layout->addWidget(this->requests_buttons[SEE_SALARY]);
            this->layout->addWidget(this->requests_buttons[PENDING_REQUESTS]);
            this->layout->addWidget(this->requests_buttons[VACATION_MANAGER]);
            this->layout->addWidget(this->requests_buttons[SEE_VACATIONS]);
            this->layout->addWidget(this->requests_buttons[SEE_RECORD]);
            this->layout->addWidget(this->requests_buttons[SUPERVISOR_SEP]);
            this->layout->addWidget(this->requests_buttons[REQUEST_HANDLER]);
            this->layout->addWidget(this->requests_buttons[USER_SEP]);
            this->layout->addWidget(this->requests_buttons[USER_MANAGER]);
            this->layout->addWidget(this->requests_buttons[USER_MOD]);
            this->layout->addWidget(this->requests_buttons[CHANGE_TOKEN]);
            this->layout->addWidget(this->requests_buttons[SEE_OFFICE]);
            this->layout->addWidget(this->requests_buttons[OFFICE_MOD]);
            this->layout->addWidget(this->requests_buttons[AUDITOR_SEP]);
            this->layout->addWidget(this->requests_buttons[AUDITOR_PAGE]);
            this->layout->addWidget(this->requests_buttons[SYS_SEP]);
            this->layout->addWidget(this->requests_buttons[SYS_PAGE]);

            this->requests_buttons[EMPLOYEE_SEP]->show();
            this->requests_buttons[WORK_PAGE]->show();
            this->requests_buttons[PAYMENT_PAGE]->show();
            this->requests_buttons[SALARY_PAGE]->show();
            this->requests_buttons[SEE_SALARY]->show();
            this->requests_buttons[PENDING_REQUESTS]->show();
            this->requests_buttons[VACATION_MANAGER]->show();
            this->requests_buttons[SEE_VACATIONS]->show();
            this->requests_buttons[SEE_RECORD]->show();
            this->requests_buttons[SUPERVISOR_SEP]->show();
            this->requests_buttons[REQUEST_HANDLER]->show();
            this->requests_buttons[USER_SEP]->show();
            this->requests_buttons[USER_MANAGER]->show();
            this->requests_buttons[USER_MOD]->show();
            this->requests_buttons[CHANGE_TOKEN]->show();
            this->requests_buttons[SEE_OFFICE]->show();
            this->requests_buttons[OFFICE_MOD]->show();
            this->requests_buttons[AUDITOR_SEP]->show();
            this->requests_buttons[AUDITOR_PAGE]->show();
            this->requests_buttons[SYS_SEP]->show();
            this->requests_buttons[SYS_PAGE]->show();
        } else {
            this->layout->removeWidget(this->requests_buttons[SEE_OFFICE]);
            this->requests_buttons[SEE_OFFICE]->hide();
            this->layout->removeWidget(this->requests_buttons[OFFICE_MOD]);
            this->requests_buttons[OFFICE_MOD]->hide();
            if ((this->role & EMPLOYEE) == EMPLOYEE) {
                this->layout->addWidget(this->requests_buttons[EMPLOYEE_SEP]);
                this->layout->addWidget(this->requests_buttons[WORK_PAGE]);
                this->layout->addWidget(this->requests_buttons[PAYMENT_PAGE]);
                this->layout->addWidget(this->requests_buttons[SALARY_PAGE]);
                this->layout->addWidget(this->requests_buttons[SEE_SALARY]);
                this->layout->addWidget(this->requests_buttons[PENDING_REQUESTS]);
                this->layout->addWidget(this->requests_buttons[VACATION_MANAGER]);
                this->layout->addWidget(this->requests_buttons[SEE_VACATIONS]);
                this->layout->addWidget(this->requests_buttons[SEE_RECORD]);
                this->requests_buttons[EMPLOYEE_SEP]->show();
                this->requests_buttons[WORK_PAGE]->show();
                this->requests_buttons[PAYMENT_PAGE]->show();
                this->requests_buttons[SALARY_PAGE]->show();
                this->requests_buttons[SEE_SALARY]->show();
                this->requests_buttons[PENDING_REQUESTS]->show();
                this->requests_buttons[VACATION_MANAGER]->show();
                this->requests_buttons[SEE_VACATIONS]->show();
                this->requests_buttons[SEE_RECORD]->show();
            } else {
                this->layout->removeWidget(this->requests_buttons[EMPLOYEE_SEP]);
                this->requests_buttons[EMPLOYEE_SEP]->hide();
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
                this->layout->removeWidget(this->requests_buttons[VACATION_MANAGER]);
                this->requests_buttons[VACATION_MANAGER]->hide();
                this->layout->removeWidget(this->requests_buttons[SEE_VACATIONS]);
                this->requests_buttons[SEE_VACATIONS]->hide();
                this->layout->removeWidget(this->requests_buttons[SEE_RECORD]);
                this->requests_buttons[SEE_RECORD]->hide();
            }
            if (((this->role & SUPERVISOR) == SUPERVISOR) || ((this->role & HUMAN_RESOURCES) == HUMAN_RESOURCES)) {
                this->layout->addWidget(this->requests_buttons[SUPERVISOR_SEP]);
                this->requests_buttons[SUPERVISOR_SEP]->show();
                this->layout->addWidget(this->requests_buttons[REQUEST_HANDLER]);
                this->requests_buttons[REQUEST_HANDLER]->show();
            } else {
                this->layout->removeWidget(this->requests_buttons[SUPERVISOR_SEP]);
                this->requests_buttons[SUPERVISOR_SEP]->hide();
                this->layout->removeWidget(this->requests_buttons[REQUEST_HANDLER]);
                this->requests_buttons[REQUEST_HANDLER]->hide();
            }
            if (((this->role & HUMAN_RESOURCES) == HUMAN_RESOURCES) || ((this->role & ADMIN_USER) == ADMIN_USER)) {
                this->layout->addWidget(this->requests_buttons[USER_SEP]);
                this->layout->addWidget(this->requests_buttons[USER_MANAGER]);
                this->layout->addWidget(this->requests_buttons[USER_MOD]);
                this->layout->addWidget(this->requests_buttons[CHANGE_TOKEN]);
                this->requests_buttons[USER_SEP]->show();
                this->requests_buttons[USER_MANAGER]->show();
                this->requests_buttons[USER_MOD]->show();
                this->requests_buttons[CHANGE_TOKEN]->show();
            } else {
                this->layout->removeWidget(this->requests_buttons[USER_SEP]);
                this->requests_buttons[USER_SEP]->hide();
                this->layout->removeWidget(this->requests_buttons[USER_MANAGER]);
                this->requests_buttons[USER_MANAGER]->hide();
                this->layout->removeWidget(this->requests_buttons[USER_MOD]);
                this->requests_buttons[USER_MOD]->hide();
                this->layout->removeWidget(this->requests_buttons[CHANGE_TOKEN]);
                this->requests_buttons[CHANGE_TOKEN]->hide();
            }
            if ((this->role & AUDITOR) == AUDITOR) {
                this->layout->addWidget(this->requests_buttons[AUDITOR_SEP]);
                this->requests_buttons[AUDITOR_SEP]->show();
                this->layout->addWidget(this->requests_buttons[AUDITOR_PAGE]);
                this->requests_buttons[AUDITOR_PAGE]->show();
            } else {
                this->layout->removeWidget(this->requests_buttons[AUDITOR_SEP]);
                this->requests_buttons[AUDITOR_SEP]->hide();
                this->layout->addWidget(this->requests_buttons[AUDITOR_PAGE]);
                this->requests_buttons[AUDITOR_PAGE]->hide();
            }
            if ((this->role & ADMIN_CONFIG) == ADMIN_CONFIG) {
                this->layout->addWidget(this->requests_buttons[SYS_SEP]);
                this->requests_buttons[SYS_SEP]->show();
                this->layout->addWidget(this->requests_buttons[SYS_PAGE]);
                this->requests_buttons[SYS_PAGE]->show();
            } else {
                this->layout->removeWidget(this->requests_buttons[SYS_SEP]);
                this->requests_buttons[SYS_SEP]->hide();
                this->layout->addWidget(this->requests_buttons[SYS_PAGE]);
                this->requests_buttons[SYS_PAGE]->hide();
            }
        }
    }
}

/**
 * @brief asks client for user's role
 * @return role
 */
char initial::ask_for_role(int & correct) {
    char result = '0';
    std::string to_send = "";
    to_send += (char(GET_ROLES));
    to_send += this->users_login->user;
    to_send += ",";
    std::string from_server = "";
    from_server += this->local_client->send_and_receive(to_send);
    correct = (int)(from_server[0]-48);
    result = from_server[1];
    return result;
}


/**
 * @brief Destroy the initial::initial object
 * 
 */
initial::~initial() {
    if (this->ui) {
       delete this->ui;
        this->ui = 0;
    }
    if (this->work_page) {
        delete this->work_page;
        this->work_page = 0;
    }
    if (this->payment_page) {
        delete this->payment_page;
        this->payment_page = 0;
    }
    if (this->salary_page) {
        delete this->salary_page;
        this->salary_page = 0;
    }
    if (this->see_salary) {
        delete this->see_salary;
        this->see_salary = 0;
    }
    if (this->pending_requests) {
        delete this->pending_requests;
        this->pending_requests = 0;
    }
    if (this->see_record) {
        delete this->see_record;
        this->see_record = 0;
    }
    if (this->request_handler) {
        delete this->request_handler;
        this->request_handler = 0;
    }
    if (this->user_manager) {
        delete this->user_manager;
        this->user_manager = 0;
    }
    if (this->vacation_manager) {
        delete this->vacation_manager;
        this->vacation_manager = 0;
    }
    if (this->see_vacations) {
        delete this->see_vacations;
        this->see_vacations = 0;
    }
    if (this->user_mod) {
        delete this->user_mod;
        this->user_mod = 0;
    }
    if (this->new_token) {
        delete this->new_token;
        this->new_token = 0;
    }
     if (this->update_buttons) {
        delete this->update_buttons;
        this->update_buttons = 0;
    }
     if (this->office_mod) {
        delete this->office_mod;
        this->office_mod = 0;
     }
     if (this->see_office) {
        delete this->see_office;
        this->see_office = 0;
     }
}

/**
 * @brief Opens windows when their button is clicked
 * 
 * @param id button id to know which window to open
 * @param type unused parameter
 */
void initial::create_windows(int id, int type) {
   (void) type;
   switch (id) {
    case WORK_PAGE:
      this->work_page->setModal(true);
      this->work_page->setUserData(this->users_login);
      this->work_page->show();
      break;
    case PAYMENT_PAGE:
      this->payment_page->setModal(true);
      this->payment_page->setUserData(this->users_login);
      this->payment_page->show();
      break;
    case SALARY_PAGE:
      this->salary_page->setModal(true);
      this->salary_page->setUserData(this->users_login);
      this->salary_page->show();
      break;
    case SEE_SALARY:
      this->see_salary-> setUserData(this->users_login);
      this->see_salary->setModal(true);
      this->see_salary->show();
      break;
    case PENDING_REQUESTS:
      this->pending_requests->setModal(true);
      this->pending_requests->set_user_login(this->users_login);
      this->pending_requests->show();
      break;
    case VACATION_MANAGER:
      this->vacation_manager->setModal(true);
      this->vacation_manager->reset_window();
      this->vacation_manager->set_current_user(this->users_login->user);
      this->vacation_manager->show();
      break;
    case SEE_VACATIONS:
      this->see_vacations->setModal(true);
      this->see_vacations->set_user_login(this->users_login);
      this->see_vacations->show();
      break;
    case SEE_RECORD:
      this->see_record->setModal(true);
      this->see_record->set_user_login(this->users_login);
      this->see_record->show_record();
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
      this->user_mod->set_user_role(this->role);
      this->user_mod->add_data_to_combobox();
      this->user_mod->setModal(true);
      this->user_mod->show();
      break;
    case CHANGE_TOKEN:
      this->new_token->set_login_info(this->users_login);
      this->new_token->setModal(true);
      this->new_token->show();
      break;
    case OFFICE_MOD:
      this->office_mod->set_user_login(this->users_login);
      this->office_mod->setModal(true);
      this->office_mod->show();
      break;
    case SEE_OFFICE:
      this->see_office->load_data();
      this->see_office->set_user_name(this->users_login->user);
      this->see_office->setModal(true);
      this->see_office->show();
      break;
    case AUDITOR_PAGE:
      this->auditor_page->setModal(true);
      this->auditor_page->show();
      break;
    case SYS_PAGE:
      this->sys_config_page->setModal(true);
      this->sys_config_page->set_user_login(this->users_login);
      this->sys_config_page->show();
      break;
   }
}



/**
 * @brief Sends logout signal and closes initial window
 * 
 */
void initial::on_pushButton_clicked() {
    emit this->parent_button->pressed();
    this->role = 0;
    // Hide initial window
    this->hide();
    this->parent_button->valid = false;
}

