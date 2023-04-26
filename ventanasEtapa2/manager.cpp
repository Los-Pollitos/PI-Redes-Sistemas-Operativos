#include "manager.h"
#include "ui_manager.h"
#include "handle_requests.h"

manager::manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager)
{
    ui->setupUi(this);
}

manager::~manager()
{
    delete ui;
}

void manager::on_employee_information_2_clicked()
{
    this->request_handler = new handle_requests();
    this->hide();
    this->request_handler->setModal(true);
    this->request_handler->show();
}

