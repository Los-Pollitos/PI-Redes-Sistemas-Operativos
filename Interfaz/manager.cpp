#include "manager.h"
#include "ui_manager.h"
#include "handle_requests.h"
#include "modify_user.h"

manager::manager(QWidget *parent) : QDialog(parent), ui(new Ui::manager) {
    ui->setupUi(this);
}

manager::~manager()
{
    delete ui;
}

void manager::on_employee_information_2_clicked() {
    this->request_handler = new handle_requests();
    this->hide();
    this->request_handler->setModal(true);
    this->request_handler->show();
}


void manager::on_employee_information_clicked() {
    this->modify_info = new modify_user();
    this->modify_info->set_login_info(this->user_data);
    this->hide();
    this->modify_info->setModal(true);
    this->modify_info->show();
}

void manager::set_login_info(login_info* info) {
    this->user_data = info;
}
