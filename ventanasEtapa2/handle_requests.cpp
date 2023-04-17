#include "handle_requests.h"
#include "ui_handle_requests.h"

handle_requests::handle_requests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::handle_requests)
{
    ui->setupUi(this);
}

handle_requests::~handle_requests()
{
    delete ui;
}
