#include "auditor.h"
#include "ui_auditor.h"
#include <fstream>
#include <string>
#include <iostream>

auditor::auditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::auditor) {
    ui->setupUi(this);
    this->ui->plainTextEdit->setReadOnly(true);
    this->setStyleSheet("background-color: #ECEAE5;");
    this->setWindowTitle("Consutlar archivo de registro del sistema");
    this->ui->plainTextEdit->setStyleSheet("color: #001f21;");
    this->ui->label->setStyleSheet("color: #001f21;");
    this->ui->find_text->setStyleSheet("color: #001f21;");
    this->ui->refresh_button->setStyleSheet("color: #001f21;");
     this->ui->search_button->setStyleSheet("color: #001f21;");
}

auditor::~auditor() {
    delete ui;
}

void auditor::on_refresh_button_clicked(){
    // Load all from file
    this->ui->find_text->setText("");
    std::ifstream  log_file ("../../intermediary_LOG.txt");
    std::string text = "";
    while (log_file.is_open() && !log_file.eof()) {
        std::getline(log_file, text);
        text += "\n";
        this->ui->plainTextEdit->appendPlainText(QString::fromStdString(text));
        text ="";
    }

    log_file.close();

}


void auditor::on_search_button_clicked() {

}

