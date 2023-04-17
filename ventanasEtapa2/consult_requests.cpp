#include "consult_requests.h"
#include "ui_consult_requests.h"

consult_requests::consult_requests(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::consult_requests)
{
    ui->setupUi(this);
}

consult_requests::~consult_requests()
{
    delete ui;
}
