#include "change_password.h"
#include "ui_change_password.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <QMessageBox>

change_password::change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
    this->setWindowTitle("Cambiar contraseña");
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password); // no muestra password
    this->ui->lineEdit_3->setEchoMode(QLineEdit::Password); // no muestra token
    this->ui->lineEdit_4->setEchoMode(QLineEdit::Password); // no muestra confirmacion
    this->pos = (int)(rand()%6);
    int columna = pos%3 +1;
    int fila = pos/3+1;
    this->ui->indicacion_label->setText("Fila: " + QString::number(fila) + " Columna: " + QString::number(columna));
}

change_password::~change_password()
{
    if (this->ui) {
        delete ui;
        this->ui = 0;
    }
}

bool change_password::change_data(QString username, QString password) {
    bool success = false;
    try {
        std::ifstream file("../Etapa2/Archivos/Login.txt");
        std::string read_data = "";
        std::string buffer = "";
        if (file.is_open()) {
            while (file) {
                file >> read_data;
                if (read_data != username.toStdString()) {
                    buffer += read_data;
                    file >> read_data;
                    buffer += "\t" + read_data;
                    for (int i = 0; i < TOKEN_SIZE; ++i) {
                        file >> read_data;
                        if (i == 0) {
                            buffer += "\t" + read_data;
                        } else {
                            buffer += " " + read_data;
                        }
                    }
                    read_data = "";
                } else {
                    std::cout << read_data << std::endl;
                    buffer += read_data;
                    file >> read_data;
                    buffer += "\t" + password.toStdString();
                    for (int i = 0; i < TOKEN_SIZE; ++i) {
                        file >> read_data;
                        this->token[i] = std::stoi(read_data);
                        if (i == 0) {
                            buffer += "\t" + read_data;
                        } else {
                            buffer += " " + read_data;
                        }
                        std::cout << read_data << std::endl;
                    }
                    read_data = "";
                    if (std::stoi(this->ui->lineEdit_3->text().toStdString()) == this->token[pos])
                        success = true;
                }
                buffer += "\n";
            }
            file.close();

            std::ofstream ofs("../Etapa2/Archivos/Login.txt");

            if (!ofs.is_open())
            {
                std::cerr << "Error cambiando contraseña" << std::endl;
            }
            ofs << buffer;
            ofs.close();
        } else {
            std::cerr << "Archivo de login no encontrado" << std::endl;
        }
    } catch (const std::runtime_error& exception) {
        std::cerr << exception.what() << std::endl;
    }
    return success;
}



void change_password::on_pushButton_reinicarContra_clicked()
{
    if (this->ui->lineEdit->text() == "" || this->ui->lineEdit_2->text() == "" ||
            this->ui->lineEdit_3->text() == "" || this->ui->lineEdit_4->text() == ""){
        QMessageBox::warning(this, "Error", "Datos incompletos");

    } else if(this->ui->lineEdit_2->text() != this->ui->lineEdit_4->text()) {
        QMessageBox::warning(this, "Error", "Las contraseñas no son iguales");

    } else {
        if (this->change_data(this->ui->lineEdit->text(), this->ui->lineEdit_2->text())) {
            this->hide();
        } else {
            QMessageBox::warning(this, "Error", "Datos incorrectos");
            this->ui->lineEdit->setText("");
            this->ui->lineEdit_2->setText("");
            this->ui->lineEdit_3->setText("");
            this->ui->lineEdit_4->setText("");
        }
    }
}

