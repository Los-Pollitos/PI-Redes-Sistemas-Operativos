#include "modify_office.h"
#include "ui_modify_office.h"

modify_office::modify_office(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_office)
{
    ui->setupUi(this);
}

modify_office::~modify_office()
{
    delete ui;
}
