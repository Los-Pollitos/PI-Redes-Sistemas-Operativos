#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inicial.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ingresar_clicked()
{
    QString username = ui->usuario->text();
    QString password = ui->contrasena->text();

    if (username == "angie" && password == "123") {
        hide();
        inicial wRRHHyGerente;
        wRRHHyGerente.setModal(true);
        wRRHHyGerente.exec();
    } else {
        QMessageBox::warning(this, "Ingreso", "Contraseña incorrecta");
    }
}

