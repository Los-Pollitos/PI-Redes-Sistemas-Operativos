#include "auditor.h"
#include "ui_auditor.h"

auditor::auditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auditor) {
    ui->setupUi(this);
}

auditor::~auditor() {
    delete ui;
}
