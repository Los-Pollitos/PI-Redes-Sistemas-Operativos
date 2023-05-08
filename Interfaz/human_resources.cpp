#include "human_resources.h"
#include "ui_human_resources.h"
#include "handle_requests.h"

human_resources::human_resources(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::human_resources)
{
    ui->setupUi(this);
}

human_resources::~human_resources()
{
    delete ui;
    delete request_handler;
}


void human_resources::set_user_data(login_info * user_data) {
    this->user_data = user_data;
}

void human_resources::on_process_button_clicked() {
    this->request_handler = new handle_requests();
    this->request_handler->set_user_data(this->user_data);
    this->hide();
    this->request_handler->setModal(true);
    this->request_handler->show();
}

