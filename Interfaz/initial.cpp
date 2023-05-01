#include "initial.h"
#include "ui_initial.h"

initial::initial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initial) {
    ui->setupUi(this);
    if (false) { // TODO(nosotros): completar con permisos de usuario
        ui->funciones_especiales->hide();
    }
}

initial::~initial() {
    delete ui;
    if (this->hhrr) {
        delete this->hhrr;
    }
    if (this->office_manager) {
        delete this->office_manager;
    }
}

void initial::on_funciones_especiales_clicked() {
    if (true) {  // TODO(nosotros): completar con permisos de usuario
        this->hhrr = new human_resources();
        this->hhrr->setModal(true);
        this->hhrr->show();
    } else {
        this->office_manager = new manager();
        this->office_manager->setModal(true);
        this->office_manager->show();
    }
}


void initial::on_pushButton_8_clicked()
{
    this->workP = new work_proof();
    this->workP->setModal(true);
    this->workP->show();
}


void initial::on_pushButton_4_clicked()
{
    this->salaryP = new salary_proof();
    this->salaryP->setModal(true);
    this->salaryP->show();
}


void initial::on_pushButton_2_clicked()
{
    this->paymentP = new payment_proof();
    this->paymentP->setModal(true);
    this->paymentP->show();
}

