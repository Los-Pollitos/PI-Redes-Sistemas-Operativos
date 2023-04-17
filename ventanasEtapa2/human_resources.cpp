#include "human_resources.h"
#include "ui_human_resources.h"

human_resources::human_resources(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::human_resources)
{
    ui->setupUi(this);
}

human_resources::~human_resources()
{
    delete ui;
}
