#include "human_resources.h"
#include "ui_human_resources.h"
#include "handle_requests.h"

human_resources::human_resources(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::human_resources) {
    ui->setupUi(this);
    this->request_handler = new handle_requests();
    this->user_manager = new manage_user();
}

human_resources::~human_resources() {
    delete this->ui;
    delete this->request_handler;
    delete this->user_manager;
}


void human_resources::set_user_data(login_info * user_data) {
    this->user_data = user_data;
}

void human_resources::on_process_button_clicked() {
    this->request_handler->set_user_data(this->user_data);
    this->hide();
    this->request_handler->setModal(true);
    this->request_handler->show();
}


void human_resources::on_manage_user_button_clicked() {
    this->user_manager->set_user_data(this->user_data);
    this->hide();
    this->user_manager->setModal(true);
    this->user_manager->show();
}

