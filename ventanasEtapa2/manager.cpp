#include "manager.h"
#include "ui_manager.h"

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
