#include "inicial.h"
#include "ui_inicial.h"

inicial::inicial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inicial)
{
    ui->setupUi(this);
}

inicial::~inicial()
{
    delete ui;
}
