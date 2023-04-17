#include "initial.h"
#include "ui_initial.h"

initial::initial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initial) {
    ui->setupUi(this);
    if (false) { // TODO(nosotros): completar con permisos de usuario
        ui->funciones_especiales->hide();
    }
}

initial::~initial() {
    delete ui;
}
