#include "initial.h"
#include "ui_initial.h"

initial::initial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initial) {
    ui->setupUi(this);
    ui->funciones_especiales->hide();
    this->hhrr = new human_resources();
    this->office_manager = new manager();
    this->workP = new work_proof();
    this->salaryP = new salary_proof();
    this->paymentP = new payment_proof();
    this->pending_requests = new consult_requests();
}

initial::~initial() {
    delete ui;
    if (this->hhrr) {
        delete this->hhrr;
    }
    if (this->office_manager) {
        delete this->office_manager;
    }
    delete this -> workP;
    delete this->salaryP;
    delete this->paymentP;
    delete this->pending_requests;
}

void initial::setUserData(login_info * user_data) {
    this->user_data = user_data;
    if (this->user_data->user[0] == 'e') {
        this->type_employee = EMPLEADO;
    } else if (this->user_data->user[0] == 'r') {
        this->type_employee = RECURSOS_HUMANOS;
        ui->funciones_especiales->show();
    } else {
        this->type_employee = GERENTE;
        ui->funciones_especiales->show();
    }
}

void initial::on_funciones_especiales_clicked() {
    if (this->type_employee == RECURSOS_HUMANOS) {  // TODO(nosotros): completar con permisos de usuario
        this->hhrr->set_user_data(this->user_data);
        this->hhrr->setModal(true);
        this->hhrr->show();
    } else {
        this->office_manager->set_login_info(this->user_data);
        this->office_manager->setModal(true);
        this->office_manager->show();
    }
}


void initial::on_pushButton_8_clicked()
{
    this->workP->setModal(true);
    this->workP->show();
}


void initial::on_pushButton_4_clicked()
{
    this->salaryP->setModal(true);
    this->salaryP->show();
}


void initial::on_pushButton_2_clicked()
{
    this->paymentP->setModal(true);
    this->paymentP->show();
}


void initial::on_pushButton_7_clicked() {
    this->pending_requests->setModal(true);
    this->pending_requests->set_user_data(this->user_data);
    this->pending_requests->show();
}

