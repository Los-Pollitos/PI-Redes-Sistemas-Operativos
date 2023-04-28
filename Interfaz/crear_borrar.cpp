#include "crear_borrar.h"
#include "ui_crear_borrar.h"

crear_borrar::crear_borrar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crear_borrar)
{
    ui->setupUi(this);
}

crear_borrar::~crear_borrar()
{
    delete ui;
}
