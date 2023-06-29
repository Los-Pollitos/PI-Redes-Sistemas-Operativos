#include "auditor.h"
#include "ui_auditor.h"
#include <fstream>
#include <string>
#include <iostream>
#include <QProcess>
#include <QMessageBox>

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
    this->ui->plainTextEdit->clear();
    system("cp ../../intermediary_LOG.txt ../temp.txt");
    std::ifstream  log_file ("../temp.txt");
    if (log_file.is_open()) {
        std::string text = "";
        while (log_file.is_open() && !log_file.eof()) {
            std::getline(log_file, text);
            text += "\n";
            this->ui->plainTextEdit->appendPlainText(QString::fromStdString(text));
            text ="";
        }

        log_file.close();
        system("rm ../temp.txt");
    } else {
        QMessageBox show_error =  QMessageBox();
        show_error.setWindowTitle("Error");
        show_error.setModal(true);
        show_error.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_error.setText("Hubo un error al intentar leer el archivo, por favor intente más tarde o contacte al encargado");
        show_error.exec();
    }
}


void auditor::on_search_button_clicked() {
    this->ui->plainTextEdit->clear();
    std::string to_find = this->ui->find_text->text().toStdString();
    system("cp ../../intermediary_LOG.txt ../../temp.txt");
    if (to_find != "") {
        std::string grep_command = "grep \"";
        grep_command += to_find;
        grep_command += "\" ../../temp.txt > ../temp_file.txt";
        if (system(grep_command.data()) == 0) {
            std::ifstream  temp_file ("../temp_file.txt");
            std::string text = "";
            while (temp_file.is_open() && !temp_file.eof()) {
                std::getline(temp_file, text);
                text += "\n";
                this->ui->plainTextEdit->appendPlainText(QString::fromStdString(text));
                text ="";
            }
            temp_file.close();
            std::string delete_command = "rm ../temp_file.txt";
            system(delete_command.data());
            system("rm ../../temp.txt");
        } else {
            QMessageBox show_error =  QMessageBox();
            show_error.setWindowTitle("Error");
            show_error.setModal(true);
            show_error.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
            show_error.setText("Hubo un error al intentar procesar el archivo, por favor intente más tarde o contacte al encargado");
            show_error.exec();
        }
    } else {
        QMessageBox show_message =  QMessageBox();
        show_message.setWindowTitle("Error");
        show_message.setModal(true);
        show_message.setStyleSheet("color: #001f21;background-color: #ECEAE5;");
        show_message.setText("Favor indicar el texto a buscar en la sección de buscar");
        show_message.exec();
    }
}

