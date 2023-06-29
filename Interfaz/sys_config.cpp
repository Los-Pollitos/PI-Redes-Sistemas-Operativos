#include "sys_config.h"
#include "ui_sys_config.h"

sys_config::sys_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sys_config) {
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->setWindowTitle("Modificar configuración del sistema");
}

sys_config::~sys_config() {
    delete ui;
}

void sys_config::on_pushButton_clicked() {

}

