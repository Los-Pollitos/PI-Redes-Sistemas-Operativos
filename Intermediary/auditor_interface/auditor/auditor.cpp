#include "auditor.h"
#include "ui_auditor.h"
#include <fstream>

auditor::auditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auditor) {
    ui->setupUi(this);
}

auditor::~auditor() {
    delete ui;
}

void auditor::on_refresh_button_clicked(){
    // Load all from file
    this->ui->find_text->setText("");

}


void auditor::on_search_button_clicked() {

}

